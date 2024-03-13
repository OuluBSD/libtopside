#include "LittleApps.h"


class ShellProg : public ConsoleProgram {
	
	
	
};

int Run_Shell(int argc, const char** argv, struct multiboot* mboot) {
	ShellProg prog;
	
	if (prog.Init(argc, argv)) {
		prog.Run();
		
		
	}
	
	return prog.GetExitCode();
}
