#ifndef _EcsCtrl_Parts_h_
#define _EcsCtrl_Parts_h_

NAMESPACE_OULU_BEGIN


class EntityListCtrl : public ParentCtrl {
	ArrayCtrl list;
	Ref<EntityStore> es;
	EntityRef selected;
	uint64 last_hash = 0;

	void OnCursor();
	hash_t GetEntityListHash() const;
	
public:
	typedef EntityListCtrl CLASSNAME;
	EntityListCtrl();
	
	void Updated() override;
	void Data();
	
	EntityRef GetSelected() {return selected;}
	
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
	void GetCursor(ComponentBase*& c);
	
	Callback WhenContentCursor;
	
};


class InterfaceListCtrl : public ParentCtrl {
	Vector<InterfaceBase*> ifaces;
	ArrayCtrl list;
	EntityRef ent;
	int64 ent_changed_time = -1;
	int write_cursor;
	
	void OnCursor();
	void Data();
	
	
	template <class T>
	void AddInterface(int comp_i, T* o) {
		int iface_i = ifaces.GetCount();
		ifaces << o;
		list.Set(write_cursor, 0, comp_i);
		list.Set(write_cursor, 1, iface_i);
		list.Set(write_cursor, 2, TypeId(typeid(T)).CleanDemangledName());
		list.Set(write_cursor, 3, o->GetConnectionCount());
		write_cursor++;
	}
	
public:
	typedef InterfaceListCtrl CLASSNAME;
	InterfaceListCtrl();
	
	void Updated() override;
	
	void SetEntity(EntityRef e) {ent = e;}
	void GetCursor(ComponentBase*& c, InterfaceBase*& i);
	
	Callback WhenInterfaceCursor;
	
};


NAMESPACE_OULU_END

#endif
