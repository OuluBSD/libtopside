#ifndef _OrgCtrl_Class_h_
#define _OrgCtrl_Class_h_


BEGIN_TEXTLIB_NAMESPACE


class ClassView : public NodeViewBase {
	
public:
	typedef ClassView CLASSNAME;
	ClassView();
	
	void Data() override;
	
};

class ClassCtrl : public NodeCtrlBase {
	WithClass<Ctrl> form;
	
public:
	typedef ClassCtrl CLASSNAME;
	ClassCtrl();
	
	void Data() override;
	void OnValueChange();
	void Do(int fn);
	void ToolMenu(Bar& bar) override;
	
};



END_TEXTLIB_NAMESPACE



#endif
