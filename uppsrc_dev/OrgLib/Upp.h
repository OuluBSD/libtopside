#ifndef _OrgLib_Upp_h_
#define _OrgLib_Upp_h_


BEGIN_TEXTLIB_NAMESPACE


struct UppAssemblyData;


class UppAssembly {
	Index<String> dirs;
	VectorMap<String, String> prj_paths;
	
	
public:
	UppAssembly();
	
	void Clear();
	void AddPath(String dir);
	
	int GetDirectoryCount() const {return dirs.GetCount();}
	String GetDirectory(int i) const {return dirs[i];}
	int FindProject(String name) const {return prj_paths.Find(name);}
	String GetProjectPath(int i) const {return prj_paths[i];}
	
	void Dump() {DUMPC(dirs); DUMPM(prj_paths);}
};


class UppProject {
	String name, path, dir;
	
	Index<String> uses;
	Index<String> files;
	VectorMap<String, String> configs;
	
public:
	
	void AddUse(String use) {uses.FindAdd(use);}
	String GetUse(int i) const {return uses[i];}
	int GetUseCount() const {return uses.GetCount();}
	
	String GetFile(int i) const {return files[i];}
	int FindAddFile(String file) {return files.FindAdd(file);}
	int GetFileCount() const {return files.GetCount();}
	
	String GetConfigKey(int i) const {return configs.GetKey(i);}
	String GetConfigValue(int i) const {return configs[i];}
	int GetConfigCount() const {return configs.GetCount();}
	String& GetAddConfig(String name) {return configs.GetAdd(name);}
	
	String GetFilePath() const {return path;}
	String GetFilePath(int i) const {return AppendFileName(dir, files[i]);}
	String AddFile(String filename) {files.Add(filename); return AppendFileName(dir, filename);}
	void ClearFiles() {files.Clear();}
	void RemoveFile(int i) {files.Remove(i);}
	
	String GetName() const {return name;}
	String GetDirectory() const {return dir;}
	
	void Clear();
	void ClearContent();
	void Store();
	bool Load(String name, String path);
	void Refresh() {Load(name, path);}
	void GetRecursiveUses(Index<String>& idx, UppAssemblyData& as);
	
	void Dump() {DUMP(path); DUMP(dir); DUMPC(uses); DUMPC(files); DUMPM(configs);}
};


struct UppAssemblyData {
	const UppAssembly& as;
	ArrayMap<String, UppProject> prjs;
	Mutex lock;
	
	
	UppAssemblyData(const UppAssembly& as) : as(as) {}
	UppProject& GetProject(String name);
	UppProject& RealizeProject(String name);
	int FindName(String s) const;
	void Clear();
	
};


struct UppAssemblyCache {
	const UppAssemblyData& asd;
	String persistent_path;
	
	VectorMap<String, String> files;
	
	UppAssemblyCache(const UppAssemblyData& asd) : asd(asd) {}
	
	void SetPersistent(String path) {persistent_path = path;}
	bool LoadThis();
	bool StoreThis();
	void Serialize(Stream& s);
	void Load();
	void Clear();
	
	Callback2<int,int> WhenProgress;
	Callback1<int> WhenLoaded;
};


END_TEXTLIB_NAMESPACE


#endif
