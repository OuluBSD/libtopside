#include "MP3Player.h"

NAMESPACE_TOPSIDE_BEGIN

String file_path;
bool run_sound_gen;



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

const char* eon_gen_str = R"EON_CODE(

loop player.audio.generator: {
	center.customer.mp3player: true;
	center.audio.src.dbg_generator: true;
	center.audio.sink.realtime: true;
	center.audio.sink.hw: true;
};

)EON_CODE";

const char* eon_aud_str = R"EON_CODE(

loop player.audio.ffmpeg: {
	perma.audio.source.file.path: reg.app.arg.file;
	center.audio.source.decoder: true;
	center.audio.sink.hw: true;
};

)EON_CODE";

const char* eon_vid_str = R"EON_CODE(

loop player.media.ffmpeg: {
	reg.appmode: "video";
	perma.video.source.file.path: reg.app.arg.file;
	center.video.source.decoder: true;
	center.video.sink.hw: true;
};

)EON_CODE";

void Main() {
	SetCoutLog();
	//Ecs::Factory::Dump();
	
	REG_EXT(AppCustomer,		CUSTOMER,	CENTER,RECEIPT,		CENTER,ORDER,	CENTER,ORDER);
	
	#if HAVE_FFMPEG
	REG_EXT(MP3Player,			INPUT,		CENTER,ORDER,		CENTER,AUDIO,	CENTER,AUDIO);
	#endif
	
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
			    ExtSystemRef cust			= mach.Add<ExtSystem>();
			    EonLoaderRef eon			= mach.Add<EonLoader>();
			    
			    mach.Add<PacketTracker>();
				
				PoolRef root = es->GetRoot();
				
				String eon_str = eon_gen_str;
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

