#ifndef _EcsCtrl_InterfaceSystemCtrl_h_
#define _EcsCtrl_InterfaceSystemCtrl_h_

NAMESPACE_OULU_BEGIN



struct InterfaceDataCtrl : public InterfaceCtrl {
	ArrayCtrl list;
	int iface_cursor = 0;
	
	InterfaceDataCtrl();
	
	void UpdateInterfaceData(InterfaceBase& e);
	void AddInterfaceDataRow(Value key, Value value);
	
	void SetInterface(ComponentBase&, InterfaceBase&) override {}
	
};

class InterfaceSystemCtrl : public ParentCtrl {
	ArrayMap<TypeId, InterfaceCtrl> iface_ctrls;
	Splitter vsplit, hsplit;
	EntityListCtrl ent_list;
	InterfaceListCtrl iface_list;
	InterfaceDataCtrl ent_data;
	ParentCtrl ent_cont;
	
	VectorMap<int, int> node_ifaces;
	SharedEntity sel_ent;
	InterfaceBase* sel_iface = 0;
	InterfaceCtrl* active_ctrl = 0;
	
	Image ent_icon, comp_icon, iface_icon;
	
	void OnEntityCursorChanged();
	void OnInterfaceCursorChanged();
	void ClearActiveCtrl();
	void SetInterfaceCtrl(ComponentBase& c, InterfaceBase& b);
	
public:
	typedef InterfaceSystemCtrl CLASSNAME;
	InterfaceSystemCtrl();
	
	void Updated() override;
	
};



NAMESPACE_OULU_END

#endif
