#include "LittleApps.h"


class ShellProg : public ConsoleProgram {
	
	
public:
	
	
	bool Key(dword key, int count) override {
		global->monitor.Put(key);
		return true;
	}
	
	void Run() override {
		
		while (!IS_SHUTDOWN_THREADS) {
			
			
			Sleep(10);
		}
	}
};

int Run_Shell(int argc, const char** argv, struct multiboot* mboot) {
	ShellProg prog;
	
	if (prog.Init(argc, argv)) {
		prog.Run();
		
		
	}
	
	return prog.GetExitCode();
}
