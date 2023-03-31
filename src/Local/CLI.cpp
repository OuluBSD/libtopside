#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN

CLI::CLI() {
	
}

void CLI::RunStdIO() {
	while (!Thread::IsShutdownThreads()) {
		Cout() << ">>> ";
		String in = ReadStdIn();
		
		Vector<String> params = Split(in, " ");
		
		if (params.IsEmpty())
			continue;
		
		//int count = params.GetCount();
		String key = params[0];
		
		if (key == "q" || key == "quit")
			break;
		
	}
}

NAMESPACE_TOPSIDE_END
