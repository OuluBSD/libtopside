#include "EcsLib.h"

NAMESPACE_TOPSIDE_BEGIN


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

void PathwayRouter::Add(EntityRef e) {
	add_queue.Add(e);
}

void PathwayRouter::Update(double dt) {
	if (add_queue.IsFilled())
		ProcessAddQueue();
	
}

void PathwayRouter::ProcessAddQueue() {
	
	for (EntityRef& e : add_queue) {
		
		
		TODO
		
	}
	
}

void PathwayRouter::UnlinkAll() {
	Machine& mach = ConnectorBase::GetPool()->GetMachine();
	
	if (!mach.IsRunning()) {
		for (ExchangePointRef& pt : pts) {
			pt->Source()	->UnlinkAll();
			pt->Sink()		->UnlinkAll();
		}
	}
	else {
		for (ExchangePointRef& pt : pts) {
			pt->Source()	->Unlink(pt->Sink());
		}
	}
	
	pts.Clear();
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



NAMESPACE_TOPSIDE_END
