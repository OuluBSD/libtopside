#include "SerialMach.h"

NAMESPACE_SERIAL_BEGIN


SystemBase::SystemBase() {
	DBG_CONSTRUCT
}

SystemBase::~SystemBase() {
	DBG_DESTRUCT
}


Callback Machine::WhenInitialize;
Callback Machine::WhenPreFirstUpdate;




Machine::Machine() {
	DBG_CONSTRUCT
}

Machine::~Machine() {
	ASSERT_(!is_initialized && !is_started, "Machine should be in a clean state upon destruction");
	systems.Clear();
	DBG_DESTRUCT
}


bool Machine::Start() {
	ASSERT_(!is_initialized && !is_started, "Shouldn't call Start if we already started");
	
	WhenInitialize();
	
	is_started = true;
	
	for (auto system : systems) {
		if (!system->Initialize()) {
			LOG("Could not initialize system " << system->GetDynamicName());
			return false;
		}
	}
	
	is_initialized = true;
	
	for (auto& system : systems) {
		system->Start();
	}
	
	warning_age = 0;
	
	is_running = true;
	return true;
}

void Machine::Update(double dt) {
	ASSERT_(is_started, "Shouldn't call Update if we haven't been started");
	
	warning_age += dt;
	if (warning_age > 3.0) {
		warning_age = 0;
		last_warnings.Clear();
	}
	
	if (!ticks)
		WhenPreFirstUpdate();
	
	WhenEnterUpdate();
	
	if (dt <= 0.0) {
		WhenLeaveUpdate();
		return;
	}
	if (dt > 0.5)
		dt = 0.5;
		
	if (is_suspended) {
		WhenLeaveUpdate();
		return;
	}
	
	for (auto& system : systems) {
		SystemBase* b = &*system;
		WhenEnterSystemUpdate(*b);
		
		system->Update(dt);
		
		WhenLeaveSystemUpdate();
	}
	
	++ticks;
	
	WhenLeaveUpdate();
}

void Machine::Stop() {
	bool was_started = is_started;
	
	is_running = false;
	is_started = false;
	
	DBG_BEGIN_UNREF_CHECK
	
	if (was_started) {
		for (auto it = systems.rbegin(); it != systems.rend(); --it) {
			(*it)->Stop();
		}
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

bool Machine::HasStarted() const {
	return is_started;
}

void Machine::Add(TypeCls type_id, SystemBase* system) {
	ASSERT_(!is_started, "Invalid to add systems after the machine has started");
	
	auto it = FindSystem(type_id);
	ASSERT(!it);
	
	ASSERT(system->GetParent());
	systems.Add(type_id, system);
}

void Machine::Remove(TypeCls type_id) {
	ASSERT_(!is_started, "Invalid to remove systems after the machine has started");
	
	Machine::SystemCollection::Iterator it = FindSystem(type_id);
	ASSERT(it);
	
	systems.Remove(it);
}

void Machine::Visit(RuntimeVisitor& vis) {
	for (auto iter = systems.begin(); iter; ++iter)
		vis.Visit(iter());
}

void Machine::WarnDeveloper(String msg) {
	if (last_warnings.Find(msg) < 0) {
		last_warnings.Add(msg);
		
		#if !defined flagDEBUG_RT && defined flagDEBUG
		LOG("Machine: developer warning: " << msg);
		#endif
	}
}







Machine* __active_machine;

Machine& GetActiveMachine() {
	ASSERT(__active_machine);
	return *__active_machine;
}

void SetActiveMachine(Machine& m) {
	__active_machine = &m;
}

void ClearActiveMachine() {
	__active_machine = 0;
}


NAMESPACE_SERIAL_END



NAMESPACE_TOPSIDE_BEGIN


void SingleMachine::Run(bool gui, void(*fn)()) {
	if (Open(gui)) {
		fn();
		Close();
	}
}



NAMESPACE_TOPSIDE_END
