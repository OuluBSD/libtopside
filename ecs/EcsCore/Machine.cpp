#include "EcsCore.h"


NAMESPACE_OULU_BEGIN


SystemBase::SystemBase(Machine& machine) : machine(machine) {}

Callback Machine::WhenStarting;
		
bool Machine::Start() {
	ASSERT_(!is_initialized && !is_started, "Shouldn't call Start if we already started");
	
	WhenStarting();
	
	for (auto& system : m_systems) {
		if (!system->Initialize())
			return false;
	}
	
	is_initialized = true;
	
	for (auto& system : m_systems) {
		system->Start();
	}
	
	is_started = true;
	is_running = true;
	return true;
}

void Machine::Update(float dt) {
	ASSERT_(is_started, "Shouldn't call Update if we haven't been started");
	
	if (dt <= 0.0)
		return;
	if (dt > 0.5)
		dt = 0.5;
		
	if (is_suspended) {
		return;
	}
	
	for (auto& system : m_systems) {
		system->Update(dt);
	}
	
	ticks += 1;
}

void Machine::Stop() {
	ASSERT_(is_started, "Shouldn't call Stop if we haven't been started");
	
	is_started = false;
	
	for (auto it = m_systems.End() - 1; it != m_systems.Begin() - 1; --it) {
		(*it)->Stop();
	}
	
	is_initialized = false;
	
	for (auto it = m_systems.End() - 1; it != m_systems.Begin() - 1; --it) {
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

Machine::SystemCollection::Iterator Machine::FindSystem(const TypeId& typeId) {
	return FindIf(m_systems.begin(), m_systems.end(),
		[typeId](const Shared<SystemBase>& system) {
		return typeId == system->GetType();
	});
}

void Machine::Add(const TypeId& typeId, Shared<SystemBase> system) {
	ASSERT_(!is_started, "Invalid to add systems after the machine has started");
	
	auto it = FindSystem(typeId);
	ASSERT(it == m_systems.end());
	
	m_systems.Add(pick(system));
}

void Machine::Remove(const TypeId& typeId) {
	ASSERT_(!is_started, "Invalid to remove systems after the machine has started");
	
	Machine::SystemCollection::Iterator it = FindSystem(typeId);
	ASSERT(it != m_systems.end());
	
	m_systems.Remove(it - m_systems.Begin());
}


NAMESPACE_OULU_END

