#ifndef _OrgCtrl_Package_h_
#define _OrgCtrl_Package_h_


BEGIN_TEXTLIB_NAMESPACE


class PackageView : public NodeViewBase {
	
public:
	typedef PackageView CLASSNAME;
	PackageView();
	
	void Data() override;
	
};

class PackageCtrl : public NodeCtrlBase {
	WithPackage<Ctrl> form;
	
public:
	typedef PackageCtrl CLASSNAME;
	PackageCtrl();
	
	void Data() override;
	void OnValueChange();
	void Do(int fn);
	void ToolMenu(Bar& bar) override;
	
};



END_TEXTLIB_NAMESPACE



#endif
