#include "LittleApps.h"


class ShellProg : public ConsoleProgram {
	VirtualScreen vscreen;
	
public:
	
	
	bool Key(dword key, int count) override {
		global->monitor.Put(key);
		return true;
	}
	
	void Run() override {
		#if EMU
		while (!IS_SHUTDOWN_THREADS) {
			
			
			Sleep(10);
		}
		#endif
	}
};

int Run_Shell(int argc, const char** argv, struct multiboot* mboot) {
	ShellProg prog;
	
	if (prog.Init(argc, argv)) {
		prog.Run();
		
		
	}
	
	return prog.GetExitCode();
}
