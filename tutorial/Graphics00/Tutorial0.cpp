#include <AtomComplete/AtomComplete.h>


using namespace TS;

struct Tutorial0 : Component<Tutorial0>, public DisplaySink {
	IFACE_CB(DisplaySink);
	IFACE_GENERIC;
	void operator=(const Tutorial0& t) {Panic("Can't copy");}
	
	void Render(SystemDraw& draw) override {
		draw.DrawRect(draw.GetPageSize(), Black());
	}
	
};


struct StandaloneTutorial0 : EntityPrefab<Tutorial0>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		return components;
    }
};


RENDER_APP_MAIN {
	Machine& mach = GetMachine();
	
	try {
	    RegistrySystem& reg = *mach.Add<RegistrySystem>();
		EntityStore& ents = *mach.Add<EntityStore>();
	    mach.Add<ComponentStore>();
	    mach.Add<ConnectorSystem>();
	    mach.Add<HumanSystem>();
	    mach.Add<DisplaySystem>();
	    
	    reg.SetAppName("Tutorial0");
	    
	    if (mach.Start()) {
			EntityRef app = ents.Create<StandaloneWindow>();
			app->Add<Tutorial0>();
			app->Find<Connector>()->ConnectAll();
			
		    TimeStop t;
		    while (mach.IsRunning()) {
		        double dt = t.ResetSeconds();
		        mach.Update(dt);
		        Sleep(1);
		    }
	    }
	}
	catch (Exc e) {
		LOG("Fatal error: " << e);
	}
	
	mach.Stop();
}
