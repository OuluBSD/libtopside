#include "MakefileUpdater.h"

NAMESPACE_TOPSIDE_BEGIN

struct Assembly {
	String code;
	String dir;
	int order;
	dword compat;
	
	
	
	bool operator()(const Assembly& a, const Assembly& b) const {return a.order < b.order;}
	
	String ToString() const {
		String s;
		s << code << " (" << dir << "): order=" << order << ", compat=" << IntStr64(compat);
		return s;
	}
};

struct Repository {
	ArrayMap<String, Assembly> ass_list;
	
	enum {
		UPP = 1 << 0,
		ALT_STD14 = 1 << 1,
		ALT_STD23 = 1 << 2
	};
	static const dword FULL_COMPAT = 0xffffffff;
	
	
	Repository() {
		Add("accel",		 60,	FULL_COMPAT);
		Add("ai",			 21,	FULL_COMPAT);
		Add("alt",			  1,	ALT_STD14);
		Add("audio",		 22,	FULL_COMPAT);
		Add("compiler",		 11,	FULL_COMPAT);
		Add("ecs",			 50,		FULL_COMPAT);
		Add("examples",		102,	FULL_COMPAT);
		//Add("fusion");
		Add("local",		 10,	FULL_COMPAT);
		Add("lib",			  2,	FULL_COMPAT);
		Add("reference",	101,	FULL_COMPAT);
		Add("tutorial",		100,	FULL_COMPAT);
		Add("uppsrc",		  0,	UPP);
		Add("video",		 20,	FULL_COMPAT);
		
		SortByValue(ass_list, Assembly());
		Dump();
	}
	
	void Dump() {DUMPC(ass_list);}
	
	void Add(String ass, int order, dword compat_base) {
		Assembly& a = ass_list.Add(ass);
		a.code = ass;
		a.order = order;
		a.compat = compat_base;
	}
	
	bool Open(String dir) {
		for (Assembly& a : ass_list.GetValues()) {
			a.dir = AppendFileName(dir, a.code);
			if (!DirectoryExists(a.dir)) {
				LOG("error: directory does not exist: " << a.dir);
				return false;
			}
			
		}
		return true;
	}
	
};

void MakefileUpdaterMain() {
	SetCoutLog();
	
	CommandLineArguments cmd;
	cmd.AddArg('d', "Repository directory", true, "dir");
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return;
	}
	
	String dir;
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'd') dir = in.value;
	}
	if (dir.IsEmpty() || !DirectoryExists(dir)) {
		cmd.PrintHelp();
		SetExitCode(1);
		return;
	}
	
	LOG("Updating Makefiles in " + dir);
	
	Repository r;
	if (!r.Open(dir)) {
		SetExitCode(1);
		return;
	}
	
	Index<String> sub_assemblies;


	
	/*UppAssembly as;
	UppAssemblyData ad(as);
	as.AddPath(GetHomeDirFile("fos/tests/plan"));
	as.Dump();
	
	UppProject& prj = ad.GetProject(prj_name);*/
	
	
	
	// Visit project dirs
	
	
	// Open .upp file
	
	
	// Create VS proj
	
	
	// Create VS sln
	
	
	// Create unix makefile
	
}

NAMESPACE_TOPSIDE_END


CONSOLE_APP_MAIN {TS::MakefileUpdaterMain();}
