#include "TemplatesLocalTests.h"

NAMESPACE_TOPSIDE_BEGIN




bool SimpleDebugInitializer() {
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

tester.generator: {
	customer.id.ABCD: true;
	center.audio.src: true;
	center.audio.sink: true;
	center.audio.sink.realtime: true;
}

)EON_CODE";

void Main() {
	SetCoutLog();
	EcsFactory::Dump();
	
	
	EcsFactory::RegisterExtension<TestCustomer>();
	EcsFactory::RegisterExtension<TestRealtimeSink>();
	
	
	//BreakRefAdd(0x7FFFFFFFE430);
	
	if (!SimpleDebugInitializer())
		Exit(1);
	
	{
		Machine mach;
		
		SetDebugRefVisits();
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
			    
			    mach.Add<ScopeValCoreT<AudioSpec>::PacketTracker>();
				
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




void TestRealtimeSink::Initialize() {
	
	flag.Start(1);
	Thread::Start(THISBACK(IntervalSinkProcess));
}

void TestRealtimeSink::Uninitialize() {
	flag.Stop();
}

void TestRealtimeSink::IntervalSinkProcess() {
	AudioOutputComponent& base = GetParentT();
	AudioFormat fmt =  base.GetValue(AUDCTX).GetFormat();
	Vector<byte> data;
	data.SetCount(fmt.GetFrameSize());
	double step_s = fmt.GetFrameSeconds();
	TimeStop ts;
	while (flag.IsRunning()) {
		double t = ts.Seconds();
		
		if (t < step_s) {
			Sleep(1);
			continue;
		}
		ts.Reset();
		
		RTLOG("TestRealtimeSink::IntervalSinkProcess: trying to consume " << data.GetCount());
		base.ForwardMem(data.Begin(), data.GetCount());
	}
	flag.DecreaseRunning();
}


NAMESPACE_TOPSIDE_END

#ifdef flagGUI
GUI_APP_MAIN {TS::Main();}
#else
CONSOLE_APP_MAIN {TS::Main();}
#endif

