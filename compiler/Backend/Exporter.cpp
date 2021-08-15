#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN

AssemblyExporter::AssemblyExporter() {
	
}

bool AssemblyExporter::Export(String dir) {
	LOG("Realizing directory: " << dir);
	RealizeDirectory(dir);
	if (!DirectoryExists(dir)) {LOG("error: could not create directory " << dir); return false;}
	
	prjs.Clear();
	
	TODO
	DUMPC(prjs);
	
	for(String prj: prjs.GetKeys()) {
		LOG("Exporting project: " << prj);
		if (!ExportProject(dir, prj))
			return false;
	}
	if (!ExportComplete(dir))
		return false;
	
	LOG("AssemblyExporter export successful");
	return true;
}

bool AssemblyExporter::ExportProject(String dir, String prj_name) {
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
	
	Vector<Project*> deps;
	auto& prj = prjs.Get(prj_name);
	for (String dep : prj.deps) {
		int i = prjs.Find(dep);
		if (i < 0) {
			LOG("error: could not find dep project: " + dep);
			return false;
		}
		deps.Add(&prjs[i]);
	}
	
	
	fout << "description \"\\377B113,42,150\";\n\n";

	if (!deps.IsEmpty()) {
		fout << "uses\n";
		fout << "\tSerialCore" << (deps.IsEmpty() ? ";\n\n" : ",\n");
		
		for (Project* dep : deps) {
			fout << "\t" << dep->name;
			
			fout << (dep == deps.Top() ? ";\n\n" : ",\n");
		}
	}
	
	//fout << "file\n\t;";
	
	return true;
}

bool AssemblyExporter::ExportComplete(String dir) {
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
	const auto& deps = prjs.GetKeys();
	for(int i = 0; i < deps.GetCount(); i++) {
		String dep = deps[i];
		fout << "\t" << dep;
		fout << (i == deps.GetCount()-1 ? ";\n\n" : ",\n");
	}
	
	//fout << "file\n\t;";
	
	fout << "mainconfig\n\t\"\" = \"\";\n\n";
	
	return true;
}

NAMESPACE_TOPSIDE_END
