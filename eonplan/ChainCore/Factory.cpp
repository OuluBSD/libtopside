#include "ChainCore.h"

NAMESPACE_PLAN_BEGIN

String Factory::Val::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Dev::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::ValDev::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Base::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Header::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Loop::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Link::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Chain::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Scope::ToString() const {
	String s;
	s << name;
	return s;
}

String Factory::Machine::ToString() const {
	String s;
	s << name;
	return s;
}

void Factory::Dump() {
	
	auto& vals = Vals();
	DUMPC(vals);
	
	auto& devs = Devs();
	DUMPC(devs);
	
	auto& valdevs = ValDevs();
	DUMPC(valdevs);
	
	auto& bases = Bases();
	DUMPC(bases);
	
	auto& headers = Headers();
	DUMPC(headers);
	
	auto& loops = Loops();
	DUMPC(loops);
	
	auto& links = Links();
	DUMPC(links);
	
	auto& chains = Chains();
	DUMPC(chains);
	
	auto& scopes = Scopes();
	DUMPC(scopes);
	
	auto& machines = Machines();
	DUMPC(machines);
	
}

bool Factory::ExportAll() {
	String dir = GetDataDirectory();
	//DUMP(dir);
	dir = GetParentDirectory(dir);
	//DUMP(dir);
	if (GetFileName(dir) != "eonplan") {
		LOG("error: expected dir 'eonplan': " << dir);
		return false;
	}
	dir = GetParentDirectory(dir);
	
	String serial_dir = AppendFileName(dir, "serial");
	LOG("Realizing directory: " << serial_dir);
	RealizeDirectory(serial_dir);
	if (!DirectoryExists(serial_dir)) {LOG("error: could not create directory " << serial_dir); return false;}
	
	auto& prjs = Projects();
	DUMPC(prjs);
	
	for(String prj: prjs.GetKeys()) {
		LOG("Exporting project: " << prj);
		if (!Export(serial_dir, prj))
			return false;
	}
	if (!ExportComplete(serial_dir))
		return false;
	
	LOG("Factory export successful");
	return true;
}

bool Factory::Export(String dir, String prj_name) {
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
	auto& prj = Projects().Get(prj_name);
	for (String dep : prj.deps) {
		int i = Projects().Find(dep);
		if (i < 0) {
			LOG("error: could not find dep project: " + dep);
			return false;
		}
		deps.Add(&Projects()[i]);
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

bool Factory::ExportComplete(String dir) {
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
	
	return true;
}

NAMESPACE_PLAN_END
