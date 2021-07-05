#include "MP3Player.h"

NAMESPACE_TOPSIDE_BEGIN

MAKE_STATIC(String, file_path);
bool run_sound_gen;
bool use_splitted_loop;



bool MP3PlayerInitializer() {
	SetCoutLog();
	
	CommandLineArguments cmd;
	cmd.AddArg('g', "Test sound generator", false);
	cmd.AddArg('f', "The path for the music file", true, "path");
	cmd.AddArg('2', "Use secondary mode with splitted eon loops", false);
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return false;
	}
	
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'f') file_path = in.value;
		if (in.key == 'g') run_sound_gen = true;
		if (in.key == '2') use_splitted_loop = true;
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
	//Ecs::Factory::Dump();
	
	
	//BreakRefAdd(0x80AE32468);
	
	if (!MP3PlayerInitializer())
		Exit(1);
	
	String eon_file;
	if (run_sound_gen) {
		if (!use_splitted_loop)
			eon_file = "play_audio_test.eon";
		else
			eon_file = "play_audio_test_2.eon";
	}
	else {
		if (!use_splitted_loop)
			eon_file = "play_audio_file.eon";
		else
			eon_file = "play_audio_file_2.eon";
	}
	
	VectorMap<String,Object> args;
	args.Add("FILE", file_path);
	
	if (run_sound_gen)
		args.Add("MACHINE_TIME_LIMIT", 3);
	
	Ecs::DebugMain(eon_file, args);
}


NAMESPACE_TOPSIDE_END

#ifdef flagGUI
GUI_APP_MAIN {TS::Main();}
#else
CONSOLE_APP_MAIN {TS::Main();}
#endif

