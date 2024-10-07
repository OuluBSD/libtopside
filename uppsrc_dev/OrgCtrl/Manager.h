#ifndef _OrgCtrl_Manager_h_
#define _OrgCtrl_Manager_h_


BEGIN_TEXTLIB_NAMESPACE


class ManagerCtrl : public Ctrl {
	
	
public:
	typedef ManagerCtrl CLASSNAME;
	ManagerCtrl();
	
	void Init();
	void Data();
	void ToolMenu(Bar& bar);
	
	
	
};



END_TEXTLIB_NAMESPACE


#endif
