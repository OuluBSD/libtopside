#ifndef _EcsCtrl_InterfaceConnectionCtrl_h_
#define _EcsCtrl_InterfaceConnectionCtrl_h_

NAMESPACE_TOPSIDE_BEGIN


class InterfaceConnectionGraph : public Ctrl {
	
	
public:
	typedef InterfaceConnectionGraph CLASSNAME;
	InterfaceConnectionGraph();
	
	void Updated() override;
	
};

class InterfaceConnectionCtrl : public ParentCtrl {
	EntityBrowserCtrl			ent_browser;
	ParentCtrl					graph_cont;
	One<GraphLib::SpringGraph>	graph;
	Splitter					hsplit;
	EntityRef					sel_ent;
	Color						fill_ent;
	Color						fill_comp;
	Color						fill_iface;
	
	void OnEntityCursorChanged();
	void UpdateGraph();
	
	template <class T>
	void AddInterfaceT(String from, String name, T i) {
		GraphLib::SpringGraph& g = *graph;
		
		g.AddNode(name).SetFill(fill_iface);
		g.AddEdge(from, name).SetWeight(2);
		
		auto& conns = i->GetConnections();
		for(auto& b : conns) {
			ComponentBaseRef tgt_base = b.dst->template AsRef<ComponentBase>();
			EntityRef tgt_ent = tgt_base->GetEntity();
			
			String id_str = "(" + IntStr64(tgt_ent->GetId()) + ")";
			String b_name = TypeId(typeid(typename T::Type)).CleanDemangledName() + id_str;
			String c_name = tgt_base->GetType().CleanDemangledName() + id_str;
			String e_name = tgt_ent->GetPrefab() + id_str;
			
			g.AddNode(b_name).SetFill(fill_iface);
			g.AddNode(c_name).SetFill(fill_comp);
			g.AddNode(e_name).SetFill(fill_ent);
			
			g.AddEdge(name, b_name).SetWeight(10);
			g.AddEdge(b_name, c_name).SetWeight(2);
			g.AddEdge(c_name, e_name).SetWeight(1);
		}
	}

public:
	typedef InterfaceConnectionCtrl CLASSNAME;
	InterfaceConnectionCtrl();
	
	void Updated() override;
	void SetMachine(Machine& m) {ent_browser.SetMachine(m);}
	
};


NAMESPACE_TOPSIDE_END

#endif
