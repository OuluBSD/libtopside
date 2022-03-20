#include "Adventure.h"

namespace Adventure {



Point Program::GetUsePoint(SObj& obj) {
	UsePos obj_use_pos = GetUsePos(obj);
	
	Point pt = GetXY(obj);
	Size sz = GetSize(obj);
	Point off = GetOffset(obj);
	
	int y = pt.y;
	int x = pt.x;
	int w = sz.cx;
	int h = sz.cy;
	int offset_x = off.x;
	int offset_y = off.y;
	
	// first check for (specific pos
	TODO
	/*if (IsTable(obj_use_pos)) {
		x = obj_use_pos[1];
		y = obj_use_pos[2]; // -cam_x, -stage-top
	}
	// determine use pos
	else*/ {
		if (obj_use_pos == POS_LEFT && offset_x) {
			// diff calc for (actors
			x -= (w * 8 + 4);
			y += 1;
		}
		else {
			int xd = 0, yd = 0;
			switch (obj_use_pos) {
				case POS_LEFT:
					xd = -2;
					yd = h * 8 - 2;
					break;
				case POS_RIGHT:
					xd = w * 8;
					yd = h * 8 - 2;
					break;
				case POS_ABOVE:
					xd = w * 4 - 4;
					yd = -2;
					break;
				case POS_CENTER:
					xd = w * 4;
					yd = h * 4 - 4;
					break;
				case POS_INFRONT:
					xd = w * 4 - 4;
					yd = h * 8 + 2;
					break;
				default:
					break;
			}
			
			x += xd;
			y += yd;
		}
	}

	return Point(x,y);
}

void Program::DoAnim(SObj thing, const String& param1, int& param2) {
	//
	// scumm examples:
	// do-animation selected-actor stand
	// do-animation selected-actor get-up
	
	// do-animation bernard ring-bell
	//  break-here 4
	// do-animation bernard reach-low
	
	// do-animation hermit face-towards guybrush
	// do-animation max face-towards sam
	
	// face-towards?
	//   animate turn to face (object/actor || explicit direction)
	if (param1 == "face_towards") {
		TODO
		/*
		// check if param2 is an actor/object, rather than explicit face_dir
		if (IsTable(param2)) {
			// need to calculate face_dir from positions
			double angle_rad = atan2(thing.x  - param2.x , param2.y - thing.y);
			
			// calc player's angle offset in this
			double plr_angle = 93 * (3.1415 / 180);
			
			// adjust for (player's angle
			angle_rad = plr_angle - angle_rad;
			
			// convert radians to degrees
			// (note: everyone says should be: rad * (180/pi), but
			//        that only seems to give me degrees 0..57? so...)
			double degrees = (angle_rad * 360) % 360; //(1130.938/3.1415)
			
			// set final target face direction to obj/actor
			param2 = 4 - flr(degrees / 90);
			
			// convert final value
			param2 = face_dirs[param2];
		}
		
		int face_dir = face_dirs[thing.face_dir];
		//!!! param2 = face_dirs[param2];
		
		while (face_dir != param2) {
			// turn to target face_dir
			if (face_dir < param2) {
				face_dir += 1;
			}
			else {
				face_dir -= 1;
			}
			
			// set face dir
			thing.face_dir = face_dirs[face_dir];
			
			// is target dir left? flip?
			thing.flip = (thing.face_dir == "face_left");
			BreakTime(10);
		}*/
	}
	else {
		// must be an explicit animation (e.g. "idle")
		// so start it now
		thing.Set("curr_anim", param1);
		thing.Set("anim_pos", 1);
		thing.Set("tmr", 1);
	}
	
}


Point Program::GetXY(SObj o) {
	return Point(
		o("x").GetInt(),
		o("y").GetInt());
}

Point Program::GetOffset(SObj o) {
	return Point(
		o("offset_x").GetInt(),
		o("offset_y").GetInt());
}

Size Program::GetSize(SObj o) {
	return Size(
		o("w").GetInt(),
		o("h").GetInt());
}

Program::UsePos Program::GetUsePos(SObj o) {
	TODO
	/*
	UsePos obj_use_pos =
		obj.use_pos != POS_NULL
			? obj.use_pos
			: POS_INFRONT;
	*/
}

StateType Program::GetState(SObj o) {
	String s = o("state");
	if (s == "state_open")   return STATE_OPEN;
	if (s == "state_closed") return STATE_CLOSED;
	ASSERT(0);
	return STATE_CLOSED;
}

void Program::SetState(SObj o, StateType s) {
	if      (s == STATE_OPEN)	o.Set("state", "state_open");
	else if (s == STATE_CLOSED)	o.Set("state", "state_closed");
	else ASSERT(0);
}

FaceDir Program::GetFaceDir(SObj o) {
	String s = o("face_dir");
	ASSERT(s.GetCount());
	//String s = o.MapGet("state");
	if (s == "face_front")	return FACE_FRONT;
	if (s == "face_left")	return FACE_LEFT;
	if (s == "face_back")	return FACE_BACK;
	if (s == "face_right")	return FACE_RIGHT;
	return FACE_NULL;
}

String Program::GetFaceString(FaceDir d) {
	switch (d) {
		case FACE_FRONT:	return "face_front";
		case FACE_LEFT:		return "face_left";
		case FACE_BACK:		return "face_back";
		case FACE_RIGHT:	return "face_right";
		default: break;
	}
	return String();
}

void Program::SetSelectedActor(SObj o) {
	auto& global = ctx.global;
	global.GetAdd("selected_actor") = o;
}


}
