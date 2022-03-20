#include "Adventure.h"

namespace Adventure {



const SObj* Program::FindRoom(const String& name) const {
	const auto& arr = rooms.GetArray();
	for (const auto& val : arr) {
		String room_str = val;
		//LOG(room_str);
		if (room_str == name)
			return FindDeep(name);
	}
	return 0;
}

SObj Program::GetInRoom(SObj o) {
	//LOG(o.ToString());
	if (o.IsMap()) {
		SObj in_room = o.MapGet("in_room");
		if (in_room.IsMap())
			return in_room;
		
		//LOG(in_room.ToString());
		/*String name = in_room;
		if (name.GetCount()) {
			const SObj* ptr = FindDeep(name);
			if (ptr) {
				ASSERT(ptr->IsMap());
				return *ptr;
			}
		}*/
	}
	return SObj();
}

// open one (or more) doors
void Program::OpenDoor(SObj door_obj1, SObj door_obj2) {
	StateType state1 = GetState(door_obj1);
	
	if (state1 == STATE_OPEN) {
		SayLine("it's already open");
	}
	else {
		SetState(door_obj1, STATE_OPEN);
		if (door_obj2)
			SetState(door_obj2, STATE_OPEN);
	}
}

// close one (or more) doors
void Program::CloseDoor(SObj door_obj1, SObj door_obj2) {
	StateType state1 = GetState(door_obj1);
	if (state1 == STATE_CLOSED) {
		SayLine("it's already closed");
	}
	else {
		SetState(door_obj1, STATE_CLOSED);
		if (door_obj2)
			SetState(door_obj2, STATE_CLOSED);
	}
}

void Program::ComeOutDoor(SObj from_door, SObj to_door, bool fade_effect) {
	// check param
	/*if (to_door == NULL) {
		ShowError("target door does not exist");
		return;
	}*/
	HiValue selected_actor = GetSelectedActor();
	
	StateType from_state = GetState(from_door);
	if (from_state != STATE_OPEN) {
		SayLine("the door is closed");
		return;
	}
	
	// go to new room!
	SObj new_room = GetInRoom(to_door);
	
	if (new_room != room_curr) {
		ChangeRoom(new_room, fade_effect); // switch to new room and ...
	    
		// ...auto-position actor at to_door in new room...
		Point pos = GetUsePoint(to_door);
		PutAt(selected_actor, pos.x, pos.y, new_room);
	}
	
	FaceDir to_dir = GetFaceDir(to_door);
	FaceDir opp_dir;
	
	if (to_dir) {
		//  ... in opposite use direction!
		opp_dir = (FaceDir)(((int)to_dir + 1) % 4 + 1);
		
		// opp_dir = to_dir + 2
		// if (opp_dir > 4 {
		// opp_dir -= 4
		// }
	}
	else {
		opp_dir = FACE_FRONT;
	}
	
	selected_actor.Set("face_dir", GetFaceString(opp_dir));
	
	// is target dir left? flip?
	selected_actor.Set("flip", GetFaceDir(selected_actor) == FACE_LEFT);
	
}

void Program::ChangeRoom(SObj new_room, SObj fade_) {
	if (!new_room.IsMap()) {
		DUMP(new_room);
		TODO
		/*
		String name = new_room;
		const SObj* ptr = FindDeep(name);
		if (!ptr) {
			LOG("Could not find room '" << name << "'");
			return;
		}
		new_room = *ptr;
		*/
	}
	ASSERT(new_room.IsMap());
	int fade = fade_.GetInt();
	
	// check param
	if (new_room.IsVoid()) {
		ShowError("room does not exist");
		return;
	}

	// stop any existing fade (shouldn't be any, but just in case!)
	if (fade_script) {
		StopScript(*fade_script);
		fade_script = 0;
	}

	// fade) {wn existing room (or skip if (first room)
	if (fade && room_curr) {
		Fades(fade, 1);
	}
	
	// switch to new room
	// execute the exit() script of old room
	if (room_curr) {
		StartScriptHi(&room_curr, "exit", 0, room_curr); // run script directly, so wait to finish
	}
	
	// stop all active (local) scripts
	ctx.RemoveProgramGroup(SCRIPT_LOCAL);
	
	// clear current command
	ClearCurrCmd();
	
	// actually change rooms now
	room_curr = new_room;
	
	// reset camera pos in new room (unless camera following)
	if (cam_following_actor.IsVoid() || GetInRoom(cam_following_actor) != room_curr)
		cam = Point(0,0);
	
	// stop everyone talking & remove displayed text
	StopTalking();
	
	// fade up again?
	// (use "thread" so that room.enter code is able to
	//  reposition camera before fade-up, if (needed)
	if (fade) {
		// setup new fade up
		StartScript(THISBACK2(Fades, fade, -1), true);
	}
	else {
		// no fade - reset any existing fade
		fade_iris = 0;
	}

	// execute the enter() script of new room
	if (room_curr) {
		StartScriptHi(&room_curr, "enter", 0, room_curr);
	}
	else {
		LOG("Program::ChangeRoom. error: room is not string");
	}
}

void Program::PutAt(SObj obj, int x, int y, SObj room) {
	//GetReference(obj, true);
	//GetReference(room, true);
	//LOG(obj.ToString());
	//LOG(room.ToString());
	ASSERT(obj.IsMap());
	ASSERT(room.IsMap());
	
	if (room.IsMap()) {
		if (!HasFlag(Classes(obj), "class_actor")) {
			SObj in_room = obj.MapGet("in_room");
			//if (in_room.IsArray())
			//	GetReference(in_room, true);
			ASSERT(in_room.IsMap() || in_room.IsVoid());
			if (in_room.IsMap()) {
				SObj objects = in_room.MapGet("objects");
				Vector<HiValue>& arr = (Vector<HiValue>&)objects.GetArray();
				VectorRemoveKey(arr, obj);
			}
			obj.Set("owner", HiValue());
			SObj objects = room.MapGet("objects");
			ASSERT(objects.IsArray());
			objects.ArrayAdd(obj);
		}
	}
	obj.Set("in_room", room);
	
	//LOG(obj.ToString());
	ASSERT(obj.IsMap());
	obj.Set("x", x);
	obj.Set("y", y);
}



}
