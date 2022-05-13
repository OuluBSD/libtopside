#ifndef _CtrlLibAlt_Bar_h_
#define _CtrlLibAlt_Bar_h_


NAMESPACE_UPP




class BarCtrl : public Bar, public CtrlFrame {
	
	
public:
	RTTI_DECL2(BarCtrl, Bar, CtrlFrame)
	BarCtrl();
	
	void Set(Callback1<Bar&> menu);
	
};


class ToolButton : public Ctrl, public Bar::Item {
	using Ctrl::Key;

public:
	RTTI_DECL1(ToolButton, Ctrl)
	ToolButton();
	
	virtual void   Paint(Draw& w) override;
	virtual void   MouseEnter(Point, dword) override;
	virtual void   MouseLeave() override;
	virtual Size   GetMinSize() const override;
	virtual void   LeftDown(Point, dword) override;
	virtual void   LeftRepeat(Point, dword) override;
	virtual void   LeftUp(Point, dword) override;
	virtual bool   HotKey(dword key) override;
	virtual String GetDesc() const override;
	virtual int    OverPaint() const override;

	virtual Bar::Item& Text(const char *text) override;
	virtual Bar::Item& Key(dword key) override;
	virtual Bar::Item& Repeat(bool repeat = true) override;
	virtual Bar::Item& Image(const UPP::Image& img) override;
	virtual Bar::Item& Enable(bool _enable = true) override;
	virtual Bar::Item& Tip(const char *tip) override;
	virtual Bar::Item& Help(const char *help) override;
	virtual Bar::Item& Topic(const char *help) override;
	virtual Bar::Item& Description(const char *desc) override;
	virtual Bar::Item& Radio(bool check) override;
	virtual Bar::Item& Check(bool check) override;
	virtual void       FinalSync() override;

public:
	struct Style : ChStyle<Style> {
		Value look[6];
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
	ToolBar();
	
	virtual bool HotKey(dword key) override;
	virtual void Paint(Draw& w) override;

protected:
	virtual Bar::Item& AddItem(Callback cb) override;
	virtual Bar::Item& AddSubMenu(Callback1<Bar&> proc) override;

public:
	struct Style : ChStyle<Style> {
		ToolButton::Style    buttonstyle;
		Size                 buttonminsize;
		Size                 maxiconsize;
		int                  buttonkind;
		Value               look, arealook;
		SeparatorCtrl::Style breaksep;
		SeparatorCtrl::Style separator;
	};
};


class MenuBar : public BarCtrl {
	
	
public:
	MenuBar();
	
	void   FrameLayout(Rect& r) override;
	void   FrameAddSize(Size& sz) override;
	
	static void Execute(Callback1<Bar&> cb);
	
};

END_UPP_NAMESPACE

#endif
