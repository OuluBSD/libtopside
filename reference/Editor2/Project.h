#ifndef _Editor_Project_h_
#define _Editor_Project_h_

#include "NodeCache.h"


class Assembly;

class PackageFile : public Moveable<PackageFile> {
	bool compiled;
public:
	String path, name;
	
	//void SetCompiled(bool b=true) {compiled=b;}
	//bool IsCompiled() {return compiled;}
	
	void SetCompiled(String obj_path);
	bool IsCompiled(String obj_path);
};

class Package : public Moveable<Package> {

public:
	Package() {builder=-1; assembly=1;}
	Package(const Package& src) {*this = src;}
	
	Package& operator=(const Package& src) {
		name = src.name;
		desc = src.desc;
		nest = src.nest;
		info <<= info;
		path = src.path;
		builder = src.builder;
		assembly = src.assembly;
		files <<= src.files;
		return *this;
	}
	String name, desc, nest;
	ArrayMap<String, Vector<String> > info;
	String path;
	int builder, assembly;
	
	Array<PackageFile> files;
	
	void Load(String path);
	void Store();
	
	Vector<String> GetConfigurations();
};

class Project {
	
	Package* main;
	NodeCache cache;
	
public:
	typedef Project CLASSNAME;
	Project();
	Project(const Project& prj);
	Project& operator=(const Project& prj) {main = prj.main; cache = prj.cache; return *this;}
	
	void RefreshCache();
	bool OpenUsedPackageExists(int i);
	int FindPackageConfiguration(String s);
	
	Vector<String> GetUseList();
	Vector<String> GetTopFolders();
	int GetOpenUsedPackageCount();
	Package& GetOpenUsedPackage(int i);
	Assembly& GetOpenAssembly();
	Package& GetOpenPackage() {return *main;}
	String GetPackageConfiguration(int i);
	Translation::Project& GetTranslator() {return cache.GetTranslator();}
	NodeCache& GetCache() {return cache;}
	
	void SetPackage(Package& pkg) {main = &pkg;}
	
};

#endif
