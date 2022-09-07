#include "StartupDialog.h"


#undef DLOG
#define DLOG(x)

void Package::Load(String path) {
	DLOG("Package::Load " << path);
	
	info.Clear();
	name.Clear();
	desc.Clear();
	nest.Clear();
	files.Clear();
	
	this->path = path;
	
	FileIn in(path);
	if (in.IsOpen() == false) return;
	
	int a, b;
	b = path.Find(".upp");
	a = path.ReverseFind(DIR_SEPS, b) + 1;
	name = path.Mid(a, b-a);
	
	String s = in.Get(in.GetSize());
	
	Vector<String> v = Split(s, ";");
	
	for(int i = 0; i < v.GetCount(); i++) {
		//v[i] = TrimBoth(v[i]);
		String item = TrimBoth(v[i]);
		a = item.Find("\n");
		b = item.Find(" ");
		if (b != -1 && (b < a || a == -1) )
			a = b;
		else if (b == -1 && a == -1)
			continue;
		
		String key = item.Left(a);
		DLOG("key: " << key);
		
		Vector<String>& out = info.Add(key);
		
		Vector<String> v2 = Split(item.Mid(a), ",");
		for(int j = 0; j < v2.GetCount(); j++) {
			String value = TrimBoth(v2[j]);
			value.Replace("\n","");
			out.Add(value);
			DLOG("\tvalue: " << value);
		}
		
	}
	
	if (info.Find("description") != -1) {
		Vector<String>& v = info.Get("description");
		if (v.GetCount()) {
			desc = v[0];
			int i = desc.Find("\\377");
			if (i != -1) desc = desc.Left(i);
			if (desc.Left(1) == "\"") desc = desc.Mid(1);
		}
	}
	
	if (info.Find("file") != -1) {
		Vector<String>& v = info.Get("file");
		for(int i = 0; i < v.GetCount(); i++) {
			String filename = v[i];
			if (filename.Find("\"") != -1) // TODO: support separators
				continue;
			int j = filename.Find(" ");
			if (j > 0 && filename[j-1] != '\\') {
				filename = filename.Left(j);
			}
			PackageFile& pf = files.Add();
			pf.path = AppendFileName(GetFileDirectory(path), filename);
			pf.name = v[i];
		}
	}
	else info.Add("file");
}

void Package::Store() {
	FileOut out(path);
	String dir = GetFileDirectory(path);
	int dir_len = dir.GetCount();
	for(int i = 0; i < info.GetCount(); i++) {
		out << info.GetKey(i) << "\n";
		if (info.GetKey(i) == "file") {
			for(int j = 0; j < files.GetCount(); j++) {
				out << "    " << files[j].path.Mid(dir_len);
				if (j < files.GetCount() - 1)
					out << ",\n";
				else
					out << ";\n";
			}
		} else {
			
			Vector<String>& v = info[i];
			for(int j = 0; j < v.GetCount(); j++) {
				out << "    " << v[j];
				if (j < v.GetCount() - 1)
					out << ",\n";
				else
					out << ";\n";
			}
		}
	}
}

Vector<String> Package::GetConfigurations() {
	Vector<String> out;
	for(int i = 0; i < info.GetCount(); i++) {
		if (info.GetKey(i) != "mainconfig") continue;
		out.Append(info[i]);
		break;
	}
	return out;
}

void Assembly::RefreshPackages() {
	Vector<String> nestlist = GetNests();
	pkgs.Clear();
	
	Vector<String> prj;
	
	for(int i = 0; i < nestlist.GetCount(); i++) {
		FindFile ff;
		if(!ff.Search(AppendFileName(nestlist[i], "*")))
			continue;
        ff.Next();
        do {
            if (ff.GetPath().Right(2)== "..") 
            	continue;
            DLOG("Path: " << ff.GetPath());
            if (DirectoryExists(ff.GetPath())) {
                	prj.Add(ff.GetPath());
            }
            
		}
        while(ff.Next());
	}
	
	for(int i = 0; i < prj.GetCount(); i++) {
		FindFile ff;
		DLOG(prj[i]);
		if(!ff.Search(AppendFileName(prj[i], "*.upp")))
			continue;
        
        do {
            if (ff.GetPath().Right(2)== "..") continue;
            DLOG("IDE project: " << ff.GetPath());
            String filename = GetFileTitle( ff.GetPath() );
            Package& pkg = pkgs.Add(filename);
            pkg.Load(ff.GetPath());
            pkg.nest = name;
		}
        while(ff.Next());
	}
	
	return;
}


PackageEditor::PackageEditor() {
	SetRect(0,0,600,3*40);
	
	Add(lname.TopPos(5,30).LeftPos(5,200));
	Add(name.TopPos(5,30).LeftPos(210, 385));
	lname.SetLabel("Name:");
	
	Add(ldesc.TopPos(40,30).LeftPos(5,200));
	Add(desc.TopPos(40,30).LeftPos(210, 385));
	ldesc.SetLabel("Description:");
	
	Add(bcreate.BottomPos(5,30).RightPos(5,100));
	Add(cancel.BottomPos(5,30).RightPos(110,100));
	bcreate.SetLabel("Create");
	cancel.SetLabel("Cancel");
	
	bcreate.WhenAction = THISBACK(Create);
	cancel.WhenAction = THISBACK(Cancel);
	
	create = 0;
}

void PackageEditor::Get(Package& p) {
	p.name = name.GetData();
	p.desc = desc.GetData();
}

void PackageEditor::SetPackage(Package& pkg) {
	this->pkg = &pkg;
	name.SetData(pkg.name);
	desc.SetData(pkg.desc);
}

AssemblyEditor::AssemblyEditor() {
	SetRect(0,0,600,4*40);
	
	Add(lname.TopPos(5,30).LeftPos(5,200));
	Add(name.TopPos(5,30).LeftPos(210, 385));
	lname.SetLabel("Name:");
	
	Add(lnests.TopPos(40,30).LeftPos(5,200));
	Add(nests.TopPos(40,30).LeftPos(210, 385));
	lnests.SetLabel("Nests:");
	
	Add(loutput.TopPos(80,30).LeftPos(5,200));
	Add(output.TopPos(80,30).LeftPos(210, 385));
	loutput.SetLabel("Output:");
	
	Add(bcreate.BottomPos(5,30).RightPos(5,100));
	Add(cancel.BottomPos(5,30).RightPos(110,100));
	bcreate.SetLabel("Create");
	cancel.SetLabel("Cancel");
	
	bcreate.WhenAction = THISBACK(Create);
	cancel.WhenAction = THISBACK(Cancel);
	
	create = 0;
}

void AssemblyEditor::SetAssembly(Assembly& a) {
	as = &a;
	name.SetData(a.name);
	nests.SetData(a.nests);
	output.SetData(a.output);
}






ProjectManagerDialog::ProjectManagerDialog() {
	open_assembly = -1;
	open_package  = -1;
	
	Title("Open project");
	
	Add(split.VSizePos(0,40).HSizePos());
	split.Set(assembly, package);
	split.SetPos(2000);
	
	Add(ok.BottomPos(5,30).RightPos(5,100));
	Add(cancel.BottomPos(5,30).RightPos(110,100));
	Add(newpkg.BottomPos(5,30).RightPos(215,100));
	
	ok.SetLabel("OK");
	cancel.SetLabel("Cancel");
	newpkg.SetLabel("New package");
	
	package.WhenLeftDouble = THISBACK(Ok);
	ok.WhenAction = THISBACK(Ok);
	cancel.WhenAction = THISBACK(Cancel);
	newpkg.WhenAction = THISBACK(NewPackage);
	
	assembly.AddColumn("Assembly");
	assembly.WhenLeftDouble << THISBACK(EditAssembly);
	assembly.WhenLeftClick << THISBACK(SelectAssembly);
	
	assembly.RemoveAssembly << THISBACK(RemoveAssembly);
	assembly.EditAssembly << THISBACK(EditAssembly);
	assembly.NewAssembly << THISBACK(NewAssembly);
	
	package.AddColumn("Package");
	package.AddColumn("Nest");
	package.AddColumn("Description");
	package.ColumnWidths("2 1 8");
	
	SetRect(0,0,800,400);
	
	PostCallback(THISBACK(RefreshAssemblies));
	
}


void ProjectManagerDialog::RefreshAssemblies() {
	ProjectManager& pman = GetProjectManager();
	for(int i = 0; i < pman.GetAssemblyCount(); i++) {
		Assembly& a = pman.GetAssembly(i);
		assembly.Set(i, 0, a.name);
	}
	if (assembly.GetCursor() == -1 && assembly.GetCount()) assembly.SetCursor(0);
	SelectAssembly();
}



void ProjectManagerDialog::Ok() {
	open_assembly	= assembly.GetCursor();
	open_package	= package.GetCursor();
	open = 1; PostCallback(THISBACK(DoClose));
}

void ProjectManagerDialog::Cancel() {
	open = 0; PostCallback(THISBACK(DoClose));
}



void ProjectManagerDialog::NewPackage() {
	int c = assembly.GetCursor();
	if (c == -1) return;
	ProjectManager& pman = GetProjectManager();
	Assembly& as = pman.GetAssembly(c);
	Package pkg;
	
	PackageEditor pkged;
	pkged.SetPackage(pkg);
	pkged.create = 1;
	pkged.Run();
	
	if (pkged.create) {
		pkged.Get(pkg);
		Vector<String> nestlist = as.GetNests();
		if (!nestlist.GetCount()) return;
		String pkg_path = AppendFileName(nestlist[0], pkg.name);
		RealizeDirectory(pkg_path);
		String pkg_upp_file = AppendFileName(pkg_path, pkg.name + ".upp");
		FileOut out(pkg_upp_file);
		out << "description \"" << pkg.desc << "\\377\";\n";
		out.Close();
		SelectAssembly();
	}
}

void ProjectManagerDialog::NewAssembly() {
	Assembly as;
	asmed.SetAssembly(as);
	asmed.create = 0;
	asmed.Run();
	if (asmed.create) {
		asmed.Get(as);
		Assembly& newasm = GetProjectManager().AddAssembly(as);
		Vector<String> nestlist = newasm.GetNests();
		for(int i = 0; i < nestlist.GetCount(); i++)
			RealizeDirectory(nestlist[i]);
	}
}

void ProjectManagerDialog::EditAssembly() {
	int c = assembly.GetCursor();
	if (c == -1) {
		NewAssembly();
	} else {
		ProjectManager& pman = GetProjectManager();
		Assembly& as = pman.GetAssembly(c);
		asmed.SetAssembly(as);
		asmed.create = 0;
		asmed.Run();
		if (asmed.create) {
			asmed.Get(as);
			pman.RefreshAssemblies();
			pman.StoreThis();
		}
	}
}

void ProjectManagerDialog::RemoveAssembly() {
	int c = assembly.GetCursor();
	if (c != -1) {
		GetProjectManager().RemoveAssembly(c);
		assembly.Remove(c);
	} 
}
	
void ProjectManagerDialog::SelectAssembly() {
	int c = assembly.GetCursor();
	if (c == -1) return;
	
	Assembly& a = GetProjectManager().GetAssembly(c);
	a.RefreshPackages();
	
	package.Clear();
	for(int i = 0; i < a.pkgs.GetCount(); i++) {
		Package& p = a.pkgs[i];
		package.Set(i, 0, p.name);
		package.Set(i, 1, p.nest);
		package.Set(i, 2, p.desc);
	}
}

