#ifndef _EcsCtrl_EntityCtrl_h_
#define _EcsCtrl_EntityCtrl_h_


NAMESPACE_OULU_BEGIN


struct EntityDataCtrl : public ComponentCtrl {
	ArrayCtrl list;
	int ent_cursor = 0;
	
	EntityDataCtrl();
	
	void UpdateEntityData(Entity& e);
	void AddEntityDataRow(Value key, Value value);
	
	void SetComponent(ComponentBase&) override {}
	
};

class EntityCtrl : public ParentCtrl {
	ArrayMap<TypeId, ComponentCtrl>		comp_ctrls;
	Splitter							vsplit, hsplit;
	EntityBrowserCtrl					ent_browser;
	EntityContentCtrl					ent_content;
	EntityDataCtrl						ent_data;
	ParentCtrl							ent_cont;
	
	EntityRef							sel_ent;
	ComponentCtrl*						active_ctrl = 0;
	Machine*							mach = 0;
	
	void ClearActiveCtrl();
	void UpdateEntityData();
	void SetEntityDataCtrl();
	void SetComponentCtrl(ComponentBase& c);
	
public:
	typedef EntityCtrl CLASSNAME;
	EntityCtrl();
	
	void SetMachine(Machine& m) {mach = &m; ent_browser.SetMachine(m);}
	void Updated() override;
	void OnEntityCursorChanged();
	void OnContentCursorChanged();
	
	
};


NAMESPACE_OULU_END


#endif
