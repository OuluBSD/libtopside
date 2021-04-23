#include "EcsCtrl.h"


NAMESPACE_OULU_BEGIN


EntityListCtrl::EntityListCtrl() {
	ParentCtrl::Add(list.SizePos());
	
	list.AddIndex();
	list.AddColumn("Created");
	list.AddColumn("Prefab");
	list.AddColumn("Id");
	list.ColumnWidths("1 2 1");
	
	list.WhenCursor << THISBACK(OnCursor);
	
	es = GetMachine().TryGet<EntityStore>();
}

hash_t EntityListCtrl::GetEntityListHash() const {
	hash_t v = 0;
	if (es) {
		CombineHash ch;
		const auto& ents = es->GetEntities();
		for (const auto& e : ents)
			ch.Put(e->GetId());
		v = ch;
	}
	return v;
}

void EntityListCtrl::Updated() {
	hash_t h = GetEntityListHash();
	if (h == last_hash)
		ClearModify();
	else {
		last_hash = h;
		SetModify();
	}
	
	if (IsModified()) {
		ClearModify();
		Data();
	}
}

void EntityListCtrl::OnCursor() {
	if (!es || !list.IsCursor())
		return;
	
	int cursor = list.GetCursor();
	int ent_i = list.Get(cursor, 0);
	
	EntityRef new_sel;
	
	Vector<EntityRef>& v = es->GetEntities();
	if (ent_i >= 0 && ent_i < v.GetCount())
		new_sel = v[ent_i];
	
	if (new_sel != selected) {
		selected = new_sel;
		WhenEntityChanged();
	}
}

void EntityListCtrl::Data() {
	if (!es)
		return;
	Vector<EntityRef>& v = es->GetEntities();
	
	int cursor = -1;
	int i = 0;
	for (EntityRef& e : v) {
		if (selected == e)
			cursor = i;
		list.Set(i, 0, i);
		if (e) {
			list.Set(i, 1, e->GetCreatedTick());
			list.Set(i, 2, e->GetPrefab());
			list.Set(i, 3, e->GetId());
		}
		else {
			list.Set(i, 1, Value());
			list.Set(i, 2, Value());
			list.Set(i, 3, Value());
		}
		i++;
	}
	list.SetCount(v.GetCount());
	
	if (!list.IsCursor() && list.GetCount())
		list.SetCursor(0);
	else if (cursor >= 0 && list.GetCursor() != cursor)
		list.SetCursor(cursor);
}








EntityContentCtrl::EntityContentCtrl() {
	ParentCtrl::Add(tree.SizePos());
	
	tree.WhenCursor << THISBACK(OnCursor);
	
	ent_icon	= StreamRaster::LoadFileAny(ShareDirFile("imgs" DIR_SEPS "icons" DIR_SEPS "package.png"));
	comp_icon	= StreamRaster::LoadFileAny(ShareDirFile("imgs" DIR_SEPS "icons" DIR_SEPS "component.png"));
	iface_icon	= StreamRaster::LoadFileAny(ShareDirFile("imgs" DIR_SEPS "icons" DIR_SEPS "interface.png"));
	
}

void EntityContentCtrl::Updated() {
	if (!ent)
		return;
	
	if (!IsModified()) {
		int64 time = ent->GetChangedTick();
		if (time != ent_changed_time) {
			ent_changed_time = time;
			SetModify();
		}
	}
	
	if (IsModified()) {
		ClearModify();
		
		tree.Clear();
		node_comps.Clear();
		
		int64 id = ent->GetId();
		String name;
		if (id >= 0) name = IntStr64(id);
		if (name.IsEmpty())	name = ent->GetPrefab();
		if (name.IsEmpty())	name = "Entity";
		tree.SetRoot(ent_icon, name);
		
		AddTreeEntity(0, *ent);
		tree.OpenDeep(0);
		tree.SetCursor(0);
		
		WhenContentCursor();
	}
}

void EntityContentCtrl::OnCursor() {
	if (!ent || !tree.IsCursor())
		return;
	
	WhenContentCursor();
}

void EntityContentCtrl::AddTreeEntity(int tree_i, const Entity& e) {
	const ComponentMap& m = e.GetComponents();
	
	for(int i = 0; i < m.GetCount(); i++) {
		TypeId type = m.GetKey(i);
		int node_i = tree.Add(tree_i, comp_icon, type.CleanDemangledName());
		node_comps.Add(node_i, i);
	}
}

void EntityContentCtrl::GetCursor(ComponentBase*& c) {
	c = 0;
	
	int i = tree.GetCursor();
	if (i == 0)
		return;
	
	int j = node_comps.Find(i);
	if (j >= 0) {
		int comp = node_comps[j];
		auto& map = ent->GetComponents();
		if (comp >= 0 && comp < map.GetCount())
			c = &*map[comp];
	}
}












InterfaceListCtrl::InterfaceListCtrl() {
	ParentCtrl::Add(list.SizePos());
	
	list.AddIndex();
	list.AddIndex();
	list.AddColumn("Name");
	list.AddColumn("Connections");
	list.ColumnWidths("1 1");
	
	list.WhenCursor << THISBACK(OnCursor);
	
	
}

void InterfaceListCtrl::Updated() {
	if (!ent)
		return;
	
	if (!IsModified()) {
		int64 time = ent->GetChangedTick();
		if (time != ent_changed_time) {
			ent_changed_time = time;
			SetModify();
		}
	}
	
	if (IsModified()) {
		ClearModify();
		Data();
	}
}

void InterfaceListCtrl::OnCursor() {
	if (!ent || !list.IsCursor())
		return;
	
	WhenInterfaceCursor();
}

void InterfaceListCtrl::Data() {
	if (!ent)
		return;
	
	ifaces.Clear();
	write_cursor = 0;
	ComponentMap& comps = ent->GetComponents();
	for(int i = 0; i < comps.GetCount(); i++) {
		auto& comp = comps[i];
		ComponentBase& b = *comp;
		#define IFACE(x) {\
			x##Source* src = b.As##x##Source(); \
			if (src) AddInterface(i, src); \
			x##Sink* sink = b.As##x##Sink(); \
			if (sink) AddInterface(i, sink); \
		}
		IFACE_LIST
		#undef IFACE
	}
	list.SetCount(write_cursor);
	
	WhenInterfaceCursor();
}

void InterfaceListCtrl::GetCursor(ComponentBase*& c, InterfaceBase*& i) {
	c = 0;
	i = 0;
	if (!ent || !list.IsCursor())
		return;
	
	int cursor = list.GetCursor();
	int comp_i = list.Get(cursor, 0);
	int iface_i = list.Get(cursor, 1);
	
	ComponentMap& comps = ent->GetComponents();
	ComponentBase& comp = *comps[comp_i];
	InterfaceBase& iface = *ifaces[iface_i];
	
	c = &comp;
	i = &iface;
}


NAMESPACE_OULU_END
