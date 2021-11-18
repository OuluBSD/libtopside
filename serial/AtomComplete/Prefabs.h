#ifndef _Complete_Prefabs_h_
#define _Complete_Prefabs_h_



NAMESPACE_SERIAL_BEGIN



template <class T> void SimpleSerialApp() {
	Machine& mach = GetActiveMachine();
	
	#ifdef flagSTDEXC
	try {
	#endif
		Ref<LoopStore> loops = mach.Find<LoopStore>();
		if (loops.IsEmpty())
			THROW(Exc("LoopStore was not added to the ECS machine"));
		
		LoopRef loop = loops->GetRoot()->GetAddLoop("app");
		LoopRef app = loop->CreateEmpty();
		
		TODO
		//app->Add<T>();
		
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

void SimpleSerialMain(String title, bool start_machine=false);

#define CONSOLE_APP_(x) CONSOLE_APP_MAIN {TS::SimpleSerialApp<x>();}
#define RENDER_APP_(x) RENDER_APP_MAIN {TS::SimpleSerialApp<x>();}
#define GUI_APP_(x) SERIAL_APP_MAIN {TS::SimpleSerialApp<x>();}
#define APP_INITIALIZE_(x) \
	NAMESPACE_UPP \
	INITBLOCK {TS::Serial::Machine::WhenInitialize << callback(x);} \
	END_UPP_NAMESPACE
#define APP_STARTUP_(x) \
	NAMESPACE_UPP \
	INITBLOCK {TS::Serial::Machine::WhenPreFirstUpdate << callback(x);} \
	END_UPP_NAMESPACE
#define APP_INITIALIZE_STARTUP_(init, startup) \
	NAMESPACE_UPP \
	INITBLOCK {TS::Serial::Machine::WhenInitialize << callback(init); TS::Serial::Machine::WhenPreFirstUpdate << callback(startup);} \
	END_UPP_NAMESPACE
#define APP_DEFAULT_GFX_(x) \
	NAMESPACE_UPP \
	INITBLOCK {TS::Serial::GetAppFlags().gfx = TS::AppFlags::x;} \
	END_UPP_NAMESPACE
#define ECS_INITIALIZE_STARTUP_(init, startup) \
	NAMESPACE_UPP \
	INITBLOCK {TS::Ecs::Engine::WhenInitialize << callback(init); TS::Ecs::Engine::WhenPreFirstUpdate << callback(startup);} \
	END_UPP_NAMESPACE

NAMESPACE_SERIAL_END


#endif
