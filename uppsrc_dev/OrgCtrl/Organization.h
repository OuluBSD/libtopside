#ifndef _OrgCtrl_Organization_h_
#define _OrgCtrl_Organization_h_


BEGIN_TEXTLIB_NAMESPACE


class OrganizationCtrl : public Ctrl {
	ArrayCtrl pkgs;
	TreeCtrl nodes;
	Splitter hsplit, vsplit;
	Ctrl main;
	
	VectorMap<int, Node*> node_ptrs;
	
	enum {
		ADD_PKG,
		REM_PKG,
		REM_NODE,
	};
	
	NodeType cur_view = NODE_INVALID;
	int cur_ff = -1;
	One<NodeCtrlBase> ctrl;
	One<NodeViewBase> view;
	
public:
	typedef OrganizationCtrl CLASSNAME;
	OrganizationCtrl();
	
	void Init();
	void Data();
	void DataPackage();
	void DataNode();
	void DataView();
	void ToolMenu(Bar& bar);
	void ViewNodeCtrl();
	void RemoveCtrl();
	void Do(int fn);
	void AddNode(int i, int j);
	void AddNodeToList(int cur, Node& n);
	void AddNodeSubToList(int cur, Node& n);
	
	TextDatabase& GetDatabase();
	EditorPtrs& GetPointers();
	
	Event<> WhenToolMenuUpdate;
	
};



END_TEXTLIB_NAMESPACE


#endif
