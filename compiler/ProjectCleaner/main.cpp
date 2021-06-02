#include "ProjectCleaner.h"

#ifdef flagMAIN


CONSOLE_APP_MAIN {
	using namespace UPP;
	using namespace TS;
	
	const auto& cmds = CommandLine();
	if (cmds.GetCount() && cmds[0] == "clang") {
		if (cmds.GetCount() < 3)
			Exit(1);
		
		String out_file = cmds[1];
		Vector<const char*> ptrs;
		ptrs.Add(GetExeFilePath());
		for(int i = 2; i < cmds.GetCount(); i++)
			ptrs.Add(cmds[i].Begin());
		Vector<CodeItem> items;
		ClangToolMain(ptrs.GetCount(), ptrs.Begin(), items);
		FileOut fout(out_file);
		fout % items;
		return;
	}
	
	SetCoutLog();
	
	//RunTests();
	CommandLineArguments cmd;
	cmd.AddArg('h', "Show help.", false);
	cmd.AddArg('c', "Use cache.", false);
	cmd.AddArg('i', "Configuration file.", true);
	cmd.AddArg('a', "Directory for the U++ assembly.", true);
	cmd.AddArg('p', "Project in the assembly.", true);
	cmd.AddArg('o', "Output directory.", true);
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return;
	}
	
	
	bool use_cache = false;
	String ass_dir, out_dir;
	String conf_file;
	Index<String> packages;
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'c') use_cache = true;
		if (in.key == 'i') conf_file = in.value;
		if (in.key == 'a') ass_dir = in.value;
		if (in.key == 'o') out_dir = in.value;
		if (in.key == 'p') packages.FindAdd(in.value);
		if (in.key == 'h') {cmd.PrintHelp(); return;}
	}
	
	if (conf_file.GetCount() &&
		packages.GetCount() &&
		ass_dir.GetCount() &&
		out_dir.GetCount()) {
		CleanAssembly(conf_file, ass_dir, packages, out_dir, use_cache);
	}
	else {
		cmd.PrintHelp();
	}
}


#endif
