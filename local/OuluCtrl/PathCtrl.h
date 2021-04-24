#ifndef _OuluCtrl_PathCtrl_h_
#define _OuluCtrl_PathCtrl_h_

NAMESPACE_OULU_BEGIN

class ToolBarBg : public Ctrl {
	
public:
	ToolBarBg();
	
	virtual void Paint(Draw& d);
	
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

NAMESPACE_OULU_END

#endif
