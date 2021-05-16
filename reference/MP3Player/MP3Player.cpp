#include "MP3Player.h"

NAMESPACE_TOPSIDE_BEGIN

String file_path;
bool run_sound_gen;


void DummyGenerator::OnError() {
	GetEntity().GetMachine().SetNotRunning();
}

void DummyGenerator::Initialize() {
	Entity& e = GetEntity();
	gen     = e.Find<SoundGeneratorComponent>();
	audio   = e.Find<PortaudioSinkComponent>();
	
	Pool& p = e.GetPool();
	p.Add<ConnectAllInterfaces<AudioSource>>();
}

void DummyGenerator::Uninitialize() {
	gen.Clear();
	audio.Clear();
	GetEntity().Destroy();
}






void MP3Player::OnError() {
	GetEntity().GetMachine().SetNotRunning();
}

void MP3Player::OnStop() {
	GetEntity().GetMachine().SetNotRunning();
}

void MP3Player::Initialize() {
	Entity& e = GetEntity();
	file_in = e.Find<FfmpegComponent>();
	audio   = e.Find<PortaudioSinkComponent>();
	if (!file_in || !audio)
		Panic("Invalid MP3 player");
	
	file_in->WhenStopped = THISBACK(OnStop);
	
	Pool& p = e.GetPool();
	p.Add<ConnectAllInterfaces<AudioSource>>();
	
	if (!file_in->LoadFileAny(file_path)) {
		LOG("opening media file failed: " << file_in->GetLastError());
		GetMachine().SetNotRunning();
		return;
	}
	
}

void MP3Player::Uninitialize() {
	file_in.Clear();
	audio.Clear();
	GetEntity().Destroy();
}

bool MP3PlayerStartup() {
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
	
	//BreakRefAdd(0x80AE43230);
	
	if (!MP3PlayerStartup())
		Exit(1);
	
	{
		Machine mach;
		
		//SetDebugRefVisits();
		RuntimeDiagnostics::Static().SetRoot(mach);
		
		RegistrySystemRef reg = mach.Add<RegistrySystem>();
		EntityStoreRef es = mach.Add<EntityStore>();
		PoolRef root = es->GetRoot();
	    mach.Add<ComponentStore>();
	    mach.Add<ConnectorStore>();
	    mach.Add<AudioSystem>();
	    mach.Add<ActionSystem>();
	    
	    
	    try {
	        if (run_sound_gen) {
				VAR gen = root->Create<DummyGeneratorPrefab>();
	        }
	        else {
	            VAR player = root->Create<MP3PlayerPrefab>();
	        }
	        
		    mach.Start();
		    
		    TimeStop t, total;
		    while (mach.IsRunning()) {
		        double dt = ResetSeconds(t);
		        mach.Update(dt);
		        Sleep(1);
		        
		        if (run_sound_gen && total.Seconds() > 3)
		            mach.SetNotRunning();
		    }
		    
		    RuntimeDiagnostics::Static().CaptureSnapshot();
	    }
	    catch (Exc e) {
	        LOG("error: " << e);
	        Exit(1);
	    }
	    
	    mach.Stop();
	}
    
    //RefDebugVisitor::Static().DumpUnvisited();
}


NAMESPACE_TOPSIDE_END


CONSOLE_APP_MAIN {
	Topside::Main();
}

