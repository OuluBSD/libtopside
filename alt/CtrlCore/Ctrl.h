#ifndef _CtrlCore_Ctrl_h_
#define _CtrlCore_Ctrl_h_


NAMESPACE_UPP



class GuiLock {};


bool GetMouseLeft();
Point GetMousePos();

class Ctrl;

class CtrlFrame :
	RTTIBase
{
	
public:
	RTTI_DECL0(CtrlFrame)
	
	CtrlFrame() {}
	virtual ~CtrlFrame() {}

};


struct KeyInfo {
	const char *name;
	dword key[4];
};


class Bar :
	RTTIBase
{
public:
	struct Item {
		Item() {}
		virtual ~Item(){}
	};
	
private:
	
	
	
public:
	RTTI_DECL0(Bar)
	typedef Bar CLASSNAME;
	Bar();
	
	Bar& Add(String title, Callback cb);
	Bar& Separator();
	
	virtual void   Paint(Draw& w) {}
	virtual int    OverPaint() const {return 0;}
	virtual bool   HotKey(dword key) {return false;}
	virtual Bar::Item& AddItem(Callback cb) {NEVER()}
	virtual Bar::Item& AddSubMenu(Callback1<Bar&> proc) {NEVER()}
	
};


class TopWindow;

class Ctrl :
	public Pte<Ctrl>,
	RTTIBase
{
	
public:
	RTTI_DECL0(Ctrl)
	
	enum {
		MOUSEMOVE,
		MOUSEWHEEL,
		LEFTDOUBLE,
		RIGHTDOUBLE,
		MIDDLEDOUBLE,
		LEFTDOWN,
		RIGHTDOWN,
		MIDDLEDOWN,
		LEFTUP,
		RIGHTUP,
		MIDDLEUP,
	};
	
public:
	typedef Ctrl CLASSNAME;
	Ctrl() {}
	virtual ~Ctrl() {}
	
	
	virtual void   Paint(Draw& w);
	virtual void   MouseEnter(Point p, dword keyflags) {}
	virtual void   MouseMove(Point p, dword keyflags) {}
	virtual void   LeftDown(Point p, dword keyflags) {}
	virtual void   LeftDouble(Point p, dword keyflags) {}
	virtual void   LeftTriple(Point p, dword keyflags) {}
	virtual void   LeftRepeat(Point p, dword keyflags) {}
	virtual void   LeftDrag(Point p, dword keyflags) {}
	virtual void   LeftHold(Point p, dword keyflags) {}
	virtual void   LeftUp(Point p, dword keyflags) {}
	virtual void   RightDown(Point p, dword keyflags) {}
	virtual void   RightDouble(Point p, dword keyflags) {}
	virtual void   RightTriple(Point p, dword keyflags) {}
	virtual void   RightRepeat(Point p, dword keyflags) {}
	virtual void   RightDrag(Point p, dword keyflags) {}
	virtual void   RightHold(Point p, dword keyflags) {}
	virtual void   RightUp(Point p, dword keyflags) {}
	virtual void   MiddleDown(Point p, dword keyflags) {}
	virtual void   MiddleDouble(Point p, dword keyflags) {}
	virtual void   MiddleTriple(Point p, dword keyflags) {}
	virtual void   MiddleRepeat(Point p, dword keyflags) {}
	virtual void   MiddleDrag(Point p, dword keyflags) {}
	virtual void   MiddleHold(Point p, dword keyflags) {}
	virtual void   MiddleUp(Point p, dword keyflags) {}
	virtual void   MouseWheel(Point p, int zdelta, dword keyflags) {}
	virtual void   MouseLeave() {}
	virtual bool   Key(dword key, int count);
	void        Refresh();
	
	// VirtualGui
	void        Invalidate();
	static bool ProcessEvents(double dt, bool *quit);
	static bool ProcessEvent(bool *quit);
	static void TimerProc(double dt);
	static void DoMouseFB(int event, Point p, int zdelta = 0);
	static bool DoKeyFB(dword key, int cnt);
	static void PaintAll();
	static void EndSession();
	
};

inline String GetKeyDesc(dword key) {return "";}


class TopWindow :
	public Ctrl
{
	
public:
	RTTI_DECL1(TopWindow, Ctrl)
	TopWindow() {}
	virtual ~TopWindow() {}
	
	TopWindow& Title(const char *s) {return *this;}
	
};


END_UPP_NAMESPACE

#endif
