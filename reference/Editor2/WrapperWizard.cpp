#include "WrapperWizard.h"
#include "MainEditor.h"

Frame1::Frame1() {
	CtrlLayout(*this);
	
	recent.AddColumn("Package");
	recent.AddColumn("Path");
	recent.ColumnWidths("2 1");
	
}


Frame2::Frame2() {
	Add(split.HSizePos().VSizePos(0,30));
	Add(prev.BottomPos(3, 24).RightPos(108, 100));
	Add(next.BottomPos(3, 24).RightPos(4, 100));
	
	split.Horz();
	split << files << contents << cls_contents;
	split.SetPos(0, 2000);
	
	files.AddColumn("Assembly");
	files.AddColumn("Filename");
	
	contents.AddColumn("Type");
	contents.AddColumn("Return value");
	contents.AddColumn("Key");
	contents.AddColumn("Wrap");
	
	cls_contents.AddColumn("Type");
	cls_contents.AddColumn("Return value");
	cls_contents.AddColumn("Key");
	cls_contents.AddColumn("Wrap");
	
	prev.SetLabel("Previous");
	next.SetLabel("Next");
	
}


Frame3::Frame3() {
	CtrlLayout(*this);
}


Frame4::Frame4() {
	
	Add(output.VSizePos(4, 30).HSizePos(4, 4));
	Add(restart.BottomPos(3, 24).RightPos(12+200, 100));
	Add(prev.BottomPos(3, 24).RightPos(8+100, 100));
	Add(ok.BottomPos(3, 24).RightPos(4, 100));
	
	ok.SetLabel("OK");
	prev.SetLabel("Previous");
	restart.SetLabel("Restart");
	
}




WrapperWizard::WrapperWizard(IDE* ide) : ide(ide) {
	ide = 0;
	
	LoadThis();
	
	Title("WrapperWizard");
	Sizeable();
	MaximizeBox();
	
	Add(f1.SizePos());
	Add(f2.SizePos());
	Add(f3.SizePos());
	Add(f4.SizePos());
	
	Phase1();
	f1.next.WhenAction = THISBACK(Phase2);
	f2.next.WhenAction = THISBACK(Phase3);
	f3.next.WhenAction = THISBACK(Phase4);
	f4.restart.WhenAction = THISBACK(Phase1);
	f4.ok.WhenAction = THISBACK(Ok);
	
	f2.prev.WhenAction = THISBACK(Phase1);
	f3.prev.WhenAction = THISBACK(Phase2);
	f4.prev.WhenAction = THISBACK(Phase3);
	
	f1.recent.WhenAction = THISBACK(SetF1Recent);
	f1.browse.WhenAction = THISBACK(F1Browse);
	
	f2.files.WhenAction = THISBACK(SetF2File);
	f2.contents.WhenAction = THISBACK(SetF2Class);
	
}

void WrapperWizard::HideAll() {
	f1.Hide();
	f2.Hide();
	f3.Hide();
	f4.Hide();
	
}

void WrapperWizard::SetView(int i) {
	view = i;
	HideAll();
	switch (i) {
		case 0: f1.Show(); break;
		case 1: f2.Show(); break;
		case 2: f3.Show(); break;
		case 3: f4.Show(); break;
	}
}

void WrapperWizard::SetF1Recent() {
	int cursor = f1.recent.GetCursor();
	if (cursor >= 0 && cursor < recent_wraps.GetCount())
		f1.path.SetData(recent_wraps.GetKey(cursor));
}

void WrapperWizard::F1Browse() {
	String path = SelectFileSaveAs("WrapperWizard files\t*.ww");
	if (path.GetCount()) f1.path.SetData(path);
}

void WrapperWizard::Phase1() {
	SetView(0);
	
	// Refresh recent files
	f1.recent.Clear();
	for(int i = 0; i < recent_wraps.GetCount(); i++)
		f1.recent.Add(GetFileName(recent_wraps.GetKey(i)), recent_wraps[i]);
	if (recent_wraps.GetCount())
		f1.recent.SetCursor(0);
	
}

void WrapperWizard::Phase2() {
	Project& prj = ide->GetProject();
	Package& pkg = prj.GetOpenPackage();
	
	if (view == 0) {
		wrap_path = f1.path.GetData();
		if (!wrap_path.GetCount()) {Phase1(); return;}
		file.Open(wrap_path);
		if (!file.IsOpen()) {Phase1(); return;}
		int i = recent_wraps.Find(wrap_path);
		if (i != -1) recent_wraps.Remove(i);
		recent_wraps.Insert(0, wrap_path, pkg.name);
		StoreThis();
	}
	
	SetView(1);
	
	// Refresh files and content (classes and functions)
	basic = prj.GetCache().GetAllBasic();
	f2.files.Clear();
	f2.contents.Clear();
	f2.cls_contents.Clear();
	for(int i = 0; i < basic.GetCount(); i++) {
		ClangNode& file = basic[i];
		String path = file.GetString();
		String filename = GetFileName(path);
		String project = *(Split(GetFileDirectory(path), DIR_SEPS).End()-1);
		f2.files.Add(project, filename);
		
	}
	
}

void WrapperWizard::SetF2File() {
	int cursor = f2.files.GetCursor();
	f2.contents.Clear();
	f2.cls_contents.Clear();
	if (cursor < 0 || cursor >= basic.GetCount()) return;
	ClangNode& file = basic[cursor];
	for(int j = 0; j < file.GetCount(); j++) {
		ClangNode& global_node = file[j];
		f2.contents.Add(
			global_node.GetKindString(),
			global_node.GetString(),
			global_node.GetKey(),
			0);
		f2.contents.SetCtrl(j, 3, new Option());
	}
	if (f2.contents.GetCount())
		f2.contents.SetCursor(0);
	f2.Refresh();
}

void WrapperWizard::SetF2Class() {
	f2.cls_contents.Clear();
	int cursor = f2.files.GetCursor();
	if (cursor < 0 || cursor >= basic.GetCount()) return;
	ClangNode& file = basic[cursor];
	int cls_cursor = f2.contents.GetCursor();
	if (cls_cursor < 0 || cls_cursor >= file.GetCount()) return;
	ClangNode& cls_item = file[cls_cursor];
	for(int j = 0; j < cls_item.GetCount(); j++) {
		ClangNode& cls_node = cls_item[j];
		f2.cls_contents.Add(
			cls_node.GetKindString(),
			cls_node.GetString(),
			cls_node.GetKey(),
			0);
		f2.cls_contents.SetCtrl(j, 3, new Option());
	}
	f2.Refresh();
}



void WrapperWizard::Phase3() {
	SetView(2);
	
	// Asks output file
	
	
}
void WrapperWizard::Phase4() {
	SetView(3);
	
	// Process. Show progress, results and errors.
	
	
}

bool WrapperWizard::Key(dword key, int count) {
	if (key == K_ESCAPE) {
		PostCallback(THISBACK(Ok));
		return true;
	}
	return false;
}