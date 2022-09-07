#include "Project.h"
#include "ProjectManager.h"
#include "Builder.h"










void PackageFile::SetCompiled(String obj_path) {
	hash_t hash = 0;
	
	FileIn in(path);
	if (in.IsOpen()) {
		String content;
		content = in.Get(in.GetSize());
		hash = content.GetHashValue();
		in.Close();
	}
	
	hash_t obj_hash = obj_path.GetHashValue();
	
	hash_t name_hash = path.GetHashValue();
	RealizeDirectory(ConfigFile("hashes"));
	String hash_path = AppendFileName( ConfigFile("hashes"), IntStr(name_hash) + IntStr(obj_hash) );
	FileOut out(hash_path);
	if (out.IsOpen()) {
		out.Put(&hash, 8);
	}
}

bool PackageFile::IsCompiled(String obj_path) {
	if (!FileExists(obj_path)) return false;
	
	hash_t hash = 0;
	hash_t old_hash = 0;
	
	FileIn in(path);
	if (in.IsOpen()) {
		String content;
		content = in.Get(in.GetSize());
		hash = content.GetHashValue();
		in.Close();
	}
	
	hash_t obj_hash = obj_path.GetHashValue();
	
	hash_t name_hash = path.GetHashValue();
	RealizeDirectory(ConfigFile("hashes"));
	String hash_path = AppendFileName( ConfigFile("hashes"), IntStr(name_hash) + IntStr(obj_hash));
	FileIn old(hash_path);
	if (old.IsOpen()) {
		old.Get(&old_hash, 8);
	}
	return old_hash == hash;
}







Project::Project() {
	main = 0;
	
}

Project::Project(const Project& prj) {
	*this = prj;
}

void Project::RefreshCache() {
	Translation::Project& translator = cache.GetTranslator();
	ProjectManager& pman = GetProjectManager();
	int assembly = main->assembly;
	translator.Clear();
	
	// Every recursively used package
	Vector<String> use_list = GetUseList();
	Vector<String> top_paths = GetTopFolders();
	for(int i = 0; i < use_list.GetCount(); i++) {
		String use = use_list[i];
		if (use.Find("\\") != -1) continue; // TODO: allow "plugin\bmp" -type packages
		Package& p = pman.GetPackage(assembly, use);
		ClangNode& pkg = cache.GetPackage(p.name);
		for(int j = 0; j < p.files.GetCount(); j++) {
			PackageFile& pf = p.files[j];
			String ext = GetFileExt(pf.path);
			if (ext==".c" || ext==".cpp" || ext==".h") {
				LOG(Format("%d/%d: %d/%d: %s", i, use_list.GetCount(), j, p.files.GetCount(), pf.path));
				//translator.AddUnit(pf.path, top_paths);
				ClangNode& file = NodeGetFile(pkg, GetFileName(pf.path));
				cache.LoadFileNode(pf.path, file);
			}
		}
	}
}

int Project::GetOpenUsedPackageCount() {
	Package& p = *main;
	if (p.info.Find("uses") == -1) return 0;
	Vector<String>& uses = p.info.Get("uses");
	return uses.GetCount();
}

Vector<String> Project::GetUseList() {
	ArrayMap<String, int> use_list;
	Vector<String> out;
	
	Package& p = *main;
	ProjectManager& pman = GetProjectManager();
	
	use_list.Add(p.name);
	if (p.info.Find("uses") != -1) {
		Vector<String>& uselist = p.info.Get("uses");
		for(int i = 0; i < uselist.GetCount(); i++) {
			if (use_list.Find(uselist[i]) == -1)
				use_list.Add( uselist[i], 0);
		}
	}
	
	int c1 = GetOpenUsedPackageCount();
	for(int i = 0; i < c1; i++) {
		Package& up = GetOpenUsedPackage(i);
		if (up.info.Find("uses") != -1) {
			Vector<String>& uselist = up.info.Get("uses");
			for(int i = 0; i < uselist.GetCount(); i++) {
				if (use_list.Find(uselist[i]) == -1)
					use_list.Add( uselist[i], 0);
			}
		}
	}
	for(int i = 0; i < use_list.GetCount(); i++) {
		String s = use_list.GetKey(i);
		if (!s.GetCount()) continue;
		out.Add(s);
	}
	return out;
}

Vector<String> Project::GetTopFolders() {
	Assembly& a = GetOpenAssembly();
	Vector<String> out = a.GetNests();
	if (!GetBuilder().HasCurrentBuilder()) return out;
	BuilderMethod& bm = GetBuilder().GetCurrentBuilder();
	out.Append(bm.incs);
	return out;
}

Package& Project::GetOpenUsedPackage(int i) {
	Assembly& a = GetOpenAssembly();
	Package& p = *main;
	
	ASSERT(p.info.Find("uses") != -1);
	
	Vector<String>& uses = p.info.Get("uses");
	ASSERT(i >= 0 && i < uses.GetCount());
	
	const String& use = uses[i];
	for(int i = 0; i < a.pkgs.GetCount(); i++) {
		//TODO: Handle duplicate package names
		//LOG(a.pkgs[i].name << " == " << use);
		if (a.pkgs[i].name == use) {
			return a.pkgs[i];
		}
	}
	
	Panic("GetOpenUsedPackage failed");
	return *(Package*)0;
}

Assembly& Project::GetOpenAssembly() {
	return GetProjectManager().GetAssembly(main->assembly);
}

bool Project::OpenUsedPackageExists(int i) {
	Assembly& a = GetOpenAssembly();
	Package& p = GetOpenPackage();
	
	if (p.info.Find("uses") == -1)
		return 0;
	
	Vector<String>& uses = p.info.Get("uses");
	if (i < 0 || i >= uses.GetCount())
		return 0;
	
	const String& use = uses[i];
	for(int i = 0; i < a.pkgs.GetCount(); i++) {
		//TODO: Handle duplicate package names
		if (a.pkgs[i].name == use) {
			return true;
		}
	}
	return false;
}


String Project::GetPackageConfiguration(int i) {
	Package& p = GetOpenPackage();
	Vector<String> confs = p.GetConfigurations();
	if (i < 0 || i >= confs.GetCount()) {
		if (confs.GetCount()) return confs[0];
		else return "";
	}
	return confs[i];
}

int Project::FindPackageConfiguration(String s) {
	Package& p = GetOpenPackage();
	Vector<String> confs = p.GetConfigurations();
	for(int i = 0; i < confs.GetCount(); i++) {
		if (confs[i] == s) return i;
	}
	return -1;
}
