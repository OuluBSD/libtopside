#ifndef _TopTool_EntityInfoCtrl_h_
#define _TopTool_EntityInfoCtrl_h_


BEGIN_TEXTLIB_NAMESPACE


class ToolEditor;


class EntityInfoCtrl : public WithEntityInfo<ToolAppCtrl> {
	
	
public:
	typedef EntityInfoCtrl CLASSNAME;
	EntityInfoCtrl();
	
	void Data();
	void Clear();
	void OnValueChange();
	
	
};


END_TEXTLIB_NAMESPACE


#endif
