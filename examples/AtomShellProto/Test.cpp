#include "AtomShellProto.h"

#
NAMESPACE_TOPSIDE_BEGIN


void Test() {
	using namespace Parallel;
	using namespace Serial;
	
	Machine mach;
	SetActiveMachine(mach);
	
	try {
	    RegistrySystem& reg = *mach.Add<RegistrySystem>();
		LoopStore& ents = *mach.Add<LoopStore>();
	    mach.Add<AtomStore>();
	    mach.Add<AtomSystem>();
	    TODO
	    
		LoopRef root = ents.GetRoot();
	    
	    reg.SetAppName("Test");
	    
	    if (!mach.Start()) {
	        LOG("error: machine wouldn't start");
	        return;
	    }
	    
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
	
	mach.Stop();
}


NAMESPACE_TOPSIDE_END

//CONSOLE_APP_MAIN {TS::Test();}
