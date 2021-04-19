#ifndef _CtrlLibAlt_Bar_h_
#define _CtrlLibAlt_Bar_h_


NAMESPACE_UPP




class BarCtrl : public Bar, public CtrlFrame {
	
	
public:
	
};


class ToolButton : public Ctrl, public Bar::Item {
	using Ctrl::Key;

public:
	virtual void   Paint(Draw& w);
	virtual void   MouseEnter(Point, dword);
	virtual void   MouseLeave();
	virtual Size   GetMinSize() const;
	virtual void   LeftDown(Point, dword);
	virtual void   LeftRepeat(Point, dword);
	virtual void   LeftUp(Point, dword);
	virtual bool   HotKey(dword key);
	virtual String GetDesc() const;
	virtual int    OverPaint() const;

	virtual Bar::Item& Text(const char *text);
	virtual Bar::Item& Key(dword key);
	virtual Bar::Item& Repeat(bool repeat = true);
	virtual Bar::Item& Image(const UPP::Image& img);
	virtual Bar::Item& Enable(bool _enable = true);
	virtual Bar::Item& Tip(const char *tip);
	virtual Bar::Item& Help(const char *help);
	virtual Bar::Item& Topic(const char *help);
	virtual Bar::Item& Description(const char *desc);
	virtual Bar::Item& Radio(bool check);
	virtual Bar::Item& Check(bool check);
	virtual void       FinalSync();

public:
	struct Style : ChStyle<Style> {
		Value  look[6];
		Font   font;
		Color  textcolor[6];
		bool   light[6];
		int    contrast[6];
		Point  offset[6];
		int    overpaint;
	};
};

class ToolBar : public BarCtrl {
public:
	virtual bool HotKey(dword key);
	virtual void Paint(Draw& w);

protected:
	virtual Item& AddItem(Callback  cb);
	virtual Item& AddSubMenu(Callback1<Bar&> proc);

public:
	struct Style : ChStyle<Style> {
		ToolButton::Style    buttonstyle;
		Size                 buttonminsize;
		Size                 maxiconsize;
		int                  buttonkind;
		Value                look, arealook;
		SeparatorCtrl::Style breaksep;
		SeparatorCtrl::Style separator;
	};
};


class MenuBar : public BarCtrl {
	
	
public:
	
	static void Execute(Callback1<Bar&> cb);
	
};

END_UPP_NAMESPACE

#endif
