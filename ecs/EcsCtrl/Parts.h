#ifndef _EcsCtrl_Parts_h_
#define _EcsCtrl_Parts_h_

NAMESPACE_TOPSIDE_BEGIN


class PoolTreeCtrl : public ParentCtrl {
	Ecs::Engine*		mach = 0;
	Ecs::EntityStoreRef	es;
	Ecs::PoolRef		selected;
	TreeCtrl			tree;
	uint64				last_hash = 0;

	void OnCursor();
	hash_t GetPoolTreeHash() const;
	
	void AddPool(int parent, Ecs::PoolRef pool);
	
public:
	typedef PoolTreeCtrl CLASSNAME;
	PoolTreeCtrl();
	
	void SetEngine(Ecs::Engine& m);
	void Updated() override;
	void Data();
	
	Ecs::PoolRef GetSelected() {return selected;}
	
	Callback WhenPoolChanged;
	
};


class EntityListCtrl : public ParentCtrl {
	Ecs::EntityStoreRef	es;
	Ecs::PoolRef		pool;
	Ecs::EntityRef		selected;
	ArrayCtrl			list;
	uint64				last_hash = 0;

	void OnCursor();
	hash_t GetEntityListHash() const;
	
public:
	typedef EntityListCtrl CLASSNAME;
	EntityListCtrl();
	
	void SetPool(Ecs::PoolRef pool);
	void Updated() override;
	void Data();
	
	Ecs::EntityRef GetSelected() {return selected;}
	
	Callback WhenEntityChanged;
	
};


class EntityBrowserCtrl : public ParentCtrl {
	Splitter			vsplit;
	PoolTreeCtrl		pool_tree;
	EntityListCtrl		ent_list;
	Ecs::PoolRef				sel_pool;
	
	void OnPoolCursorChanged();
	
public:
	typedef EntityBrowserCtrl CLASSNAME;
	EntityBrowserCtrl();
	
	void SetEngine(Ecs::Engine& m) {pool_tree.SetEngine(m);}
	void Updated() override;
	void Data();
	Ecs::EntityRef GetSelected() {return ent_list.GetSelected();}
	
	Callback WhenEntityChanged;
	
};

class EntityContentCtrl : public ParentCtrl {
	TreeCtrl tree;
	Image ent_icon, comp_icon, iface_icon;
	Ecs::EntityRef ent;
	int64 ent_changed_time = -1;
	VectorMap<int, int> node_comps;
	
	void OnCursor();
	void AddTreeEntity(int tree_i, const Ecs::Entity& e);
	
public:
	typedef EntityContentCtrl CLASSNAME;
	EntityContentCtrl();
	
	void Updated() override;
	
	void SetEntity(Ecs::EntityRef e) {ent = e;}
	void GetCursor(Ecs::ComponentBaseRef& c);
	
	Callback WhenContentCursor;
	
};


class InterfaceListCtrl : public ParentCtrl {
	LinkedList<ExchangeProviderBaseRef> ifaces;
	ArrayCtrl list;
	Ecs::EntityRef ent;
	int64 ent_changed_time = -1;
	int write_cursor;
	
	void OnCursor();
	void Data();
	
	
	template <class T>
	void AddInterface(int comp_i, Ref<T> o) {
		int iface_i = ifaces.GetCount();
		ifaces.Add(o);
		list.Set(write_cursor, 0, comp_i);
		list.Set(write_cursor, 1, iface_i);
		list.Set(write_cursor, 2, TypeId(AsTypeCls<T>()).CleanDemangledName());
		list.Set(write_cursor, 3, o->GetConnections().GetCount());
		write_cursor++;
	}
	
public:
	typedef InterfaceListCtrl CLASSNAME;
	InterfaceListCtrl();
	
	void Updated() override;
	
	void SetEntity(Ecs::EntityRef e) {ent = e;}
	void GetCursor(Ecs::ComponentBaseRef& c, ExchangeProviderBaseRef& i);
	
	Callback WhenInterfaceCursor;
	
};


NAMESPACE_TOPSIDE_END

#endif
