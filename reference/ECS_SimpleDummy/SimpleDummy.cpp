#include "SimpleDummy.h"

NAMESPACE_TOPSIDE_BEGIN

String file_path;


void DummyGenerator::OnError() {
	GetEntity()->GetMachine().SetNotRunning();
}

void DummyGenerator::Initialize() {
	EntityRef e = GetEntity();
	gen     = e->Find<DummySoundGeneratorComponent>();
	audio   = e->Find<DummyAudioSinkComponent>();
	
    //e->FindConnector<ConnectAllCenterInterfaces>()->LinkAll();
}

void DummyGenerator::Uninitialize() {
	gen.Clear();
	audio.Clear();
	GetEntity()->Destroy();
}




bool SimpleDummyInitializer() {
	SetCoutLog();
	
	return true;
}



/*
To debug reference bugs, uncomment:
	- SetDebugRefVisits
	- RefDebugVisitor::Static().DumpUnvisited();
You'll see something like this in log
	0:	[0x7FFFFFFFE488]
	1:	[0x7FFFFFFFE478]
	2:	[0x7FFFFFFFE460]
	3:	[0x80AE80688]
	4:	[0x80AE57610]
	5:	[0x80AE43230]
	6:	[0x7FFFFFFFE2A8]
	7:	[0x7FFFFFFFE200]
	8:	[0x7FFFFFFFE138]
Take any address and put to BreakRefAdd
*/


const char* eon_str = R"EON_CODE(

player.audio.generator: {
	center.audio.src.test: true;
	center.audio.sink.test: true;
}

)EON_CODE";

void Main() {
	SetCoutLog();
	//EcsFactory::Dump();
	
	
	//BreakRefAdd(0x7FFFFFFFE430);
	
	if (!SimpleDummyInitializer())
		Exit(1);
	
	{
		Machine mach;
		
		//SetDebugRefVisits();
		RuntimeDiagnostics::Static().SetRoot(mach);
		
	    #ifdef flagSTDEXC
	    try {
	    #endif
			bool fail = false;
			{
				RegistrySystemRef reg		= mach.Add<RegistrySystem>();
				EntityStoreRef es			= mach.Add<EntityStore>();
				ComponentStoreRef compstore	= mach.Add<ComponentStore>();
			    ConnectorStoreRef connstore	= mach.Add<ConnectorStore>();
			    CustomerSystemRef cust		= mach.Add<CustomerSystem>();
			    EonLoaderRef eon			= mach.Add<EonLoader>();
			    
			    mach.Add<ScopeValLibT<AudioSpec>::PacketTracker>();
		    
				PoolRef root = es->GetRoot();
				
				LOG(eon_str);
		        eon->PostLoadString(eon_str);
		    }
		        
		    if (!fail) {
			    mach.Start();
			    
			    int iter = 0;
			    TimeStop t, total;
			    while (mach.IsRunning()) {
			        double dt = ResetSeconds(t);
			        mach.Update(dt);
			        
			        if (!iter++)
			            mach.Get<EntityStore>()->GetRoot()->Dump();
			        
			        Sleep(1);
			        
			        if (total.Seconds() > 3)
			            mach.SetNotRunning();
			    }
			    
			    RuntimeDiagnostics::Static().CaptureSnapshot();
		    }
		#ifdef flagSTDEXC
	    }
	    catch (Exc e) {
	        LOG("error: " << e);
	        Exit(1);
	    }
	    #endif
	    
	    mach.Stop();
	}
    
    //RefDebugVisitor::Static().DumpUnvisited();
}


NAMESPACE_TOPSIDE_END

#ifdef flagGUI
GUI_APP_MAIN {TS::Main();}
#else
CONSOLE_APP_MAIN {TS::Main();}
#endif

