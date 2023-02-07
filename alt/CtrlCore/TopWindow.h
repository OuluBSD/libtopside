#ifndef _CtrlCoreAlt_TopWindow_h_
#define _CtrlCoreAlt_TopWindow_h_


NAMESPACE_UPP



class TopWindow :
	public Ctrl,
	public Absolute2DProxy
{
	
public:
	RTTI_DECL2(TopWindow, Ctrl, Absolute2DProxy)
	TopWindow();
	virtual ~TopWindow() {}
	
	void CreateGeom2DComponent();
	void UpdateFromTransform2D();
	void RunInMachine();
	
	//Ctrl* GetCtrl() override;
	
	
};


END_UPP_NAMESPACE


#endif
