#ifndef _Adventure_Engine_h_
#define _Adventure_Engine_h_


namespace Adventure {

struct Program {
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
	};
	
	
	int verb_default_inventory_index = V_LOOKAT;
	
	Color verb_maincol;
	Color verb_hovcol;
	Color verb_shadcol;
	Color verb_defcol;
	
	Image ui_cursorspr;
	Image ui_uparrowspr;
	Image ui_dnarrowspr;
	
	int cam_shake_amount = 0;
	bool cam_shake = false;

	
	
	void reset_ui();
	void startup_script();
	void shake(bool enabled);
	Verb find_default_verb(Object& obj);
	void unsupported_action(Verb verb, Object& obj1, Object& obj2);
	
	
};

}

#endif
