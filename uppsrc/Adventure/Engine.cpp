#include "Adventure.h"

namespace Adventure {





void Program::reset_ui() {
	verb_maincol = Color(28, 170, 255);
	verb_hovcol = Color(255, 255, 255);
	verb_shadcol = Color(28, 42, 150);
	verb_defcol = Color(226, 212, 0);
	
	TODO
}


void Program::startup_script() {
	reset_ui();
	
	change_room(rm_hall,  1);
}







void Program::shake(bool enabled) {
	cam_shake = enabled;
	cam_shake_amount = enabled ? 1 : cam_shake_amount;
}


Program::Verb Program::find_default_verb(Object& obj) {
	Verb default_verb = V_LOOKAT;

	if (has_flag(obj.classes, "class_talkable"))
		default_verb = V_TALKTO;
	else if (has_flag(obj.classes, "class_openable")) {
		if (obj.state == "state_closed")
			default_verb = V_OPEN;
		else
			default_verb = V_CLOSE;
	}

	// now find the full verb definition
	for (auto v : all(verbs)) {
		vi = get_verb(v);
		if (vi[2] == default_verb) { default_verb = v; break; }
	}
	
	return default_verb;
}

// actions to perform when object doesn't have an entry for (verb
void Program::unsupported_action(Verb verb, Object& obj1, Object& obj2) {
	bool is_actor = has_flag(obj1.classes, "class_actor");

	if (verb == V_WALKTO
		return;

	else if (verb == V_PICKUP)
		say_line(is_actor ? "i don't need them" : "i don't need that");

	else if (verb == V_USE)
		say_line(
			is_actor ? "i can't just *use* someone" :
				((obj2 ? has_flag(obj2.classes, class_actor)) ?
					"i can't use that on someone!" : "that doesn't work"));

	else if (verb == V_GIVE)
		say_line(is_actor ? "i don't think i should be giving this away" : "i can't do that");

	else if (verb == V_LOOKAT)
		say_line(is_actor ? "i think it's alive" : "looks pretty ordinary");

	else if (verb == V_OPEN || verb == V_CLOSE)
		say_line((is_actor ? "they don't" : "it doesn't")  + " seem to " + VerbStr(verb));

	else if (verb == V_PUSH || verb == V_PULL)
		say_line(is_actor ? "moving them would accomplish nothing" : "it won't budge!");

	else if (verb == "talkto")
		say_line(is_actor ? "erm ...  i don't think they want to talk" : "i am not talking to that!");

	else
		say_line("hmm. no.");
	
}



function camera_at(val) {
	// point center of camera at val, clear other cam values
	cam_x, cam_pan_to_x, cam_following_actor = _center_camera(val);
}

function camera_follow(actor) {
	stop_script(cam_script); // bg script

	// set target, clear other cam values
	cam_following_actor, cam_pan_to_x = actor;

	cam_script = function() {
		// keep the camera following actor
		// (until further notice)
		while (cam_following_actor) {
			// keep camera within "room" bounds
			if (cam_following_actor.in_room == room_curr) cam_x = _center_camera(cam_following_actor);
			yield();
		}
	};
	start_script(cam_script, true); // bg script

	// auto-switch to room actor resides in
	if (cam_following_actor.in_room != room_curr) change_room(cam_following_actor.in_room, 1);
}


function camera_pan_to(val) {
	// set target, but keep camera within "room" bounds, clear other cam values
	cam_pan_to_x, cam_following_actor = _center_camera(val);

	cam_script = function() {
		// update the camera pan until reaches dest
		while (cam_x ~= cam_pan_to_x) {
			cam_x += sgn(cam_pan_to_x-cam_x)/2
			// don't hog cpu
			yield()
		}
		// pan complete
		cam_pan_to_x = nil
	};
	start_script(cam_script, true); // bg script
}


function wait_for_camera() {
	while (script_running(cam_script)) {
		yield();
	}
}


function cutscene(type, func_cutscene, func_override) {
	cut = {
		flags = type,
		thread = cocreate(func_cutscene),
		override = func_override,
		paused_cam_following = cam_following_actor
	};
	
	add(cutscenes, cut);
	// set as active cutscene
	cutscene_curr = cut;

	// yield for (system catch-up
	// todo: see if (this is still needed!
	break_time();
}

function dialog_set(msg_table) {
	for (msg in all(msg_table)) {
		dialog_add(msg);
	}
}

function dialog_add(msg) {
	// check params
	dialog_curr = dialog_curr || { sentences = {} };
	// break msg into lines (if (necc.)
	lines = create_text_lines(msg, 32);
	// find longest line
	longest_line = longest_line_size(lines);
	sentence={
		num = #dialog_curr.sentences+1,
		msg = msg,
		lines = lines,
		char_width = longest_line
	};
	add(dialog_curr.sentences, sentence);
}

function dialog_start(col, hlcol) {
	dialog_curr.col = col;
	dialog_curr.hlcol = hlcol;
	dialog_curr.visible = true;
	selected_sentence = nil;
}

function dialog_hide() {
	dialog_curr.visible = false;
}

function dialog_clear() {
	dialog_curr.sentences = {};
	selected_sentence = nil;
}

function dialog_end() {
	dialog_curr=nil;
}

function get_use_pos(obj) {
	local obj_use_pos, y, x = obj.use_pos || "pos_infront", obj.y, obj.x; // -cam_x

	// first check for (specific pos
	if (istable(obj_use_pos)) {
		x, y = obj_use_pos[1], obj_use_pos[2]; // -cam_x, -stage-top
	}
	// determine use pos
	else {
		local use_pos_offsets = {
			pos_left = { -2, obj.h * 8 - 2 },
			pos_right = { obj.w * 8, obj.h * 8 - 2 },
			pos_above = { obj.w * 4 - 4, -2 },
			pos_center = { obj.w * 4, obj.h * 4 - 4 },
			pos_infront = { obj.w * 4 - 4, obj.h * 8 + 2 }
		};
		if (obj_use_pos == "pos_left" && obj.offset_x) {
		// diff calc for (actors
			x -= (obj.w*8 +4);
			y += 1;
		}
		else {
			x += use_pos_offsets[obj_use_pos][1];
			y += use_pos_offsets[obj_use_pos][2];
		}
	}

	return {x=x,y=y};
}

function _anim(thing, param1, param2) {
 //
 // scumm examples:
 // ) {-animation selected-actor stand
 // ) {-animation selected-actor get-up

 // ) {-animation bernard ring-bell
 //  break-here 4
 // ) {-animation bernard reach-low

 // ) {-animation hermit face-towards guybrush
 // ) {-animation max face-towards sam

 // face-towards?
	//   animate turn to face (object/actor || explicit direction)
	if (param1 == "face_towards") {
		// check if (param2 is an actor/object, rather than explicit face_dir
		if (istable(param2)) {
			// need to calculate face_dir from positions
			angle_rad = atan2(thing.x  - param2.x , param2.y - thing.y);
			// calc player's angle offset in this
			plr_angle = 93 * (3.1415/180);
			// adjust for (player's angle
			angle_rad = plr_angle - angle_rad;

			// convert radians to degrees
			// (note: everyone says should be: rad * (180/pi), but
			//        that only seems to give me degrees 0..57? so...)
			degrees = (angle_rad * 360) % 360; //(1130.938/3.1415)

			// set final target face direction to obj/actor
			param2 = 4 - flr(degrees/90);

			// convert final value
			param2 = face_dirs[param2];
		}

		face_dir = face_dirs[thing.face_dir];
		param2 = face_dirs[param2];

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
			break_time(10);
		}
	}

 else {
  // must be an explicit animation (e.g. "idle")
  // so start it now
  thing.curr_anim = param1;
  thing.anim_pos = 1;
  thing.tmr = 1;
	} //  if (param1 == "face_towards"

}

// open one (or more)) {ors
function open_door(door_obj1, door_obj2) {
	if (door_obj1.state == "state_open") {
		say_line = "it's already open";
	}
	else {
		door_obj1.state = "state_open";
		if ((door_obj2))
			door_obj2.state = "state_open";
	}
}

// close one (or more)) {ors
function close_door(door_obj1, door_obj2) {
	if (door_obj1.state == "state_closed" {
		say_line("it's already closed");
	}
	else {
		door_obj1.state = "state_closed";
		if ((door_obj2))
			door_obj2.state = "state_closed";
	}
}

function come_out_door(from_door, to_door, fade_effect) {
	// check param
	if (to_door == nil)
		show_error("target door does not exist") return;

	if ((from_door.state ~= "state_open") {
		say_line("the door is closed");
		return;
	}

	// go to new room!
	new_room = to_door.in_room;

	if ((new_room != room_curr)
		change_room(new_room, fade_effect); // switch to new room and ...

	// ...auto-position actor at to_door in new room...
	local pos = get_use_pos(to_door);
	put_at(selected_actor, pos.x, pos.y, new_room);

	if (to_door.use_dir) {
  //  ... in opposite use direction!
	 opp_dir = face_dirs[(face_dirs[to_door.use_dir]+1)%4+1];
		// opp_dir = to_door.use_dir + 2
		// if (opp_dir > 4 {
		// 	opp_dir -= 4
		// }
	}
	else {
	opp_dir = "face_front"; // front
	}
	selected_actor.face_dir = opp_dir;
	// is target dir left? flip?
	selected_actor.flip = (selected_actor.face_dir == "face_left");
}

door_funcs = {
	open = open_door,
	close = close_door,
	walkto = come_out_door
}

function fades(fade, int dir) {
	// dir: 1=down, -1=up
	local fade_amount = 25 - 25 * dir;

	while (true) {
		fade_amount += dir*2;

		if (fade_amount > 50 || fade_amount < 0) {
			return;
		}

		// iris) {wn/up
		if (fade == 1)
			fade_iris = min(fade_amount, 32);;

		yield();
	}
}

function change_room(new_room, fade) {
	// check param
	if (!new_room) {show_error("room does not exist") return; }

	// stop any existing fade (shouldn't be any, but just in case!)
	stop_script(fade_script);

	// fade) {wn existing room (or skip if (first room)
	if (fade && room_curr) {
		fades(fade, 1);
	}
	// switch to new room
	// execute the exit() script of old room
	if (room_curr && room_curr.exit) room_curr.exit(room_curr); // run script directly, so wait to finish

	// stop all active (local) scripts
	local_scripts = {};

	// clear current command
	clear_curr_cmd();

	// actually change rooms now
	room_curr = new_room;

	// reset camera pos in new room (unless camera following)
	if (!cam_following_actor || cam_following_actor.in_room != room_curr) cam_x = 0;

	// stop everyone talking & remove displayed text
	stop_talking();

	// fade up again?
	// (use "thread" so that room.enter code is able to
	//  reposition camera before fade-up, if (needed)
	if (fade) {
		// setup new fade up
		fade_script = function() {
				fades(fade, -1);
		}
		start_script(fade_script, true);
	}
	else {
		// no fade - reset any existing fade
		fade_iris = 0;
	}

	// execute the enter() script of new room
	if (room_curr.enter) {
		// run script directly
		room_curr.enter(room_curr);
	}
}

function valid_verb(verb, object) {
 // check params
	if ((!object || !object.verbs)
		return false;
	// look for (verb
	if (istable(verb)) {
		if (object.verbs[verb[1]]) return true;
	}
	else {
		if (object.verbs[verb]) return true;
	}
	// must not be valid if (reached here
	// return false
}

function pickup_obj(obj, actor) {
	// use actor spectified, || default to selected
    actor = actor || selected_actor;

	add(actor.inventory, obj);
	obj.owner = actor;
	// remove it from room
	del(obj.in_room.objects, obj);
}


function start_script(func, bg, noun1, noun2) {
	// create new thread for (script and add to list of local_scripts (or background scripts)
	local thread = cocreate(func);
	
	// background || local?
	add(bg ? global_scripts : local_scripts, {func, thread, noun1, noun2} );
}


function script_running(func)  {
	// loop through both sets of scripts...
	for (s in all( { local_scripts, global_scripts } )) {
		for (k,scr_obj in pairs(s)) {
			if (scr_obj[1] == func) {
				return scr_obj;
			}
		}
	}
	// must not be running
	// return false
}

function stop_script(func) {
	// find script and stop it running
	scr_obj = script_running(func) {
		// just delete from all scripts (don't bother checking!)
		del(local_scripts, scr_obj);
		del(global_scripts, scr_obj);
	}
}

function break_time(jiffies) {
	// wait for (cycles specified (min 1 cycle)
	for (x = 1, jiffies || 1) {
		yield();
	}
}

function wait_for_message() {
	while (talking_curr) {
		yield();
	}
}

// uses actor's position and color
function say_line(actor, msg, use_caps, duration) {
	// check for (missing actor
	if (type(actor) == "string") {
		// assume actor ommitted and default to current
		msg, actor = actor, selected_actor;
	}

	// trigger actor's talk anim
	talking_actor = actor;
	
	// offset to display speech above actors (dist in px from their feet)
	// call the base print_line to show actor line
	print_line(msg, actor.x, actor.y - actor.h * 8 + 4, actor.col, 1, use_caps, duration);
}

// stop everyone talking & remove displayed text
function stop_talking() {
	talking_curr, talking_actor = nil;
}


function print_line(msg, x, y, col, align, use_caps, duration, big_font) {
  // punctuation...
	//  > ":" new line, shown after text prior expires
	//  > ";" new line, shown immediately
	// note: an actor's talk animation is not activated as it is with say-line.

	col = col || 7;   // default to white
	align = align || 0; // default to no align

	// calc max line width based on x-pos/available space
	local screen_space = 127 - (x - cam_x);
	if (align == 1)
		screen_space = min(x -cam_x, screen_space);
	local max_line_length = max(flr(screen_space/2), 16);

	// search for (";"'s
	local msg_left = "";
	for (i = 1, #msg) {
		local curchar=sub(msg,i,i);
		if (curchar == ":") {
			// show msg up to this point
			// and process the rest as new message

			// next message?
			msg_left = sub(msg, i+1);
			// redefine curr msg
			msg = sub(msg, 1, i-1);
			break;
		}
	}

	local lines = create_text_lines(msg, max_line_length);

	// find longest line
	local longest_line = longest_line_size(lines);

	// center-align text block
	xpos = x -cam_x;
	if ((align == 1) xpos -= longest_line * (big_font ? 4 : 2);

	// screen bound check
	local xpos, ypos = max(2, xpos), max(18, y); // left, top
	xpos = min(xpos, 127 - (longest_line*4)-1); // right

	talking_curr = {
		msg_lines = lines,
		x = xpos,
		y = ypos,
		col = col,
		align = align,
		time_left = duration || #msg * 8,
		char_width = longest_line,
		use_caps = use_caps,
		big_font = big_font
	};
	 // ref point for (skip #####################??????
	//talking_curr.time_orig=talking_curr.time_left


	// if (message was split...
	if (#msg_left > 0) {
	  talking = talking_actor
		wait_for_message()
		talking_actor = talking
		print_line(msg_left, x, y, col, align, use_caps, nil, big_font)
	}

	// and wait for (message?
	//if (!dont_wait_msg) {
		wait_for_message();
	//}
}

function put_at(obj, x, y, room) {
	if (room) {
		if (!has_flag(obj.classes, "class_actor")) {
			if (obj.in_room) del(obj.in_room.objects, obj);
			add(room.objects, obj);
			obj.owner = nil;
		}
		obj.in_room = room;
	}
	obj.x, obj.y = x, y;
}


function stop_actor(actor) {
 // 0=stopped, 1=walking, 2=arrived
	actor.moving, actor.curr_anim = 0;
 // no need to) {_anim(idle) here, as actor_draw code handles this
	clear_curr_cmd();
}

// walk actor to position
function walk_to(actor, x, y) {
	local actor_cell_pos = getcellpos(actor);
	local celx, cely = flr(x /8) + room_curr.map[1], flr(y /8) + room_curr.map[2];
	local target_cell_pos = { celx, cely };
	
	// use pathfinding!
	local path = find_path(actor_cell_pos, target_cell_pos, {x,y});
	
	actor.moving = 1;

 	 for (c=1,#path) {
			local p = path[c];
   // auto-adjust walk-speed for (depth
   local scaled_speed = actor.walk_speed * (actor.scale || actor.auto_scale);
   //local y_speed = actor.walk_speed/2 // removed, messes up the a* pathfinding

			local px, py = (p[1] - room_curr.map[1]) * 8 + 4, (p[2] - room_curr.map[2]) * 8 + 4;

    // last cell (walk to precise location, if (clicked in it)
		if (c == #path && x >= px-4 && x <= px+4 && y >= py-4 && y <= py+4) px, py = x, y;

			local distance = sqrt((px - actor.x) ^ 2 + (py - actor.y) ^ 2);
			local step_x = scaled_speed * (px - actor.x) / distance;
			local step_y = scaled_speed * (py - actor.y) / distance;

			// only walk if (we're not already there!
		if (distance > 0) {

    //walking

			for (i = 0, distance/scaled_speed-1) {

     // todo: need to somehow recalc here, else walk too fast/slow in depth planes

     // abort if (actor stopped
     if (actor.moving == 0) {
      return
     }

					actor.flip = step_x < 0;

     // choose walk anim based on dir
     //if (abs(step_x) < abs(step_y) {
     if (abs(step_x) < scaled_speed/2) {
						// vertical walk
						actor.curr_anim = step_y > 0 ? actor.walk_anim_front : actor.walk_anim_back;
						actor.face_dir = step_y > 0 ? "face_front" : "face_back";
     }
     else {
      // horizontal walk
      actor.curr_anim = actor.walk_anim_side;
      // face dir (at end of walk)
						actor.face_dir = actor.flip ? "face_left" : "face_right";
     }

     // actually move actor
					actor.x += step_x;
					actor.y += step_y;
					yield();

			}

		}
	}
	actor.moving, actor.curr_anim = 2; //arrived
}

function wait_for_actor(actor) {
	actor = actor || selected_actor;
	// wait for (actor to stop moving/turning
	while (actor.moving != 2) {
		yield();
	}
}

function proximity(obj1, obj2) {
	// calc dist between objects, || big value for (different room
	return obj1.in_room == obj2.in_room ? sqrt((obj1.x - obj2.x) ^ 2 + (obj1.y - obj2.y) ^ 2) : 1000;
}



// internal functions


// global vars
stage_top = 16;
cam_x, cam_shake_amount = 0, 0;
cursor_x, cursor_y, cursor_tmr, cursor_colpos = 63.5, 63.5, 0, 1;

ui_arrows = {
	{ spr = ui_uparrowspr, x = 75, y = stage_top + 60 },
	{ spr = ui_dnarrowspr, x = 75, y = stage_top + 72 }
};

face_dirs = {
	"face_front",
	"face_left",
	"face_back",
	"face_right",
	face_front=1,
	face_left=2,
	face_back=3,
	face_right=4
};

function get_keys(obj) {
	local keys = {};
	for (k,v in pairs(obj)) {
		add(keys,k);
	}
	return keys;
}

function get_verb(obj) {
	local verb, keys = {}, get_keys(obj[1]);
	add(verb, keys[1]);						// verb func
	add(verb, obj[1][ keys[1] ]);  // verb ref name
	add(verb, obj.text);						// verb disp name
	return verb;
}

function clear_curr_cmd() {
	// reset all command values
	verb_curr, executing_cmd, cmd_curr, noun1_curr, noun2_curr, me = get_verb(verb_default), false, ""
}



function _update60() {
	// process selected_actor threads/actions
	if (selected_actor && selected_actor.thread && !coresume(selected_actor.thread)) {
		selected_actor.thread = nil;
	}

	// global scripts (always updated - regardless of cutscene)
	update_scripts(global_scripts);

	// update active cutscene (if (any)
	if (cutscene_curr) {
		if (cutscene_curr.thread && !coresume(cutscene_curr.thread)) {
			// cutscene ended, restore prev state

			// restore follow-cam if (flag allows (and had a value!)
			if (cutscene_curr.flags != 3
			//if (!has_flag(cutscene_curr.flags, "cut_no_follow")
			 && cutscene_curr.paused_cam_following)
			{
				camera_follow(cutscene_curr.paused_cam_following);
					// assume to re-select prev actor
				selected_actor = cutscene_curr.paused_cam_following;
			}
			// now delete cutscene
			del(cutscenes, cutscene_curr);

			// any more cutscenes?
			if (#cutscenes > 0) {
				cutscene_curr = cutscenes[#cutscenes];
			}
			else {
				// start countdown (delay to ensure cutscenes/dialogs all over!)
				if (cutscene_curr.flags != 2) cutscene_cooloff = 3;
				
				cutscene_curr = nil;
			}
		}
	}
	else {
		// no cutscene...
		// update all the active scripts
		// (will auto-remove those that have ended)

		// local/room-level scripts
		update_scripts(local_scripts);
	}

	// player/ui control
	playercontrol();

	// check for (collisions
	check_collisions();

	// update camera shake (if (active)
	cam_shake_x, cam_shake_y = 1.5-rnd(3), 1.5-rnd(3);
	cam_shake_x = flr(cam_shake_x * cam_shake_amount);
  cam_shake_y = flr(cam_shake_y * cam_shake_amount);
	if (!cam_shake) cam_shake_amount = cam_shake_amount > 0.05 ? cam_shake_amount * 0.90 : 0;
}


function _draw() {
	// clear screen every frame
	cls();

	// reposition camera (account for (shake, if (active)
	camera(cam_x+cam_shake_x, 0+cam_shake_y);

	// clip room bounds (also used for ("iris" transition)
	clip(
		0 +fade_iris -cam_shake_x,
		stage_top +fade_iris -cam_shake_y,
		128 -fade_iris*2 -cam_shake_x,
		64 -fade_iris*2);

	// draw room (bg + objects + actors)
	room_draw();

	// reset camera and clip bounds for ("static" content (ui, etc.)
	camera(0,0);
	clip();

	if (show_debuginfo) {
		print("cpu: "..flr(100*stat(1)).."%", 0, stage_top - 16, 8);
		print("mem: "..flr(stat(0)/1024*100).."%", 0, stage_top - 8, 8);
		print("x: "..flr(cursor_x+cam_x).." y:"..cursor_y-stage_top, 80, stage_top - 8, 8);
	}
 // if (show_depth {
 //  fillp(0b0011001111001100.1)
 //  line(0,room_curr.autodepth_pos[1]+stage_top,128,room_curr.autodepth_pos[1]+stage_top,1)
 //  print(room_curr.autodepth_scale[1], 0,room_curr.autodepth_pos[1]+stage_top+2)
 //  line(0,room_curr.autodepth_pos[2]+stage_top,128,room_curr.autodepth_pos[2]+stage_top,12)
 //  print(room_curr.autodepth_scale[2], 0,room_curr.autodepth_pos[2]+stage_top+2)
 //  fillp()
 // }

	// draw active/speech text
	talking_draw();

	// in dialog mode?
	if (dialog_curr && dialog_curr.visible) {
		// draw dialog sentences?
		dialog_draw();
		cursor_draw();
		// skip rest
		return;
	}

 // hack:
 // skip draw if (just exited a cutscene
 // as could be going straight into a dialog
 // (would prefer a better way than this, but couldn't find one!)
//
	if (cutscene_cooloff > 0) {cutscene_cooloff -= 1; return;}

	// draw current command (verb/object)
	if (!cutscene_curr) command_draw();

	// draw ui and inventory (only if (actor selected to use it!)
	if (!cutscene_curr
		? cutscene_curr.flags == 2 // quick-cut
		// and not just left a cutscene
		: cutscene_cooloff == 0) {
		ui_draw();
	}

	if ((!cutscene_curr) cursor_draw();
}

function update_mouse_click_state() {
	ismouseclicked = stat(34) > 0;
}

// handle button inputs
function playercontrol() {

	// check for (skip/override's
	if (talking_curr && !ismouseclicked && (btnp(4) || stat(34) == 1)) {
			// skip current talking message
		talking_curr.time_left, ismouseclicked = 0, true;
			return;
			
 }

 // cutscene? (or skip?)
 if (cutscene_curr) {
		if ((btnp(5) || stat(34)==2) && cutscene_curr.override) {
    cutscene_curr.thread = cocreate(cutscene_curr.override);
    cutscene_curr.override = nil;
    return;
  }

  // either way - don't allow other user actions!
  update_mouse_click_state();
  return;
 }


	//
	if (btn(0)) { cursor_x -= 1; }
	if (btn(1)) { cursor_x += 1; }
	if (btn(2)) { cursor_y -= 1; }
	if (btn(3)) { cursor_y += 1; }

	if (btnp(4)) { input_button_pressed(1); }
	if (btnp(5)) { input_button_pressed(2); }

	// only update position if (mouse moved
 mouse_x,mouse_y = stat(32)-1, stat(33)-1;
 if (mouse_x != last_mouse_x) { cursor_x = mouse_x; }	// mouse xpos
 if (mouse_y!= last_mouse_y) { cursor_y = mouse_y; }  // mouse ypos

 // don't repeat action if (same press/click
 if (stat(34)>0 && !ismouseclicked) {
  input_button_pressed(stat(34));
 }
 // store for (comparison next cycle
	last_mouse_x, last_mouse_y = mouse_x, mouse_y;

 update_mouse_click_state();
}

// keep cursor within screen
cursor_x, cursor_y = mid(0, cursor_x, 127), mid(0, cursor_y, 127);

// 1 = z/lmb, 2 = x/rmb, (4=middle)
function input_button_pressed(button_index) {

 
	// abort if (no actor selected at this point
	if (!selected_actor) return;

	// check for (sentence selection
	if (dialog_curr && dialog_curr.visible) {
		if (hover_curr_sentence) selected_sentence = hover_curr_sentence;
		// skip remaining
		return;
	}

 // if (already executing, clear current command
 // (allow abort of commands by) {ing other actions, like walking)
	if (executing_cmd)	clear_curr_cmd();

	if (hover_curr_verb) {
		// change verb and now reset any active objects
		verb_curr, noun1_curr, noun2_curr = get_verb(hover_curr_verb);
	}
	else if (hover_curr_object) {
		// if (valid obj, complete command
		// else, abort command (clear verb, etc.)
		if (button_index == 1) {
		}
	   // if (already have obj #1
	   if (noun1_curr && !executing_cmd) {
	    // complete with obj #2
	    noun2_curr = hover_curr_object;
	   }
	   else {
	    noun1_curr = hover_curr_object;
	   }
	
	   if (verb_curr[2] == get_verb(verb_default)[2]
	    && hover_curr_object.owner) {
	     // inventory item, perform look-at
	     verb_curr = get_verb(verbs[verb_default_inventory_index]);
				}
	
			else if (hover_curr_default_verb) {
				// perform default verb action (if (present)
				verb_curr, noun1_curr = get_verb(hover_curr_default_verb), hover_curr_object;
	   // force repaint of command (to reflect default verb)
				command_draw();
				}
	
		// ui arrow clicked
		else if (hover_curr_arrow) {
			// up arrow
			if (hover_curr_arrow == ui_arrows[1]) {
				if (selected_actor.inv_pos > 0) selected_actor.inv_pos -= 1;
			}
			else { //) {wn arrow
				if (selected_actor.inv_pos + 2 < flr(#selected_actor.inventory/4)) {
					selected_actor.inv_pos += 1;
				}
			}
			return;
		}
		//else
			// what else could there be? actors!?
	}

	local vc2 = verb_curr[2];

	// attempt to use verb on object (if is not already executing verb)
	if (noun1_curr) {
		// are we starting a 'use' command?
		if (vc2 == V_USE || vc2 == V_GIVE) {
			if (noun2_curr) {
				// 'use' part 2
			}
			else if (noun1_curr.use_with && noun1_curr.owner == selected_actor) {
				// 'use' part 1 (e.g. "use hammer")
				// wait for (noun2 to be set
				return;
			}
		}

		// execute verb script
		executing_cmd = true;
		selected_actor.thread = cocreate(function() {
			// if (obj not in inventory (or about to give/use it)...
			if ((!noun1_curr.owner
				   ? (!has_flag(noun1_curr.classes, "class_actor")
							: vc2 != V_USE))
			 || noun2_curr)
			{
				// walk to use pos and face dir
				// determine which item we're walking to
				walk_obj = noun2_curr || noun1_curr;
				//todo: find nearest usepos if (none set?
				dest_pos = get_use_pos(walk_obj);
				walk_to(selected_actor, dest_pos.x, dest_pos.y);
				// abort if (walk was interrupted
				if (selected_actor.moving != 2) { return; }
				// face object/actor by default
				use_dir = walk_obj;
				// unless a diff dir specified
				if (walk_obj.use_dir) { use_dir = walk_obj.use_dir; }
				// turn to use dir
				do_anim(selected_actor, "face_towards", use_dir);
			}
			//) {es current object support active verb?
			if (valid_verb(verb_curr,noun1_curr)) {
				// finally, execute verb script
				start_script(noun1_curr.verbs[verb_curr[1]], false, noun1_curr, noun2_curr);
			}
			else {
				// check for (door
				if (has_flag(noun1_curr.classes, "class_door")) {
					// perform default) {or action
					//start_script(function()
						local func = door_funcs[vc2];
						if (func) func(noun1_curr, noun1_curr.target_door);
					//}, false)
				}
				else {
					// e.g. "i don't think that will work"
					unsupported_action(vc2, noun1_curr, noun2_curr);
				}
			}
			// clear current command
			clear_curr_cmd();
		});
		coresume(selected_actor.thread);
	}
	else if (cursor_y > stage_top && cursor_y < stage_top+64) {
		// in map area
		executing_cmd = true;
		// attempt to walk to target
		selected_actor.thread = cocreate(function() {
			walk_to(selected_actor, cursor_x+cam_x, cursor_y - stage_top);
			// clear current command
			clear_curr_cmd();
		});
		coresume(selected_actor.thread);
	}
}

// collision detection
function check_collisions() {
 // check for (current room
	if (!room_curr) return;

	// reset hover collisions
	hover_curr_verb, hover_curr_default_verb, hover_curr_object, hover_curr_sentence, hover_curr_arrow = nil;
	
	// are we in dialog mode?
	if (dialog_curr && dialog_curr.visible) {
		for (s in all(dialog_curr.sentences)) {
			if (iscursorcolliding(s)) hover_curr_sentence = s;
		}
		// skip remaining collisions
		return;
	}

	// reset zplane info
	reset_zplanes();

	// check room/object collisions
	for (obj in all(room_curr.objects)) {
		// capture bounds (even for ("invisible", but not untouchable/dependent, objects)
		if ((!obj.classes
			|| (obj.classes && !has_flag(obj.classes, "class_untouchable")))
			&&
			(!obj.dependent_on			// object has a valid dependent state?
			 || obj.dependent_on.state == obj.dependent_on_state))
		{
			recalc_bounds(obj, obj.w*8, obj.h*8, cam_x, cam_y);
		}
		else {
			// reset bounds
			obj.bounds = nil;
		}

		if (iscursorcolliding(obj)) {
			// if (highest (or first) object in hover "stack"
			if (!hover_curr_object || max(obj.z,hover_curr_object.z) == obj.z)
			{
				hover_curr_object = obj;
			}
		}
		// recalc z-plane
		recalc_zplane(obj);
	}

	// check actor collisions
	for (k,actor in pairs(actors)) {
		if (actor.in_room == room_curr) {
			recalc_bounds(actor, actor.w*8, actor.h*8, cam_x, cam_y);
			// recalc z-plane
			recalc_zplane(actor);
			// are we colliding (ignore self!)
			if (iscursorcolliding(actor) && actor != selected_actor)
				hover_curr_object = actor;
		}
	}

	if (selected_actor) {
		// check ui/inventory collisions
		for (v in all(verbs)) {
			if ((iscursorcolliding(v)) hover_curr_verb = v;
		}
		for (a in all(ui_arrows)) {
			if ((iscursorcolliding(a)) hover_curr_arrow = a;
		}

		// check room/object collisions
		for (k,obj in pairs(selected_actor.inventory)) {
			if (iscursorcolliding(obj)) {
				hover_curr_object = obj;
				// pickup override for (inventory objects
				if (verb_curr[2] == V_PICKUP && hover_curr_object.owner) verb_curr = nil;
			}
			// check for (disowned objects!
			if (obj.owner != selected_actor) del(selected_actor.inventory, obj);
		}

		// default to walkto (if (nothing set)
		verb_curr = verb_curr || get_verb(verb_default);

		// update "default" verb for (hovered object (if (any)
		hover_curr_default_verb = hover_curr_object ? find_default_verb(hover_curr_object) : hover_curr_default_verb;
	}
}


function reset_zplanes() {
	// draw_zplanes = {}
	for (x = -64, 64) {
		draw_zplanes[x] = {};
	}
}

function recalc_zplane(obj) {
	// calculate the correct z-plane
	// based on obj || x,y pos + elevation
	add(draw_zplanes[obj.z ? obj.z : flr(obj.y + (obj.offset_y ? 0 : obj.h * 8))], obj);
}

function room_draw() {
 // check for (current room
 if (!room_curr) {
 	print("-error-  no current room set",5+cam_x,5+stage_top,8,0);
  return;
 }

	// set room background col (or black by default)
	rectfill(0, stage_top, 127, stage_top+64, room_curr.bg_col || 0);

	// draw each zplane, from back to front
	for (z = -64,64) {

		// draw bg layer?
		if (z == 0) {
			// replace colors?
			replace_colors(room_curr);

			if (room_curr.trans_col) {
				palt(0, false);
				palt(room_curr.trans_col, true);
			}
			map(room_curr.map[1], room_curr.map[2], 0, stage_top, room_curr.map_w, room_curr.map_h);
			
			//reset palette
			pal();


					// ===============================================================
					// debug walkable areas

					// if (show_pathfinding {
					// 	actor_cell_pos = getcellpos(selected_actor)

     // //## need to correct this offset (in code above)
     // //actor_cell_pos[2] -= 2

					// 	celx = flr((cursor_x + cam_x + 0) /8) + room_curr.map[1]
					// 	cely = flr((cursor_y - stage_top + 0) /8 ) + room_curr.map[2]
					// 	target_cell_pos = { celx, cely }

					// 	path = find_path(actor_cell_pos, target_cell_pos)

					// 	// finally, add our destination to list
					// 	click_cell = getcellpos({x=(cursor_x + cam_x), y=(cursor_y - stage_top)})
					// 	if (is_cell_walkable(click_cell[1], click_cell[2]) {
					// 	//if ((#path>0) {
					// 		add(path, click_cell)
					// 	}

					// 	for (p in all(path)) {
					// 		//printh("  > "..p[1]..","..p[2])
					// 		rect(
					// 			(p[1]-room_curr.map[1])*8,
					// 			stage_top+(p[2]-room_curr.map[2])*8,
					// 			(p[1]-room_curr.map[1])*8+7,
					// 			stage_top+(p[2]-room_curr.map[2])*8+7, 11)
					// 	}
					// }

     // ===============================================================
		}
		else {
			// draw other layers
			zplane = draw_zplanes[z];

			// draw all objs/actors in current zplane
			for (obj in all(zplane)) {
				// object || actor?
				if (!has_flag(obj.classes, "class_actor")) {
					// object
					if (obj.states	  /* object has a state?*/
				    ? (obj.state
					   && obj[obj.state]
					   && obj[obj.state] > 0)
					 : (!obj.dependent_on 			/* object has a valid dependent state?*/
						|| obj.dependent_on.state == obj.dependent_on_state)
					 ? !obj.owner   						/* object is not "owned"*/
					 : obj.draw
      || obj.curr_anim)
					{
						// something to draw
						object_draw(obj);
					}
				}
				else {
					// actor
					if (obj.in_room == room_curr) actor_draw(obj);
				}
				//show_collision_box(obj);
			}
		}
	}

}

function replace_colors(obj) {
	// replace colors (where defined)
	if (obj.col_replace) {
		c = obj.col_replace;
		//for (c in all(obj.col_replace)) {
			pal(c[1], c[2]);
		//}
	}
	// also apply brightness (default to room-level, if (not set)
	if (obj.lighting) {
		_fadepal(obj.lighting);
	}
	else if (obj.in_room && obj.in_room.lighting) {
		_fadepal(obj.in_room.lighting);
	}
}


function object_draw(obj) {
	local sprnum = 0;
	// replace colors?
	replace_colors(obj);
	               
	// check for (custom draw
	if (obj.draw) {
		obj.draw(obj);
	}
	
	else {
		if (obj.curr_anim) {
			// update animation state
			animate(obj);
			// choose walk anim frame
			sprnum = obj.curr_anim[obj.anim_pos];
				 }
				 // allow for (repeating
		for (h = 0, obj.repeat_x ? obj.repeat_x - 1 : 0) {
			// draw object (in its state!)
			if (obj.states) {
				sprnum = obj.states[obj.state];
			}
			else if (sprnum == 0) {
				sprnum = obj[obj.state];
			}
			sprdraw(sprnum, obj.x + (h * (obj.w * 8)), obj.y, obj.w, obj.h, obj.trans_col, obj.flip_x, obj.scale);
		}
	}
     
// debug
	//pset(obj.x, obj.y + stage_top, 8)
     
	//reset palette
	pal();
 }


// draw actor(s)
function actor_draw(actor) {

	local dirnum, sprnum = face_dirs[actor.face_dir];

	if (actor.curr_anim && (actor.moving == 1 || istable(actor.curr_anim))
	{
		// update animation state
		animate(actor);
		// choose walk anim frame
		sprnum = actor.curr_anim[actor.anim_pos];
	}
	else {

		// idle
		sprnum = actor.idle[dirnum];
	}

	// replace colors?
	replace_colors(actor);

 // auto-scaling for (depth?
 local factor = (actor.y-room_curr.autodepth_pos[1]) / (room_curr.autodepth_pos[2]-room_curr.autodepth_pos[1]);
 factor = room_curr.autodepth_scale[1]+(room_curr.autodepth_scale[2]-room_curr.autodepth_scale[1])*factor;
 actor.auto_scale = mid(room_curr.autodepth_scale[1], factor, room_curr.autodepth_scale[2]);

 // apply "zoom" to autoscale (e.g. camera further away)
 //auto_scale *= (room_curr.scale || 1)


 // calc scaling offset (to align to bottom-centered)
 local scale = actor.scale || actor.auto_scale;
	local scale_height, scale_width = (8 * actor.h), (8 * actor.w);
 local scaleoffset_y = scale_height - (scale_height * scale);
 local scaleoffset_x = scale_width - (scale_width * scale);
 local draw_x = actor.offset_x + flr(scaleoffset_x/2);
 local draw_y = actor.offset_y + scaleoffset_y;

	sprdraw(sprnum,
		draw_x,
		draw_y,
		actor.w ,
		actor.h,
		actor.trans_col,
		actor.flip,
		false,
		scale);


	// talking overlay
	if (talking_actor
	 && talking_actor == actor
	 && talking_actor.talk)
	{
		if (actor.talk_tmr < 7) {
		    // note: scaling from top-left
		    sprdraw(actor.talk[dirnum],
				draw_x + (actor.talk[5] || 0),
				draw_y + flr((actor.talk[6] || 8)*scale),
				(actor.talk[7] || 1),
				(actor.talk[8] || 1),
				actor.trans_col,
				actor.flip,
				false,
				scale);
			}
		actor.talk_tmr = actor.talk_tmr % 14 + 1;
	}

 // debug
 // if (show_debuginfo {
  // pset(actor.x, actor.y + stage_top, 8)
  // pset(actor.offset_x, actor.offset_y+stage_top, 11)
 // }

	//reset palette
	pal();
}

function command_draw() {
	// draw current command
	local cmd_col, verb_curr_ref, command = verb_maincol, verb_curr[2], verb_curr ? verb_curr[3] : "";

	if (noun1_curr) {
		command = command.." "..noun1_curr.name;
		if (verb_curr_ref == V_USE && (!executing_cmd || noun2_curr)) {
			command = command.." with";
		}
		else if (verb_curr_ref == V_GIVE) {
			command = command.." to";
		}
	}
	if (noun2_curr) {
		command = command.." "..noun2_curr.name;
	}
	else if (hover_curr_object
		and hover_curr_object.name != ""
		// don't show use object with itself!
		and ( !noun1_curr || (noun1_curr != hover_curr_object) )
		// || walk-to objs in inventory!
		// && ( not hover_curr_object.owner or
		// 				or verb_curr_ref != get_verb(verb_default)[2] )
  // || when already executing!
  && !executing_cmd)
	{
	  // default to look-at for (inventory items
	  if (hover_curr_object.owner && verb_curr_ref == get_verb(verb_default)[2]) {
	   command = "look-at";
	  }
		command = command.." "..hover_curr_object.name;
	}
	cmd_curr = command;

	if (executing_cmd) {
		// highlight active command
		command = cmd_curr;
		cmd_col = verb_hovcol;
	}

	print( smallcaps(command), 63.5-flr(#command*2), stage_top + 66, cmd_col );
}

function talking_draw() {
	// alignment
	//   0 = no align
	//   1 = center
	if (talking_curr) {
		local line_offset_y = 0;
		for (l in all(talking_curr.msg_lines)) {
			local line_offset_x = 0;
			// center-align line
			if (talking_curr.align == 1) {
				line_offset_x = ((talking_curr.char_width*4)-(#l*4))/2;
			}
			outline_text(
				l,
				talking_curr.x + line_offset_x,
				talking_curr.y + line_offset_y,
				talking_curr.col,
				0,
				talking_curr.use_caps,
    talking_curr.big_font);
			line_offset_y += talking_curr.big_font ? 12 : 6;
		}
		// update message lifespan
		talking_curr.time_left -= 1;
		// remove text & reset actor's talk anim
		if (talking_curr.time_left <= 0) stop_talking();
	}
}

// draw ui and inventory
function ui_draw() {
	// draw verbs
	local xpos, ypos, col_len = 0, 75, 0;

	for (v in all(verbs)) {
		local txtcol = v == hover_curr_verb ? verb_hovcol :
			(hover_curr_default_verb && v == hover_curr_default_verb ? verb_defcol :
			verb_maincol);

		// get verb info
		local vi = get_verb(v);
		print(vi[3], xpos, ypos+stage_top+1, verb_shadcol);  // shadow
		print(vi[3], xpos, ypos+stage_top, txtcol);  // main

		// capture bounds
		v.x = xpos;
		v.y = ypos;
		recalc_bounds(v, #vi[3]*4, 5, 0, 0);
		//show_collision_box(v)

		// auto-size column
		if (#vi[3] > col_len) col_len = #vi[3];

		ypos += 8;

		// move to next column
		if (ypos >= 95) {
			ypos = 75;
			xpos += (col_len + 1.0) * 4;
			col_len = 0;
		}
	}

	if (selected_actor) {
		// draw inventory
		xpos, ypos = 86, 76;
		// determine the inventory "window"
		local start_pos = selected_actor.inv_pos * 4;
		local end_pos = min(start_pos+8, #selected_actor.inventory);

		for (ipos = 1,8) {
			// draw inventory bg
			rectfill(xpos-1, stage_top+ypos-1, xpos+8, stage_top+ypos+8, verb_shadcol);

			obj = selected_actor.inventory[start_pos+ipos];
			if (obj) {
				// something to draw
				obj.x, obj.y = xpos, ypos;
				// draw object/sprite
				object_draw(obj);
				// re-calculate bounds (as pos may have changed)
				recalc_bounds(obj, obj.w*8, obj.h*8, 0, 0);
				//show_collision_box(obj)
			}
			xpos += 11;

			if (xpos >= 125) {
				ypos += 12;
				xpos = 86;
			}
			ipos += 1;
		}

		// draw arrows
		for (i = 1,2) {
			arrow = ui_arrows[i];
			pal(7, hover_curr_arrow == arrow ? verb_hovcol : verb_maincol);
			pal(5, verb_shadcol);
			sprdraw(arrow.spr, arrow.x, arrow.y, 1, 1, 0);
			// capture bounds
			recalc_bounds(arrow, 8, 7, 0, 0);
			//show_collision_box(arrow)
			pal(); //reset palette
		}
	}
}

function dialog_draw() {
	local xpos, ypos = 0, 70;

	for (s in all(dialog_curr.sentences)) {
		if (s.char_width > 0) {
			// capture bounds
			s.x, s.y = xpos, ypos;
			recalc_bounds(s, s.char_width*4, #s.lines*5, 0, 0);

			local txtcol = s == hover_curr_sentence ? dialog_curr.hlcol : dialog_curr.col;

			for (l in all(s.lines)) {
				print(smallcaps(l), xpos, ypos+stage_top, txtcol);
				ypos += 5;
			}

			//show_collision_box(s)
			ypos += 2;
		}
	}
}

// draw cursor
function cursor_draw() {
	col = ui_cursor_cols[cursor_colpos];
	// switch sprite color accordingly
	pal(7,col);
	spr(ui_cursorspr, cursor_x-4, cursor_y-3, 1, 1, 0);
	pal(); //reset palette

	cursor_tmr += 1;
	if (cursor_tmr > 7) {
		//reset timer
		cursor_tmr = 1;
		// move to next color?
		cursor_colpos = cursor_colpos % #ui_cursor_cols + 1;
	}
}

function sprdraw(n, x, y, w, h, transcol, flip_x, flip_y, scale) {
	// switch transparency
	set_trans_col(transcol); //, true)

 n = n || 0;
	// draw zoomed sprite
 //https://www.lexaloffle.com/bbs/?tid=2429
	local sx, sy = 8 * (n % 16), 8 * flr(n / 16);
	local sw, sh = 8 * w, 8 * h;
 local dz = scale || 1;
	local dw, dh = sw * dz, sh * dz;
  sspr(sx, sy, sw, sh, x, stage_top + y, dw, dh, flip_x, flip_y);

  // first scale, bottom-anchored
 //sspr(sx, sy, sw, sh, x, stage_top + y +(sh-dh), dw, dh, flip_x, flip_y)

	//spr(n, x, stage_top + y, w, h, flip_x, flip_y) // orig method (pre-scale)

	//pal() // don't) {, affects lighting!
}

function set_trans_col(transcol) { //, enabled)
	// set transparency for (specific col
	palt(0, false);
	palt(transcol, true);
}


// initialise all the rooms (e.g. add in parent links)
function game_init() {

	for (room in all(rooms)) {
		explode_data(room);

		room.map_w = #room.map > 2 ? room.map[3] - room.map[1] + 1 : 16;
		room.map_h = #room.map > 2 ? room.map[4] - room.map[2] + 1 : 8;
  // auto-depth (or defaults)
  room.autodepth_pos = room.autodepth_pos || {9,50};
  room.autodepth_scale = room.autodepth_scale || {0.25,1};

		// init objects (in room)
		for (obj in all(room.objects)) {
			explode_data(obj);
			obj.in_room, obj.h = room, obj.h || 0;
			if (obj.init) obj.init(obj);
		}
	}
	// init actors with defaults
	for (ka,actor in pairs(actors)) {
		explode_data(actor);
		actor.moving = 2 ;		// 0=stopped, 1=walking, 2=arrived
		actor.tmr = 1; 		  // internal timer for (managing animation
		actor.talk_tmr = 1;
		actor.anim_pos = 1; 	// used to track anim pos
		actor.inventory = {
			// obj_switch_player,
			// obj_switch_tent
		};
		actor.inv_pos = 0; 	// pointer to the row to start displaying from
	}
}

// function show_collision_box(obj)
// 	local obj_bounds = obj.bounds
// 	if (show_collision
// 	 && obj_bounds
// 	then
// 		rect(obj_bounds.x, obj_bounds.y, obj_bounds.x1, obj_bounds.y1, 8)
// 	}
// }

function update_scripts(scripts) {
	for (scr_obj in all(scripts)) {
		if (scr_obj[2] && !coresume(scr_obj[2], scr_obj[3], scr_obj[4]) {
			del(scripts, scr_obj);
		}
	}
}

function _fadepal(perc) {
	if ((perc) perc = 1-perc;
 local p=flr(mid(0,perc,1)*100);
 local dpal={0,1,1, 2,1,13,6,
          4,4,9,3, 13,1,13,14};
 for (j=1,15) {
  col = j;
  kmax=(p+(j*1.46))/22;
  for (k=1,kmax) {
   col=dpal[col];
  }
  pal(j,col);
 }
}


function istable(t) {
	return type(t) == "table";
}

function _center_camera(val) {
	// check params for (obj/actor
	// keep camera within "room" bounds
	return mid(0, (istable(val) ? val.x : val)-64, (room_curr.map_w*8) -128 );
}



function getcellpos(obj) {
	return { flr(obj.x/8) + room_curr.map[1], flr(obj.y/8) + room_curr.map[2] };
}

function is_cell_walkable(celx, cely) {
		return fget(mget(celx, cely),0);
}


// auto-break message into lines
function create_text_lines(msg, max_line_length) { //, comma_is_newline)
	//  > ";" new line, shown immediately
	local lines, currline, curword, curchar = {}, "", "", "";

	local function upt(max_length) {
		if (#curword + #currline > max_length) {
			add(lines,currline);
			currline="";
		}
		currline=currline..curword;
		curword="";
	}

	for (i = 1, #msg) {
		curchar=sub(msg,i,i);
		curword=curword..curchar;

		if (curchar == " " || #curword > max_line_length-1) {
			upt(max_line_length);
		}
		else if (#curword>max_line_length-1) {
			curword=curword.."-";
			upt(max_line_length);
		}
		else if (curchar == ";") {
			// line break
			currline=currline..sub(curword,1,#curword-1);
			curword="";
			upt(0);
		}
	}

	upt(max_line_length);
	if (currline != "") add(lines,currline);

	return lines
}

// find longest line
function longest_line_size(lines) {
	local longest_line = 0;
	for (l in all(lines)) {
		if ((#l > longest_line) longest_line = #l;
	}
	return longest_line;
}

function has_flag(obj, value) {
	for (f in all(obj)) {
		if ((f == value) return true;
	 }
	// return false
}


function recalc_bounds(obj, w, h, cam_off_x, cam_off_y) {
	local x, y = obj.x, obj.y;
	// offset for (actors?
	if (has_flag(obj.classes, "class_actor")) {
  obj.offset_x = x - (obj.w *8) /2;
		obj.offset_y = y - (obj.h *8) +1;
  x = obj.offset_x;
		y = obj.offset_y;
	}
	obj.bounds = {
		x = x,
		y = y + stage_top,
		x1 = x + w -1,
		y1 = y + h + stage_top -1,
		cam_off_x = cam_off_x,
		cam_off_y = cam_off_y
	};
}


//
// a* pathfinding functions
//


function find_path(start, goal) {
	local frontier, came_from, cost_so_far, lowest_dist, lowest_dist_node, current = {}, {}, {};
	insert(frontier, start, 0);
	// came_from[vectoindex(start)] = nil
	cost_so_far[vectoindex(start)] = 0;

	while (#frontier > 0 && #frontier < 1000) {
		// pop the last element off a table
		current = frontier[#frontier][1];
		del(frontier, frontier[#frontier]);

		if (vectoindex(current) == vectoindex(goal)) break;

		//local neighbours = getneighbours(current)
		local neighbours = {};
		for (x = -1, 1) {
			for (y = -1, 1, x == 0 ? 2 : 1) {
				local chk_x, chk_y = current[1] + x, current[2] + y;

				if (chk_x >= room_curr.map[1] && chk_x <= room_curr.map[1] + room_curr.map_w
					and chk_y >= room_curr.map[2] && chk_y <= room_curr.map[2] + room_curr.map_h
					and is_cell_walkable(chk_x, chk_y)
				// squeeze check for (corners
					and ((abs(x) != abs(y))
						or is_cell_walkable(chk_x, current[2])
						or is_cell_walkable(chk_x - x, chk_y)
						or enable_diag_squeeze))
				 {
					// process a valid neighbor
					local next = {chk_x, chk_y};
					local nextindex = vectoindex(next);
					local new_cost = cost_so_far[vectoindex(current)] + (x * y == 0 ? 1.0 : 1.414); // diagonals cost more

					if (!cost_so_far[nextindex] || new_cost < cost_so_far[nextindex]) {
						cost_so_far[nextindex] = new_cost;
						local h = max(abs(goal[1] - chk_x), abs(goal[2] - chk_y)) + min(abs(goal[1] - chk_x), abs(goal[2] - chk_y)) * .414;
						insert(frontier, next, new_cost + h);
						came_from[nextindex] = current;

						if (!lowest_dist || h < lowest_dist) {
							lowest_dist = h;
							lowest_dist_node = nextindex;
							lowest_dist_neigh = next;
						}
					}
				}
			}
		}
	}

 // now find goal..
 local path = {};
 current = came_from[vectoindex(goal)];

 if (current) {
 	// add "goal" to path
	 add(path, goal);
 // check for ("no goal found"
 }
 else if (lowest_dist_node) {
   // start from closest to goal instead
   current = came_from[lowest_dist_node];
	 add(path, lowest_dist_neigh);
 }

 if (current) {
		local cindex, sindex = vectoindex(current), vectoindex(start);

	while (cindex != sindex) {
		add(path, current);
		current = came_from[cindex];
		cindex = vectoindex(current);
	}

	//reverse(path)
	for (i=1,#path/2) {
		local temp = path[i];
		local oppindex = #path-(i-1);
		path[i] = path[oppindex];
		path[oppindex] = temp;
	}
 }

 return path;
}



// insert into table and sort by priority
function insert(t, val, p) {
	local new = {val, p};
 if (#t >= 1) {
		for (i = #t + 1, 2, -1) {
   local next = t[i-1];
   if (p < next[2]) {
				t[i] = new; // found the right spot, insert the new item
    return;
   }
   else{
				t[i] = next; // copy the next item to this spot
   }
  }
 }
	t[1] = new; // empty table || new highest p
}

// translate a 2d x,y coordinate to a 1d index and back again
function vectoindex(vec) {
	return ((vec[1]+1) * 16) + vec[2];
}




//
// helper functions
//

function animate(obj) {
 // animate the object
 // (update frames, looping as req)
 obj.tmr += 1;
	if (obj.tmr > obj.frame_delay) {
		obj.tmr = 1;
	 obj.anim_pos = obj.anim_pos % #obj.curr_anim + 1;
	}
}


function show_error(msg) {
	print_line("-error-;"..msg,5+cam_x,5,8,0);
}

function explode_data(obj) {
	for (l in all(split(obj.data, "\n"))) {
		local pairs=split(l, "=");
		if (#pairs==2) {
			obj[pairs[1]] = autotype(pairs[2]);
		}
		else {
			printh(" > invalid data: ["..pairs[1].."]");
		}
	}
}

// split s on delimiter, ignoring leading and trailing space and tab

function split(s, delimiter) {
	local retval, start_pos, last_char_pos = {}, 0, 0;

	for (i=1,#s) {
		local curr_letter = sub(s,i,i);
		if (curr_letter == delimiter) {
			add(retval, sub(s,start_pos,last_char_pos));
			start_pos, last_char_pos = 0, 0;
		}
		else if (curr_letter != " "
		 && curr_letter != "\t") {
			// curr letter is useful
			last_char_pos, start_pos = i, start_pos == 0 ? i : start_pos;
		}
	}
	// add remaining content?
	if (start_pos + last_char_pos > 0) {
		add(retval, sub(s,start_pos,last_char_pos));
	}
	return retval
}

function autotype(str_value) {
	local first_letter = sub(str_value,1,1);

	if (str_value == "true") {
		return true;
	}
	else if (str_value == "false") {
		return false;
	}
	else if (tonum(str_value)) {
		// must be number
		return tonum(str_value);
	}
	else if (first_letter == "{") {
		// array - so split it
		local temp = sub(str_value,2,#str_value-1);
		retarray = {};
		for (val in all(split(temp, ","))) {
			add(retarray, autotype(val));
		}
		return retarray;
	}
	else {//if (first_letter == "\"" {
		// string - so) { nothing
		return str_value;
	}
}

function outline_text(str,x,y,c0,c1,use_caps,big_font) {
	if ((!use_caps) str = smallcaps(str);
 if ((big_font) str="\^w\^t"..str;
 for (xx = -1, 1) {
		for (yy = -1, 1, xx == 0 ? 2 : 1) {
			print(str, x+xx, y+yy, c1);
		}
 }
 print(str,x,y,c0);
}


// collision check
function iscursorcolliding(obj) {
	// check params / not in cutscene
	if ((!obj.bounds || cutscene_curr) return false;

	local bounds = obj.bounds;
	return !((cursor_x + bounds.cam_off_x > bounds.x1 || cursor_x + bounds.cam_off_x < bounds.x)
			|| (cursor_y > bounds.y1 || cursor_y < bounds.y));
}

function smallcaps(s) {
  local t="";
  for (i=1,#s) {
    local c=ord(s,i);
    t..=chr(c>96 && c<123 ? c-32 : c);
  }
  return t;
}

/*
__gfx__
0000000000000000000000000000000044444444440000004444444477777777f9e9f9f9ddd5ddd5bbbbbbbb5500000010101010000000000000000000000000
00000000000000000000000000000000444444404400000044444444777777779eee9f9fdd5ddd5dbbbbbbbb5555000001010101000000000000000000000000
00800800000000000000000000000000aaaaaa00aaaa000005aaaaaa77777777feeef9f9d5ddd5ddbbbbbbbb5555550010101010000000000000000000000000
0008800055555555ddddddddeeeeeeee999990009999000005999999777777779fef9fef5ddd5dddbbbbbbbb5555555501010101000000000000000000000000
0008800055555555ddddddddeeeeeeee44440000444444000005444477777777f9f9feeeddd5ddd5bbbbbbbb5555555510101010000000000000000000000000
0080080055555555ddddddddeeeeeeee444000004444440000054444777777779f9f9eeedd5ddd5dbbbbbbbb5555555501010101000000000000000000000000
0000000055555555ddddddddeeeeeeeeaa000000aaaaaaaa000005aa77777777f9f9feeed5ddd5ddbbbbbbbb5555555510101010000000000000000000000000
0000000055555555ddddddddeeeeeeee900000009999999900000599777777779f9f9fef5ddd5dddbbbbbbbb5555555501010101000000000000000000000000
0000000077777755666666ddbbbbbbee888888553333333313131344666666665888858866666666cbcbcbcb0000005510101044999999990000000088845888
00000000777755556666ddddbbbbeeee88888855333333333131314466666666588885881c1c1c1cbcbcbcbc0000555501010144444444440000000088845888
000010007755555566ddddddbbeeeeee88887777333333331313aaaa6666666655555555c1c1c1c1cbcbcbcb005555551010aaaa000450000000000088845888
0000c00055555555ddddddddeeeeeeee88886666333333333131999966666666888588881c1c1c1cbcbcbcbc5555555501019999000450000000000088845888
001c7c1055555555ddddddddeeeeeeee8855555533333333134444446666666688858888c1c1c1c1cbcbcbcb5555555510444444000450000000000088845888
0000c00055555555ddddddddeeeeeeee88555555333333333144444466666666555555551c1c1c1cbcbcbcbc5555555501444444000450000000000088845888
0000100055555555ddddddddeeeeeeee7777777733333333aaaaaaaa6666666658888588c1c1c1c1cbcbcbcb55555555aaaaaaaa000450000000000088845888
0000000055555555ddddddddeeeeeeee66666666333333339999999966666666588885887c7c7c7cbcbcbcbc5555555599999999000450000000000088845888
0000000055777777dd666666eebbbbbb558888885555555544444444777777777777777755555555444444454444444444444445000450008888888999999999
0000000055557777dddd6666eeeebbbb5588888855553333444444447777777777777777555555554444445c4444444444444458000450008888889444444444
0000000055555577dddddd66eeeeeebb7777888855333333aaaaaaaa777777777777777755555555444445cbaaaaaa4444444588000450008888894888845888
000c000055555555ddddddddeeeeeeee66668888533333339999999977777777777777775555555544445cbc9999994444445888000450008888948888845888
0000000055555555ddddddddeeeeeeee5555558853333333444444447777775555777777555555554445cbcb4444444444458888000450008889488888845888
0000000055555555ddddddddeeeeeeee555555885533333344444444777755555555777755555555445cbcbc4444444444588888000450008894588888845888
0000000055555555ddddddddeeeeeeee7777777755553333aaaaaaaa77555555555555770000000045cbcbcbaa44444445888888999999998944588888845888
0000000055555555ddddddddeeeeeeee6666666655555555999999995555555555555555000000005cbcbcbc9944444458888888555555559484588888845888
0000000055555555ddddddddbbbbbbbb555555555555555544444444cccccccc5555555677777777c77777776555555533333336633333338884588988845888
0000000055555555ddddddddbbbbbbbb555555553333555544444444cccccccc555555677777777ccc7777777655555533333367763333338884589488845888
0000000055555555ddddddddbbbbbbbb7777777733333355aaaaaa50cccccccc55555677777777ccccc777777765555533333677776333338884594488845888
0000000055555555ddddddddbbbbbbbb666666663333333599999950cccccccc5555677777777ccccccc77777776555533336777777633338884944488845888
0000000055555555ddddddddbbbbbbbb555555553333333544445000cccccccc555677777777ccccccccc7777777655533367777777763338889444488845888
0000000055555555ddddddddbbbbbbbb555555553333335544445000cccccccc55677777777ccccccccccc777777765533677777777776338894444488845888
0b03000055555555ddddddddbbbbbbbb7777777733335555aa500000cccccccc5677777777ccccccccccccc77777776536777777777777638944444499999999
b00030b055555555ddddddddbbbbbbbb666666665555555599500000cccccccc677777777ccccccccccccccc7777777667777777777777769444444455555555
00000000000000000000000000000000777777777777777777555555555555770000000000000000000000000000000000000000d00000004444444444444444
9f00d70000c0006500c0096500000000700000077000000770700000000007070000000000000000000000000000000000000000d50000004ffffff44ffffff4
9f2ed728b3c55565b3c5596500000000700000077000000770070000000070070000000000000000000000000000000000000000d51000004f4444944f444494
9f2ed728b3c50565b3c5946500000000700000077000000770006000000600070000000000000000000000000000000000000000d51000004f4444944f444494
9f2ed728b3c50565b3c5946500000000700000077000000770006000000600070000000000000000000000000000000000000000d51000004f4444944f444494
9f2ed728b3c55565b3c9456500000000700000077000000770006000000600070000000000000000000000000000000000000000d51000004f4444944f444494
9f2ed728b3c55565b3c9456500000000700000077000000770006000000600070000000000000000000000000000000000000000d51000004f4444944f444494
44444444444444444444444400000000777777777777777777776000000677770000000000000000000000000000000000000000d51000004f4444944f444494
00000000000000000000000000000000700000677600000770066000000660070000000000000000000000000000000000000000d51000004f4444944f444494
00cd006500000000000a000000000000700006077060000770606000000606070000000000000000000000000000000000000000d51000004f9999944f444494
b3cd8265000000000000000000000000700005077050000770506000000605070000000000000000000000000000000000000000d5100000444444444f449994
b3cd826500a0a000000aa000000a0a00700000077000000770006000000600070000000000000000000000000000000000000000d5100000444444444f994444
b3cd826500aaaa0000aaaa0000aaa000700000077000000770050000000050070000000000000000000000000000000000000000d510000049a4444444444444
b3cd826500a9aa0000a99a0000aa9a00700000077000000770500000000005070000000000000000000000000000000000000000d51000004994444444444444
b3cd826500a99a0000a99a0000a99a00777777777777777775000000000000770000000000000000000000000000000000000000d51000004444444449a44444
44444444004444000044440000444400555555555555555555555555555555550000000000000000000000000000000000000000d51000004ffffff449944444
99999999777777777777777777777777700000077776000077777777777777770000000000000000000000000000000000000000d51000004f44449444444444
55555555555555555555555555555555700000077776000055555555555555550000000000000000000000000000000000000000d51000004f4444944444fff4
444444441dd6dd6dd6dd6dd6d6dd6d51700000077776000044444444444444440000000000000000000000000000000000000000d51000004f4444944fff4494
ffff4fff1dd6dd6dd6dd6dd6d6dd6d517000000766665555444ffffffffff4440000000000000000000000000000000000000000d51000004f4444944f444494
44494944166666666666666666666651700000070000777644494444444494440000000000000000000000000000000000000000d51000004f4444944f444494
444949441d6dd6dd6dd6dd6ddd6dd65170000007000077764449444aa44494440000000000000000000000000000000000000000d51111114f4444944f444494
444949441d6dd6dd6dd6dd6ddd6dd651777777770000777644494444444494440000000000000000000000000000000000000000d55555554ffffff44f444494
44494944166666666666666666666651555555555555666644499999999994440000000000000000000000000000000000000000dddddddd444444444f444494
444949441dd6dd600000000056dd6d516dd6dd6d0000000044494444444494440000000000000000000000000000000000000000000000004f4444944f444494
444949441dd6dd650000000056dd6d51666666660000000044494444444494440000000000000000000000000000000000000000000000004f4444944f444994
44494944166666650000000056666651d6dd6dd60000000044494444444494440000000000000000000000000000000000000000000000004f4444944f499444
444949441d6dd6d5000000005d6dd651d6dd6dd60000000044494444444494440000000000000000000000000000000000000000000000004f4444944f944444
444949441d6dd6d5000000005d6dd651666666660000000044494444444494440000000000000000000000000000000000000000000000004f44449444444400
444949441666666500000000566666516dd6dd6d0000000044494444444494440000000000000000000000000000000000000000000000004f44449444440000
999949991dd6dd650000000056dd6d516dd6dd6d0000000044499999999994440000000000000000000000000000000000000000000000004f44449444000000
444444441dd6dd650000000056dd6d51666666660000000044444444444444440000000000000000000000000000000000000000000000004f44449400000000
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ccccccccffffffff
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ccccccccf666677f
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000cccccccc7cccccc7
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ccaaccccd776666d
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000caaaccccf676650f
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ccaaaaacf676650f
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ccaaaaacf676650f
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ccccccccff7665ff
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffff000000000000000000000000fff76fffffffffff
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffff000000000000000000000000fff76ffff666677f
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffff000000000000000000000000fbbbbccf75555557
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffff000000000000000000000000bbbcccc8d776666d
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffff000000000000000000000000fccccc8ff676650f
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffff000000000000000000000000fccc888ff676650f
00000000000000000000000000000000000000000000000000000000000000000000000000000000fff22fff000000000000000000000000fff00ffff676650f
00000000000000000000000000000000000000000000000000000000000000000000000000000000ff0020ff000000000000000000000000fff00fffff7665ff
00000000000000000000000000000000000000000000000000000000000000000000000000000000ff2302ffff2302ff0000000000007aa0fff76fff00000094
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffb33bffffb33bff00000000000070a0fff76fff00000944
00000000000000000000000000000000000000000000000000000000000000000000000000000000ff2bb2ffff2bb2ff000000000000aaa0f8888bbf00009440
00000000000000000000000000000000000000000000000000000000000000000000000000000000ff2222ffff2222ff00000000000a4440888bbbbc00094400
00000000000000000000000000000000000000000000000000000000000000000000000000000000ff2bb2ffff2bb2ff0000000000a40000fbbbbbcf00044000
00000000000000000000000000000000000000000000000000000000000000000000000000000000f2b33b2ff2b33b2f000000000a400000fbbbcccf00400000
00000000000000000000000000000000000000000000000000000000000000000000000000000000f22bb22ff2b33b2f0000000074a90000fff00fff94000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000f222222ff22bb22f00000000007a0000fff00fff44000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000f222222f00000000000000000066060bfff76fffcccccccc
00000000000000000000000000000000000000000000000000000000000000000000000000000000f22bb22f000000000000000000660600fff76fffc000000c
00000000000000000000000000000000000000000000000000000000000000000000000000000000f2b33b2f000000000000000000666600fcccc88fc0c00c0c
0000000000000000000000000000000000000000000000000000000000000000000000000000000022b33b22000000000000000000000000ccc8888bc00cc00c
00000000000000000000000000000000000000000000000000000000000000000000000000000000222bb222000000000000000007777770f88888bfc00cc00c
0000000000000000000000000000000000000000000000000000000000000000000000000000000022222222000000000000000007777770f888bbbfc0c00c0c
0000000000000000000000000000000000000000000000000000000000000000000000000000000022222222000000000000000007777770fff00fffc000000c
00000000000000000000000000000000000000000000000000000000000000000000000000000000bbbbbbbb000000000000000008888880fff00fffcccccccc
00000000bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb000000000000000000000000000000000000000000000000
00000000bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb000000000000000000000000000000000000000000000000
00000000bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb000000000000000000000000000000000000000000000000
00000000b444449bb444449bb444449bb494449bb494449bb494449bb999449bb999449bb999449b000000000000000000000000000000000000000000000000
00000000444044494440444944404449494444494944444949444449944444499444444994444449000000000000000000000000000000000000000000000000
00000000404000044040000440400004494400044944000449440004944444449444444494444444000000000000000000000000000000000000000000000000
0000000004ffff0004ffff0004ffff000440fffb0440fffb0440fffb444444444444444444444444000000000000000000000000000000000000000000000000
000000000fdffdf00fdffdf00fdffdf004f0fdfb04f0fdfb04f0fdfb444444444444444444444444000000000000000000000000000000000000000000000000
000770000f5ff5f00f5ff5f00f5ff5f000fff5fb00fff5fb00fff5fb444444404444444044444440bbbbbbbbbbbbbbbbbbbbbbbb000000000000000000000000
007557004ffffff44ffffff44ffffff440ffffff40ffffff40ffffff044444440444444404444444bffffffbbbbbbbbbbbbbbbbb000000000000000000000000
07500570bff44ffbbff44ffbbff44ffbb0fffff4b0fffff4b0fffff4b044444bb044444bb044444bbff44ffbbbfffffbbbbbbbbb000000000000000000000000
77700777b6ffff6bb6ffff6bb6ffff6bb6fffffbb6fffffbb6fffffbb044444bb044444bb044444bb6ffff6bbbfffffbbbbbbbbb000000000000000000000000
00700700bbfddfbbbbfddfbbbbfddfbbbb6fffdbbb6fffdbbb6fffdbbb0000bbbb0000bbbb0000bbbbf00fbbbb6ff00bbbbbbbbb000000000000000000000000
00700700bbbffbbbbbbffbbbbbbffbbbbbbffbbbbbbffbbbbbbffbbbbbbffbbbbbbffbbbbbbffbbbbbf00fbbbbbff00bbbbbbbbb000000000000000000000000
00777700bdc55cdbbdc55cdbbdc55cdbbbddcbbbbbbddbbbbbddcbbbbddddddbbddddddbbddddddbbbbffbbbbbbbfffbbbbbbbbb000000000000000000000000
00555500dcc55ccddcc55ccddcc55ccdb1ccdcbbbb1ccdbbb1ccdcbbdccccccddccccccddccccccdbbbbbbbbbbbbbbbbbbbbbbbb000000000000000000000000
00070000c1c66c1cc1c66c1dd1c66c1cb1ccdcbbbb1ccdbbb1ccdcbbc1cccc1cc1cccc1dd1cccc1c000000000000000000000000000000000000000000000000
00070000c1c55c1cc1c55c1dd1c55c1cb1ccdcbbbb1ccdbbb1ccdcbbc1cccc1cc1cccc1dd1cccc1c000000000000000000000000000000000000000000000000
00070000c1c55c1ccc155c1dd1c551ccb1ccdcbbbb1ccdbbb1ccdcbbc1cccc1ccc1ccc1dd1ccc1cc000000000000000000000000000000000000000000000000
77707770c1c55c1ccc155c1dd1c551ccb1ccdcbbbb1ccdbbb1ccdcbbc1cccc1ccc1ccc1dd1ccc1cc000000000000000000000000000000000000000000000000
00070000d1cddc1dbc1ddcdbbdcdd1cbb1dddcbbbb1dddbbb1dddcbbd1cccc1dbc1cccdbbdccc1cb000000000000000000000000000000000000000000000000
00070000fe1111efbfe1112bb2111efbbbff11bbbb2ff1bbbbff11bbfe1111efbfe1112bb2111efb000000000000000000000000000000000000000000000000
00070000bf1111fbbff111ebbe111ffbbbfe11bbbb2fe1bbbbfe11bbbf1111fbbff111ebbe111ffb000000000000000000000000000000000000000000000000
00000000bb1121bbbb1121bbbb1121bbbb2111bbbb2111bbbb2111bbbb1211bbbb1211bbbb1211bb000000000000000000000000000000000000000000000000
00777700bb1121bbbb1121bbbb1121bbbb1111bbbb2111bbbb2111bbbb1211bbbb1211bbbb1211bb000000000000000000000000000000000000000000000000
00755700bb1121bbbb1121bbbb1121bbbb1111bbbb2111bbbb2111bbbb1211bbbb1211bbbb1211bb000000000000000000000000000000000000000000000000
00700700bb1121bbbb1121bbbb1121bbbb1112bbbb2111bbbb21111bbb1211bbbb1211bbbb1211bb000000000000000000000000000000000000000000000000
77700777bb1121bbbb1121bbbb1121bbbb1112bbbb2111bbbb22111bbb1211bbbb1211bbbb1211bb000000000000000000000000000000000000000000000000
57500575bb1121bbbb1121bbbb1121bbb111122bbb2111bbb222111bbb1211bbbb121cbbbbc211bb000000000000000000000000000000000000000000000000
05700750bb1121bbbb1121bbbb1121bbc111222bbb2111bbb22211ccbb1211bbbb12cc7bb7cc11bb000000000000000000000000000000000000000000000000
00577500bbccccbbbb77c77bb77c77bb7ccc222bbbccccbbb222cc77bbccccbbbbcc677bb776ccbb000000000000000000000000000000000000000000000000
00055000b776677bbbbb677bb776bbbbb7776666bb6777bbb66677bbb776677bbb77bbbbbbbb77bb000000000000000000000000000000000000000000000000
__label__
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
fffffffffffffffffffffffff9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9ffffffffffffffffffffffff
ffffffffffffffffffffffff9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9fffffffffffffffffffffffff
fffffffffffffffffffffffffeeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9ffffffffffffffffffffffff
ffffffffffffffffffffffff9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fefffffffffffffffffffffffff
fffffffffffffffffffffffff9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeeffffffffffffffffffffffff
ffffffffffffffffffffffff9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eeeffffffffffffffffffffffff
fffffffffffffffffffffffff9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeeffffffffffffffffffffffff
ffffffffffffffffffffffff9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fefffffffffffffffffffffffff
fffffffffffffffffffffffff9e9f9f97755555555555577f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9ffffffffffffffffffffffff
ffffffffffffffffffffffff9eee9f9f70700000000007079eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9fffffffffffffffffffffffff
fffffffffffffffffffffffffeeef9f97007000000007007feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9ffffffffffffffffffffffff
ffffffffffffffffffffffff9fef9fef70006000000600079fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fefffffffffffffffffffffffff
fffffffffffffffffffffffff9f9feee7000600000060007f9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeeffffffffffffffffffffffff
ffffffffffffffffffffffff9f9f9eee70006000000600079f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eeeffffffffffffffffffffffff
fffffffffffffffffffffffff9f9feee7000600000060007f9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeeffffffffffffffffffffffff
ffffffffffffffffffffffff9f9f9fef77776000494449779f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fefffffffffffffffffffffffff
ffffffff00000000fffffffff9e9f9f97006600494444497f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9ffffffff00000000ffffffff
ffffffff00000000ffffffff9eee9f9f70606004944000479eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9fffffffff00000000ffffffff
ffffffff00000000fffffffffeeef9f970506000440fff07feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9ffffffff00000000ffffffff
ffffffff00000000ffffffff9fef9fef700060004f0f9f079fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fefffff7fff00000000ffffffff
ffffffff00000000fffffffff9f9feee700500000fff5f07f9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeeffff7fff00000000ffffffff
ffffffff00000000ffffffff9f9f9eee705000040ffffff79f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eeeffff7fff00000000ffffffff
ffffffff00000000fffffffff9f9feee750000000fffff47f9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef777f77700000000ffffffff
ffffffff00000000ffffffff9f9f9fef555555556fffff559f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fefffff7fff00000000ffffffff
ffffffff00000000ffffffff999999999999999996fffd9999999999ffffffffffffffffffffffff999999999999999999999999ffff7fff00000000ffffffff
ffffffff00000000ffffffff555555555555555555ff555555555555555555555555555555555555555555555555555555555555ffff7fff00000000ffffffff
ffffffff00000000ffffffff444444444444444444dd4444444444440dd6dd6dd6dd6dd6d6dd6d50444444444444444444444444ffffffff00000000ffffffff
ffffffff00000000ffffffffffff4fffffff4ffff1ccdfffffff4fff0dd6dd6dd6dd6dd6d6dd6d50ffff4fffffff4fffffff4fff22ffffff00000000ffffffff
ffffffff00000000ffffffff444949444449494441ccd94444494944066666666666666666666650444949444449494444494940020fffff00000000ffffffff
ffffffff00000000ffffffff444949444449494441ccd944444949440d6dd6dd6dd6dd6ddd6dd650444949444449494444494942302fffff00000000ffffffff
ffffffff00000000ffffffff444949444449494441ccd944444949440d6dd6dd6dd6dd6ddd6dd65044494944444949444449494b33bfffff00000000ffffffff
ffffffff00000000ffffffff444949444449494441ccd94444494944066666666666666666666650444949444449494444494942bb2fffff00000000ffffffff
ffffffff00000000ffffffff444949444449494441ddd944444949440dd6dd600000000056dd6d50444949444449494444494942222fffff00000000ffffffff
ffffffff00000000ffffffff444949444449494442ff1944444949440dd6dd650000000056dd6d50444949444449494444494942bb2fffff00000000ffffffff
ffffffff00000000ffffffff444949444449494442fe19444449494406666665000000005666665044494944444949444449492b33b2ffff00000000ffffffff
ffffffff00000000ffffffff444949444449494442111944444949440d6dd6d500a0a0005d6dd650444949444449494444494922bb22ffff00000000ffffffff
ffffffff00000000ffffffff444949444449494442111944444949440d6dd6d500aaaa005d6dd6504449494444494944444949222222ffff00000000ffffffff
ffffffff00000000ffffffff444949444449494442111944444949440666666500a9aa00566666504449494444494944444949222222ffff00000000ffffffff
ffffffff00000000ffffffff999949999999499992111999999949990dd6dd6500a99a0056dd6d50999949999999499999994922bb22ffff00000000ffffffff
ffffffff00000000ffffffff444444444444444442111444444444440dd6dd650044440056dd6d5044444444444444444444442b33b2ffff00000000ffffffff
ffffffff00000000ffffff555555555555555555521115555555555555555555555555555555555555555555555555555555522b33b22fff00000000ffffffff
ffffffff00000000ffff555555555555555555555211155555555555555555555555555555555555555555555555555555555222bb222fff00000000ffffffff
ffffffff00000000ff55555555555555555555555cccc55555555555555555555555555555555555555555555555555555555222222225ff00000000ffffffff
ffffffff5555555555555555555555555555555556777555555555555555555555555555555555555555555555555555555552222222255555555555ffffffff
ffffffff555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555bbbbbbbb55555555555ffffffff
ffffffff5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555ffffffff
ffffffff5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555ffffffff
ffffffff5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555ffffffff
ffffff55555555555557655555555555555555553333333333333333333333333333333333333333333333335555555555555555555555555555555555ffffff
ffff555555555555555765555555555555553333333333333333333333333333333333333333333333333333333355555555555556666775555555555555ffff
ff555555555555555bbbb775555555555533333333333333333333333333333333333333333333333333333333333355555555557555555755555555555555ff
5555555555555555bbb7777855555555533333333333333333333333333333333333333333333333333333333333333555555555d776666d5555555555555555
55555555555555555777778555555555533333333333333333333333333333333333333333333333333333333333333555555555567665055555555555555555
55555555555555555777888555555555553333333333333333333333333333333333333333333333333333333333335555555555567665055555555555555555
55555555555555555550055555555555555533333333333333333333333333333333333333333333333333333333555555555555567665055555555555555555
55555555555555555550055555555555555555553333333333333333333333333333333333333333333333335555555555555555557665555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000c0c0ccc0c000c0c00000ccc00cc00000ccc0c0c0ccc0ccc0c000ccc00000ccc0ccc0cc00ccc0ccc0ccc0c000ccc00000000000000000000
00000000000000000c0c0c0c0c000cc0000000c00c0c00000c0c0c0c0c0c0c0c0c000cc0000000c00cc00c0c00c00c0c0c000c000cc000000000000000000000
00000000000000000ccc0ccc0c000c0c000000c00c0c00000ccc0c0c0cc00ccc0c000c00000000c00c000c0c00c00ccc0c000c000c0000000000000000000000
00000000000000000ccc0c0c0ccc0c0c000000c00cc000000c0000cc0c0c0c000ccc0ccc000000c00ccc0c0c00c00c0c0ccc0ccc0ccc00000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
0cc0ccc0ccc0cc0000000000ccc0ccc00cc0c0c00000c0c0ccc00000ccc0c0c00cc0c0c000000000000001111111111011111111110111111111101111111111
c1c0c1c0c110c1c000000000c1c01c10c110c0c00000c0c0c1c00000c1c0c0c0c110c0c0000000cc000001111111111011111111110111111111101111111111
c0c0ccc0cc00c0c000000000ccc00c00c000cc10ccc0c0c0ccc00000ccc0c0c0ccc0ccc000000c11c00001111111111011111111110111111111101111111111
c0c0c110c100c0c000000000c1100c00c000c1c01110c0c0c1100000c110c0c011c0c1c00000c1001c0001111111111011111111110111111111101111111111
cc10c000ccc0c0c000000000c000ccc01cc0c0c000001cc0c0000000c0001cc0cc10c0c0000ccc00ccc001111111111011111111110111111111101111111111
11001000111010100000000010001110011010100000011010000000100001101100101000000c00c00001111111111011111111110111111111101111111111
00000000000000000000000000000000000000000000000000000000000000000000000000000c00c00001111111111011111111110111111111101111111111
00000000000000000000000000000000000000000000000000000000000000000000000000000cccc00001111111111011111111110111111111101111111111
0cc0c0000cc00cc0ccc00000c0000cc00cc0c0c00000ccc0ccc00000ccc0c0c0c000c00000000111100001111111111011111111110111111111101111111111
c110c000c1c0c110c1100000c000c1c0c1c0c0c00000c1c01c100000c1c0c0c0c000c00000000000000001111111111011111111110111111111101111111111
c000c000c0c0ccc0cc000000c000c0c0c0c0cc10ccc0ccc00c000000ccc0c0c0c000c00000000000000000000000000000000000000000000000000000000000
c000c000c0c011c0c1000000c000c0c0c0c0c1c01110c1c00c000000c110c0c0c000c00000000000000000000000000000000000000000000000000000000000
1cc0ccc0cc10cc10ccc00000ccc0cc10cc10c0c00000c0c00c000000c0001cc0ccc0ccc000000000000001111111111011111111110111111111101111111111
01101110110011001110000011101100110010100000101001000000100001101110111000000cccc00001111111111011111111110111111111101111111111
00000000000000000000000000000000000000000000000000000000000000000000000000000c11c00001111111111011111111110111111111101111111111
00000000000000000000000000000000000000000000000000000000000000000000000000000c00c00001111111111011111111110111111111101111111111
0cc0ccc0c0c0ccc000000000aaa0aaa0a000a0a00000aaa00aa00000c0c00cc0ccc00000000ccc00ccc001111111111011111111110111111111101111111111
c1101c10c0c0c110000000001a10a1a0a000a0a000001a10a1a00000c0c0c110c11000000001c1001c1001111111111011111111110111111111101111111111
c0000c00c0c0cc00000000000a00aaa0a000aa10aaa00a00a0a00000c0c0ccc0cc00000000001c00c10001111111111011111111110111111111101111111111
c0c00c00ccc0c100000000000a00a1a0a000a1a011100a00a0a00000c0c011c0c1000000000001cc100001111111111011111111110111111111101111111111
ccc0ccc01c10ccc0000000000a00a0a0aaa0a0a000000a00aa1000001cc0cc10ccc0000000000011000001111111111011111111110111111111101111111111
11101110010011100000000001001010111010100000010011000000011011001110000000000000000001111111111011111111110111111111101111111111
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

__gff__
0001010100010100000000010000000000010101010101000000000100000000000101010101010101000000000000000001010101010100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
__map__
0707070808080808080808080807070707070717171717171717171717070707171717080808080808080808081717170707071717171717171717171707070717171708080808080808080808171717070707171717171717171717170707071717170808080808080808080817171707070717171717171717171717070707
0707070800000808080808080807070707070717171717171717171717070707171717080808080808080808081717170707071717171717171717171707070717171708080808080808080808171717070707171717171717171717170707071717170808080808080808080817171707070717171717171717171717070707
0707070800000808080808080807000707000717171717171717171717070007170017080808080808080808081700170700071717171717171717171707000717001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007
0707076060606061626360606007000707000717171717171717171717070007170017080808080808080808081700170700071717171717171717171707000717001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007
0707077070707071727370707007000707000717171717171717171717070007170017080808080808080808081700170700071717171717171717171707000717001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007
0727113131313131313131313121010707011131313131313131313131210107170212323232323232323232322202170701113131313131313131313121010717021232323232323232323232220217070111313131313131313131312101071702123232323232323232323222021707011131313131313131313131210107
1131313125151515151515353131312111313131313131313131313131313121123232323232323232323232323232221131313131313131313131313131312112323232323232323232323232323222113131313131313131313131313131211232323232323232323232323232322211313131313131313131313131313121
3131313131313131313131313131313131313131313131313131313131313131323232323232323232323232323232323131313131313131313131313131313132323232323232323232323232323232313131313131313131313131313131313232323232323232323232323232323231313131313131313131313131313131
0707071717171717171717171707070717171708080808080808080808171717070707171717171717171717170707071717170808080808080808080817171707070717171717171717171717070707171717080808080808080808081717170707071717171717171717171707070717171708080808080808080808171717
0707071717171717171717171707070717171708080808080808080808171717070707171717171717171717170707071717170808080808080808080817171707070717171717171717171717070707171717080808080808080808081717170707071717171717171717171707070717171708080808080808080808171717
0700071717171717171717171707000717001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007170017080808080808080808081700170700071717171717171717171707000717001708080808080808080808170017
0700071717171717171717171707000717001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007170017080808080808080808081700170700071717171717171717171707000717001708080808080808080808170017
0700071717171717171717171707000717001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007170017080808080808080808081700170700071717171717171717171707000717001708080808080808080808170017
0701113131313131313131313121010717021232323232323232323232220217070111313131313131313131312101071702123232323232323232323222021707011131313131313131313131210107170212323232323232323232322202170701113131313131313131313121010717021232323232323232323232220217
1131313131313131313131313131312112323232323232323232323232323222113131313131313131313131313131211232323232323232323232323232322211313131313131313131313131313121123232323232323232323232323232221131313131313131313131313131312112323232323232323232323232323222
3131313131313131313131313131313132323232323232323232323232323232313131313131313131313131313131313232323232323232323232323232323231313131313131313131313131313131323232323232323232323232323232323131313131313131313131313131313132323232323232323232323232323232
0000000000000000002000000000002007070717171717171717171717070707070707080808080808614858485863080808080808070707000000000000000017171708080808080808080808171717070707171717171717171717170707071717170808080808080808080817171707070717171717171717171717070707
0020000000000000000000000010000007070717171717171717171717070707070707080808080808715848584873080808080808070707000000000000000017171708080808080808080808171717070707171717171717171717170707071717170808080808080808080817171707070717171717171717171717070707
0000002000000000000000000000000007000717171717171717171717070007070007080808000808714858485873080800080808070007000000000000000017001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007
0000000000000000000000000000000007000717171717171717171717070007070007626262006262716667666773626200626262070007000000000000000017001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007
0000000000000000000000000000000007000717171717171717171717070007070007747474007474717677767773747400747474070007000000000000000017001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007
0000000000000000000000000000200007011131313131313131313131210107070111313131313131313131313131313131313131210107000000000000000017021232323232323232323232220217070111313131313131313131312101071702123232323232323232323222021707011131313131313131313131210107
0000000000100000002000000000000011313131313131313131313131313121113131313131312515151515151515353131313131313121000000000000000012323232323232323232323232323222113131313131313131313131313131211232323232323232323232323232322211313131313131313131313131313121
2000000000000000000020000000000031313131313131313131313131313131312f2f2f2f2f2f2f2f2f3131312f2f2f2f2f2f2f2f2f2f2f000000000000000032323232323232323232323232323232313131313131313131313131313131313232323232323232323232323232323231313131313131313131313131313131
000000100000200000001f0061626262626262626262626262626263001f0010070707080808080808080808080808080808080808070707070707405040504050405040504050405040504050070707171717090909090909090909090909090909090909171717000000100000616262626262626262626262626200000010
002000000000001000001f2071447144714473004e71447344734473001f200007070708080808080808080808080808080808080807070707070750405040504050405040504050405040504007070717171709090909090909444444450909090909090917171700200000002071447474744473b271447474447400002000
200000000020000000201f0071647164716473005e71647364736473201f000007000708080808004e080808080808080808080808070007070707405040504050405040504050404e00504050070707170017656565656565655464645565656565656565170017182f2f2f2f2f71647474746473b27164747464742f2f2f2f
000020000000000020001f0062626262626273006e71626262626263001f002007000760606060005e606060606060606060606060070007070707606060606060606162636060607e00606060070707170017666766676667666766676667666766676667170017183f3f3f3f3f61747474747473b27174747474743f3f3f3f
303030303030303030301b3131313131313131253531313131313131310b303007000770707070006e707070707070707070707070070007070707707070707070707172737070706e00707070070707170017767776777677767776777677767776777677170017151515151515151515151515151515151515151515151515
151515151515151515151818181818181818343434341818181818181818151507011131313131313131313131313131313131313121010707271131313131313131313131313131313131313121280717021232323232323232323232323232323232323222021715153c191919191919191919343434191919193d15151515
1515151515151515151515151515151515143434343424151515151515151515113131313131312515151515151515353131313131313121113131313131312515151515151515353131313131313121123232323232323232323232323232323232323232323222153c3937373737378e373737373737373737373a3d151515
15151515151515151515151515151515151515151515151515151515151515153131313131313131313131313131313131313131313131313131313131313131313131313131313131313131313131313232323232323232323232323232323232323232323232323c393737373737373737373737373737373737373a3d1515

*/

}
