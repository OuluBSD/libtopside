#include "Backend.h"

NAMESPACE_TOPSIDE_BEGIN


AssemblyExporter::AssemblyExporter(AstNode& root) : root(root) {
	
}

void AssemblyExporter::Dump() {
	for (const Package& pkg : pkgs.GetValues()) {
		LOG("Package: " << pkg.name);
		for (const PackageFile& file : pkg.files.GetValues()) {
			LOG("\tFile: " << file.name);
			for (NodeBase* n : file.refs) {
				LOG("\t\tRef: " << n->ToString());
			}
		}
	}
	
	LOG(root.GetTreeString());
}

bool AssemblyExporter::Export(String dir) {
	export_dir = dir;
	
	LOG("Realizing directory: " << dir);
	RealizeDirectory(dir);
	if (!DirectoryExists(dir)) {LOG("error: could not create directory " << dir); return false;}
	
	pkgs.Clear();
	
	if (!Visit(root))
		return false;
	
	Dump();
	
	for(Package& pkg: pkgs.GetValues()) {
		LOG("Exporting project: " << pkg.name);
		if (!ExportPackage(pkg))
			return false;
	}
	if (!ExportComplete(dir))
		return false;
	
	LOG("AssemblyExporter export successful");
	return true;
}

bool AssemblyExporter::ExportPackage(Package& pkg) {
	String pkg_dir = AppendFileName(export_dir, pkg.name);
	RealizeDirectory(pkg_dir);
	if (!DirectoryExists(pkg_dir)) {
		LOG("error: could not realize directory: " << pkg_dir);
		return false;
	}
	
	String pkg_path = AppendFileName(pkg_dir, pkg.name + ".upp");
	
	if (protect_pkg && FileExists(pkg_path)) {
		LOG("warning: skipping protected " + pkg_path);
	}
	else {
		FileOut fout(pkg_path);
		if (!fout.IsOpen()) {
			LOG("error: could not open file: " + pkg_path);
			return false;
		}
		
		Vector<Package*> deps;
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
		
		if (!pkg.files.IsEmpty()) {
			fout << "file\n";
			int i = 0, c = pkg.files.GetCount();
			for (PackageFile& f : pkg.files.GetValues()) {
				fout << "\t" << f.name << ".h,\n";
				fout << "\t" << f.name << ".cpp";
				fout <<  (++i == c ? ";\n\n" : ",\n");
			}
		}
		fout.Close();
	}
	
	if (!pkg.files.IsEmpty()) {
		for (PackageFile& f : pkg.files.GetValues()) {
			String h_path = AppendFileName(pkg_dir, f.name + ".h");
			String cpp_path = AppendFileName(pkg_dir, f.name + ".cpp");
			TouchFile(h_path);
			TouchFile(cpp_path);
			
			LOG("Exporting " << h_path);
			if (!ExportHeader(pkg, f, h_path))
				return false;
			
			LOG("Exporting " << cpp_path);
			if (!ExportImplementation(pkg, f, cpp_path))
				return false;
		}
	}
	
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
	
	fout << "mainconfig\n\t\"\" = \"\";\n\n";
	
	return true;
}

bool AssemblyExporter::ExportHeader(Package& pkg, PackageFile& file, String path) {
	FileOut fout(path);
	if (!fout.IsOpen()) {
		LOG("error: could not open file for writing: " << path);
		return false;
	}
	
	fout << "#ifndef _" << pkg.name << "_" << file.name << "_h_\n";
	fout << "#define _" << pkg.name << "_" << file.name << "_h_\n\n";
	
	fout << "// This file is generated. Do not modify this file.\n";
	fout << "\n";
	
	String path_name = GetFileTitle(path);
	if (pkg.name == file.name) {
		for (String dep : pkg.deps) {
			fout << "#include <" << dep << "/" << dep << ".h>\n";
		}
		if (pkg.deps.GetCount())
			fout << "\n";
		for (const PackageFile& f0 : pkg.files.GetValues()) {
			if (&file != &f0)
				fout << "#include \"" << file.name << ".h\"\n";
		}
		fout << "\n";
	}
	
	CodeArgs args;
	args.pkg = &pkg;
	args.file = &file;
	args.have_header = true;
	fout << root.GetCodeString(args);
	
	fout << "\n\n#endif\n";
	
	return true;
}

bool AssemblyExporter::ExportImplementation(Package& pkg, PackageFile& file, String path) {
	FileOut fout(path);
	if (!fout.IsOpen()) {
		LOG("error: could not open file for writing: " << path);
		return false;
	}
	
	fout << "#include \"" << pkg.name << ".h\"\n\n";
	
	CodeArgs args;
	args.pkg = &pkg;
	args.file = &file;
	args.have_impl = true;
	fout << root.GetCodeString(args);
	
	return true;
}

void AssemblyExporter::Push(NodeBase& n) {
	for(int i = 0; i < 2; i++) {
		String pkg, file;
		if (i == 0) {
			pkg = n.GetHint(HINT_PKG);
			file = n.GetHint(HINT_FILE);
		}
		else if (i == 1) {
			pkg = n.GetHint(HINT_FWD_DECL_PKG);
			file = n.GetHint(HINT_FWD_DECL_FILE);
		}
		
		if (!pkg.IsEmpty()) {
			Package& p = pkgs.GetAdd(pkg);
			if (p.name.IsEmpty()) p.name = pkg;
			
			if (!file.IsEmpty()) {
				PackageFile& f = p.files.GetAdd(file);
				if (f.name.IsEmpty()) f.name = file;
				VectorFindAdd(f.refs, &n);
			}
		}
	}
	
	scopes.Add(&n);
}

void AssemblyExporter::Pop() {
	scopes.SetCount(scopes.GetCount()-1);
}

bool AssemblyExporter::Visit(AstNode& n) {
	TODO
}

#if 0

bool AssemblyExporter::Visit(CompilationUnit& o) {
	ScopeHolder __h(this, o);
	
	
	if (!Visit(o.root))
		return false;
	
	return true;
}

bool AssemblyExporter::Visit(Namespace& o) {
	o.DefaultHintsFromOwner();
	
	ScopeHolder __h(this, o);
	
	
	for (Namespace& ns : o.namespaces.GetValues()) {
		if (!Visit(ns))
			return false;
	}
	
	for (Class& o : o.classes.GetValues()) {
		if (!Visit(o))
			return false;
	}
	
	for (MetaStatement& o0 : o.mstmts.GetValues()) {
		if (!Visit(o0))
			return false;
	}
	
	for (UsingStatement& o0 : o.using_stmts.GetValues()) {
		if (!Visit(o0))
			return false;
	}
	
	return true;
}

bool AssemblyExporter::Visit(Class& o) {
	if (o.tmpl.is)
		return true;
	
	o.DefaultHintsFromOwner();
	
	ScopeHolder __h(this, o);
	
	for (Class& o0 : o.classes.GetValues()) {
		if (!Visit(o0))
			return false;
	}
	
	for (Field& o0 : o.fields.GetValues()) {
		if (!Visit(o0))
			return false;
	}
	
	for (FunctionIdScope& o0 : o.funcids.GetValues()) {
		if (!Visit(o0))
			return false;
	}
	
	for (MetaStatement& o0 : o.mstmts.GetValues()) {
		if (!Visit(o0))
			return false;
	}
	
	return true;
}

bool AssemblyExporter::Visit(Field& o) {
	o.DefaultHintsFromOwner();
	
	ScopeHolder __h(this, o);
	
	if (o.ctor) {
		if (!Visit(*o.ctor))
			return false;
	}
	
	return true;
}

bool AssemblyExporter::Visit(FunctionIdScope& o) {
	o.DefaultHintsFromOwner();
	
	ScopeHolder __h(this, o);
	
	for (Function& f : o.funcs) {
		if (!Visit(f))
			return false;
	}
	
	return true;
}

bool AssemblyExporter::Visit(Function& o) {
	o.DefaultHintsFromOwner();
	
	ScopeHolder __h(this, o);
	
	if (o.impl) {
		if (!Visit(*o.impl))
			return false;
	}
	
	return true;
}

bool AssemblyExporter::Visit(Statement& o) {
	o.DefaultHintsFromOwner();
	
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

bool AssemblyExporter::Visit(MetaStatement& o) {
	o.DefaultHintsFromOwner();
	
	ScopeHolder __h(this, o);
	
	if (o.mexpr) {
		if (!Visit(*o.mexpr))
			return false;
	}
	
	return true;
}

bool AssemblyExporter::Visit(MetaExpression& o) {
	o.DefaultHintsFromOwner();
	
	ScopeHolder __h(this, o);
	
	for (MetaExpression& o0 : o.mexprs) {
		if (!Visit(o0))
			return false;
	}
	
	return true;
}

bool AssemblyExporter::Visit(UsingStatement& o) {
	o.DefaultHintsFromOwner();
	
	ScopeHolder __h(this, o);
	
	if (o.expr) {
		if (!Visit(*o.expr))
			return false;
	}
	
	return true;
}

#endif


NAMESPACE_TOPSIDE_END
