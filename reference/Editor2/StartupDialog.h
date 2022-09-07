#ifndef _Editor_StartupDialog_h_
#define _Editor_StartupDialog_h_

#include <CtrlLib/CtrlLib.h>
using namespace UPP;

#include "ProjectManager.h"


class AssemblyEditor : public TopWindow {
	Assembly* as;
	EditString nests, output, name;
	Label lnests, loutput, lname;
	Button bcreate, cancel;
	
public:
	typedef AssemblyEditor CLASSNAME;
	AssemblyEditor();
	
	void SetAssembly(Assembly& a);
	void Get(Assembly& a) {a.name = name.GetData(); a.nests = nests.GetData(); a.output = output.GetData();}
	
	void Create() {create = 1; Cancel();}
	void Cancel() {Close();}
	
	bool create;
};

class AssemblyCtrl : public ArrayCtrl {
	
public:
	typedef AssemblyCtrl CLASSNAME;
	
	void LocalMenu(Bar& bar) {
		bar.Add("New assembly", Proxy(NewAssembly));
		bar.Add("Edit assembly", Proxy(EditAssembly));
		bar.Add("Remove assembly", Proxy(RemoveAssembly));
	}

	void RightDown(Point, dword) {
		MenuBar::Execute(THISBACK(LocalMenu));
	}
	
	Callback NewAssembly, EditAssembly, RemoveAssembly;
	
};

class PackageEditor : public TopWindow {
	Package* pkg;
	EditString name, desc;
	Label lname, ldesc;
	Button bcreate, cancel;
	
public:
	typedef PackageEditor CLASSNAME;
	PackageEditor();
	
	void Get(Package& p);
	void SetPackage(Package&);
	void Create() {create = 1; Cancel();}
	void Cancel() {Close(); Close();}
	
	bool create;
	
};

class ProjectManagerDialog : public TopWindow {
	Splitter split;
	AssemblyCtrl assembly;
	ArrayCtrl package;
	Button ok, cancel, newpkg;
	AssemblyEditor asmed;
	
public:
	typedef ProjectManagerDialog CLASSNAME;
	
	ProjectManagerDialog();
	
	void OpenFirst() {GetProjectManager().OpenFirst(); open = true;}
	
	void DoClose() {TopWindow::Close();}
	void RefreshAssemblies();
	
	void Ok();
	void Cancel();
	void NewPackage();
	void NewAssembly();
	void EditAssembly();
	void RemoveAssembly();
	void SelectAssembly();
	
	int open_assembly, open_package;
	bool open;
	
};


#endif
