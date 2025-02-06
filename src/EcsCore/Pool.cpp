#include "EcsCore.h"


NAMESPACE_ECS_BEGIN


//PoolRef GetConnectorBasePool(ConnectorBase* conn) {return conn->GetPool();}

Engine& GetPoolEngine(PoolRef pool) {return pool->GetEngine();}



Pool::Pool() {
	DBG_CONSTRUCT
}

Pool::~Pool() {
	DBG_DESTRUCT
}

void Pool::Etherize(Ether& e) {
	byte magic = 0, chk = 0xAF;
	/*
	e % freeze_bits
	  % name
	  % id
	  ;
	*/
	GeomVar type;
	if (e.IsLoading()) {
		e.GetT(magic);
		ASSERT(magic == chk);
		
		int pc = 0, ec = 0;
		e.GetT(pc);
		e.GetT(ec);
		
		// Don't destroy objects during loading.
		// Remove non-loaded pools afterwards.
		thread_local static Index<String> rem_pool;
		rem_pool.Clear();
		for (PoolRef p : pools)
			rem_pool.Add(p->name);
		for(int i = 0; i < pc; i++) {
			e.GetT(magic);
			ASSERT(magic == chk);
			// Realize pool and remove name from to-be-removed list
			String name = e.GetString();
			rem_pool.RemoveKey(name);
			PoolRef p = GetAddPool(name);
			
			p->Etherize(e);
			
			// Check again
			e.GetT(magic);
			ASSERT(magic == chk);
		}
		for (String rem : rem_pool.GetKeys())
			RemovePool(rem);
		
		for(int i = 0; i < ec; i++) {
			e.GetT(magic);
			ASSERT(magic == chk);
			String name = e.GetString();
			EntityRef o = GetAddEmpty(name);
			
			o->Etherize(e);
			
			e.GetT(magic);
			ASSERT(magic == chk);
		}
	}
	else {
		e.PutT(chk);
		int pc = pools.GetCount();
		e.PutT(pc);
		int ec = objects.GetCount();
		e.PutT(ec);
		
		for (PoolRef p : pools) {
			e.PutT(chk);
			e.Put(p->name);
			
			p->Etherize(e);
			
			e.PutT(chk);
		}
		for (EntityRef o : objects) {
			e.PutT(chk);
			e.Put(o->name);
			
			o->Etherize(e);
			
			e.PutT(chk);
		}
	}
}

PoolId Pool::GetNextId() {
	static Atomic next_id;
	return ++next_id;
}

Pool* Pool::GetParent() const {
	return RefScopeParent<PoolParent>::GetParent().b;
}

Engine& Pool::GetEngine() {
	if (machine)
		return *machine;
	Pool* p = this;
	int levels = 0;
	while (p && levels++ < 1000) {
		const PoolParent& par = p->RefScopeParent<PoolParent>::GetParent();
		if (par.a) {
			machine = &par.a->GetEngine();
			ASSERT(machine);
			return *machine;
		}
		ASSERT(p != par.b);
		p = par.b;
	}
	THROW(Exc("Engine ptr not found"));
}

void Pool::Initialize(Entity& e, String prefab) {
	uint64 ticks = GetEngine().GetTicks();
	e.SetPrefab(prefab);
	e.SetCreated(ticks);
	e.SetChanged(ticks);
	
}

EntityRef Pool::CreateEmpty() {
	Entity& e = objects.Add();
	e.SetParent(this);
	e.SetId(GetNextId());
	Initialize(e);
	return e;
}

EntityRef Pool::GetAddEmpty(String name) {
	EntityRef e = FindEntityByName(name);
	if (e)
		return e;
	e = CreateEmpty();
	e->SetName(name);
	return e;
}

EntityRef Pool::Clone(const Entity& c) {
	EntityRef e = CreateEmpty();
	e->CopyHeader(c);
	GetEngine().Get<ComponentStore>()->Clone(*e, c);
	return e;
}

void Pool::UnlinkDeep() {
	for (auto it = pools.rbegin(); it != pools.rend(); --it) {
		it().UnlinkDeep();
	}
	
}

void Pool::UnrefDeep() {
	RefClearVisitor vis;
	vis.Visit(*this);
}

void Pool::UninitializeComponentsDeep() {
	for (PoolRef& p : pools)
		p->UninitializeComponentsDeep();
	
	for (auto it = objects.rbegin(); it != objects.rend(); --it) {
		it().UninitializeComponents();
	}
	
}

void Pool::ClearComponentsDeep() {
	for (PoolRef& p : pools)
		p->ClearComponentsDeep();
	
	for (auto it = objects.rbegin(); it != objects.rend(); --it) {
		it().ClearComponents();
	}
	
}

void Pool::ClearDeep() {
	for (PoolRef& p : pools)
		p->ClearDeep();
	pools.Clear();
	
	objects.Clear();
}

void Pool::ReverseEntities() {
	objects.Reverse();
}

void Pool::Clear() {
	UnrefDeep();
	UnlinkDeep();
	UninitializeComponentsDeep();
	ClearComponentsDeep();
	ClearDeep();
}

void Pool::PruneFromContainer() {
	for (auto& pool : pools)
		pool->PruneFromContainer();
	Destroyable::PruneFromContainer(objects);
}

void Pool::Dump() {
	LOG(GetTreeString());
}

String Pool::GetTreeString(int indent) {
	String s;
	
	String pre;
	pre.Cat('\t', indent);
	
	s << ".." << name << "[" << id << "]\n";
	
	for (EntityRef& e : objects)
		s << e->GetTreeString(indent+1);
	
	for (PoolRef& p : pools)
		s << p->GetTreeString(indent+1);
	
	return s;
}

PoolRef Pool::FindPool(String name) {
	for (PoolRef& p : pools) {
		if (p->GetName() == name)
			return p;
	}
	return PoolRef();
}

EntityRef Pool::FindEntityByName(String name) {
	for (EntityRef object : objects)
		if (object->GetName() == name)
			return object;
	return EntityRef();
}

PoolRef Pool::AddPool(String name) {
	Pool& p = pools.Add();
	p.SetParent(PoolParent(0, this));
	p.SetName(name);
	p.SetId(GetNextId());
	return p;
}

PoolRef Pool::GetAddPool(String name) {
	for (PoolRef& pool : pools)
		if (pool->GetName() == name)
			return pool;
	return AddPool(name);
}

void Pool::RemovePool(String name) {
	for (PoolVec::Iterator iter = pools.begin(); iter; ++iter) {
		if (iter->GetName() == name) {
			iter->ClearDeep();
			pools.Remove(iter);
		}
	}
}

void Pool::RemoveEntity(Entity* e) {
	int i = 0;
	auto it = objects.begin();
	auto end = objects.end();
	while (it != end) {
		if (e == &**it) {
			objects.Remove(it);
			break;
		}
		++i;
		++it;
	}
}

ComponentBaseRef Pool::RealizeComponentPath(const Vector<String>& path) {
	int c = path.GetCount();
	ASSERT(c >= 2);
	if (c < 2) return ComponentBaseRef();
	
	String ent_name = path[c-2];
	String comp_name = path[c-1];
	ASSERT(!ent_name.IsEmpty())
	ASSERT(!comp_name.IsEmpty())
	
	Pool* pool = this;
	for(int i = 0; i < c-2; i++) {
		String pool_name = path[i];
		ASSERT(!pool_name.IsEmpty());
		pool = &*pool->GetAddPool(pool_name);
		ASSERT(pool);
	}
	
	EntityRef ent = pool->GetAddEmpty(ent_name);
	ComponentBaseRef comp = ent->GetAdd(comp_name);
	ASSERT(comp);
	
	return comp;
}

EntityRef Pool::RealizeEntityPath(const Vector<String>& path) {
	int c = path.GetCount();
	ASSERT(c >= 1);
	if (c < 1) return EntityRef();
	
	String ent_name = path[c-1];
	ASSERT(!ent_name.IsEmpty())
	
	Pool* pool = this;
	for(int i = 0; i < c-1; i++) {
		String pool_name = path[i];
		ASSERT(!pool_name.IsEmpty());
		pool = &*pool->GetAddPool(pool_name);
		ASSERT(pool);
	}
	
	EntityRef ent = pool->GetAddEmpty(ent_name);
	
	return ent;
}




bool PoolHashVisitor::OnEntry(const RTTI& type, TypeCls derived, const char* derived_name, void* mem, LockedScopeRefCounter* ref) {
	if (derived == AsTypeCls<Pool>()) {
		Pool& p = *(Pool*)mem;
		ch.Put(p.GetId());
	}
	return true;
}






NAMESPACE_ECS_END
