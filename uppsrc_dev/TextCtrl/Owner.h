#ifndef _TextCtrl_Owner_h_
#define _TextCtrl_Owner_h_


BEGIN_TEXTLIB_NAMESPACE


class LeadsCtrl;

class OwnerInfoCtrl : public WithOwnerInfo<ToolAppCtrl> {
	
	
public:
	typedef OwnerInfoCtrl CLASSNAME;
	OwnerInfoCtrl();
	
	void Data();
	void Clear();
	void OnValueChange();
	
	LeadsCtrl* editor = 0;
	
};


END_TEXTLIB_NAMESPACE


#endif
