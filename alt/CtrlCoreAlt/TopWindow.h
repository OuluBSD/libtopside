#ifndef _CtrlCoreAlt_TopWindow_h_
#define _CtrlCoreAlt_TopWindow_h_




NAMESPACE_UPP


class TopWindow : public Ctrl {
	String title;
	
public:
	TopWindow();
	virtual ~TopWindow() {}
	//void Init(SysWindow* sw, int id);
	
	virtual void Start() {}
	virtual void CloseWindow() {}
	virtual String GetTitle() {return title;}
	virtual void RefreshData() {};
	virtual void FocusEvent() {}
	virtual void SetFrameRect(const Rect& r);
	void Title(const String& title);
	int Run(bool appmodal=false);
	
	#include GUIPLATFORM_TOPWINDOW_DECLS_INCLUDE
	
};


END_UPP_NAMESPACE



#endif
