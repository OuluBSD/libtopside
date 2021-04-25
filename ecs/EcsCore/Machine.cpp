#include "EcsCore.h"


NAMESPACE_OULU_BEGIN


SystemBase::SystemBase(Machine& machine) : machine(machine) {}

Callback Machine::WhenStarting;
		
bool Machine::Start() {
	ASSERT_(!is_initialized && !is_started, "Shouldn't call Start if we already started");
	
	WhenStarting();
	
	for (auto system : systems) {
		if (!system->Initialize())
			return false;
	}
	
	is_initialized = true;
	
	for (auto& system : systems) {
		system->Start();
	}
	
	is_started = true;
	is_running = true;
	return true;
}

void Machine::Update(double dt) {
	ASSERT_(is_started, "Shouldn't call Update if we haven't been started");
	
	if (dt <= 0.0)
		return;
	if (dt > 0.5)
		dt = 0.5;
		
	if (is_suspended) {
		return;
	}
	
	for (auto& system : systems) {
		system->Update(dt);
	}
	
	ticks += 1;
}

void Machine::Stop() {
	ASSERT_(is_started, "Shouldn't call Stop if we haven't been started");
	
	is_started = false;
	
	for (auto it = systems.rbegin(); it != systems.rend(); --it) {
		(*it)->Stop();
	}
	
	is_initialized = false;
	
	for (auto it = systems.rbegin(); it != systems.rend(); --it) {
		(*it)->Uninitialize();
	}
}

void Machine::Suspend() {
	is_suspended = true;
}

void Machine::Resume() {
	is_suspended = false;
}

Machine::Machine() = default;

Machine::~Machine() {
	ASSERT_(!is_initialized && !is_started, "Machine should be in a clean state upon destruction");
}

bool Machine::HasStarted() const {
	return is_started;
}

void Machine::Add(const TypeId& type_id, SystemBase* system) {
	ASSERT_(!is_started, "Invalid to add systems after the machine has started");
	
	auto it = FindSystem(type_id);
	ASSERT(!it);
	
	systems.Add(type_id, system);
}

void Machine::Remove(const TypeId& type_id) {
	ASSERT_(!is_started, "Invalid to remove systems after the machine has started");
	
	Machine::SystemCollection::Iterator it = FindSystem(type_id);
	ASSERT(it);
	
	systems.Remove(it);
}


NAMESPACE_OULU_END

