#ifndef _OrgCtrl_Directory_h_
#define _OrgCtrl_Directory_h_


BEGIN_TEXTLIB_NAMESPACE


class DirectoryView : public NodeViewBase {
	
public:
	typedef DirectoryView CLASSNAME;
	DirectoryView();
	
	void Data() override;
	
};

class DirectoryCtrl : public NodeCtrlBase {
	
public:
	typedef DirectoryCtrl CLASSNAME;
	DirectoryCtrl();
	
	void Data() override;
	void OnValueChange();
	void Do(int fn);
	void ToolMenu(Bar& bar) override;
	
};



END_TEXTLIB_NAMESPACE


#endif
