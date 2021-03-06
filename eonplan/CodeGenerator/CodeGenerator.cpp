#include "CodeGenerator.h"
using namespace UPP;
using namespace TS;


bool Export(CompilationUnit& cu) {
	String dir = GetDataDirectory();
	//DUMP(dir);
	
	dir = GetParentDirectory(dir);
	//DUMP(dir);
	
	if (GetFileName(dir) != "eonplan") {
		LOG("error: expected dir 'eonplan': " << dir);
		return false;
	}
	dir = GetParentDirectory(dir);
	
	String assembly = cu.hints.Get(HINT_ASSEMBLY, "parallel");
	
	String serial_dir = AppendFileName(dir, assembly);
	//String serial_dir = ConfigFile("serial");
	
	LOG("Realizing directory: " << serial_dir);
	RealizeDirectory(serial_dir);
	if (!DirectoryExists(serial_dir)) {LOG("error: could not create directory " << serial_dir); return false;}
	
	//cu.SetPackage("BackendTest");
	//cu.SetFile("BackendTest");
	
	AssemblyExporter ae(cu);
	
	ae.ProtectPackageFile();
	if (!ae.Export(serial_dir))
		return false;
	
	
	{
		LOG("TODO");
		/*
		String prj_name = "CompleteSerial";
		String prj_dir = AppendFileName(dir, prj_name);
		RealizeDirectory(prj_dir);
		if (!DirectoryExists(prj_dir)) {
			LOG("error: could not realize directory: " << prj_dir);
			return false;
		}
		
		String prj_path = AppendFileName(prj_dir, prj_name + ".upp");
		FileOut fout(prj_path);
		if (!fout.IsOpen()) {
			LOG("error: could not open file: " + prj_path);
			return false;
		}
		
		fout << "description \"\\377B113,42,150\";\n\n";
	
		fout << "uses\n";
		const auto& deps = Projects().GetKeys();
		for(int i = 0; i < deps.GetCount(); i++) {
			String dep = deps[i];
			fout << "\t" << dep;
			fout << (i == deps.GetCount()-1 ? ";\n\n" : ",\n");
		}
		
		//fout << "file\n\t;";
		
		fout << "mainconfig\n\t\"\" = \"\";\n\n";
		*/
	}
	
	return true;
}

CONSOLE_APP_MAIN {
	SetCoutLog();
	
	int have_code = 3;
	if (CommandLine().GetCount() == 1)
		have_code = StrInt(CommandLine()[0]);
	
	bool have_atoms = have_code & 1;
	bool have_ifaces = have_code & 2;
	
	
	if (have_atoms) {
		CompilationUnit	cu;
		Plan::Factory::Dump();
		
		cu.WeakHint(HINT_PKG, "AtomLocal");
		cu.WeakHint(HINT_FILE, "Generated");
		
		Plan::Factory::Export(cu);
		
		if (!Export(cu)) {
			LOG("Plan export failed.");
		}
		else {
			LOG("Plan export was a success!");
		}
	}
	
	if (have_ifaces) {
		Plan::IfaceLib::Dump();
		
		#if 1
		// prototyping export with easier internals
		Plan::IfaceLib::Export();
		#else
		
		cu.WeakHint(HINT_PKG, "");
		cu.WeakHint(HINT_FILE, "");
		
		Plan::IfaceLib::Export(cu);
		
		if (!Export(cu)) {
			LOG("Plan export failed.");
		}
		else {
			LOG("Plan export was a success!");
		}
		#endif
	}
}
