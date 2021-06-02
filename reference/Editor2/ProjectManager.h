#ifndef _Editor_ProjectManager_h_
#define _Editor_ProjectManager_h_

#include <Core/Core.h>
using namespace UPP;

#include "Project.h"

class ProjectManagerDialog;


class Assembly : public Moveable<Assembly> {
	
public:
	Assembly() {}
	Assembly(const Assembly& src) {*this = src;}
	Assembly& operator=(const Assembly& src) {
		pkgs <<= src.pkgs;
		nests = src.nests;
		output = src.output;
		name = src.name;
		return *this;
	}
	
	ArrayMap<String, Package> pkgs;
	String nests, output, name;
	
	void Serialize(Stream& s) {s % nests % output % name;}
	
	void RefreshPackages();
	Vector<String> GetNests() {return Split(nests, ";");}
};





class ProjectManager {
	
protected:
	friend class ProjectManagerDialog;
	ArrayMap<String, Assembly> assemblies;
	
public:
	ProjectManager();
	
	void OpenFirst();
	
	void LoadThis() {LoadFromFile(*this, ConfigFile("ProjectManager.bin"));}
	void StoreThis() {StoreToFile(*this, ConfigFile("ProjectManager.bin"));}
	void Serialize(Stream& s) {s % assemblies;}
	
	void RefreshAssemblies();
	void RefreshAssemblyPackages();
	void RemoveAssembly(int i) {assemblies.Remove(i); StoreThis();}
	
	Package& GetPackage(int assembly, String name);
	int GetAssemblyCount() {return assemblies.GetCount();}
	Assembly& GetAssembly(int i) {return assemblies[i];}
	Project GetProject(int open_assembly, int open_package);
	Assembly& AddAssembly(Assembly& as);
	
};


inline ProjectManager& GetProjectManager() {return Single<ProjectManager>();}




#endif
