#ifndef _EcsMinimal_Prefabs_h_
#define _EcsMinimal_Prefabs_h_



NAMESPACE_ECS_BEGIN


#if 0

template <class T> void SimpleEntityApp() {
	Engine& mach = GetActiveEngine();
	
	#ifdef flagSTDEXC
	try {
	#endif
		Ref<EntityStore> ents = mach.TryGet<EntityStore>();
		if (ents.IsEmpty())
			THROW(Exc("EntityStore was not added to the ECS machine"));
		
		PoolRef pool = ents->GetRoot()->GetAddPool("app");
		EntityRef app = pool->CreateEmpty();
		app->Add<T>();
		
	    TimeStop t;
	    while (mach.IsRunning()) {
	        double dt = ResetSeconds(t);
	        mach.Update(dt);
	        if (t.Seconds() < 0.001)
				Sleep(1);
	    }
	#ifdef flagSTDEXC
	}
	catch (Exc e) {
		LOG("error: " << e);
	}
	#endif
}

template <class T> void SimpleEngineMain(String title, bool start_machine=false) {
	Engine& mach = GetActiveEngine();
	
	
	if (start_machine) {
		ASSERT(!mach.IsRunning());
		
		try {
		    RegistrySystem& reg = *mach.Add<RegistrySystem>();
			EntityStore& ents = *mach.Add<EntityStore>();
		    mach.Add<ComponentStore>();
		    mach.Add<ConnectorStore>();
		    mach.Add<ExtSystem>();
		    
		    #if HAVE_SDL2
		    mach.Add<SDL2GUI3DSystem>();
		    #endif
		    
		    #ifdef flagOPENVR
		    mach.Add<OpenVR>();
		    #endif
		    
		    reg.SetAppName(title);
		    
		    if (!mach.Start()) {
		        LOG("error: machine wouldn't start");
		        return;
		    }
		}
		catch (Exc e) {
			LOG("error: " << e);
			return;
		}
	}
	else if (!mach.IsRunning()) {
		LOG("error: machine is not running and start argument wasn't set");
		return;
	}
	
	try {
		Ref<EntityStore> ents = mach.TryGet<EntityStore>();
		if (ents.IsEmpty())
			throw Exc("EntityStore was not added to the ECS machine");
		
		PoolRef root = ents->GetRoot();
		
		#if HAVE_SDL2
			#ifdef flagGUI
				EntityRef app = root->Create<StandaloneWindow>();
			#else
				EntityRef app = root->Create<StandaloneConsole>
				();
			#endif
			app->Add<T>();
			app->Find<Connector>()->ConnectAll();
		#endif
		
		#ifdef flagVR
		EntityRef cam = root->Create<CameraPrefab>();
		cam->Find<Connector>()->ConnectAll(CONNAREA_POOL_CURRENT);
		#endif
		
	    TimeStop t;
	    while (mach.IsRunning()) {
	        double dt = ResetSeconds(t);
	        mach.Update(dt);
	        Sleep(1);
	    }
	}
	catch (Exc e) {
		LOG("error: " << e);
	}
	
	if (start_machine) {
		mach.Stop();
	}
	
}


#define CONSOLE_APP_(x) CONSOLE_APP_MAIN {TS::SimpleEntityApp<x>();}
#define RENDER_APP_(x) RENDER_APP_MAIN {TS::SimpleEntityApp<x>();}
#define GUI_APP_(x) GUI_APP_MAIN {TS::SimpleEntityApp<x>();}
#define APP_INITIALIZE_(x) \
	NAMESPACE_UPP \
	INITBLOCK {TS::Engine::WhenInitialize << callback(x);} \
	END_UPP_NAMESPACE
#define APP_STARTUP_(x) \
	NAMESPACE_UPP \
	INITBLOCK {TS::Engine::WhenPreFirstUpdate << callback(x);} \
	END_UPP_NAMESPACE
#define APP_DEFAULT_GFX_(x) \
	NAMESPACE_UPP \
	INITBLOCK {TS::GetAppFlags().gfx = TS::AppFlags::x;} \
	END_UPP_NAMESPACE



#endif




void DefaultEcsInitializer();
void DefaultEcsStartup();

#define ECS_PREFAB_MAIN(x) \
	NAMESPACE_UPP \
	INITBLOCK {TS::Ecs::Engine::WhenInitialize << callback(TS::Ecs::DefaultEcsInitializer); TS::Ecs::Engine::WhenPreFirstUpdate << callback(TS::Ecs::DefaultEcsStartup); TS::Ecs::DefaultCreateOnStart<x>();} \
	END_UPP_NAMESPACE \
	ECS_APP_MAIN


#define SIMPLE_ECS_APP_(ecs_component, eon_path, eon_args) \
	PREFAB_BEGIN(App) \
		ecs_component \
	PREFAB_END \
	APP_STARTUP_(TS::BindEcsToSerial) \
	 \
	ECS_PREFAB_MAIN(App) { \
		using namespace UPP; \
		String eon_file  = Parallel::RealizeEonFile(eon_path); \
		if (FileExists(eon_file)) { \
			/*TS::ECS::DefaultCreateOnStart<App>();*/ \
			TS::DefaultRunner(true, #ecs_component, eon_file, 0, eon_args); \
		} \
		else { \
			LOG("Eon file was not found"); \
		} \
	}

#define SIMPLE_ECS_APP(ecs_component, eon_path) SIMPLE_ECS_APP_(ecs_component, eon_path, "")



#define GUI_APP_MAIN_ \
	void UserGuiMainFn_(); \
	\
	PREFAB_BEGIN(App) \
		TS::Ecs::DefaultGuiAppComponent \
	PREFAB_END \
	\
	APP_INITIALIZE_STARTUP2_2_ECS(TS::DefaultSerialInitializer, TS::DefaultStartup, TS::BindEcsToSerial, UserGuiMainFn_) \
	\
	ECS_PREFAB_MAIN(App) { \
		using namespace UPP; \
		String eon_file  = Parallel::RealizeEonFile("DefaultGuiApp.eon"); \
		if (FileExists(eon_file)) { \
			/*TS::ECS::DefaultCreateOnStart<App>();*/ \
			TS::DefaultRunner(false, "Gui App", eon_file, 0, 0); \
		} \
		else { \
			LOG("Eon file was not found"); \
			Exit(1); \
		} \
		UserGuiMainFn_(); \
		TS::DefaultRunnerStop(); \
	} \
	void UserGuiMainFn_()


#undef GUI_APP_MAIN
#define GUI_APP_MAIN GUI_APP_MAIN_


NAMESPACE_ECS_END


#endif
