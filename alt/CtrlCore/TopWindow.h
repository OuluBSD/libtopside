#ifndef _CtrlCoreAlt_TopWindow_h_
#define _CtrlCoreAlt_TopWindow_h_


NAMESPACE_UPP



class TopWindow :
	public Ctrl,
	public Absolute2DProxy
{
	
public:
	RTTI_DECL1(TopWindow, Ctrl)
	TopWindow();
	virtual ~TopWindow() {}
	
	void CreateGeom2DComponent();
	void UpdateFromTransform2D();
	
	void SetFrameRect(const Rect& r) override;
	Ctrl* GetCtrl() override;
	
	
};


END_UPP_NAMESPACE


#endif
