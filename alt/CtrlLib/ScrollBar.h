#ifndef _CtrlLibAlt_ScrollBar_h_
#define _CtrlLibAlt_ScrollBar_h_

NAMESPACE_UPP


class ScrollBar : public CtrlFrame {
	
	
public:
	RTTI_DECL1(ScrollBar, CtrlFrame)
	
	
	void FrameLayout(Rect& r) override;
	void FrameAddSize(Size& sz) override;
	
	ScrollBar& Vert();
	ScrollBar& Horz();
	ScrollBar& SetLine(int i);
	ScrollBar& SetTotal(int i);
	ScrollBar& SetPage(int i);
	ScrollBar& Set(int i);
	ScrollBar& ScrollInto(int i) {return Set(i);}
	ScrollBar& Wheel(int i);
	bool VertKey(dword key);
	bool HorzKey(dword key);
	
	int Get() const;
	int GetLine() const;
	int GetTotal() const;
	int GetPage() const;
	
	Callback WhenScroll;
	
	
	operator int() const {return Get();}
	
};


END_UPP_NAMESPACE

#endif
