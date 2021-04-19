#include "EcsCtrl.h"

NAMESPACE_OULU_BEGIN


InterfaceConnectionGraph::InterfaceConnectionGraph() {
	
}

void InterfaceConnectionGraph::Updated() {
	
}




InterfaceConnectionCtrl::InterfaceConnectionCtrl() {
	Add(hsplit.SizePos());
	
	hsplit.Horz();
	hsplit << ent_list << graph_cont;
	hsplit.SetPos(2000);
	
	ent_list.WhenEntityChanged << THISBACK(OnEntityCursorChanged);
	
	fill_ent	= Color(255, 212, 209);
	fill_comp	= Color(216, 217, 255);
	fill_iface	= Color(211, 255, 209);
}

void InterfaceConnectionCtrl::OnEntityCursorChanged() {
	SharedEntity ent = ent_list.GetSelected();
	if (ent != sel_ent) {
		sel_ent = ent;
		UpdateGraph();
	}
}

void InterfaceConnectionCtrl::UpdateGraph() {
	if (!sel_ent)
		return;
	
	Entity& e = *sel_ent;
	ComponentMap& comps = e.GetComponents();
	
	if (graph) {
		graph_cont.RemoveChild(&*graph);
		graph.Clear();
	}
	
	graph.Create();
	GraphLib::SpringGraph& g = *graph;
	graph_cont.Add(g.SizePos());
	
	String ent_name = e.GetPrefab() + "(" + IntStr64(e.GetId()) + ")";
	auto& initial = g.AddNode(ent_name).SetFill(fill_ent);
	for(int i = 0; i < comps.GetCount(); i++) {
		ComponentBase& b = *comps[i];
		
		String id_str = "(" + IntStr64(e.GetId()) + "," + IntStr(i) + ")";
		String c_name = b.GetType().CleanDemangledName() + id_str;
		g.AddNode(c_name).SetFill(fill_comp);
		g.AddEdge(ent_name, c_name).SetWeight(1);
		
		#define IFACE(x) {\
			x##Source* src = b.As##x##Source(); \
			if (src) AddInterface(c_name, #x "Source" + id_str, *src); \
			x##Sink* sink = b.As##x##Sink(); \
			if (sink) AddInterface(c_name, #x "Sink" + id_str, *sink); \
		}
		IFACE_LIST
		#undef IFACE
	}
	
	//g.RouteWeights(); // enable dijkstra update by clicking nodes
	g.Dijkstra(initial); // route initial dijkstra
	g.ZoomAll();
	/*PostCallback(THISBACK(UpdateLayout));
	g.Center();
	g.Layout();*/
}

/*void InterfaceConnectionCtrl::UpdateLayout() {
	if (graph) {
		graph->ZoomAll();
		//graph->Center();
		//graph->Layout();
	}
}*/

void InterfaceConnectionCtrl::AddInterface(String from, String name, InterfaceBase& i) {
	GraphLib::SpringGraph& g = *graph;
	
	g.AddNode(name).SetFill(fill_iface);
	g.AddEdge(from, name).SetWeight(2);
	
	const auto& conns = i.GetConnections();
	for(InterfaceBase* b : conns) {
		ComponentBase* tgt_base = b->AsComponentBase();
		Entity& tgt_ent = tgt_base->GetEntity();
		
		String id_str = "(" + IntStr64(tgt_ent.GetId()) + ")";
		String b_name = b->GetInterfaceType().CleanDemangledName() + id_str;
		String c_name = tgt_base->GetType().CleanDemangledName() + id_str;
		String e_name = tgt_ent.GetPrefab() + id_str;
		
		g.AddNode(b_name).SetFill(fill_iface);
		g.AddNode(c_name).SetFill(fill_comp);
		g.AddNode(e_name).SetFill(fill_ent);
		
		g.AddEdge(name, b_name).SetWeight(10);
		g.AddEdge(b_name, c_name).SetWeight(2);
		g.AddEdge(c_name, e_name).SetWeight(1);
	}
}

void InterfaceConnectionCtrl::Updated() {
	ent_list.Updated();
}


NAMESPACE_OULU_END
