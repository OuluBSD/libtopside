#include "Editor.h"
#include "Builder.h"

bool LoadVarFile(const char *name, VectorMap<String, String>& _var)
{
	try {
		VectorMap<String, String> var;
		String env = LoadFile(name);
		CParser p(env);
		while(!p.IsEof()) {
			String v = p.ReadId();
			p.Char('=');
			if(p.IsString())
				var.GetAdd(v) = p.ReadString();
			else {
				String ln;
				while(p.PeekChar() != '\r' && p.PeekChar() != '\n' && p.PeekChar() != ';')
					ln.Cat(p.GetChar());
				var.GetAdd(v) = ln;
				p.Spaces();
			}
			p.Char(';');
		}
		_var = pick(var);
		return true;
	}
	catch(...) {
		return false;
	}
}








ProjectManager::ProjectManager() {
	RefreshAssemblies();
	RefreshAssemblyPackages();
	
}


Package& ProjectManager::GetPackage(int assembly, String name) {
	//LOG("ProjectManager::GetPackage " << name);
	
	Assembly& a = assemblies[assembly];
	for(int i = 0; i < a.pkgs.GetCount(); i++) {
		//TODO: Handle duplicate package names
		if (a.pkgs[i].name == name) {
			return a.pkgs[i];
		}
	}
	
	Panic("GetOpenUsedPackage failed");
	return *(Package*)0;
}







void ProjectManager::RefreshAssemblies() {
	assemblies.Clear();
	#ifdef flagPOSIX
	String dir = GetHomeDirFile(".config/u++/theide");
	#else
	#error Todo
	#endif
	FindFile ff(AppendFileName(dir, "*.var"));
	while(ff) {
		String name = ff.GetName();
		String p = AppendFileName(dir, name);
		if(ff.IsFile()) {
			VectorMap<String,String> var;
			LoadVarFile(p,var);
			int upp=var.Find("UPP");
			int out=var.Find("OUTPUT");
			if(upp>=0&&out>=0){
				Vector<String> paths = Split(var[upp], ";");
				if (!paths.GetCount()) {ff.Next(); continue;}
				String name = GetFileName(paths[0]);
				Assembly& a = assemblies.Add(name);
				a.name = name;
				a.nests = var[upp];
				a.output = var[out];
			}
		}
		ff.Next();
	}
}

void ProjectManager::RefreshAssemblyPackages() {
	for(int i = 0; i < assemblies.GetCount(); i++) {
		Assembly& a = assemblies[i];
		a.RefreshPackages();
	}
}

Assembly& ProjectManager::AddAssembly(Assembly& as) {
	Assembly& newasm = assemblies.Add(as.name, as);
	RefreshAssemblies();
	StoreThis();
	return newasm;
}

Project ProjectManager::GetProject(int open_assembly, int open_package) {
	Project out;
	Assembly& as = assemblies[open_assembly];
	Package& pkg = as.pkgs[open_package];
	out.SetPackage(pkg);
	return out;
}
