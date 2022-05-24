#ifndef _EcsCtrl_EntityCtrl_h_
#define _EcsCtrl_EntityCtrl_h_


NAMESPACE_TOPSIDE_BEGIN


struct EntityDataCtrl : public ComponentCtrl {
	ArrayCtrl list;
	int ent_cursor = 0;
	
	EntityDataCtrl();
	
	void UpdateEntityData(Ecs::Entity& e);
	void AddEntityDataRow(UPP::Value key, UPP::Value value);
	
	void SetComponent(Ecs::ComponentBase&) override {}
	
};

class EntityCtrl : public ParentCtrl {
	ArrayMap<TypeId, ComponentCtrl>		comp_ctrls;
	Splitter							vsplit, hsplit;
	EntityBrowserCtrl					ent_browser;
	EntityContentCtrl					ent_content;
	EntityDataCtrl						ent_data;
	ParentCtrl							ent_cont;
	
	Ecs::EntityRef						sel_ent;
	ComponentCtrl*						active_ctrl = 0;
	Ecs::Engine*						mach = 0;
	
	void ClearActiveCtrl();
	void UpdateEntityData();
	void SetEntityDataCtrl();
	void SetComponentCtrl(Ecs::ComponentBase& c);
	
public:
	typedef EntityCtrl CLASSNAME;
	EntityCtrl();
	
	void SetEngine(Ecs::Engine& m) {mach = &m; ent_browser.SetEngine(m);}
	void Updated() override;
	void OnEntityCursorChanged();
	void OnContentCursorChanged();
	
	
};


NAMESPACE_TOPSIDE_END


#endif
