#include "ProjectCleaner.h"


#if 0


#include <CtrlLib/CtrlLib.h>
using namespace UPP;

#define LAYOUTFILE <ProjectCleaner/ProjectCleaner.lay>
#include <CtrlCore/lay.h>



class ProjectCleaner : public WithMainLayout<TopWindow> {
	String assembly_dir, prj_name;
	UppAssembly ass;
	UppAssemblyData ass_data;
	
public:
	typedef ProjectCleaner CLASSNAME;
	ProjectCleaner();
	
	
	bool Init(String assembly_dir, String prj_name);
	
	
};

GUI_APP_MAIN {
	CommandLineArguments cmd;
	cmd.AddArg('a', "The directory for the U++ assembly.", true);
	cmd.AddArg('p', "The package in the assembly.", true);
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return;
	}
	
	String ass_dir, prj_name;
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'a') ass_dir = in.value;
		if (in.key == 'p') prj_name = in.value;
	}
	String prj_dir = AppendFileName(ass_dir, prj_name);
	
	if (ass_dir.IsEmpty() || !DirectoryExists(prj_dir)) {
		cmd.PrintHelp();
		return;
	}
	
	ProjectCleaner pc;
	
	if (!pc.Init(ass_dir, prj_name))
		return;
	
	pc.Run();
	
	
}

#define TITLEBASE String("U++ Project Cleaner")

ProjectCleaner::ProjectCleaner() : ass_data(ass) {
	CtrlLayout(*this, TITLEBASE);
	Sizeable().MaximizeBox();
	SetMinSize(Size(1024, 768));
	
	prog.Set(0, 1);
}

bool ProjectCleaner::Init(String assembly_dir, String prj_name) {
	this->assembly_dir = assembly_dir;
	this->prj_name = prj_name;
	
	Title(TITLEBASE + " - " + assembly_dir + " - { " + prj_name + " }");
	
	ass.AddPath(assembly_dir);
	if (ass.FindUppProject(prj_name) < 0) {
		Cout()	<< "Can't find project '" << prj_name << "' in assembly '" << assembly_dir
				<< "'" << endl;
		return false;
	}
	
	UppProject& prj = ass_data.GetUppProject(prj_name);
	
	//prj.Dump();
	
	Index<String> uses;
	prj.GetRecursiveUses(uses, ass_data);
	DUMPC(uses);
	
	return true;
}

#endif
