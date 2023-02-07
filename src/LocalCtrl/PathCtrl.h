#ifndef _LocalCtrl_PathCtrl_h_
#define _LocalCtrl_PathCtrl_h_

NAMESPACE_TOPSIDE_BEGIN

class ToolBarBg : public Ctrl {
	
public:
	RTTI_DECL1_(ToolBarBg, Ctrl)
	ToolBarBg();
	
	virtual void Paint(Draw& d) override;
	
};

class PathCtrl : public ParentCtrl {
	
	Array<Button> path_buttons;
	Button edit;
	EditString path;
	ToolBarBg bg;
	int is_edit;
	String dir_seps;
	void RefreshEdit();
	
public:
	RTTI_DECL1_(PathCtrl, ParentCtrl)
	typedef PathCtrl CLASSNAME;
	PathCtrl();
	
	void SetEdit(bool b=false);
	void SetPath(String path);
	bool IsEdit() {return is_edit;}
	void SwitchMode() {SetEdit(!is_edit);}
	void SetDirectory(String path) {WhenPath(path);}
	void SetEditPath();
	void SetDirectorySeparator(String s) {dir_seps = s;}
	
	Callback1<String> WhenPath;
	
};

NAMESPACE_TOPSIDE_END

#endif
