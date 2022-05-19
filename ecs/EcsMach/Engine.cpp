#include "EcsMach.h"


NAMESPACE_SERIAL_BEGIN

bool EntitySystem::Initialize() {
	engine = new Ecs::Engine;
	engine->sys = this;
	SetActiveEngine(*engine);
	return true;
}

void EntitySystem::Start() {
	engine->Start();
}

void EntitySystem::Update(double dt) {
	if (engine->IsRunning())
		engine->Update(dt);
}

void EntitySystem::Stop() {
	engine->Stop();
}

void EntitySystem::Uninitialize() {
	ClearEngine();
}

void EntitySystem::ClearEngine() {
	if (engine) {
		engine->Clear();
		delete engine;
		engine = 0;
	}
}

NAMESPACE_SERIAL_END



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


Callback Engine::WhenGuiProgram;
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
	
	is_looping_systems = true;
	
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
	
	is_looping_systems = false;
	
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
	
	is_looping_systems = true;
	
	for (auto& system : systems) {
		SystemBase* b = &*system;
		WhenEnterSystemUpdate(*b);
		
		system->Update(dt);
		
		WhenLeaveSystemUpdate();
	}
	
	is_looping_systems = false;
	
	++ticks;
	
	WhenLeaveUpdate();
}

void Engine::Stop() {
	if (!is_started)
		return;
	
	is_running = false;
	is_started = false;
	
	DBG_BEGIN_UNREF_CHECK
	
	is_looping_systems = true;
	
	for (auto it = systems.rbegin(); it != systems.rend(); --it) {
		(*it)->Stop();
	}
	
	is_initialized = false;
	
	for (auto it = systems.rbegin(); it != systems.rend(); --it) {
		(*it)->Uninitialize();
	}
	
	is_looping_systems = false;
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
	//ASSERT_(!is_started, "adding systems after the machine has started" is error-prone);
	ASSERT_(!is_looping_systems, "adding systems while systems are being iterated is error-prone");
	
	auto it = FindSystem(type_id);
	ASSERT(!it);
	
	ASSERT(system->GetParent());
	if (is_started) {
		if (system->Initialize()) {
			RTLOG("Engine::Add: added system to already running engine: " << system->GetDynamicName());
			systems.Add(type_id, system);
		}
		else {
			RTLOG("Engine::Add: error: could not initialize system in already running engine: " << system->GetDynamicName());
			delete system;
		}
	}
}

void Engine::Remove(TypeCls type_id) {
	ASSERT_(!is_started, "removing systems after the machine has started is error-prone");
	
	Engine::SystemCollection::Iterator it = FindSystem(type_id);
	ASSERT(it);
	
	systems.Remove(it);
}

void Engine::Visit(RuntimeVisitor& vis) {
	for (auto iter = systems.begin(); iter; ++iter)
		vis.Visit(iter());
}

void Engine::AddToUpdateList(ComponentBase* c) {
	VectorFindAdd(update_list, c);
}

void Engine::RemoveFromUpdateList(ComponentBase* c) {
	VectorRemoveKey(update_list, c);
}

Ref<SystemBase> Engine::Add(TypeCls type)
{
    NewSystemFn fn = TypeNewFn().Get(type, 0);
    ASSERT(fn);
    if (!fn)
        return Ref<SystemBase>();
	SystemBase* syst = fn(*this);
    Add(type, syst);
    return syst->AsRefT<SystemBase>();
}

Ref<SystemBase> Engine::GetAdd(String id) {
    int i = EonToType().Find(id);
    if (i < 0)
        return Ref<SystemBase>();
    TypeCls type = EonToType()[i];
    SystemCollection::Iterator it = FindSystem(type);
    if (it)
        return it->AsRef<SystemBase>();
    return Add(type);
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


NAMESPACE_SERIAL_BEGIN


void MachineEcsInit() {
	Machine& mach = GetActiveMachine();
	
	mach.Add<EntitySystem>();
	
	
	/*Ecs::Engine& eng = Ecs::GetActiveEngine();
	
    #ifdef flagOPENVR
    eng.Add<OpenVR>();
    #endif*/
    /*eng.Add<HolographicScene>();
    eng.Add<EasingSystem>();
    eng.Add<MotionControllerSystem>();
    eng.Add<WorldLogicSystem>();*/
	   
    //if (flags.HaveOdePhysics())
	//	eng.Add<OdeSystem>();
	
    
}


NAMESPACE_SERIAL_END
