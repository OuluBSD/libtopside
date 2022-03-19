#ifndef _Adventure_Program_h_
#define _Adventure_Program_h_


namespace Adventure {

#define PALETTE_SIZE 16

/*struct ScriptObject {
	
};

using SObj = ScriptObject;
*/

typedef int PaletteColor;
typedef int PaletteImage;
typedef ArrayMap<String, HiValue> HiGlobal;


Color GetPicoPalette(PaletteColor idx);

struct Room {
	
};

using SObj = HiValue;
using StrMap = VectorMap<String,String>;
using StrVec = Vector<String>;

Color ReadColor(const SObj& o, HiValue key, Color def);
bool TryReadColor(const SObj& o, HiValue key, Color& c);
bool ReadFlag(const SObj& o, String key);
bool HasArrayValue(SObj arr, SObj value);

typedef enum {
	SCENE_NULL,
	SCENE_NO_VERBS,
	SCENE_QUICK_CUT,
	SCENE_CUT_NO_FOLLOW // no verbs & no follow,
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

typedef enum {
	BTN_LEFT,
	BTN_RIGHT,
	BTN_UP,
	BTN_DOWN,
	BTN_O,
	BTN_X,
	
	BTN_COUNT,
} GamepadButton;

typedef enum {
	MBMASK_LEFT = 0x1,
	MBMASK_RIGHT = 0x2,
	MBMASK_MIDDLE = 0x4,
} MouseButtonMask;

struct Bounds {
	int cam_off_x, x1, y1, x, y;
};

struct Sentence : Moveable<Sentence> {
	int num;
	String msg;
	Vector<String> lines;
	int char_width;
	Bounds bounds;
};

struct Dialog {
	Array<Sentence> sentences;
	int col = 0;
	int hlcol = 0;
	bool visible = 0;
	bool enabled = false;
	
	
	Sentence& Add();
	void Clear();
	
	operator bool() const {return enabled;}
	
};

struct Script {
	int op_limit = 1000000;
	static const int op_limit_at_once = 100;
	
	SceneType type = SCENE_NULL;
	bool running = false;
	Gate0 fn;
	TimeCallback tc;
	SObj* paused_cam_following = 0;
	dword flags = 0;
	HiGlobal* global = 0;
	String fn_name;
	HiValue a0, a1;
	One<Hi> esc;
	bool is_esc = false;
	Callback1<Script*> WhenStop;
	
	typedef Script CLASSNAME;
	void Clear();
	Script& Set(Gate0 cb, HiValue a0=HiValue(), HiValue a1=HiValue());
	Script& Set(HiGlobal& g, HiValue *self, HiValue fn, HiValue a0=HiValue(), HiValue a1=HiValue());
	Script& Start();
	Script& Stop();
	void Execute();
	bool ProcessHi();
	bool RunHiSteps();
	
};

struct TalkingState {
	Vector<String> msg_lines;
	int x = 0;
	int y = 0;
	int col = 0;
	int align = 0;
	int time_left = 0;
	int char_width = 0;
	bool use_caps = 0;
	bool big_font = 0;
	bool enabled = false;
	
	operator bool() const {return enabled;}
	
};

struct ZPlane : Moveable<ZPlane> {
	Vector<HiValue> objs;
	
	
};

class Program {
	
protected:
	friend class ProgramDraw;
	
	typedef Program CLASSNAME;
	
	
	bool show_collision = true;
	bool show_pathfinding = true;
	bool show_depth = true;
	bool enable_diag_squeeze = false;
	
	/*typedef enum {
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
		
		V_COUNT,
		
		V_BEGIN = V_OPEN,
		V_END = V_COUNT,
	} Verb;*/
	
	/*const char* verbs[(int)V_COUNT] {
		"<null>",
		
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
	};*/
	
	typedef enum {
		POS_NULL,
		POS_LEFT,
		POS_RIGHT,
		POS_ABOVE,
		POS_CENTER,
		POS_INFRONT
	} UsePos;
	
	/*struct Thing {
		int x = 0;
		int y = 0;
		int face_dir = 0;
		bool flip = 0;
		String curr_anim;
		int anim_pos = 0;
		int tmr = 0;
		
	};*/
	
	
	Array<Script> global_scripts;	// table of scripts that are at game-level (background)
	Array<Script> local_scripts;	// table of scripts that are actively running
	Array<Script> cutscenes;		// table of scripts for (the active Cutscene(s)
	
	
	Script* cutscene_curr = 0;
	
	
	int verb_default = 4;
	
	PaletteColor verb_maincol;
	PaletteColor verb_hovcol;
	PaletteColor verb_shadcol;
	PaletteColor verb_defcol;
	PaletteColor ui_cursor_cols[6];
	static const int ui_cursor_cols_len = 6;
	
	PaletteImage ui_cursorspr;
	PaletteImage ui_uparrowspr;
	PaletteImage ui_dnarrowspr;
	
	bool cam_shake = false;
	Point cam_pan_to;
	SObj cam_following_actor;
	Thread thrd;
	
	int stage_top = 16;
	Point cam;
	float cam_shake_amount = 0;
	float cursor_x = 63.5;
	float cursor_y = 63.5;
	float last_cursor_x = 0;
	float last_cursor_y = 0;
	int cursor_tmr = 0;
	int cursor_colpos = 1;
	
	Script cam_script;
	
	String cmd_curr;
	Sentence* selected_sentence = 0;
	Dialog dialog_curr;
	
	SObj hover_curr_arrow;
	
	int fade_iris = 0;
	int cutscene_cooloff = 0;
	Script* fade_script = 0;
	
	TalkingState talking_curr;
	SObj talking_actor;
	
	HiValue ui_arrows;
	SObj arrow[2];
	
	HiValue hover_curr_default_verb;
	HiValue hover_curr_verb;
	Sentence* hover_curr_sentence = 0;
	
	HiValue verb_curr;
	SObj noun1_curr;
	SObj noun2_curr;
	SObj hover_curr_object;
	bool executing_cmd = false;
	bool is_mouse_clicked = false;
	
	float cam_shake_x = 0;
	float cam_shake_y = 0;
	
	bool pressed[BTN_COUNT];
	dword mouse_pressed = 0;
	
	// Script
	HiGlobal global;
	HiValue game;
	HiValue rooms;
	HiValue cutscene_override;
	HiValue verbs;
	HiValue V_DEFAULT, V_USE, V_GIVE, V_PUSH, V_PULL, V_WALKTO, V_PICKUP, V_LOOKAT, V_OPEN, V_CLOSE, V_TALKTO;
	HiValue room_curr;
	Script* scr_obj = 0;
	int V_COUNT = 0;
	Index<String> verb_idx;
	
	int fade_iter = 0;
	
	Vector<ZPlane> draw_zplanes; // table of tables for (each of the (8) zplanes for (drawing depth
	Vector<Point> path;
	
	
	Vector<uint16> map, gff;
	Size map_sz, gff_sz;
	
	
	AnimScene scene;
	
	
public:
	
	Program();
	
	bool ParseGame(String content, String path);
	bool ReadGame();
	HiValue RunLambda1(HiValue* self, const HiValue& l, const HiValue& arg0);
	//void GetReference(SObj& o, bool everywhere=false);
	void ProcessHi();
	void ResetPalette();
	void ResetUI();
	void Shake(bool enabled);
	HiValue FindDefaultVerb(SObj& obj);
	void UnsupportedAction(HiValue verb, SObj& obj1, SObj& obj2);
	void CameraAt(const Point& val);
	
	
	void HiCameraFollow(HiEscape& e);
	void HiChangeRoom(HiEscape& e);
	void HiSetGlobalGame(HiEscape& e);
	void HiCutscene(HiEscape& e);
	void HiPutAt(HiEscape& e);
	void HiPrintLine(HiEscape& e);
	void HiBreakTime(HiEscape& e);
	void HiSelectActor(HiEscape& e);
	void HiTodo(HiEscape& e);
	
	void ClearCutsceneOverride(Script* s);
	void RealizeGame();
	void CameraFollow(SObj actor);
	void ChangeRoom(SObj new_room, SObj fade);
	bool CamScript0();
	bool CamScript1();
	bool VerbScript(HiValue vc2);
	bool WalkScript();
	void CameraPanTo(SObj& val);
	void WaitForCamera();
	bool ScriptRunning(Script& script);
	void Cutscene(SceneType type, HiValue* self, HiValue func_cutscene, HiValue func_override);
	void DialogAdd(const String& msg);
	void DialogStart(int col, int hlcol);
	void DialogHide();
	void DialogClear();
	void DialogEnd();
	void DialogSet(StrVec& msg_table);
	Point GetUsePoint(SObj& obj);
	void DoAnim(SObj thing, const String& param1, int& param2);
	void OpenDoor(SObj door_obj1, SObj door_obj2);
	void CloseDoor(SObj door_obj1, SObj door_obj2);
	void ComeOutDoor(SObj from_door, SObj to_door, bool fade_effect);
	bool Fades(int fade, int dir);
	bool IsValidVerb(HiValue verb, SObj object);
	void PickupObj(SObj& obj, SObj& actor);
	void StartScript(Gate0 func, bool bg, HiValue noun1=HiValue(), HiValue noun2=HiValue());
	void StartScriptHi(HiValue* self, HiValue func, bool bg, HiValue noun1=HiValue(), HiValue noun2=HiValue());
	void StopScript(Script& func);
	void RemoveStoppedScripts();
	void BreakTime(int jiffies=0);
	void WaitForMessage();
	void SayLine(SObj& actor, String msg, bool use_caps=false, float duration=1.0f);
	void SayLine(String msg);
	void StopTalking();
	void PrintLine(String msg, int x, int y, int col, int align, bool use_caps, float duration, bool big_font);
	void PutAt(SObj obj, int x, int y, SObj room);
	void StopActor(SObj& actor);
	void WalkTo(SObj a, int x, int y);
	void WaitForActor(SObj& actor);
	double Proximity(SObj& obj1, SObj& obj2);
	HiValue GetVerb(int idx);
	String GetVerbString(int idx);
	String GetVerbString(SObj v);
	void ClearCurrCmd();
	void Update();
	void UpdateMouseClickState();
	void PlayerControl();
	void InputButtonPressed(dword button_index);
	void CheckCollisions();
	void ResetZPlanes();
	void RecalcZPlane(SObj& obj);
	bool InitGame();
	void UpdateScripts(Array<Script>& scripts);
	void RemoveStoppedScripts(Array<Script>& scripts);
	bool IsTable(SObj& t);
	Point CenterCamera(const Point& val);
	Point CenterCamera(SObj& val);
	Point GetCellPos(SObj& obj);
	bool IsCellWalkable(int celx, int cely);
	void CreateTextLines(String msg, int max_line_length, Vector<String>& lines);
	int GetLongestLineSize(const Vector<String>& lines);
	bool HasFlag(const SObj& obj, String key);
	void RecalculateBounds(SObj obj, int w, int h, int cam_off_x, int cam_off_y);
	void ShowError(String msg);
	void ExplodeData(SObj& obj);
	bool IsCursorColliding(const SObj& obj);
	bool IsCursorColliding(const Sentence& obj);
	String SmallCaps(const String& s);
	String Autotype(const String& str_value);
	void FindPath(Point start, Point goal, Vector<Point>& pt);
	double GetHeuristic(Point chk, Point goal);
	
	bool Init();
	
	const SObj* FindRoom(const String& name) const;
	const SObj* FindDeep(const String& name) const;
	const SObj* FindDeep(const String& name, const SObj* o) const;
	HiValue Classes(SObj s);
	String State(SObj& s);
	//String GetInRoomString(SObj& o);
	SObj GetInRoom(SObj o);
	Point GetXY(SObj o);
	Point GetOffset(SObj o);
	Size GetSize(SObj o);
	UsePos GetUsePos(SObj o);
	static FaceDir GetFaceDir(SObj o);
	StateType GetState(SObj o);
	String GetFaceString(FaceDir d);
	SObj GetSelectedActor();
	dword GetMouseButtonMask() const {return mouse_pressed;}
	bool IsPressed(GamepadButton b) const;
	bool IsMousePressed(MouseButtonMask m) const;
	bool IsAnyMousePressed() const {return mouse_pressed;}
	bool IsMouseLeftPressed() const {return IsMousePressed(MBMASK_LEFT);}
	bool IsMouseRightPressed() const {return IsMousePressed(MBMASK_RIGHT);}
	
	void SetState(SObj o, StateType s);
	void SetSelectedActor(SObj o);
	
	//static void LoadBuiltinGfxStr(const char* s, Image& out);
	static void LoadBuiltinGfxStr(const char* s, Vector<byte>& out, Size& sz);
	static void LoadBuiltinGfxStr(const char* s, Vector<uint16>& out, Size& sz);
	
};


class ProgramDraw : public Ctrl {
	
	Image gfx, lbl;
	Vector<byte> gfx_data, lbl_data;
	Size gfx_sz, lbl_sz;
	Size canvas_sz;
	double size_mul = 1.0;
	
	Font fnt;
	PaletteColor dyn_palette[PALETTE_SIZE];
	Color palette[PALETTE_SIZE];
	Program* p = 0;
	bool show_debuginfo = true;
	
	
	
	Color GetPaletteColor(int i) const {
		ASSERT(i >= 0 && i < PALETTE_SIZE);
		i = dyn_palette[i];
		ASSERT(i >= 0 && i < PALETTE_SIZE);
		return palette[i];
	}
	
	void LoadBuiltinGfx();
	void Animate(SObj obj);
	void GetPaletteImage(const Vector<byte>& src, Size src_sz, Image& out);
	
public:
	
	ProgramDraw();

	void SetProgram(Program& p) {this->p = &p;}
	
	void Paint(Draw& d) override;
	
	void PaintLog(Draw& d, String s, int x, int y, PaletteColor clr);
	
	
	void PaintRoom(Draw& d);
	void PaintTalking(Draw& d);
	void OutlineText(Draw& d, String str, int x, int y, int c0, int c1, bool use_caps, bool big_font);
	void PaintObject(Draw& d, SObj obj);
	void PaintActor(Draw& d, SObj actor);
	void PaintCommand(Draw& d);
	void PaintUI(Draw& d);
	void PaintDialog(Draw& d);
	void PaintCursor(Draw& d);
	void PaintSprite(Draw& d, const Image& src, PaletteImage n, int x, int y, bool flip_x, bool flip_y, int scale);
	void PaintSprite(Draw& d, const Image& src, PaletteImage n, int x, int y, int w, int h, bool transcol, bool flip_x, bool flip_y, int scale);
	void PaintMap(Draw& d, int x, int y, int dst_x, int dst_y, int w, int h);
	
	void SetPalette(int idx, PaletteColor clr);
	void ResetPalette();
	void ReplaceColors(SObj o);
	void FadePalette(float perc);
	
	
	void MouseMove(Point p, dword keyflags) override;
	void LeftDown(Point p, dword keyflags) override;
	void LeftUp(Point p, dword keyflags) override;
	void RightDouble(Point p, dword keyflags) override;
	void RightUp(Point p, dword keyflags) override;
	bool Key(dword key, int count) override;
	
	// TODO remove
	void SetTransCol(int transcol);
	
};


class ProgramApp : public TopWindow {
	ProgramDraw draw;
	Program prog;
	TimeCallback tc;
	
public:
	typedef ProgramApp CLASSNAME;
	
	ProgramApp();
	
	void ProcessScript();
	
	bool Init() {return prog.Init();}
	
};

}

#endif
