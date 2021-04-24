#include "AudioShaderEditor.h"


using namespace Oulu;
using namespace Upp;


GUI_APP_MAIN {
	SetCoutLog();
	
	Machine& mach = GetMachine();
	
	String audiofile_path;
	/*const auto& cmds = CommandLine();
	if (cmds.IsEmpty()) {
		LOG("Give a audio file path as an argument");
		SetExitCode(1);
		return;
	}
	audiofile_path = cmds[0];*/
	
	{
		RegistrySystem& reg = *mach.Add<RegistrySystem>();
		EntityStore& ents = *mach.Add<EntityStore>();
	    mach.Add<ComponentStore>();
	    mach.Add<ConnectorSystem>();
	    mach.Add<PortaudioSystem>();
	    
	    #if 0
	    #ifdef flagSDL2
	    mach.Add<SDL2System>();
	    #endif
	    mach.Add<FluidsynthSystem>();
	    #endif
	    
	    mach.Add<EventSystem>();
	    mach.Add<RenderingSystem>();
	    mach.Add<AudioSystem>();
	    mach.Add<FusionSystem>();
	    
	    reg.SetAppName("ECS machine");
	    
	    if (!mach.Start()) {
	        SetExitCode(1);
			return;
	    }
	}
	
	
	AudioShaderEditor e;
	if (!e.InitializeDefault(audiofile_path))
		SetExitCode(1);
	else
		e.Run();
	
	
	{
		mach.Stop();
	}
}
