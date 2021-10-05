#include "EonIDE.h"


NAMESPACE_TOPSIDE_BEGIN


String assembly_dir;
String project_name;

bool AppInitializer() {
	SetCoutLog();
	
	CommandLineArguments cmd;
	cmd.AddArg('a', "The 'eonplan' assembly directory", true, "path");
	cmd.AddArg('p', "The project in the 'eonplan' assembly directory", true, "name");
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return false;
	}
	
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'a') assembly_dir = in.value;
		if (in.key == 'p') project_name = in.value;
	}
	if (assembly_dir.IsEmpty()) {
		cmd.PrintHelp();
		return false;
	}
	if (!DirectoryExists(assembly_dir)) {
		cmd.PrintHelp();
		LOG("error: directory does not exist: " << assembly_dir);
		SetExitCode(2);
		return false;
	}
	
	if (project_name.IsEmpty())
		project_name = "Complete";
	
	return true;
}


/*EonIDE::EonIDE() {
	Title("EonIDE");
	Sizeable().MaximizeBox().MinimizeBox().Maximize();
	
	
}*/


NAMESPACE_TOPSIDE_END



GUI_APP_MAIN {
	using namespace TS;
	
	if (!AppInitializer())
		return;
	
	
	UppAssembly ass;
	ass.AddPath(assembly_dir);
	
	UppAssemblyData ass_data(ass);
	UppAssemblyCache ass_cache(ass_data);
	
	UppProject& main_prj = ass_data.GetProject(project_name);
	
	
	EonPlanEditor e;
	e.SetProject(main_prj, ass, ass_data);
	e.PostCompile();
	e.Run();
	
}
