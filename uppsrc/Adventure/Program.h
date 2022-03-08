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
typedef ArrayMap<String, EscValue> EscGlobal;


Color GetPicoPalette(PaletteColor idx);

struct Room {
	
};

using SObj = EscValue;
using StrMap = VectorMap<String,String>;
using StrVec = Vector<String>;

Color ReadColor(const SObj& o, EscValue key, Color def);
bool TryReadColor(const SObj& o, EscValue key, Color& c);
bool ReadFlag(const SObj& o, String key);
SObj* ReadKey(SObj& o, String key);
void SrcMapSet(EscValue map, EscValue key, EscValue value);

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
	EscGlobal* global = 0;
	String fn_name;
	EscValue a0, a1;
	One<Esc> esc;
	bool is_esc = false;
	Callback WhenStop;
	
	typedef Script CLASSNAME;
	void Clear();
	Script& Set(Gate0 cb, EscValue a0=EscValue(), EscValue a1=EscValue());
	Script& Set(EscGlobal& g, EscValue *self, EscValue fn, EscValue a0=EscValue(), EscValue a1=EscValue());
	Script& Start();
	Script& Stop();
	void Execute();
	void ProcessEsc();
	bool RunEscSteps();
	
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

struct Program {
	typedef Program CLASSNAME;
	
	
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
		
		V_COUNT,
		
		V_BEGIN = V_OPEN,
		V_END = V_COUNT,
	} Verb;
	
	const char* verbs[(int)V_COUNT] {
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
	
	
	Script* cutscene_curr = 0;
	
	
	Verb verb_default_inventory_index = Verb::V_LOOKAT;
	
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
	Point cam_pan_to_x;
	SObj cam_following_actor;
	Thread thrd;
	
	int stage_top = 16;
	Point cam_x;
	int cam_shake_amount = 0;
	float cursor_x = 63.5;
	float cursor_y = 63.5;
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
	SObj* talking_actor = 0;
	
	PaletteImage ui_arrows[2];
	SObj arrow[2];
	/*ui_arrows = {
		{ spr = ui_uparrowspr, x = 75, y = stage_top + 60 },
		{ spr = ui_dnarrowspr, x = 75, y = stage_top + 72 }
	};*/
	
	Verb hover_curr_default_verb;
	Verb hover_curr_verb;
	
	Verb verb_curr;
	SObj* noun1_curr = 0;
	SObj* noun2_curr = 0;
	SObj* hover_curr_object = 0;
	bool executing_cmd = false;
	bool is_mouse_clicked = false;
	
	int cam_shake_x = 0;
	int cam_shake_y = 0;
	
	
	// Script
	EscGlobal global;
	EscValue game;
	EscValue rooms;
	EscValue room_curr;
	EscValue cutscene_override;
	Script* scr_obj = 0;
	Vector<String> room_names;
	
	int fade_iter = 0;
	
	
	void FindRooms(String name, EscValue v, Vector<String>& names);
public:
	
	Program();
	
	bool ParseGame(String content, String path);
	bool ReadGame();
	EscValue RunLambda1(EscValue* self, const EscValue& l, const EscValue& arg0);
	void GetReference(SObj& o, bool everywhere=false);
	void ProcessEsc();
	void ResetPalette();
	void ResetUI();
	void Shake(bool enabled);
	Verb FindDefaultVerb(SObj& obj);
	void UnsupportedAction(Verb verb, SObj& obj1, SObj& obj2);
	void CameraAt(const Point& val);
	
	
	void EscCameraFollow(EscEscape& e);
	void EscChangeRoom(EscEscape& e);
	void EscSetGlobalGame(EscEscape& e);
	void EscCutscene(EscEscape& e);
	void EscPutAt(EscEscape& e);
	void EscPrintLine(EscEscape& e);
	void EscBreakTime(EscEscape& e);
	void EscSelectActor(EscEscape& e);
	
	void ClearCutsceneOverride();
	void RealizeGame();
	void CameraFollow(SObj actor);
	void ChangeRoom(SObj new_room, SObj fade);
	bool CamScript0();
	bool CamScript1();
	void CameraPanTo(SObj& val);
	void WaitForCamera();
	bool ScriptRunning(Script& script);
	void Cutscene(SceneType type, EscValue* self, EscValue func_cutscene, EscValue func_override);
	void DialogAdd(const String& msg);
	void DialogStart(int col, int hlcol);
	void DialogHide();
	void DialogClear();
	void DialogEnd();
	void DialogSet(StrVec& msg_table);
	Point GetUsePoint(SObj& obj);
	void DoAnim(Thing& thing, const String& param1, int& param2);
	void OpenDoor(SObj& door_obj1, SObj* door_obj2);
	void CloseDoor(SObj& door_obj1, SObj* door_obj2);
	void ComeOutDoor(SObj& from_door, SObj& to_door, bool fade_effect);
	bool Fades(int fade, int dir);
	void ValidVerb(Verb verb, SObj& object);
	void PickupObj(SObj& obj, SObj& actor);
	void StartScript(Gate0 func, bool bg, EscValue noun1=EscValue(), EscValue noun2=EscValue());
	void StartScriptEsc(EscValue* self, EscValue func, bool bg, EscValue noun1=EscValue(), EscValue noun2=EscValue());
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
	void WalkTo(SObj& actor, int x, int y);
	void WaitForActor(SObj& actor);
	double Proximity(SObj& obj1, SObj& obj2);
	Verb GetVerb(SObj& obj);
	String GetVerbString(const Verb& v);
	void ClearCurrCmd();
	void Update60();
	void UpdateMouseClickState();
	void PlayerControl();
	void InputButtonPressed(int button_index);
	void CheckCollisions();
	void ResetZPlanes();
	void RecalcZPlane(SObj& obj);
	void SetTransCol(int transcol);
	bool InitGame();
	void UpdateScripts(Vector<String>& scripts);
	bool IsTable(SObj& t);
	Point CenterCamera(const Point& val);
	Point CenterCamera(SObj& val);
	Point GetCellPos(SObj& obj);
	bool IsCellWalkable(int celx, int cely);
	void CreateTextLines(String msg, int max_line_length, Vector<String>& lines);
	int GetLongestLineSize(const Vector<String>& lines);
	bool HasFlag(const SObj& obj, String key);
	void RecalculateBounds(SObj& obj, int w, int h, int cam_off_x, int cam_off_y);
	void Animate(SObj& obj);
	void ShowError(String msg);
	void ExplodeData(SObj& obj);
	bool IsCursorColliding(SObj& obj);
	String SmallCaps(const String& s);
	String Autotype(const String& str_value);
	
	
	bool Init();
	
	const SObj* FindRoom(const String& name) const;
	const SObj* FindDeep(const String& name) const;
	const SObj* FindDeep(const String& name, const SObj* o) const;
	EscValue Classes(SObj& s);
	String State(SObj& s);
	SObj GetInRoom(SObj& o);
	Point GetXY(SObj& o);
	Point GetOffset(SObj& o);
	Size GetSize(SObj& o);
	UsePos GetUsePos(SObj& o);
	FaceDir GetFaceDir(SObj& o);
	StateType GetState(SObj& o);
	String GetFaceString(FaceDir d);
	SObj GetSelectedActor();
	
	void SetState(SObj& o, StateType s);
	
};


struct ZPlane : Moveable<ZPlane> {
	Vector<SObj*> objs;
	
	
};

class ProgramDraw : public Ctrl {
	Vector<ZPlane> draw_zplanes; // table of tables for (each of the (8) zplanes for (drawing depth
	
	Image gfx, lbl, gff;
	Vector<uint16> map;
	Size map_sz;
	
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
	void LoadBuiltinGfxStr(const char* s, Image& out);
	void LoadBuiltinGfxStr(const char* s, Vector<uint16>& out, Size& sz);
	
public:
	
	ProgramDraw();

	void SetProgram(Program& p) {this->p = &p;}
	
	void Paint(Draw& d) override;
	
	void PaintLog(Draw& d, String s, int x, int y, PaletteColor clr);
	
	
	void PaintRoom(Draw& d);
	void PaintTalking(Draw& d);
	void OutlineText(Draw& d, String str, int x, int y, int c0, int c1, bool use_caps, bool big_font);
	void PaintObject(SObj& obj);
	void PaintActor(SObj& actor);
	void PaintCommand(Draw& d);
	void PaintUI(Draw& d);
	void PaintDialog(Draw& d);
	void PaintCursor(Draw& d);
	void PaintSprite(Draw& d, const Image& src, PaletteImage n, int x, int y, bool flip_x, bool flip_y, int scale);
	void PaintSprite(Draw& d, const Image& src, PaletteImage n, int x, int y, int w, int h, bool transcol, bool flip_x, bool flip_y, int scale);
	void PaintMap(Draw& d, int x, int y, int dst_x, int dst_y, int w, int h);
	
	void SetPalette(int idx, PaletteColor clr);
	void ResetPalette();
	void ReplaceColors(const SObj& o);
	void FadePalette(float perc);
	
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
