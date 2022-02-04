#ifndef _Adventure_Engine_h_
#define _Adventure_Engine_h_


namespace Adventure {

struct Script {
	
	
	
	void Clear() {TODO}
	
};

/*struct ScriptObject {
	
};

using SObj = ScriptObject;
*/

struct Door {
	
};

struct Room {
	
};

using SObj = EscValue;
using StrMap = VectorMap<String,String>;
using StrVec = Vector<String>;

typedef enum {
	
} SceneType;

struct CutScene {
	
};

struct Program {
	typedef Program CLASSNAME;
	
	
	bool show_debuginfo = true;
	bool show_collision = true;
	bool show_pathfinding = true;
	bool show_depth = true;
	bool enable_diag_squeeze = false;
	
	typedef enum {
		V_OPEN,
		V_CLOSE,
		V_GIVE,
		V_PICKUP,
		V_LOOKAT,
		V_TALKTO,
		V_PUSH,
		V_PULL,
		V_USE,
		V_WALKTO,
		
		V_COUNT
	} Verb;
	
	const char* verbs[V_COUNT] {
		"open",
		"close",
		"give",
		"pickup",
		"look at",
		"talk to",
		"push",
		"pull",
		"use",
		"walk to",
	};
	
	typedef enum {
		POS_NULL,
		POS_LEFT,
		POS_RIGHT,
		POS_ABOVE,
		POS_CENTER,
		POS_INFRONT
	} UsePos;
	
	struct Thing {
		int x = 0;
		int y = 0;
		int face_dir = 0;
		bool flip = 0;
		String curr_anim;
		int anim_pos = 0;
		int tmr = 0;
		
	};
	
	
	Vector<Script> global_scripts;	// table of scripts that are at game-level (background)
	Vector<Script> local_scripts;	// table of scripts that are actively running
	Vector<Script> cutscenes;		// table of scripts for (the active cutscene(s)
	Vector<Script> draw_zplanes;	// table of tables for (each of the (8) zplanes for (drawing depth
	CutScene cut;
	
	CutScene* cutscene_curr = 0;
	
	
	int verb_default_inventory_index = V_LOOKAT;
	
	Color verb_maincol;
	Color verb_hovcol;
	Color verb_shadcol;
	Color verb_defcol;
	
	Image ui_cursorspr;
	Image ui_uparrowspr;
	Image ui_dnarrowspr;
	
	bool cam_shake = false;

	Point cam_pan_to_x;
	SObj* cam_following_actor = 0;
	Thread thrd;
	
	int stage_top = 16;
	Point cam_x;
	int cam_shake_amount = 0;
	float cursor_x = 63.5;
	float cursor_y = 63.5;
	int cursor_tmr = 0;
	int cursor_colpos = 1;
	
	Script cam_script;
	
	Room* room_curr = 0;
	
	/*ui_arrows = {
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
	};*/
	
	void reset_ui();
	void startup_script();
	void shake(bool enabled);
	Verb find_default_verb(SObj& obj);
	void unsupported_action(Verb verb, SObj& obj1, SObj& obj2);
	void camera_at(const Point& val);
	void camera_follow(SObj& actor);
	void cam_script0();
	void cam_script1();
	void camera_pan_to(SObj& val);
	void wait_for_camera();
	bool script_running(Script& script);
	void cutscene(SceneType type, Callback func_cutscene, Callback func_override);
	void dialog_add(const String& msg);
	void dialog_start(int col, int hlcol);
	void dialog_hide();
	void dialog_clear();
	void dialog_end();
	Point get_use_pos(SObj& obj);
	void _anim(Thing& thing, const String& param1, int& param2);
	void open_door(SObj& door_obj1, SObj& door_obj2);
	void close_door(SObj& door_obj1, SObj& door_obj2);
	void come_out_door(Door& from_door, Door& to_door, bool fade_effect);
	void fades(int fade, int dir);
	void change_room(Room& new_room, bool fade);
	void valid_verb(Verb verb, SObj& object);
	void pickup_obj(SObj& obj, SObj& actor);
	void start_script(Callback func, bool bg, String noun1="", String noun2="");
	void stop_script(Script& func);
	void break_time(int jiffies=0);
	void wait_for_message();
	void say_line(SObj& actor, String msg, bool use_caps=false, float duration=1.0f);
	void stop_talking();
	void print_line(String msg, int x, int y, int col, int align, bool use_caps, float duration, bool big_font);
	void put_at(SObj& obj, int x, int y, Room* room);
	void stop_actor(SObj& actor);
	void walk_to(SObj& actor, int x, int y);
	void wait_for_actor(SObj& actor);
	void proximity(SObj& obj1, SObj& obj2);
	const StrMap& get_keys(SObj& obj);
	Verb get_verb(SObj& obj);
	void clear_curr_cmd();
	void _update60();
	void _draw();
	void update_mouse_click_state();
	void playercontrol();
	void input_button_pressed(int button_index);
	void check_collisions();
	void reset_zplanes();
	void recalc_zplane(SObj& obj);
	void room_draw();
	void replace_colors(SObj& obj);
	void object_draw(SObj& obj);
	void actor_draw(SObj& actor);
	void command_draw();
	void talking_draw();
	void ui_draw();
	void dialog_draw();
	void cursor_draw();
	void sprdraw(int n, int x, int y, int w, int h, bool transcol, bool flip_x, bool flip_y, int scale);
	void set_trans_col(int transcol);
	void game_init();
	void update_scripts(Vector<String>& scripts);
	void istable(SObj& t);
	Point _center_camera(const Point& val);
	Point _center_camera(SObj& val);
	Point getcellpos(SObj& obj);
	bool is_cell_walkable(int celx, int cely);
	Vector<String> create_text_lines(String msg, int max_line_length);
	int longest_line_size(const Vector<String>& lines);
	bool has_flag(SObj& obj, String value);
	void recalc_bounds(SObj& obj, int w, int h, int cam_off_x, int cam_off_y);
	void animate(SObj& obj);
	void show_error(String msg);
	void explode_data(SObj& obj);
	void outline_text(String str, int x, int y, int c0, int c1, bool use_caps, bool big_font);
	bool iscursorcolliding(SObj& obj);
	String smallcaps(const String& s);
	
	void dialog_set(StrVec& msg_table);
	
	void Run();
	
	Room* FindRoom(const String& name);
	EscValue& Classes(SObj& s);
	String State(SObj& s);
	String VerbStr(Verb v);
	EscValue& Get(SObj& o, String key);
	Room* InRoom(SObj& o);
	Point GetXY(SObj& o);
	
	void add(Vector<Script>& cutscenes, CutScene& sc);
	
};

}

#endif
