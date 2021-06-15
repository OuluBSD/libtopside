#include "Editor.h"


void CacheTests() {
	String filepath = ConfigFile("test1.cpp");
	FileCopy(GetDataFile("test1"), filepath);
	String dump1, dump2;
	{
		NodeCache cache;
		cache.SetProjectName("assembly___test1");
		ClangNode& pkg  = cache.GetPackage("pkg");
		ClangNode& file = NodeGetFile(pkg, "test1.cpp");
		cache.LoadFileNode(filepath, file);
		cache.StoreThis();
		dump1 = cache.Dump();
	}
	{
		NodeCache cache;
		cache.SetProjectName("assembly___test1");
		cache.LoadThis();
		ClangNode& pkg  = cache.GetPackage("pkg");
		ClangNode& file = NodeGetFile(pkg, "test1.cpp");
		cache.LoadFileNode(filepath, file);
		dump2 = cache.Dump();
		
		
		LOG(dump1);
		ClangNode basic = cache.GetAllBasic();
		LOG("BASIC: ----------------------------------------------------");
		LOG(Dump(basic));
	}
	//TODO: real checks
	ASSERT(dump1 == dump2);
	
	
	
	LOG("Cache test OK!");
}

void RunTests() {
	CacheTests();
}

void CleanAssembly(String ass_dir, const Index<String>& pkgs, String output_dir);



using namespace TS;


GUI_APP_MAIN {
	SetCoutLog();
	
	//RunTests();
	CommandLineArguments cmd;
	cmd.AddArg('h', "Show help.", false);
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return;
	}
	
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'h') {cmd.PrintHelp(); return;}
	}
	
	
	ProjectManagerDialog dlg;
	dlg.Run();
	if (!dlg.open)
		return;
	
	Project prj = GetProjectManager().GetProject(dlg.open_assembly, dlg.open_package);
	
	IDE ide;
	ide.LoadProject(prj);
	ide.Run();
	
}
