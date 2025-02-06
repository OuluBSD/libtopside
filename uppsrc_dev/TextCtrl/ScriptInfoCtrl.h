#ifndef _TextCtrl_ScriptInfoCtrl_h_
#define _TextCtrl_ScriptInfoCtrl_h_


BEGIN_TEXTLIB_NAMESPACE


class ToolEditor;

class ScriptInfoCtrl : public WithScriptInfo<ToolAppCtrl> {
	
	
public:
	typedef ScriptInfoCtrl CLASSNAME;
	ScriptInfoCtrl();
	
	void Data() override;
	void Clear();
	void OnValueChange();
	void ToolMenu(Bar& bar) override;
	
};


END_TEXTLIB_NAMESPACE


#endif
