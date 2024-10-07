#ifndef _OrgCtrl_Services_h_
#define _OrgCtrl_Services_h_


BEGIN_TEXTLIB_NAMESPACE


class ServicesCtrl : public Ctrl {
	Splitter hsplit, vsplit;
	Ctrl placeholder;
	ArrayCtrl src, mode;
	
	enum {
		SRC_TWITTER,
		SRC_BLOGGER,
		SRC_FORUM,
		SRC_YOUTUBE,
	};
	
	
public:
	typedef ServicesCtrl CLASSNAME;
	ServicesCtrl();
	
	void Init();
	void Data();
	void ToolMenu(Bar& bar);
	
	
	
	
};



END_TEXTLIB_NAMESPACE


#endif
