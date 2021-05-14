#ifndef _EcsCtrl_Parts_h_
#define _EcsCtrl_Parts_h_

NAMESPACE_OULU_BEGIN


class PoolTreeCtrl : public ParentCtrl {
	Machine*		mach = 0;
	TreeCtrl		tree;
	EntityStoreRef	es;
	PoolRef			selected;
	uint64			last_hash = 0;

	void OnCursor();
	hash_t GetPoolTreeHash() const;
	
	void AddPool(int parent, PoolRef pool);
	
public:
	typedef PoolTreeCtrl CLASSNAME;
	PoolTreeCtrl();
	
	void SetMachine(Machine& m);
	void Updated() override;
	void Data();
	
	PoolRef GetSelected() {return selected;}
	
	Callback WhenPoolChanged;
	
};


class EntityListCtrl : public ParentCtrl {
	EntityStoreRef	es;
	PoolRef			pool;
	ArrayCtrl		list;
	EntityRef		selected;
	uint64			last_hash = 0;

	void OnCursor();
	hash_t GetEntityListHash() const;
	
public:
	typedef EntityListCtrl CLASSNAME;
	EntityListCtrl();
	
	void SetPool(PoolRef pool);
	void Updated() override;
	void Data();
	
	EntityRef GetSelected() {return selected;}
	
	Callback WhenEntityChanged;
	
};


class EntityBrowserCtrl : public ParentCtrl {
	Splitter			vsplit;
	PoolTreeCtrl		pool_tree;
	EntityListCtrl		ent_list;
	PoolRef				sel_pool;
	
	void OnPoolCursorChanged();
	
public:
	typedef EntityBrowserCtrl CLASSNAME;
	EntityBrowserCtrl();
	
	void SetMachine(Machine& m) {pool_tree.SetMachine(m);}
	//void SetPool(PoolRef pool) {ent_list.SetPool(pool);}
	void Updated() override;
	void Data();
	EntityRef GetSelected() {return ent_list.GetSelected();}
	
	Callback WhenEntityChanged;
	
};

class EntityContentCtrl : public ParentCtrl {
	TreeCtrl tree;
	Image ent_icon, comp_icon, iface_icon;
	EntityRef ent;
	int64 ent_changed_time = -1;
	VectorMap<int, int> node_comps;
	
	void OnCursor();
	void AddTreeEntity(int tree_i, const Entity& e);
	
public:
	typedef EntityContentCtrl CLASSNAME;
	EntityContentCtrl();
	
	void Updated() override;
	
	void SetEntity(EntityRef e) {ent = e;}
	void GetCursor(ComponentBaseRef& c);
	
	Callback WhenContentCursor;
	
};


class InterfaceListCtrl : public ParentCtrl {
	LinkedList<ExchangeProviderBaseRef> ifaces;
	ArrayCtrl list;
	EntityRef ent;
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
		list.Set(write_cursor, 2, TypeId(typeid(T)).CleanDemangledName());
		list.Set(write_cursor, 3, o->GetConnections().GetCount());
		write_cursor++;
	}
	
public:
	typedef InterfaceListCtrl CLASSNAME;
	InterfaceListCtrl();
	
	void Updated() override;
	
	void SetEntity(EntityRef e) {ent = e;}
	void GetCursor(ComponentBaseRef& c, ExchangeProviderBaseRef& i);
	
	Callback WhenInterfaceCursor;
	
};


NAMESPACE_OULU_END

#endif
