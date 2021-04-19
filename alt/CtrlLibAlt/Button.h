#ifndef _CtrlLibAlt_Button_h_
#define _CtrlLibAlt_Button_h_


NAMESPACE_UPP


class Button : public Ctrl {
	Image img;
	String label;
	bool is_pressed = false;
	
	TimeCallback tc;
	
public:
	typedef Button CLASSNAME;
	Button();
	
	void SetImage(Image& img);
	
	virtual void Paint(Draw& d);
	virtual void LeftDown(Point p, dword keyflags) {is_pressed = true; Refresh();}
	virtual void LeftUp(Point p, dword keyflags) {WhenAction(); is_pressed = false; Refresh();}
	virtual void MouseEnter(Point p, dword keyflags) {Refresh();}
	virtual void MouseLeave() {is_pressed = false; Refresh();}
	
	void PostRefresh() {PostCallback(THISBACK(Refresh));}
	void Refresh() {Ctrl::Refresh();}
};


class ButtonOption : public Ctrl {
	
	
public:
	typedef ButtonOption CLASSNAME;
	ButtonOption();
	
	void Tip(String s);
	void SetImage(Image i);
	void Set(bool b);
	
};

END_UPP_NAMESPACE


#endif
