#include "EcsCore.h"


NAMESPACE_OULU_BEGIN

bool EntityStore::Initialize() {
	root.SetName("root");
	return true;
}

void EntityStore::Uninitialize() {
	root.Clear();
}

void EntityStore::Update(float) {
	root.PruneFromContainer();
}





EntityPool::EntityPool(Machine& m) : machine(m) {
	
}

Entity::EntityId EntityPool::GetNextId() {
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

SharedEntity EntityPool::Clone(const Entity& e) {
	SharedEntity c = CreateFromComponentMap(GetMachine().Get<ComponentStore>()->Clone(e.GetComponents()));
	if (c)
		Initialize(*c);
	return c;
}

void EntityPool::UnlinkDeep() {
	for (EntityPool& p : pools)
		p.UnlinkDeep();
	
	for (auto it = objects.End() - 1; it != objects.Begin() - 1; --it) {
		Connector* conn = (**it).Find<Connector>();
		if (conn)
			conn->UnlinkAll();
	}
}
	
void EntityPool::UninitializeComponentsDeep() {
	for (EntityPool& p : pools)
		p.UninitializeComponentsDeep();
	
	for (auto it = objects.End() - 1; it != objects.Begin() - 1; --it) {
		(**it).UninitializeComponents();
	}
}

void EntityPool::ClearComponentsDeep() {
	for (EntityPool& p : pools)
		p.ClearComponentsDeep();
	
	for (auto it = objects.End() - 1; it != objects.Begin() - 1; --it) {
		(**it).ClearComponents();
	}
}

void EntityPool::ClearDeep() {
	for (EntityPool& p : pools)
		p.ClearDeep();
	pools.Clear();
	
	objects.Clear();
}

void EntityPool::Clear() {
	UnlinkDeep();
	UninitializeComponentsDeep();
	ClearComponentsDeep();
	ClearDeep();
}

void EntityPool::PruneFromContainer() {
	for (auto& pool : pools)
		pool.PruneFromContainer();
	Destroyable::PruneFromContainer(&objects);
}

SharedEntity EntityPool::CreateEmpty() {
	Entity* ent = new Entity(GetNextId(), *this);
	Shared<Entity> sent;
	sent.WrapObject(ent);
	ent->InitWeak(sent);
	SharedEntity e = AddEntity(sent);
	if (e)
		Initialize(*e);
	return e;
}

SharedEntity EntityPool::CreateFromComponentMap(ComponentMap components) {
	Entity* ent = new Entity(PickFn(components), GetNextId(), *this);
	Shared<Entity> sent;
	sent.WrapObject(ent);
	ent->InitWeak(sent);
	ent->RefreshConnectorPtr();
	ent->UpdateInterfaces();
	return AddEntity(sent);
}

SharedEntity EntityPool::AddEntity(SharedEntity obj) {
	objects.Add(obj);
	return obj;
}

















EntityVisitor::EntityVisitor(EntityPool& pool, int mode) : base(pool), mode(mode) {
	Reset();
}

EntityVisitor::EntityVisitor(Machine& m, int mode) : base(m.Get<EntityStore>()->GetRoot()), mode(mode) {
	Reset();
}

EntityVisitor::EntityVisitor(Entity& e, int mode) : base(e.GetPool()), mode(mode) {
	Reset();
}

void EntityVisitor::Reset() {
	stack.SetCount(0);
	cur = 0;
	if (mode == POOL_CURRENT_AND_CHILDREN || mode == POOL_CURRENT_ONLY) {
		if (base.GetCount()) {
			Item& i = stack.Add();
			i.pool_pos = 0;
			i.pool = &base;
			i.ent_pos = 0;
			i.ent = &*base.Get(0);
			cur = i.ent;
		}
	}
	else if (mode == POOL_CHILDREN_ONLY) {
		if (base.GetPoolCount()) {
			EntityPool& first = base.GetPool(0);
			if (first.GetCount()) {
				{
					Item& i = stack.Add();
					i.pool_pos = 0;
					i.pool = &base;
					i.ent_pos = base.GetCount();
					i.ent = 0;
				} {
					Item& i = stack.Add();
					i.pool_pos = 0;
					i.pool = &first;
					i.ent_pos = 0;
					i.ent = &*first.Get(0);
					cur = i.ent;
				}
			}
		}
	}
	else Panic("Invalid EntityVisitor mode");
}

void EntityVisitor::Skip(EntityPool::Bit entpool_bit) {
	freeze_checks.SetTrue(entpool_bit);
}

Entity* EntityVisitor::operator->() {
	return cur;
}

Entity* EntityVisitor::operator*() {
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
			if (top.ent_pos < 0) {
				if (top.pool->GetCount()) {
					top.ent_pos = 0;
					top.ent = &*top.pool->Get(top.ent_pos);
					return true;
				}
				else {
					return NewPoolNextDepthFirst();
				}
			}
			else if (++top.ent_pos < top.pool->GetCount()) {
				top.ent = &*top.pool->Get(top.ent_pos);
				return true;
			}
			else {
				top.ent = 0;
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
		cur = 0;
		stack.SetCount(0);
		return false;
	}
}

bool EntityVisitor::PoolFindNextDepthFirst() {
	if (cur) {
		if (stack.GetCount() > 1) {
			Item& top = stack.Top();
			if (top.pool->GetPoolCount())
				PoolPushSub(0);
			else {
				PoolIncPopWhileTop();
				if (stack.IsEmpty()) {
					cur = 0;
					return false;
				}
				PoolPushSub(stack.Top().pool_pos);
			}
		}
		else if (stack.GetCount() == 1) {
			PoolPushSub(0);
		}
		return true;
	}
	return false;
}

void EntityVisitor::PoolIncPopWhileTop() {
	while (1) {
		if (stack.GetCount() > 1) {
			Item& top = stack.Top();
			Item& parent = stack[stack.GetCount()-2];
			if (++top.pool_pos < parent.pool->GetPoolCount()) {
				top.pool = &parent.pool->GetPool(top.pool_pos);
				break;
			}
			else
				stack.SetCount(stack.GetCount()-1);
		}
		else {
			stack.SetCount(0);
			break;
		}
	}
}

void EntityVisitor::PoolPushSub(int pos) {
	Item& top = stack.Add();
	Item& parent = stack[stack.GetCount()-2];
	top.pool_pos = pos;
	top.pool = &parent.pool->GetPool(top.pool_pos);
	top.ent_pos = -1;
	top.ent = 0;
}








EntityParentVisitor::EntityParentVisitor(EntityPool& pool) : base(pool) {
	Reset();
}

EntityParentVisitor::EntityParentVisitor(Entity& e) : base(e.GetPool()) {
	Reset();
}

void EntityParentVisitor::Reset() {
	cur = 0;
	ent_pos = -1;
	cur_pool = &base;
	if (base.GetCount()) {
		ent_pos = 0;
		cur = &*base.Get(0);
	}
}

void EntityParentVisitor::Skip(EntityPool::Bit entpool_bit) {
	freeze_checks.SetTrue(entpool_bit);
}

Entity* EntityParentVisitor::operator->() {
	return cur;
}

Entity* EntityParentVisitor::operator*() {
	return cur;
}

EntityParentVisitor::operator bool() const {
	return cur;
}

void EntityParentVisitor::operator++(int) {
	FindNextChildFirst();
}

bool EntityParentVisitor::FindNextChildFirst() {
	if (cur_pool) {
		if (++ent_pos < cur_pool->GetCount()) {
			cur = &*cur_pool->Get(ent_pos);
			return true;
		}
		else {
			ent_pos = -1;
			cur = 0;
			while (1) {
				cur_pool = cur_pool->GetParent();
				if (!cur_pool)
					break;
				if (cur_pool->GetCount()) {
					ent_pos = 0;
					cur = &*cur_pool->Get(0);
					return true;
				}
			}
		}
	}
	return false;
}











NAMESPACE_OULU_END
