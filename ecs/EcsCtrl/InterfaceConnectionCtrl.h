#ifndef _EcsCtrl_InterfaceConnectionCtrl_h_
#define _EcsCtrl_InterfaceConnectionCtrl_h_

NAMESPACE_OULU_BEGIN


class InterfaceConnectionGraph : public Ctrl {
	
	
public:
	typedef InterfaceConnectionGraph CLASSNAME;
	InterfaceConnectionGraph();
	
	void Updated() override;
	
};

class InterfaceConnectionCtrl : public ParentCtrl {
	EntityListCtrl ent_list;
	ParentCtrl graph_cont;
	One<GraphLib::SpringGraph> graph;
	Splitter hsplit;
	SharedEntity sel_ent;
	Color fill_ent, fill_comp, fill_iface;
	
	void OnEntityCursorChanged();
	void UpdateGraph();
	//void UpdateLayout();
	void AddInterface(String from, String name, InterfaceBase& i);
	
public:
	typedef InterfaceConnectionCtrl CLASSNAME;
	InterfaceConnectionCtrl();
	
	void Updated() override;
	
};


NAMESPACE_OULU_END

#endif
