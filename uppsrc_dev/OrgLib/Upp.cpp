#include "OrgLib.h"
#define LLOG(x)

BEGIN_TEXTLIB_NAMESPACE


UppAssembly::UppAssembly() {
	
}

void UppAssembly::Clear() {
	dirs.Clear();
	prj_paths.Clear();
}

void UppAssembly::AddPath(String dir) {
	if (dirs.Find(dir) >= 0) return;
	dirs.Add(dir);
	
	Index<String> files;
	GetDirectoryFiles(dir, files);
	
	for(int i = 0; i < files.GetCount(); i++) {
		String name = files[i];
		String path = AppendFileName(dir, name);
		//DUMP(path);
		if (DirectoryExists(path)) {
			String upp_file = AppendFileName(path, name + ".upp");
			if (FileExists(upp_file)) {
				prj_paths.Add(name, upp_file);
			}
		}
	}
}





void UppProject::Clear() {
	name = ""; path = ""; dir = "";
	ClearContent();
}

void UppProject::ClearContent() {
	uses.Clear();
	files.Clear();
	configs.Clear();
}

const char* CommaOrSemicolon(bool comma) {
	if (comma)
		return ",";
	else
		return ";";
}

void UppProject::Store() {
	if (path.IsEmpty()) return;
	
	RealizeDirectory(dir);
	DUMP(path);
	
	FileOut upp_out(path);
	
	if (uses.GetCount()) {
		upp_out << "uses\n";
		for(int i = 0; i < uses.GetCount(); i++)
			upp_out << "\t" << uses[i] << CommaOrSemicolon(i < uses.GetCount()-1) << "\n";
	}
	
	if (files.GetCount()) {
		upp_out << "file\n";
		for(int i = 0; i < files.GetCount(); i++)
			upp_out << "\t" << files[i] << CommaOrSemicolon(i < files.GetCount()-1) << "\n";
	}
	
	if (configs.GetCount()) {
		upp_out << "mainconfig\n";
		for(int i = 0; i < configs.GetCount(); i++)
			upp_out << "\t\"" << configs.GetKey(i) << "\" = \"" << configs[i] << "\"" << CommaOrSemicolon(i < configs.GetCount()-1) << "\n";
	}
	
}

enum {USES, FILES, CONFIGS};

bool UppProject::Load(String name, String path) {
	Clear();
	this->name = name;
	this->path = path;
	this->dir = GetFileDirectory(path);
	
	if (!FileExists(path)) return false;
	
	String content = LoadFile(path);
	
	Vector<String> lines = Split(content, "\n");
	
	int mode = -1;
	
	for(int i = 0; i < lines.GetCount(); i++) {
		String line = lines[i];
		bool intended = line.Left(1) == "\t";
		
		line = TrimBoth(line);
		LLOG(i << ": " << line);
		
		if (line == "uses")
			mode = USES;
		else if (line == "file")
			mode = FILES;
		else if (line == "mainconfig")
			mode = CONFIGS;
		else if (intended) {
			if (line.IsEmpty()) continue;
			line = line.Left(line.GetCount()-1); // ,
			int j = line.ReverseFind(" highlight ");
			if (j >= 0)
				line = line.Left(j);
			//DUMP(line);
			if (line.IsEmpty()) continue;
			if (mode == USES)
				uses.FindAdd(line);
			else if (mode == FILES) {
				int opt = line.Find(" options(");
				if (opt >= 0)
					line = line.Left(opt);
				if (line.Right(19) == " readonly separator")
					;
				else
					files.Add(line);
			}
			else if (mode == CONFIGS) {
				String key;
				String value;
				
				int j = line.Find("=");
				if (j < 0) {
					LOG("Not found char '='");
					return false;
				}
				
				key = TrimBoth(line.Left(j));
				if (key.GetCount() >= 2 && key.Left(1) == "\"" && key.Right(1) == "\"")
					key = key.Mid(1, key.GetCount()-2);
				
				value = TrimBoth(line.Mid(j+1));
				if (value.GetCount() >= 2 && value.Left(1) == "\"" && value.Right(1) == "\"")
					value = value.Mid(1, value.GetCount()-2);
				
				configs.Add(key, value);
			}
		}
	}
	
	return true;
}

void UppProject::GetRecursiveUses(Index<String>& idx, UppAssemblyData& as) {
	if (idx.Find(name) >= 0) return;
	idx.Add(name);
	for(int i = 0; i < uses.GetCount(); i++) {
		UppProject& prj = as.GetProject(uses[i]);
		prj.GetRecursiveUses(idx, as);
	}
}





UppProject& UppAssemblyData::RealizeProject(String full_name) {
	String name;
	int a = full_name.ReverseFind("/");
	if (a >= 0)
		name = full_name.Mid(a+1);
	else
		name = full_name;
	String dir = as.GetDirectory(0);
	String prj_dir = AppendFileName(dir, full_name);
	prj_dir.Replace("/", DIR_SEPS);
	String upp_path = AppendFileName(prj_dir, name + ".upp");
	if (FileExists(upp_path)) {
		RealizeDirectory(prj_dir);
		FileOut fout(upp_path);
	}
	
	return GetProject(full_name);
}

UppProject& UppAssemblyData::GetProject(String full_name) {
	String name;
	int a = full_name.ReverseFind("/");
	if (a >= 0)
		name = full_name.Mid(a+1);
	else
		name = full_name;
	
	int i = as.FindProject(full_name);
	String upp_path;
	if (i >= 0) {
		upp_path = as.GetProjectPath(i);
	}
	else {
		ASSERT(as.GetDirectoryCount() > 0);
		String dir = as.GetDirectory(0);
		upp_path = AppendFileName(dir, full_name + DIR_SEPS + name + ".upp");
		upp_path.Replace("/", DIR_SEPS);
	}
	
	lock.Enter();
	i = prjs.Find(upp_path);
	if (i == -1) {
		LLOG("Load " << upp_path);
		i = prjs.GetCount();
		prjs.Add(upp_path).Load(full_name, upp_path);
	}
	UppProject& prj = prjs[i];
	lock.Leave();
	return prj;
}

void UppAssemblyData::Clear() {
	prjs.Clear();
}

int UppAssemblyData::FindName(String s) const {
	for(int i = 0; i < prjs.GetCount(); i++)
		if (prjs[i].GetName() == s)
			return i;
	return -1;
}









bool UppAssemblyCache::LoadThis() {
	if (!FileExists(persistent_path))
		return false;
	LoadFromFile(*this, persistent_path);
	return true;
}

bool UppAssemblyCache::StoreThis() {
	String dir = GetFileDirectory(persistent_path);
	if (persistent_path.IsEmpty() || !DirectoryExists(dir))
		return false;
	StoreToFile(*this, persistent_path);
	return true;
}

void UppAssemblyCache::Serialize(Stream& s) {
	s % files;
}

void UppAssemblyCache::Clear() {
	files.Clear();
}

void UppAssemblyCache::Load() {
	files.Clear();
	
	Index<String> file_list;
	for (const UppProject& prj : asd.prjs.GetValues()) {
		for(int i = 0; i < prj.GetFileCount(); i++) {
			String file = prj.GetFilePath(i);
			file_list.FindAdd(file);
		}
	}
	
	int actual = 0, total = file_list.GetCount();
	for (String file : file_list) {
		String content = LoadFile(file);
		files.Add(file, content);
		
		WhenProgress(actual++, total);
	}
	
	WhenLoaded(total);
}


END_TEXTLIB_NAMESPACE

