#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN

RemoteDebugCtrl::RemoteDebugCtrl(Edit3D* e) : e(e) {
	/*
	TabCtrl tabs;
	
	Splitter horz;
	ArrayCtrl entities, components, compdata;
	*/
	
	Add(tabs.SizePos());
	
	tabs.Add(vert.SizePos(), "ECS");
	
	vert << horz << log;
	vert.Vert().SetPos(8000);
	log.SetFont(Monospace(14));
	
	horz.Horz();
	horz << tree << entities << components << compdata;
	
	entities.AddColumn("Entity");
	components.AddColumn("Component");
	compdata.AddColumn("Var");
	compdata.AddColumn("Data");
	
	tree.WhenSel << THISBACK1(RefreshPool, false);
	entities.WhenSel << THISBACK1(RefreshEntity, false);
	components.WhenSel << THISBACK1(RefreshComponent, false);
	
}

void RemoteDebugCtrl::Update(double dt) {
	
}

void RemoteDebugCtrl::Data() {
	if (!ex)
		return;
	
	RefreshPools(false);
	
}

DbgPool* RemoteDebugCtrl::GetPool(int tree_id) {
	if (!ex || tree_id < 0)
		return 0;
	
	Vector<int> path;
	path.Add(tree_id);
	
	int id = tree_id;
	while (id) {
		id = tree.GetParent(id);
		if (!id)
			break;
		path.Add(id);
	}
	
	DbgPool* p = &ex->read.pool;
	for (int i = path.GetCount()-1; i >= 0; i--) {
		int pos = path[i];
		if (pos < p->pools.GetCount())
			p = &p->pools[i];
		else
			return 0;
	}
	return p;
}

void RemoteDebugCtrl::RefreshPools(bool has_lock) {
	if (!ex)
		return;
	
	EngineSerializer& s = ex->read;
	if (!has_lock) s.lock.EnterRead();
	
	tree.Clear();
	tree.SetRoot(ImagesImg::Scene(), s.pool.name);
	
	RefreshTreePool(0, s.pool);
	
	tree.OpenDeep(0);
	if (!tree.IsCursor())
		tree.SetCursor(0);
	
	RefreshPool(true);
	
	if (!has_lock) s.lock.LeaveRead();
}

void RemoteDebugCtrl::RefreshTreePool(int tree_id, DbgPool& pool) {
	
	tree.Set(tree_id, pool.name);
	
	for(int i = 0; i < pool.pools.GetCount(); i++) {
		DbgPool& pool0 = pool.pools[i];
		int id = tree.Add(tree_id, ImagesImg::Scene(), pool0.name);
		RefreshTreePool(id, pool0);
	}
}

void RemoteDebugCtrl::RefreshPool(bool has_lock) {
	if (!ex)
		return;
	
	EngineSerializer& s = ex->read;
	if (!has_lock) s.lock.EnterRead();
	
	DbgPool* pool = GetPool(tree.GetCursor());
	
	if (pool) {
		int ec = pool->ents.GetCount();
		entities.SetCount(ec);
		for(int i = 0; i < ec; i++) {
			DbgEntity& e = pool->ents[i];
			entities.Set(i, 0, e.name);
		}
		
		if (!entities.HasFocus() && ec)
			entities.SetCursor(0);
		
		if (entities.HasFocus())
			RefreshEntity(true);
		
		else components.Clear();
	}
	else {
		entities.Clear();
		components.Clear();
		compdata.Clear();
	}
	
	if (!has_lock) s.lock.LeaveRead();
}

void RemoteDebugCtrl::RefreshEntity(bool has_lock) {
	if (!ex)
		return;
	
	EngineSerializer& s = ex->read;
	if (!has_lock) s.lock.EnterRead();
	
	DbgPool* pool = GetPool(tree.GetCursor());
	
	int ec = pool ? pool->ents.GetCount() : 0;
	int cursor = entities.GetCursor();
	if (cursor >= 0 && cursor < ec) {
		DbgEntity& e = pool->ents[cursor];
		int cc = e.comps.GetCount();
		components.SetCount(cc);
		for(int i = 0; i < cc; i++) {
			DbgComponent& c = e.comps[i];
			components.Set(i, 0, c.cls_name);
		}
		
		if (!compdata.HasFocus() && cc)
			compdata.SetCursor(0);
		
		if (compdata.HasFocus())
			RefreshComponent(true);
	}
	else {
		components.Clear();
		compdata.Clear();
	}
	
	if (!has_lock) s.lock.LeaveRead();
}

void RemoteDebugCtrl::RefreshComponent(bool has_lock) {
	if (!ex)
		return;
	
	EngineSerializer& s = ex->read;
	if (!has_lock) s.lock.EnterRead();
	
	DbgPool* pool = GetPool(tree.GetCursor());
	
	int ec = pool ? pool->ents.GetCount() : 0;
	int e_cursor = entities.GetCursor();
	if (e_cursor >= 0 && e_cursor < ec) {
		DbgEntity& e = pool->ents[e_cursor];
		int cc = e.comps.GetCount();
		int c_cursor = components.GetCursor();
		if (c_cursor >= 0 && c_cursor < cc) {
			DbgComponent& c = e.comps[c_cursor];
			int vc = c.vars.GetCount();
			compdata.SetCount(vc);
			for(int i = 0; i < vc; i++) {
				String var_name = c.vars.GetKey(i);
				compdata.Set(i, 0, var_name);
				String var_data = c.vars[i].ToString();
				compdata.Set(i, 1, var_data);
			}
		}
		else compdata.Clear();
	}
	
	if (!has_lock) s.lock.LeaveRead();
}


NAMESPACE_TOPSIDE_END
