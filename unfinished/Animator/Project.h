#ifndef _Animator_Project_h_
#define _Animator_Project_h_

NAMESPACE_TOPSIDE_BEGIN


class Project {
	
protected:
	friend class EditorDraw;
	
	HiAnimContext ctx;
	
	
	HiAnimProgram& StartScript(Gate0 func, bool bg, HiValue noun1, HiValue noun2);
	HiAnimProgram& StartScriptHi(HiValue* self, HiValue script_name, bool bg, HiValue noun1, HiValue noun2);
	void HiPrintLine(HiEscape& e);
	bool InitGame();
	void SetSelectedActor(HiValue o);
	HiValue GetSelectedActor();
	void AddTextObject(HiEscape& e, String txt, int x, int y, int col, int align, bool use_caps, float duration, bool big_font);
	
	
public:
	typedef Project CLASSNAME;
	Project();
	
	
	bool Init();
	void Update();
	
	
};


NAMESPACE_TOPSIDE_END

#endif
