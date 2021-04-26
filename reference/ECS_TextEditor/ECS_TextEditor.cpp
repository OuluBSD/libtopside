#include "ECS_TextEditor.h"

NAMESPACE_OULU_BEGIN



void Main() {
	SetCoutLog();
	
	Machine mach;
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
	EntityStoreRef es = mach.Add<EntityStore>();
	EntityPoolRef root = es->GetRoot();
	//EntityPoolRef actors = root->AddPool("actors");
	//EntityPoolRef externals = root->AddPool("externals");
	
    mach.Add<ComponentStore>();
    mach.Add<OverlapSystem>();
    mach.Add<ActionSystem>();
    
    
    //VAR actor = actors->Create<DemoActor>();
    
    
    try {
	    mach.Start();
	    
	    TimeStop t;
	    while (mach.IsRunning()) {
	        double dt = ResetSeconds(t);
	        mach.Update(dt);
	        Sleep(1);
	        
	        
	        
	        break;
	        
	        
	        
	    }
    }
    catch (Exc e) {
        LOG("error: " << e);
        Exit(1);
    }
    
    mach.Stop();
}

NAMESPACE_OULU_END


CONSOLE_APP_MAIN {
	Oulu::Main();
}

