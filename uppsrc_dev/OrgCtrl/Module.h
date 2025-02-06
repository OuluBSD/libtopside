#ifndef _OrgCtrl_Module_h_
#define _OrgCtrl_Module_h_


BEGIN_TEXTLIB_NAMESPACE


class ModuleView : public NodeViewBase {
	
public:
	typedef ModuleView CLASSNAME;
	ModuleView();
	
	void Data() override;
	
};

class ModuleCtrl : public NodeCtrlBase {
	
public:
	typedef ModuleCtrl CLASSNAME;
	ModuleCtrl();
	
	void Data() override;
	void OnValueChange();
	void Do(int fn);
	void ToolMenu(Bar& bar) override;
	
};



END_TEXTLIB_NAMESPACE



#endif
