#ifndef _OrgCtrl_Meta_h_
#define _OrgCtrl_Meta_h_


BEGIN_TEXTLIB_NAMESPACE


class MetaView : public NodeViewBase {
	
public:
	typedef MetaView CLASSNAME;
	MetaView();
	
	void Data() override;
	
};

class MetaCtrl : public NodeCtrlBase {
	WithMeta<Ctrl> form;
	
public:
	typedef MetaCtrl CLASSNAME;
	MetaCtrl();
	
	void Data() override;
	void OnValueChange();
	void Do(int fn);
	void ToolMenu(Bar& bar) override;
	
};



END_TEXTLIB_NAMESPACE



#endif
