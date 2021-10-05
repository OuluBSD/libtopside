#include "EcsMach.h"


NAMESPACE_ECS_BEGIN


SystemBase::SystemBase() {
	DBG_CONSTRUCT
}

SystemBase::~SystemBase() {
	DBG_DESTRUCT
}

Engine& SystemBase::GetEngine() const {
	return *GetParent().AsStatic<Engine>();
}


Callback Engine::WhenInitialize;
Callback Engine::WhenPreFirstUpdate;




Engine::Engine() {
	DBG_CONSTRUCT
}

Engine::~Engine() {
	ASSERT_(!is_initialized && !is_started, "Engine should be in a clean state upon destruction");
	systems.Clear();
	DBG_DESTRUCT
}


bool Engine::Start() {
	ASSERT_(!is_initialized && !is_started, "Shouldn't call Start if we already started");
	
	WhenInitialize();
	
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
	
	is_started = true;
	is_running = true;
	return true;
}

void Engine::Update(double dt) {
	ASSERT_(is_started, "Shouldn't call Update if we haven't been started");
	
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

void Engine::Stop() {
	if (!is_started)
		return;
	
	is_running = false;
	is_started = false;
	
	DBG_BEGIN_UNREF_CHECK
	
	for (auto it = systems.rbegin(); it != systems.rend(); --it) {
		(*it)->Stop();
	}
	
	is_initialized = false;
	
	for (auto it = systems.rbegin(); it != systems.rend(); --it) {
		(*it)->Uninitialize();
	}
}

void Engine::Suspend() {
	is_suspended = true;
}

void Engine::Resume() {
	is_suspended = false;
}

bool Engine::HasStarted() const {
	return is_started;
}

void Engine::Add(TypeCls type_id, SystemBase* system) {
	ASSERT_(!is_started, "Invalid to add systems after the machine has started");
	
	auto it = FindSystem(type_id);
	ASSERT(!it);
	
	ASSERT(system->GetParent());
	systems.Add(type_id, system);
}

void Engine::Remove(TypeCls type_id) {
	ASSERT_(!is_started, "Invalid to remove systems after the machine has started");
	
	Engine::SystemCollection::Iterator it = FindSystem(type_id);
	ASSERT(it);
	
	systems.Remove(it);
}

void Engine::Visit(RuntimeVisitor& vis) {
	for (auto iter = systems.begin(); iter; ++iter)
		vis.Visit(iter());
}







Engine* __active_engine;

Engine& GetActiveEngine() {
	ASSERT(__active_engine);
	return *__active_engine;
}

void SetActiveEngine(Engine& e) {
	__active_engine = &e;
}

void ClearActiveEngine() {
	__active_engine = 0;
}

void SingleEngine::Run(bool gui, void(*fn)()) {
	if (Open(gui)) {
		fn();
		Close();
	}
}

//#if UPP_VERSION
bool SingleEngine::Open(bool gui) {return true;}
void SingleEngine::Close() {eng.Stop();}
//#endif

NAMESPACE_ECS_END

