#include "MP3Player.h"

NAMESPACE_OULU_BEGIN

String file_path;


void MP3Player::OnError() {
	GetEntity().GetMachine().SetNotRunning();
}

void MP3Player::Initialize() {
	//auto& mach = GetEntity().GetMachine();
	//Ref<EntityStore> es = mach.Get<EntityStore>();
	//Pool& pool = GetEntity().GetPool();
	
	/*fusion = pool.Create<CompleteFusion>();
	audio = pool.Create<CompleteMixer>();
	track0 = pool.Create<CompleteMixerTrackBegin>();
	channel0 = pool.Create<CompleteMixerChannel>();
	output = pool.Create<CompleteMixerOutput>();*/
	
	/*fusion->Find<Connector>()->ConnectAll();
	audio->Find<Connector>()->ConnectAll();
	track0->Find<Connector>()->ConnectAll();
	channel0->Find<Connector>()->ConnectAll();
	output->Find<Connector>()->ConnectAll();*/
	
	/*ctx = e->Find<MixerContextComponent>();
	if (ctx) {
		ctx->WhenError << THISBACK(OnError);
		if (file_path.GetCount()) {
			ctx->PostLoadFileAny(file_path); // async cmd
		}
		else {
			LOG("error: sound file path is required");
			GetMachine().SetNotRunning();
			return;
		}
	}*/
	
	Entity& e = GetEntity();
	file_in = e.Find<FfmpegComponent>();
	audio   = e.Find<PortaudioSinkComponent>();
	if (!file_in || !audio)
		Panic("Invalid MP3 player");
	
	Pool& p = e.GetPool();
	p.Add<ConnectAllInterfaces<AudioSource>>();
	
}

void MP3Player::Uninitialize() {
	file_in.Clear();
	audio.Clear();
	GetEntity().Destroy();
}

void MP3PlayerStartup() {
	SetCoutLog();
	
	CommandLineArguments cmd;
	cmd.AddArg('f', "The path for the music file", true);
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return;
	}
	
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'f') file_path = in.value;
	}
	if (file_path.IsEmpty()) {
		cmd.PrintHelp();
		return;
	}
	
}




void Main() {
	SetCoutLog();
	
	Machine mach;
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
	EntityStoreRef es = mach.Add<EntityStore>();
	PoolRef root = es->GetRoot();
    mach.Add<ComponentStore>();
    mach.Add<ConnectorStore>();
    mach.Add<AudioSystem>();
    mach.Add<ActionSystem>();
    
    
    try {
        VAR player = root->Create<MP3PlayerPrefab>();
        
	    mach.Start();
	    
	    int dbg_i = 0;
	    TimeStop t;
	    while (mach.IsRunning()) {
	        double dt = ResetSeconds(t);
	        mach.Update(dt);
	        Sleep(1);
	        
	        
	        
	        if (++dbg_i > 100)
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

