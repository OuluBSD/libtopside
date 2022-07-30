#ifndef _LocalCtrl_TimelineCtrl_h_
#define _LocalCtrl_TimelineCtrl_h_

NAMESPACE_TOPSIDE_BEGIN


class TimelineCtrl : public Ctrl {
	
	
public:
	typedef TimelineCtrl CLASSNAME;
	TimelineCtrl();
	
	void Paint(Draw& d) override;
	void LeftDown(Point p, dword keyflags) override;
	void RightDown(Point p, dword keyflags) override;
	void MouseWheel(Point p, int zdelta, dword keyflags) override;
	
	
};


NAMESPACE_TOPSIDE_END

#endif
