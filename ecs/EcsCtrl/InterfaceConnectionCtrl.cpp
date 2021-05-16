#include "EcsCtrl.h"

NAMESPACE_TOPSIDE_BEGIN


InterfaceConnectionGraph::InterfaceConnectionGraph() {
	
}

void InterfaceConnectionGraph::Updated() {
	
}




InterfaceConnectionCtrl::InterfaceConnectionCtrl() {
	Add(hsplit.SizePos());
	
	hsplit.Horz();
	hsplit << ent_browser << graph_cont;
	hsplit.SetPos(2000);
	
	ent_browser.WhenEntityChanged << THISBACK(OnEntityCursorChanged);
	
	fill_ent	= Color(255, 212, 209);
	fill_comp	= Color(216, 217, 255);
	fill_iface	= Color(211, 255, 209);
}

void InterfaceConnectionCtrl::OnEntityCursorChanged() {
	EntityRef ent = ent_browser.GetSelected();
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
	int i = 0;
	for(auto& comp : comps) {
		ComponentBase& b = *comp;
		
		String id_str = "(" + IntStr64(e.GetId()) + "," + IntStr(i) + ")";
		String c_name = b.GetType().CleanDemangledName() + id_str;
		g.AddNode(c_name).SetFill(fill_comp);
		g.AddEdge(ent_name, c_name).SetWeight(1);
		
		#define IFACE(x) {\
			auto src = b.As##x##Source(); \
			if (src) AddInterfaceT(c_name, #x "Source" + id_str, src); \
			auto sink = b.As##x##Sink(); \
			if (sink) AddInterfaceT(c_name, #x "Sink" + id_str, sink); \
		}
		IFACE_LIST
		#undef IFACE
		++i;
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


void InterfaceConnectionCtrl::Updated() {
	ent_browser.Updated();
}


NAMESPACE_TOPSIDE_END
