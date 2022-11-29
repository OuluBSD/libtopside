#ifndef _CtrlCoreAlt_TopWindow_h_
#define _CtrlCoreAlt_TopWindow_h_


NAMESPACE_UPP



class TopWindow :
	public Ctrl,
	public AbsoluteWindowProxy
{
	
public:
	RTTI_DECL1(TopWindow, Ctrl)
	TopWindow();
	virtual ~TopWindow() {}
	
	void CreateCoreWindow();
	void UpdateFromTransform2D();
	
	void SetFrameRect(const Rect& r) override;
	Ctrl* GetWindowCtrl() override;
	
	
};


END_UPP_NAMESPACE


#endif
