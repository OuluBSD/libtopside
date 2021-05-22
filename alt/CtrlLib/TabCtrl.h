#ifndef _CtrlLibAlt_TabCtrl_h_
#define _CtrlLibAlt_TabCtrl_h_

NAMESPACE_UPP


class TabCtrl : public Ctrl {
	
	
public:
	RTTI_DECL1(TabCtrl, Ctrl)
	TabCtrl();
	
	void Add(Ctrl& c, String title);
	
	
};


END_UPP_NAMESPACE

#endif
