#ifndef _EcsCtrl_InterfaceSystemCtrl_h_
#define _EcsCtrl_InterfaceSystemCtrl_h_

NAMESPACE_TOPSIDE_BEGIN



struct InterfaceDataCtrl : public InterfaceCtrl {
	ArrayCtrl list;
	int iface_cursor = 0;
	
	InterfaceDataCtrl();
	
	void UpdateInterfaceData(ExchangeProviderBaseRef e);
	void AddInterfaceDataRow(UPP::Value key, UPP::Value value);
	
	void SetInterface(Ecs::ComponentBaseRef, ExchangeProviderBaseRef) override {}
	
};

class InterfaceSystemCtrl : public ParentCtrl {
	ArrayMap<TypeId, InterfaceCtrl>		iface_ctrls;
	Splitter							vsplit, hsplit;
	EntityBrowserCtrl					ent_browser;
	InterfaceListCtrl					iface_list;
	InterfaceDataCtrl					ent_data;
	ParentCtrl							ent_cont;
	
	VectorMap<int, int>					node_ifaces;
	Ecs::EntityRef						sel_ent;
	ExchangeProviderBaseRef				sel_iface;
	InterfaceCtrl*						active_ctrl = 0;
	
	Image ent_icon, comp_icon, iface_icon;
	
	void OnEntityCursorChanged();
	void OnInterfaceCursorChanged();
	void ClearActiveCtrl();
	void SetInterfaceCtrl(Ecs::ComponentBaseRef c, ExchangeProviderBaseRef b);
	
public:
	typedef InterfaceSystemCtrl CLASSNAME;
	InterfaceSystemCtrl();
	
	void Updated() override;
	void SetEngine(Ecs::Engine& m) {ent_browser.SetEngine(m);}
	
};



NAMESPACE_TOPSIDE_END

#endif
