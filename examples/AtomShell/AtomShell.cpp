#include <AtomCompleteDebug/AtomCompleteDebug.h>
//#include <SerialAudioCore/SerialAudioCore.h>
//#include <SerialMultimedia/SerialMultimedia.h>


NAMESPACE_TOPSIDE_BEGIN


using ObjMap = VectorMap<String,Object>;
MAKE_STATIC(ObjMap, args)
MAKE_STATIC(String, eon_file)


bool Initializer() {
	SetCoutLog();
	
	CommandLineArguments cmd;
	cmd.AddArg('e', "The path for the eon file", true, "path");
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return false;
	}
	
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'e') eon_file = in.value;
	}
	if (eon_file.IsEmpty()) {
		cmd.PrintHelp();
		LOG("");
		LOG("\te.g. -e play_audio_file.eon -MACHINE_TIME_LIMIT=3 -FILE=/home/user/some.mp3");
		return false;
	}
	
	args <<= cmd.GetVariables();
	
	return true;
}



void Main() {
	SetCoutLog();
	//Serial::Factory::Dump();
	
	
	//BreakRefAdd(0x80AE32468);
	
	
	if (!Initializer())
		return;
	
	
	DUMP(eon_file);
	DUMPC(args);
	Serial::DebugMain(eon_file, args);
}


NAMESPACE_TOPSIDE_END


#ifdef flagGUI
GUI_APP_MAIN {TS::Main();}
#else
CONSOLE_APP_MAIN {TS::Main();}
#endif
