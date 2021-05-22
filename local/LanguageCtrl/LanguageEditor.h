#ifndef _LayoutCtrl_LanguageEditor_h_
#define _LayoutCtrl_LanguageEditor_h_


NAMESPACE_LANGUAGE_BEGIN

struct LENode {
	static const int FONTH = 12;
	static const int ROWH = 16;
	static const int HDIV = 5;
	
	
	Array<LENode> sub;
	Node* n = NULL;
	
	String txt;
	int width = 0, max_depth = 0;
	
	void SetNode(Node& n);
	void Paint(Draw& d, int x, int y);
	LENode* FindByCursor(int x, int y);
};


class LanguageEditor : public Ctrl {
	
protected:
	friend class LanguageEditorCtrl;
	
	LENode root;
	Mutex lock;
	Image graph;
	int loff = 0, toff = 0;
	
	
public:
	RTTI_DECL1(LanguageEditor, Ctrl)
	typedef LanguageEditor CLASSNAME;
	LanguageEditor();
	
	void Clear();
	void SetNode(Node& n);
	
	virtual void Paint(Draw& d);
	virtual void Layout();
	virtual void LeftDown(Point p, dword keyflags);
	
	Callback WhenRuleEditActivate;
};

class LanguageEditorCtrl : public ParentCtrl {
	Splitter vsplit, hsplit;
	ArrayCtrl sentlist;
	LanguageEditor edit;
	
	Node n, orig;
	Mutex lock;
	int node_id = -1;
	
	Vector<bool> sent_ok;
	
	
public:
	typedef LanguageEditorCtrl CLASSNAME;
	LanguageEditorCtrl();
	
	void SelectSentence();
	virtual void SetData(const Value& data);
	void SetNode(const Node& n);
	
	void Data();
	void Process();
	void ProcessReady();
	
	void FetchRules();
	void PutRule(ConllRule& rule);
	void RuleMenu(Bar& bar);
};



NAMESPACE_LANGUAGE_END

#endif
