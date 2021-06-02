#include "EcsCtrlDemo.h"


using namespace TS;
using namespace UPP;


GUI_APP_MAIN {
	SetCoutLog();
	
	{
		Machine m;
		
		//SetDebugRefVisits();
		RuntimeDiagnostics::Static().SetRoot(m);
		
		{
			RegistrySystem& reg = *m.Add<RegistrySystem>();
			EntityStore& ents = *m.Add<EntityStore>();
		    m.Add<ComponentStore>();
		    m.Add<ConnectorStore>();
		    m.Add<AudioSystem>();
		    m.Add<HumanSystem>();
		    m.Add<DisplaySystem>();
		    m.Add<FusionSystem>();
		    
		    reg.SetAppName("ECS machine");
		    
		    if (!m.Start()) {
		        SetExitCode(1);
				return;
		    }
		}
		
		
		{
			EcsCtrlDemo e(m);
			if (!e.InitializeDefault()) {
				SetExitCode(1);
				return;
			}
			e.Run();
		}
		
		m.Stop();
	}
	
    //RefDebugVisitor::Static().DumpUnvisited();
}
