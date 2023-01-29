#ifndef _CtrlLibAlt_Button_h_
#define _CtrlLibAlt_Button_h_


NAMESPACE_UPP


class Button : public Ctrl {
	Image img;
	String label;
	bool is_pressed = false;
	
	TimeCallback tc;
	
public:
	RTTI_DECL1(Button, Ctrl)
	typedef Button CLASSNAME;
	Button();
	
	void SetImage(Image& img);
	
	void Paint(Draw& d) override;
	void LeftDown(Point p, dword keyflags) override;
	void LeftUp(Point p, dword keyflags) override;
	void MouseEnter(Point p, dword keyflags) override;
	void MouseLeave() override;
	void MouseMove(Point content_p, dword keyflags) override;
	
	void Refresh() override {Ctrl::Refresh();}
	
};


class ButtonOption : public Ctrl {
	
	
public:
	RTTI_DECL1(ButtonOption, Ctrl)
	typedef ButtonOption CLASSNAME;
	ButtonOption();
	
	void Tip(String s);
	void SetImage(Image i);
	void Set(bool b);
	
};

END_UPP_NAMESPACE


#endif
