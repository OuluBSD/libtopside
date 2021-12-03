#include "Tutorial7.h"

// Tutorial 7: Octree. Original work.



GUI_APP_MAIN {
	Ref<Machine> mach;
	
	
	try {
		mach.Create();
	    
	    OctreeSystem& oct = *mach->Add<OctreeSystem>();
	    EntityStore& ents = *mach->Add<EntityStore>();
	    mach->Add<ComponentStore>();
	    mach->Add<PipelineSystem>();
	    mach->Add<ConnectorSystem>();
	    
	    #if HAVE_SDL2
	    mach->Add<SDL2_System>();
	    #endif
	    
	    if (mach->Start()) {
	        
			EntityRef pipe = ents.Create<OctreeEditPipeline>();
		    pipe->Find<Connector>()->ConnectAll();
			
		    #if HAVE_SDL2
			EntityRef app = ents.Create<StandaloneSDL2>();
			#else
			#error Use at least one system
			#endif
			
			app->Add<Tutorial7>();
			app->Find<Connector>()->ConnectAll();
			
			float l = oct.GetHumanLength();
			float ll = 1.0f / 8.0f;
			EntityRef ground = ents.Create<OctreeGround>();
			
			vec3 a{-l,        0,        l};
			vec3 b{ 0, 2.0f * l, 0.5f * l};
			vec3 c{+l,        0, 2.0f * l};
			ground->Find<OctreeComponent>()->
				DrawLine(a, b, ll).
				DrawLine(b, c, ll);
			
			
		    TimeStop t;
		    while (mach->IsRunning()) {
		        double dt = t.ResetElapsedSeconds();
		        mach->Update(dt);
		        Sleep(1);
		    }
	    }
	}
	catch (Exc e) {
		LOG("Fatal error: " << e);
	}
	
	mach->Stop();
	mach.Clear();
}
