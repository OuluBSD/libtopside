#ifndef _Adventure_Program_h_
#define _Adventure_Program_h_


namespace Adventure {

/*struct ScriptObject {
	
};

using SObj = ScriptObject;
*/


struct Room {
	
};

using SObj = EscValue;
using StrMap = VectorMap<String,String>;
using StrVec = Vector<String>;

typedef enum {
	
} SceneType;

typedef enum {
	STATE_OPEN,
	STATE_CLOSED,
} StateType;

typedef enum {
	FACE_NULL,
	FACE_FRONT,
	FACE_LEFT,
	FACE_BACK,
	FACE_RIGHT,
} FaceDir;

struct Sentence : Moveable<Sentence> {
	int num;
	String msg;
	Vector<String> lines;
	int char_width;
};

struct Dialog {
	Array<Sentence> sentences;
	int col = 0;
	int hlcol = 0;
	bool visible = 0;
	
	
	Sentence& Add();
	void Clear();
	
};

struct Script {
	SceneType type;
	//Thread thrd;
	Callback override_;
	SObj* paused_cam_following = 0;
	
	void Clear() {TODO}
	
};


struct Program {
	typedef Program CLASSNAME;
	
	
	bool show_debuginfo = true;
	bool show_collision = true;
	bool show_pathfinding = true;
	bool show_depth = true;
	bool enable_diag_squeeze = false;
	
	typedef enum {
		V_DEFAULT,
		
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
	
	
	Array<Script> global_scripts;	// table of scripts that are at game-level (background)
	Array<Script> local_scripts;	// table of scripts that are actively running
	Array<Script> cutscenes;		// table of scripts for (the active Cutscene(s)
	Array<Script> draw_zplanes;		// table of tables for (each of the (8) zplanes for (drawing depth
	
	
	Script* cutscene_curr = 0;
	
	
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
	
	SObj* room_curr = 0;
	Sentence* selected_sentence = 0;
	Dialog dialog_curr;
	
	SObj* selected_actor = 0;
	
	int fade_iris = 0;
	int cutscene_cooloff = 0;
	Script* fade_script = 0;
	
	SObj* talking_curr = 0;
	SObj* talking_actor = 0;
	
	/*ui_arrows = {
		{ spr = ui_uparrowspr, x = 75, y = stage_top + 60 },
		{ spr = ui_dnarrowspr, x = 75, y = stage_top + 72 }
	};*/
	
	Verb verb_curr;
	bool executing_cmd = false;
	bool is_mouse_clicked = false;
	
	
	void ResetUI();
	void StartupScript();
	void Shake(bool enabled);
	Verb FindDefaultVerb(SObj& obj);
	void UnsupportedAction(Verb verb, SObj& obj1, SObj& obj2);
	void CameraAt(const Point& val);
	void CameraFollow(SObj& actor);
	void CamScript0();
	void CamScript1();
	void CameraPanTo(SObj& val);
	void WaitForCamera();
	bool ScriptRunning(Script& script);
	void Cutscene(SceneType type, Callback func_cutscene, Callback func_override);
	void DialogAdd(const String& msg);
	void DialogStart(int col, int hlcol);
	void DialogHide();
	void DialogClear();
	void DialogEnd();
	void DialogSet(StrVec& msg_table);
	Point GetUsePos(SObj& obj);
	void DoAnim(Thing& thing, const String& param1, int& param2);
	void OpenDoor(SObj& door_obj1, SObj* door_obj2);
	void CloseDoor(SObj& door_obj1, SObj* door_obj2);
	void ComeOutDoor(SObj& from_door, SObj& to_door, bool fade_effect);
	void Fades(int fade, int dir);
	void ChangeRoom(SObj& new_room, bool fade);
	void ValidVerb(Verb verb, SObj& object);
	void PickupObj(SObj& obj, SObj* actor);
	void StartScript(Callback func, bool bg, String noun1="", String noun2="");
	void StopScript(Script& func);
	void BreakTime(int jiffies=0);
	void WaitForMessage();
	void SayLine(SObj& actor, String msg, bool use_caps=false, float duration=1.0f);
	void SayLine(String msg);
	void StopTalking();
	void PrintLine(String msg, int x, int y, int col, int align, bool use_caps, float duration, bool big_font);
	void PutAt(SObj& obj, int x, int y, SObj* room);
	void StopActor(SObj& actor);
	void WalkTo(SObj& actor, int x, int y);
	void WaitForActor(SObj* actor);
	double Proximity(SObj& obj1, SObj& obj2);
	Verb GetVerb(SObj& obj);
	void ClearCurrCmd();
	void Update60();
	void Draw();
	void UpdateMouseClickState();
	void PlayerControl();
	void InputButtonPressed(int button_index);
	void CheckCollisions();
	void ResetZPlanes();
	void RecalcZPlane(SObj& obj);
	void RoomDraw();
	void ReplaceColors(SObj& obj);
	void DrawObject(SObj& obj);
	void DrawActor(SObj& actor);
	void DrawCommand();
	void DrawTalking();
	void DrawUI();
	void DrawDialog();
	void DrawCursor();
	void DrawSprite(int n, int x, int y, int w, int h, bool transcol, bool flip_x, bool flip_y, int scale);
	void SetTransCol(int transcol);
	void InitGame();
	void UpdateScripts(Vector<String>& scripts);
	bool IsTable(SObj& t);
	Point CenterCamera(const Point& val);
	Point CenterCamera(SObj& val);
	Point GetCellPos(SObj& obj);
	bool IsCellWalkable(int celx, int cely);
	void CreateTextLines(String msg, int max_line_length, Vector<String>& lines);
	int GetLongestLineSize(const Vector<String>& lines);
	bool HasFlag(SObj& obj, String value);
	void RecalculateBounds(SObj& obj, int w, int h, int cam_off_x, int cam_off_y);
	void Animate(SObj& obj);
	void ShowError(String msg);
	void ExplodeData(SObj& obj);
	void OutlineText(String str, int x, int y, int c0, int c1, bool use_caps, bool big_font);
	bool IsCursorColliding(SObj& obj);
	String SmallCaps(const String& s);
	void FadePalette(float perc);
	String Autotype(const String& str_value);
	
	
	void Run();
	
	SObj* FindRoom(const String& name);
	EscValue& Classes(SObj& s);
	String State(SObj& s);
	String VerbStr(Verb v);
	EscValue& Get(SObj& o, String key);
	SObj* GetInRoom(SObj& o);
	Point GetXY(SObj& o);
	Point GetOffset(SObj& o);
	Size GetSize(SObj& o);
	UsePos GetUsePos(SObj& o);
	FaceDir GetFaceDir(SObj& o);
	StateType GetState(SObj& o);
	String GetFaceString(FaceDir d);
	
	void SetState(SObj& o, StateType s);
	
};


class ProgramDraw : public Ctrl {
	
	
	
	void Paint(Draw& w) override;
	
};


class ProgramApp : public TopWindow {
	ProgramDraw draw;
	Program eng;
	TimeCallback tc;
	
public:
	typedef ProgramApp CLASSNAME;
	
	ProgramApp();
	
	void ProcessScript();
	
	
};

}

#endif
