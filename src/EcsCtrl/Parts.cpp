#include "EcsCtrl.h"


NAMESPACE_TOPSIDE_BEGIN
using namespace Ecs;


PoolTreeCtrl::PoolTreeCtrl() {
	Add(tree.SizePos());
	tree.WhenCursor << THISBACK(OnCursor);
}

void PoolTreeCtrl::SetEngine(Ecs::Engine& m) {
	mach = &m;
	es = m.TryGet<EntityStore>();
}

void PoolTreeCtrl::OnCursor() {
	if (!es || !tree.IsCursor())
		return;
	
	int cursor = tree.GetCursor();
	UPP::Value val = tree.Get(cursor);
	
	TODO
	/*if (IsTypeRaw<PoolRef>(val)) {
		PoolRef new_sel = val.To<PoolRef>();
		
		if (new_sel != selected) {
			selected = new_sel;
			WhenPoolChanged();
		}
	}*/
}

hash_t PoolTreeCtrl::GetPoolTreeHash() const {
	hash_t h = 0;
	if (es) {
		PoolHashVisitor vis;
		vis.Visit(*es.Get()->GetRoot());
		h = vis;
	}
	return h;
}

void PoolTreeCtrl::Updated() {
	hash_t h = GetPoolTreeHash();
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

void PoolTreeCtrl::Data() {
	if (!es)
		return;
	
	PoolRef root = es->GetRoot();
	
	String root_name = root->GetName();
	if (root_name.IsEmpty())
		root_name = "Root";
	tree.Clear();
	tree.SetRoot(CtrlImg::Dir(), RawToValue(root), root_name);
	AddPool(0, root);
	tree.OpenDeep(0);
	
	if (!tree.IsCursor())
		tree.SetCursor(0);
}

void PoolTreeCtrl::AddPool(int parent, PoolRef pool) {
	PoolVec& sub = pool->GetPools();
	for (PoolRef& p : sub) {
		String name = p->GetName();
		if (name.IsEmpty())
			name = IntStr64(p->GetId());
		int i = tree.Add(parent, CtrlImg::Dir(), RawToValue(p), name);
		AddPool(i, p);
	}
}









EntityListCtrl::EntityListCtrl() {
	ParentCtrl::Add(list.SizePos());
	
	list.AddIndex();
	list.AddColumn("Created");
	list.AddColumn("Prefab");
	list.AddColumn("Id");
	list.ColumnWidths("1 2 1");
	
	list.WhenCursor << THISBACK(OnCursor);
	
}

void EntityListCtrl::SetPool(PoolRef pool) {
	this->pool = pool;
	es = pool->GetEngine().TryGet<EntityStore>();
}

hash_t EntityListCtrl::GetEntityListHash() const {
	hash_t v = 0;
	if (pool) {
		EntityHashVisitor vis;
		vis.Visit(*pool.Get());
		v = vis;
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
	if (!pool || !list.IsCursor())
		return;
	
	int cursor = list.GetCursor();
	int ent_i = list.Get(cursor, 0);
	
	EntityRef new_sel;
	
	EntityVec& v = pool->GetEntities();
	if (ent_i >= 0 && ent_i < v.GetCount())
		new_sel = v.At(ent_i);
	
	if (new_sel != selected) {
		selected = new_sel;
		WhenEntityChanged();
	}
}

void EntityListCtrl::Data() {
	if (!pool)
		return;
	
	EntityVec& v = pool->GetEntities();
	
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
			list.Set(i, 1, UPP::Value());
			list.Set(i, 2, UPP::Value());
			list.Set(i, 3, UPP::Value());
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
	ComponentMap& m = const_cast<Entity&>(e).GetComponents();
	
	int i = 0;
	for(auto iter = m.begin(); iter; ++iter, ++i) {
		TypeId type = *iter.key;
		int node_i = tree.Add(tree_i, comp_icon, type.CleanDemangledName());
		node_comps.Add(node_i, i);
	}
}

void EntityContentCtrl::GetCursor(ComponentBaseRef& c) {
	c.Clear();
	
	int i = tree.GetCursor();
	if (i == 0)
		return;
	
	int j = node_comps.Find(i);
	if (j >= 0) {
		int comp = node_comps[j];
		auto& map = ent->GetComponents();
		if (comp >= 0 && comp < map.GetCount())
			c = map.At(comp);
	}
}











EntityBrowserCtrl::EntityBrowserCtrl() {
	ent_list.WhenEntityChanged = WhenEntityChanged.Proxy();
	
	Add(vsplit.SizePos());
	
	vsplit.Vert();
	vsplit << pool_tree << ent_list;
	
	pool_tree.WhenPoolChanged << THISBACK(OnPoolCursorChanged);
}

void EntityBrowserCtrl::Updated() {
	pool_tree.Updated();
	ent_list.Updated();
}

void EntityBrowserCtrl::Data() {
	pool_tree.Data();
	ent_list.Data();
}

void EntityBrowserCtrl::OnPoolCursorChanged() {
	PoolRef pool = pool_tree.GetSelected();
	if (pool != sel_pool) {
		sel_pool = pool;
		ent_list.SetPool(sel_pool);
		ent_list.Update();
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
	
	TODO
	/*ifaces.Clear();
	write_cursor = 0;
	ComponentMap& comps = ent->GetComponents();
	int i = 0;
	for (auto& comp : comps) {
		ComponentBase& b = *comp;
		#define IFACE(x) {\
			auto src = b.As##x##Source(); \
			if (src) AddInterface(i, src); \
			auto sink = b.As##x##Sink(); \
			if (sink) AddInterface(i, sink); \
		}
		IFACE_LIST
		#undef IFACE
		++i;
	}
	list.SetCount(write_cursor);
	*/
	WhenInterfaceCursor();
}

void InterfaceListCtrl::GetCursor(ComponentBaseRef& c,  ExchangeProviderBaseRef& i) {
	c.Clear();
	i.Clear();
	
	if (!ent || !list.IsCursor())
		return;
	
	int cursor = list.GetCursor();
	int comp_i = list.Get(cursor, 0);
	int iface_i = list.Get(cursor, 1);
	
	ComponentMap& comps = ent->GetComponents();
	ComponentBaseRef comp = comps.At(comp_i);
	ExchangeProviderBaseRef iface = ifaces.At(iface_i);
	
	c = comp;
	i = iface;
}


NAMESPACE_TOPSIDE_END
