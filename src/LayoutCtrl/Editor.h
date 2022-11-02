#ifndef _LayoutCtrl_Editor_h_
#define _LayoutCtrl_Editor_h_

NAMESPACE_LAYOUT_BEGIN


class Editor : public ParentCtrl {
	Splitter vsplit;
	DocEdit doc;
	
public:
	typedef Editor CLASSNAME;
	Editor();
	
	
	virtual void SetData(const Value& data);
	
};


NAMESPACE_LAYOUT_END

#endif
