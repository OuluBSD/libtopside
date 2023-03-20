#ifndef _GuboLib_Push_h_
#define _GuboLib_Push_h_

NAMESPACE_UPP_BEGIN

#undef Button2
#undef Button3

class Button2 : public Surface {
	Image img;
	String label;
	bool is_pressed = false;
	
	TimeCallback tc;
	
public:
	RTTI_DECL1(Button2, Surface)
	typedef Button2 CLASSNAME;
	Button2();
	
	void SetImage(Image& img);
	
	void Paint(Draw& d) override;
	void LeftDown(Point p, dword keyflags) override;
	void LeftUp(Point p, dword keyflags) override;
	void MouseEnter(Point p, dword keyflags) override;
	void MouseLeave() override;
	void MouseMove(Point content_p, dword keyflags) override;
	
	void Refresh() override {Surface::Refresh();}
	
};

class Button3 : public Gubo {
	
	
public:
	
	void SetImage(const Image&) {}
	
};


NAMESPACE_UPP_END

#endif
