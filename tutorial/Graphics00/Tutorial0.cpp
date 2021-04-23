#include <Complete/Complete.h>


using namespace Oulu;

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
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);
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
	    mach.Add<EventSystem>();
	    mach.Add<RenderingSystem>();
	    
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
