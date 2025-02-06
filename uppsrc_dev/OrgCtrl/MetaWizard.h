#ifndef _OrgCtrl_MetaWizard_h_
#define _OrgCtrl_MetaWizard_h_


BEGIN_TEXTLIB_NAMESPACE


class MetaWizardView : public NodeViewBase {
	
public:
	typedef MetaWizardView CLASSNAME;
	MetaWizardView();
	
	void Data() override;
	
};

class MetaWizardCtrl : public NodeCtrlBase {
	WithMetaWizard<Ctrl> form;
	
public:
	typedef MetaWizardCtrl CLASSNAME;
	MetaWizardCtrl();
	
	void Data() override;
	void OnValueChange();
	void Do(int fn);
	void ToolMenu(Bar& bar) override;
	
};



END_TEXTLIB_NAMESPACE



#endif
