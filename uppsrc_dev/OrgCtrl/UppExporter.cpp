#include "OrgCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


UppExporterView::UppExporterView() : cache(data), data(assembly) {
	
}

void UppExporterView::Clear() {
	assembly.Clear();
	data.Clear();
	cache.Clear();
	main_prj = 0;
}

void UppExporterView::Data() {
	ReadFiles();
}

void UppExporterView::ReadFiles() {
	main_prj = 0;
	
	String ass_dir = node->data.GetAdd("assembly");
	if (ass_dir.IsEmpty())
		return;
	if (ass_dir.Right(1) == DIR_SEPS)
		ass_dir = ass_dir.Left(ass_dir.GetCount()-1);
	
	RealizeDirectory(ass_dir);
	assembly.AddPath(ass_dir);
	
	String name = node->data.GetAdd("main-package");
	String pkg_dir = AppendFileName(ass_dir, name);
	
	String upp_path = AppendFileName(pkg_dir, name + ".upp");
	if (!FileExists(upp_path)) {
		RealizeDirectory(pkg_dir);
		FileOut fout(upp_path);
	}
	
	int i = assembly.FindProject(name);
	if (i < 0)
		return;
	
	UppProject& prj = data.GetProject(name);
	if (prj.Load(name, upp_path)) {
		main_prj = &prj;
	}
}










UppExporterCtrl::UppExporterCtrl() {
	Add(hsplit.SizePos());
	
	CtrlLayout(form);
	
	hsplit.Horz() << form << vsplit << edit;
	hsplit.SetPos(5000,1);
	
	vsplit.Vert() << pkgs << files;
	
	edit.Highlight("cpp");
	
	pkgs.AddColumn("Package");
	pkgs <<= THISBACK(DataPkg);
	
	files.AddColumn("File");
	files <<= THISBACK(DataFile);
	files.WhenBar << [this](Bar& bar) {
		bar.Add("Remove file", THISBACK1(Do, REM_FILE));
	};
	
	form.assembly <<= THISBACK(OnValueChange);
	form.main_pkg <<= THISBACK(OnValueChange);
	form.make_files <<= THISBACK1(Do, MAKE_FILES);
	form.update <<= THISBACK1(Do, UPDATE_FILES);
	
}

void UppExporterCtrl::OnValueChange() {
	Node& n = *view->node;
	
	n.data.GetAdd("assembly") = (String)form.assembly.GetData();
	n.data.GetAdd("main-package") = (String)form.main_pkg.GetData();
}

void UppExporterCtrl::Data() {
	UppExporterView& view = dynamic_cast<UppExporterView&>(*this->view);
	Node& n = *view.node;
	
	view.WhenTree = THISBACK(OnTreeChange);
	
	form.assembly.SetData(n.data.GetAdd("assembly"));
	form.main_pkg.SetData(n.data.GetAdd("main-package"));
	
	if (!view.main_prj) {
		pkgs.Clear();
		files.Clear();
		return;
	}
	
	pkg_list.Clear();
	view.main_prj->GetRecursiveUses(pkg_list, view.data);
	int c = pkg_list.GetCount();
	for(int i = 0; i < c; i++) {
		pkgs.Set(i, 0, pkg_list[i]);
	}
	INHIBIT_CURSOR(pkgs);
	pkgs.SetCount(c);
	if (!pkgs.IsCursor() && pkgs.GetCount())
		pkgs.SetCursor(0);
	
	DataPkg();
}

void UppExporterCtrl::DataPkg() {
	UppExporterView& view = dynamic_cast<UppExporterView&>(*this->view);
	
	if (!pkgs.IsCursor() || !view.main_prj) {
		files.Clear();
		return;
	}
	
	String pkg_name = pkgs.Get(0);
	UppProject& prj = view.data.GetProject(pkg_name);
	
	int c = prj.GetFileCount();
	for(int i = 0; i < c; i++) {
		files.Set(i, 0, prj.GetFile(i));
	}
	INHIBIT_CURSOR(files);
	files.SetCount(c);
	if (!files.IsCursor() && files.GetCount())
		files.SetCursor(0);
	
	DataFile();
}

void UppExporterCtrl::DataFile() {
	UppExporterView& view = dynamic_cast<UppExporterView&>(*this->view);
	
	if (!pkgs.IsCursor() || !files.IsCursor() || !view.main_prj) {
		files.Clear();
		return;
	}
	
	String pkg_name = pkgs.Get(0);
	UppProject& prj = view.data.GetProject(pkg_name);
	int file_i = files.GetCursor();
	
	String file_path = prj.GetFilePath(file_i);
	
	String content = LoadFile(file_path);
	edit.SetData(content);
}

void UppExporterCtrl::ToolMenu(Bar& bar) {
	bar.Add(t_("Make files"), AppImg::RedRing(), THISBACK1(Do, MAKE_FILES)).Key(K_F5);
	bar.Add(t_("Export code"), AppImg::RedRing(), THISBACK1(Do, EXPORT_CODE)).Key(K_F6);
	
}

void UppExporterCtrl::Do(int fn) {
	UppExporterView& view = dynamic_cast<UppExporterView&>(*this->view);
	
	if (fn == MAKE_FILES) {
		view.MakeFiles();
	}
	
	if (fn == MAKE_FILES || fn == UPDATE_FILES) {
		UppExporterView& view = dynamic_cast<UppExporterView&>(*this->view);
		view.Clear();
		view.Data();
		Data();
	}
	
	if (fn == EXPORT_CODE) {
		if (!pkgs.IsCursor())
			return;
		String pkg_name = pkgs.Get(0);
		UppProject& prj = view.data.GetProject(pkg_name);
		
		Vector<Node*> files;
		view.node->owner->FindChildDeep(files, NODE_FILE);
		
		for(Node* file : files) {
			int i = prj.FindAddFile(file->name);
			String path = prj.GetFilePath(i);
			LOG(path);
			FileOut fout(path);
			String content = file->data.GetAdd("content");
			fout << content;
		}
		prj.Store();
		PostCallback(THISBACK(DataPkg));
	}
	
	if (fn == REM_FILE) {
		if (!files.IsCursor())
			return;
		int file_i = files.GetCursor();
		
		String pkg_name = pkgs.Get(0);
		UppProject& prj = view.data.GetProject(pkg_name);
		if (file_i >= 0 && file_i < prj.GetFileCount()) {
			String path = prj.GetFilePath(file_i);
			prj.RemoveFile(file_i);
			::remove(path);
			prj.Store();
			PostCallback(THISBACK(DataPkg));
		}
	}
	
}


END_TEXTLIB_NAMESPACE
