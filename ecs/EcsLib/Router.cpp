#if 0
#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


void PathwayRouter::Initialize() {
	PathwaySystemRef sys = GetPool()->GetMachine().TryGet<PathwaySystem>();
	if (sys)
		sys->Add(AsRef<PathwayRouter>());
}

void PathwayRouter::Uninitialize() {
	UnlinkAll();
	
	PathwaySystemRef sys = GetPool()->GetMachine().TryGet<PathwaySystem>();
	if (sys)
		sys->Remove(AsRef<PathwayRouter>());
}

void PathwayRouter::Add(EntityRef e, String eon_code) {
	Item& i = add_queue.Add();
	i.e = e;
	i.eon_code = eon_code;
}

void PathwayRouter::Remove(EntityRef e) {
	for (auto iter = maintained.begin(); iter; ++iter) {
		if (iter->e == e) {
			maintained.Remove(iter);
			break;
		}
	}
}

void PathwayRouter::Update(double dt) {
	if (add_queue.IsFilled())
		ProcessAddQueue();
	
}

void PathwayRouter::ProcessAddQueue() {
	
	for (Item& i : add_queue) {
		
		
		TODO
		
		
	}
	
}

void PathwayRouter::UnlinkAll() {
	Machine& mach = ConnectorBase::GetPool()->GetMachine();
	
	for (ExchangePointRef& pt : pts) {
		pt->Source()	->ClearLink();
		pt->Sink()		->ClearLink();
		pt->Clear();
	}
	
	pts.Clear();
}











void PathwaySystem::Add(PathwayRouterRef p) {
	pathways.FindAdd(p);
}

void PathwaySystem::Remove(PathwayRouterRef p) {
	pathways.RemoveKey(p);
}

bool PathwaySystem::Initialize() {
	
	return true;
}

void PathwaySystem::Start() {
	
}

void PathwaySystem::Update(double dt) {
	for (auto& router : pathways)
		router->Update(dt);
}

void PathwaySystem::Stop() {
	
}

void PathwaySystem::Uninitialize() {
	
}



NAMESPACE_ECS_END
#endif
