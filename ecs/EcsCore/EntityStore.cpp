#include "EcsCore.h"


NAMESPACE_OULU_BEGIN

bool EntityStore::Initialize() {
	GetRoot()->SetName("root");
	return true;
}

void EntityStore::Uninitialize() {
	GetRoot()->Clear();
}

void EntityStore::Update(double) {
	GetRoot()->PruneFromContainer();
}





EntityPool::EntityPool() {
	
}

EntityId EntityPool::GetNextId() {
	static Atomic64 next_id;
	return ++next_id;
}

void EntityPool::Initialize(Entity& e, String prefab) {
	uint64 ticks = GetMachine().GetTicks();
	e.SetId(GetNextId());
	e.SetPrefab(prefab);
	e.SetCreated(ticks);
	e.SetChanged(ticks);
	
}

EntityRef EntityPool::Clone(const Entity& e) {
	EntityRef c = CreateFromComponentMap(GetMachine().Get<ComponentStore>()->Clone(e.GetComponents()));
	if (c) {
		Initialize(*c);
		c->CopyHeader(e);
	}
	return c;
}

void EntityPool::UnlinkDeep() {
	for (EntityPoolRef& p : pools)
		p->UnlinkDeep();
	
	for (auto it = objects.rbegin(); it != objects.rend(); --it) {
		Connector* conn = it().Find<Connector>();
		if (conn)
			conn->UnlinkAll();
	}
}
	
void EntityPool::UninitializeComponentsDeep() {
	for (EntityPoolRef& p : pools)
		p->UninitializeComponentsDeep();
	
	for (auto it = objects.rbegin(); it != objects.rend(); --it) {
		it().UninitializeComponents();
	}
}

void EntityPool::ClearComponentsDeep() {
	for (EntityPoolRef& p : pools)
		p->ClearComponentsDeep();
	
	for (auto it = objects.rbegin(); it != objects.rend(); --it) {
		it().ClearComponents();
	}
}

void EntityPool::ClearDeep() {
	for (EntityPoolRef& p : pools)
		p->ClearDeep();
	pools.Clear();
	
	objects.Clear();
}

void EntityPool::ReverseEntities() {
	objects.Reverse();
}

void EntityPool::Clear() {
	UnlinkDeep();
	UninitializeComponentsDeep();
	ClearComponentsDeep();
	ClearDeep();
}

void EntityPool::PruneFromContainer() {
	for (auto& pool : pools)
		pool->PruneFromContainer();
	Destroyable::PruneFromContainer(objects);
}

/*EntityRef EntityPool::CreateEmpty() {
	Entity* ent = new Entity(GetNextId(), *this);
	Ref<Entity> sent;
	sent.WrapObject(ent);
	ent->InitWeak(sent);
	AddEntity(sent);
	Initialize(*sent);
	return sent;
}*/

/*EntityRef EntityPool::CreateFromComponentMap(ComponentMap components) {
	Entity* ent = new Entity(PickFn(components), GetNextId(), *this);
	Ref<Entity> sent;
	sent.WrapObject(ent);
	ent->InitWeak(sent);
	ent->RefreshConnectorPtr();
	ent->UpdateInterfaces();
	AddEntity(sent);
	return sent;
}*/

/*void EntityPool::AddEntity(EntityRef obj) {
	objects.Add(obj);
}*/

















EntityVisitor::EntityVisitor(EntityPoolVec& pool, int mode) : base(pool), mode(mode) {
	Reset();
}

EntityVisitor::EntityVisitor(Machine& m, int mode) :
	base(m.Get<EntityStore>()->GetRootVec()),
	mode(mode)
{
	Reset();
}

EntityVisitor::EntityVisitor(Entity& e, int mode) : base(e.GetPool().GetParent()->GetPools()), mode(mode) {
	Reset();
}

void EntityVisitor::Reset() {
	stack.SetCount(0);
	cur.Clear();
	if (!base.IsEmpty()) {
		EntityPoolVec::Iterator pool = base.begin();
		EntityPool& p = pool();
		if (mode == POOL_CURRENT_AND_CHILDREN || mode == POOL_CURRENT_ONLY) {
			if (p.HasEntities()) {
				Item& i = stack.Add();
				i.pool = pool;
				i.ent = p.Begin();
				cur = *i.ent;
			}
		}
		else if (mode == POOL_CHILDREN_ONLY) {
			if (p.HasEntityPools()) {
				EntityPoolVec::Iterator first = p.BeginPool();
				if (first().HasEntities()) {
					{
						Item& i = stack.Add();
						i.pool = pool;
						i.finished = true;
					} {
						Item& i = stack.Add();
						i.pool = first;
						i.ent = first().Begin();
						cur = *i.ent;
					}
				}
			}
		}
		else Panic("Invalid EntityVisitor mode");
	}
}

void EntityVisitor::Skip(EntityPool::Bit entpool_bit) {
	freeze_checks.SetTrue(entpool_bit);
}

Entity* EntityVisitor::operator->() {
	return cur.Get();
}

EntityRef EntityVisitor::operator*() {
	return cur;
}

EntityVisitor::operator bool() const {
	return cur;
}

void EntityVisitor::operator++(int) {
	FindNextDepthFirst();
}

bool EntityVisitor::FindNextDepthFirst() {
	if (cur) {
		if (stack.GetCount() > 1) {
			Item& top = stack.Top();
			if (!top.ent && !top.finished) {
				if (top.pool().HasEntities()) {
					top.ent = top.pool().Begin();
					return true;
				}
				else {
					return NewPoolNextDepthFirst();
				}
			}
			else {
				++top.ent;
				if (top.ent)
					return true;
				else
					return NewPoolNextDepthFirst();
			}
		}
		return true;
	}
	return false;
}

bool EntityVisitor::NewPoolNextDepthFirst() {
	if (mode == POOL_CURRENT_AND_CHILDREN) {
		if (PoolFindNextDepthFirst())
			return FindNextDepthFirst();
		else
			return false;
	}
	else {
		cur.Clear();
		stack.SetCount(0);
		return false;
	}
}

bool EntityVisitor::PoolFindNextDepthFirst() {
	if (cur) {
		if (stack.GetCount() > 1) {
			Item& top = stack.Top();
			if (top.pool().HasEntityPools())
				PoolPushSub();
			else {
				PoolIncPopWhileTop();
				if (stack.IsEmpty()) {
					cur.Clear();
					return false;
				}
			}
		}
		else if (stack.GetCount() == 1) {
			PoolPushSub();
		}
		return true;
	}
	return false;
}

void EntityVisitor::PoolIncPopWhileTop() {
	while (1) {
		if (stack.GetCount() > 1) {
			Item& top = stack.Top();
			++top.pool;
			if (top.pool)
				break;
			else
				stack.SetCount(stack.GetCount()-1);
		}
		else {
			stack.SetCount(0);
			break;
		}
	}
}

void EntityVisitor::PoolPushSub() {
	Item& top = stack.Add();
	Item& parent = stack[stack.GetCount()-2];
	top.pool = parent.pool().BeginPool();
}








EntityParentVisitor::EntityParentVisitor(EntityPool& pool) : base(pool) {
	Reset();
}

EntityParentVisitor::EntityParentVisitor(Entity& e) : base(e.GetPool()) {
	Reset();
}

void EntityParentVisitor::Reset() {
	cur.Clear();
	cur_pool = &base;
	if (base.HasEntities()) {
		cur = base.Begin();
	}
}

void EntityParentVisitor::Skip(EntityPool::Bit entpool_bit) {
	freeze_checks.SetTrue(entpool_bit);
}

Entity* EntityParentVisitor::operator->() {
	return &cur();
}

EntityRef EntityParentVisitor::operator*() {
	return *cur;
}

EntityParentVisitor::operator bool() const {
	return cur;
}

void EntityParentVisitor::operator++(int) {
	FindNextChildFirst();
}

bool EntityParentVisitor::FindNextChildFirst() {
	if (cur_pool) {
		++cur;
		if (cur) {
			return true;
		}
		else {
			cur.Clear();
			while (1) {
				cur_pool = cur_pool->GetParent();
				if (!cur_pool) {
					break;
				}
				if (cur_pool->HasEntities()) {
					cur = cur_pool->Begin();
					return true;
				}
			}
		}
	}
	return false;
}











NAMESPACE_OULU_END
