#include "ECS_TextEditor.h"

NAMESPACE_TOPSIDE_BEGIN



void Main() {
	SetCoutLog();
	
	Machine mach;
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
	EntityStoreRef es = mach.Add<EntityStore>();
	PoolRef root = es->GetRoot();
	//PoolRef actors = root->AddPool("actors");
	//PoolRef externals = root->AddPool("externals");
	
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

NAMESPACE_TOPSIDE_END


CONSOLE_APP_MAIN {
	TS::Main();
}

