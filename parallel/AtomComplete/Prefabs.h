#ifndef _AtomComplete_Prefabs_h_
#define _AtomComplete_Prefabs_h_



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

NAMESPACE_SERIAL_END


#endif
