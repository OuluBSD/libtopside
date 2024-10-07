#ifndef _TextCtrl_LeadProfile_h_
#define _TextCtrl_LeadProfile_h_


BEGIN_TEXTLIB_NAMESPACE


class LeadsCtrl;

class ProfileInfoCtrl : public WithProfileInfo<ToolAppCtrl> {
	
	
public:
	typedef ProfileInfoCtrl CLASSNAME;
	ProfileInfoCtrl();
	
	void Data();
	void Clear();
	void OnValueChange();
	
	LeadsCtrl* editor = 0;
	
};


END_TEXTLIB_NAMESPACE


#endif
