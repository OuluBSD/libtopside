#include "MP3Player.h"

NAMESPACE_TOPSIDE_BEGIN

String file_path;
bool run_sound_gen;


void DummyGenerator::OnError() {
	GetEntity()->GetMachine().SetNotRunning();
}

void DummyGenerator::Initialize() {
	EntityRef e = GetEntity();
	gen     = e->Find<DummySoundGeneratorComponent>();
	audio   = e->Find<AudioSinkComponent>();
	
    //e->FindConnector<ConnectAllCenterInterfaces>()->LinkAll();
}

void DummyGenerator::Uninitialize() {
	gen.Clear();
	audio.Clear();
	GetEntity()->Destroy();
}





#if HAVE_FFMPEG
void MP3Player::OnError() {
	GetEntity()->GetMachine().SetNotRunning();
}

void MP3Player::OnStop() {
	GetEntity()->GetMachine().SetNotRunning();
}

void MP3Player::Initialize() {
	EntityRef e = GetEntity();
	file_in = e->Find<FfmpegComponent>();
	audio   = e->Find<AudioSinkComponent>();
	if (!file_in || !audio)
		Panic("Invalid MP3 player");
	
	file_in->WhenStopped = THISBACK(OnStop);
	
	if (!file_in->LoadFileAny(file_path)) {
		LOG("opening media file failed: " << file_in->GetLastError());
		GetMachine().SetNotRunning();
		return;
	}
	
    //e->FindConnector<ConnectAllCenterInterfaces>()->LinkAll();
}

void MP3Player::Uninitialize() {
	file_in.Clear();
	audio.Clear();
	GetEntity()->Destroy();
}
#endif



bool MP3PlayerInitializer() {
	SetCoutLog();
	
	CommandLineArguments cmd;
	cmd.AddArg('g', "Test sound generator", false);
	cmd.AddArg('f', "The path for the music file", true, "path");
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return false;
	}
	
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'f') file_path = in.value;
		if (in.key == 'g') run_sound_gen = true;
	}
	if (file_path.IsEmpty() && !run_sound_gen) {
		cmd.PrintHelp();
		return false;
	}
	
	return run_sound_gen || FileExists(file_path);
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

void Main() {
	SetCoutLog();
	
	EcsFactory::Dump();
	
	//BreakRefAdd(0x7FFFFFFFE430);
	
	if (!MP3PlayerInitializer())
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
			    EonLoaderRef eon			= mach.Add<EonLoader>();
			    
			    //mach.Add<CenterSystem>();
			    mach.Add<ScopeValLibT<AudioSpec>::PacketTracker>();
		    
				PoolRef root = es->GetRoot();
				//root->Add<CenterContextConnector>();
				//root->Add<ConnectAllCenterInterfaces>();
				//root->Add<CenterStageContextConnector>();
				
				
				
				/*auto aud_gen				= root->Create<Customer>();
				auto router					= root->Add<PathwayRouter>();
				router->Add(aud_gen, conf_path);
				
		        if (run_sound_gen) {
					VAR gen = root->Create<DummyGeneratorPrefab>();
		        }
		        else {
		            VAR player = root->Create<MP3PlayerPrefab>();
		        }
		        
		        
		        reg.Clear();
		        es.Clear();
		        customer.Clear();
		        router.Clear();*/
		        
		        eon->PostLoadFile(GetDataFile("MP3Player.eon"));
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
			        
			        if (run_sound_gen && total.Seconds() > 3)
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

