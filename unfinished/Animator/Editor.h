#ifndef _Animator_Editor_h_
#define _Animator_Editor_h_

NAMESPACE_TOPSIDE_BEGIN


class EditorDraw : public Ctrl {
	Project* proj = 0;
	
	
public:
	typedef EditorDraw CLASSNAME;
	EditorDraw();
	
	void Paint(Draw& d) override;
	
	void SetProject(Project& p);
	
};

class EditorApp : public TopWindow {
	EditorDraw draw;
	Project proj;
	TimeCallback tc;
	
public:
	typedef EditorApp CLASSNAME;
	
	EditorApp();
	
	void ProcessScript();
	
	bool Init() {return proj.Init();}
	
};


NAMESPACE_TOPSIDE_END

#endif
