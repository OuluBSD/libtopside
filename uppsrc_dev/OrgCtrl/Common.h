#ifndef _OrgCtrl_Common_h_
#define _OrgCtrl_Common_h_


BEGIN_TEXTLIB_NAMESPACE


class OrganizationCtrl;


struct NodeViewBase {
	virtual ~NodeViewBase() {}
	
	virtual void Data() = 0;
	
	void SetNode(Node* n) {node = n;}
	void Init(Node& n, OrganizationCtrl* org) {node = &n; this->org = org;}
	
	Node* node = 0;
	OrganizationCtrl* org = 0;
};

struct NodeCtrlBase : public Ctrl {
	virtual ~NodeCtrlBase() {}
	
	virtual void Data() = 0;
	virtual void ToolMenu(Bar& bar) {bar.Add("", AppImg::placeholder16(), Callback());}
	
	NodeViewBase* view = 0;
	OrganizationCtrl* org = 0;
	
};


Value& GetAddMapValue(Value& v, const String& key, const Value& value=Value());


Value GetMapValue(const Value& v, const String& key);
void SetMapValue(Value& v, const String& key, const Value& value);
void SetArrayValue(Value& v, int i, const Value& value);
void SetArrayMapValue(Value& v, int i, const String& key, const Value& value);


END_TEXTLIB_NAMESPACE


#endif
