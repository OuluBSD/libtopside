#ifndef _Complete_Prefabs_h_
#define _Complete_Prefabs_h_



NAMESPACE_TOPSIDE_BEGIN

/*struct StandaloneWindow : EntityPrefab
	<DirectWindow, Connector>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		return components;
    }
};*/



template <class T> void SimpleEntityApp() {
	Machine& mach = GetActiveMachine();
	
	#ifdef flagSTDEXC
	try {
	#endif
		Ref<EntityStore> ents = mach.TryGet<EntityStore>();
		if (ents.IsEmpty())
			THROW(Exc("EntityStore was not added to the ECS machine"));
		
		PoolRef pool = ents->GetRoot()->GetAddPool("app");
		EntityRef app = pool->CreateEmpty();
		app->Add<T>();
		//pool->Add<ConnectAllInterfaces<T>>();
		
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
	Machine& mach = GetActiveMachine();
	
	TODO
	#if 0
	
	if (start_machine) {
		ASSERT(!mach.IsRunning());
		
		try {
		    RegistrySystem& reg = *mach.Add<RegistrySystem>();
			EntityStore& ents = *mach.Add<EntityStore>();
		    mach.Add<ComponentStore>();
		    mach.Add<ConnectorSystem>();
		    mach.Add<HumanSystem>();
		    mach.Add<DisplaySystem>();
		    mach.Add<AudioSystem>();
		    
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
		
		EntityRef cam = root->Create<CameraPrefab>();
		cam->Find<Connector>()->ConnectAll(CONNAREA_POOL_CURRENT);
		
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
	
	#endif
}

#if 0

#define CONSOLE_APP_(x) CONSOLE_APP_MAIN {TS::SimpleEntityApp<x>();}
#define RENDER_APP_(x) RENDER_APP_MAIN {TS::SimpleEntityApp<x>();}
#define GUI_APP_(x) GUI_APP_MAIN {TS::SimpleEntityApp<x>();}
#define APP_INITIALIZE_(x) \
	NAMESPACE_UPP \
	INITBLOCK {TS::Machine::WhenInitialize << callback(x);} \
	END_UPP_NAMESPACE
#define APP_STARTUP_(x) \
	NAMESPACE_UPP \
	INITBLOCK {TS::Machine::WhenPreUpdate << callback(x);} \
	END_UPP_NAMESPACE
#define APP_DEFAULT_GFX_(x) \
	NAMESPACE_UPP \
	INITBLOCK {TS::GetAppFlags().gfx = TS::AppFlags::x;} \
	END_UPP_NAMESPACE

#endif

NAMESPACE_TOPSIDE_END


#endif
