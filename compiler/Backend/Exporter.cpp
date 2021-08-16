#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN

AssemblyExporter::AssemblyExporter(CompilationUnit& cu) : cu(cu) {
	
	cu.WeakHint(HINT_PKG, "Default");
	cu.WeakHint(HINT_FILE, "Default");
	
}

bool AssemblyExporter::Export(String dir) {
	LOG("Realizing directory: " << dir);
	RealizeDirectory(dir);
	if (!DirectoryExists(dir)) {LOG("error: could not create directory " << dir); return false;}
	
	pkgs.Clear();
	
	if (!Visit(cu))
		return false;
	
	Dump();
	TODO
	
	for(String pkg: pkgs.GetKeys()) {
		LOG("Exporting project: " << pkg);
		if (!ExportPackage(dir, pkg))
			return false;
	}
	if (!ExportComplete(dir))
		return false;
	
	LOG("AssemblyExporter export successful");
	return true;
}

bool AssemblyExporter::ExportPackage(String dir, String pkg_name) {
	String pkg_dir = AppendFileName(dir, pkg_name);
	RealizeDirectory(pkg_dir);
	if (!DirectoryExists(pkg_dir)) {
		LOG("error: could not realize directory: " << pkg_dir);
		return false;
	}
	
	String pkg_path = AppendFileName(pkg_dir, pkg_name + ".upp");
	FileOut fout(pkg_path);
	if (!fout.IsOpen()) {
		LOG("error: could not open file: " + pkg_path);
		return false;
	}
	
	Vector<Package*> deps;
	auto& pkg = pkgs.Get(pkg_name);
	for (String dep : pkg.deps) {
		int i = pkgs.Find(dep);
		if (i < 0) {
			LOG("error: could not find dep project: " + dep);
			return false;
		}
		deps.Add(&pkgs[i]);
	}
	
	
	fout << "description \"\\377B113,42,150\";\n\n";

	if (!deps.IsEmpty()) {
		fout << "uses\n";
		fout << "\tSerialCore" << (deps.IsEmpty() ? ";\n\n" : ",\n");
		
		for (Package* dep : deps) {
			fout << "\t" << dep->name;
			
			fout << (dep == deps.Top() ? ";\n\n" : ",\n");
		}
	}
	
	//fout << "file\n\t;";
	
	return true;
}

bool AssemblyExporter::ExportComplete(String dir) {
	String pkg_name = "CompleteSerial";
	String pkg_dir = AppendFileName(dir, pkg_name);
	RealizeDirectory(pkg_dir);
	if (!DirectoryExists(pkg_dir)) {
		LOG("error: could not realize directory: " << pkg_dir);
		return false;
	}
	
	String pkg_path = AppendFileName(pkg_dir, pkg_name + ".upp");
	FileOut fout(pkg_path);
	if (!fout.IsOpen()) {
		LOG("error: could not open file: " + pkg_path);
		return false;
	}
	
	fout << "description \"\\377B113,42,150\";\n\n";

	fout << "uses\n";
	const auto& deps = pkgs.GetKeys();
	for(int i = 0; i < deps.GetCount(); i++) {
		String dep = deps[i];
		fout << "\t" << dep;
		fout << (i == deps.GetCount()-1 ? ";\n\n" : ",\n");
	}
	
	//fout << "file\n\t;";
	
	fout << "mainconfig\n\t\"\" = \"\";\n\n";
	
	return true;
}

void AssemblyExporter::Push(NodeBase& n) {
	String pkg = n.GetHint(HINT_PKG);
	String file = n.GetHint(HINT_FILE);
	if (!pkg.IsEmpty()) {
		Package& p = pkgs.GetAdd(pkg);
		if (p.name.IsEmpty()) p.name = pkg;
		
		if (!file.IsEmpty()) {
			PackageFile& f = p.files.GetAdd(file);
			if (f.name.IsEmpty()) f.name = file;
			VectorFindAdd(f.refs, &n);
		}
	}
	
	scopes.Add(&n);
}

void AssemblyExporter::Pop() {
	scopes.SetCount(scopes.GetCount()-1);
}

bool AssemblyExporter::Visit(CompilationUnit& o) {
	ScopeHolder __h(this, o);
	
	for (Namespace& ns : o.namespaces.GetValues()) {
		if (!Visit(ns))
			return false;
	}
	
	return true;
}

bool AssemblyExporter::Visit(Namespace& o) {
	ScopeHolder __h(this, o);
	
	o.DefaultHintsFromParent();
	
	for (Class& o : o.classes.GetValues()) {
		if (!Visit(o))
			return false;
	}
	
	return true;
}

bool AssemblyExporter::Visit(Class& o) {
	ScopeHolder __h(this, o);
	
	o.DefaultHintsFromParent();
	
	for (Field& o0 : o.fields.GetValues()) {
		if (!Visit(o0))
			return false;
	}
	
	return true;
}

bool AssemblyExporter::Visit(Field& o) {
	ScopeHolder __h(this, o);
	
	o.DefaultHintsFromParent();
	
	if (o.ctor) {
		if (!Visit(*o.ctor))
			return false;
	}
	
	return true;
}

bool AssemblyExporter::Visit(Function& o) {
	ScopeHolder __h(this, o);
	
	o.DefaultHintsFromParent();
	
	if (o.impl) {
		if (!Visit(*o.impl))
			return false;
	}
	
	return true;
}

bool AssemblyExporter::Visit(Statement& o) {
	ScopeHolder __h(this, o);
	
	if (o.expr) {
		if (!Visit(*o.expr))
			return false;
	}
	
	for (Statement& s0 : o.stmts) {
		if (!Visit(s0))
			return false;
	}
	
	return true;
}

bool AssemblyExporter::Visit(Expression& o) {
	ScopeHolder __h(this, o);
	
	for (Expression& e0 : o.exprs) {
		if (!Visit(e0))
			return false;
	}
	
	return true;
}


NAMESPACE_TOPSIDE_END
