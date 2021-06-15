#include "Editor.h"


NAMESPACE_TOPSIDE_BEGIN


FindInFilesDlg::FindInFilesDlg() {
	CtrlLayout(*this);
	
	ok.WhenAction = THISBACK1(DoClose, true);
	cancel.WhenAction = THISBACK1(DoClose, false);
	
	files.Add("*.*");
	files.Add("*.js");
	files.Add("*.html");
	files.SetIndex(0);
	
}

bool FindInFilesDlg::Key(dword key, int count) {
	
	if (key == K_ESCAPE) {
		DoClose(false);
		return true;
	}
	
	if (key == K_ENTER) {
		DoClose(true);
		return true;
	}
	
	return false;
}
	
void FindInFilesDlg::Setup(bool replace) {
	
}

void FindInFilesDlg::Sync() {
	
}



void Editor::FindInFiles(int replace_mode) {
	/*int tab = tabs.Get();
	if (tab < 0 || tab >= tab_ctrls.GetCount()) return;
	SessionFileCtrl& pfc = tab_ctrls[tab];
	Size screen_size = GetScreenSize();
	CodeEditor& edit = pfc.GetEditor();
	Rect r = edit.GetLineScreenRect(edit.GetCursorLine());
	Point pt = r.TopLeft();
	pt.y += r.GetHeight();
	Point pt2 = edit.GetCaretPoint();
	Size sz = ff.GetSize();
	ff.SetRect(pt.x + pt2.x, pt.y, sz.cx, sz.cy);
	if (!ff.IsOpen()) {
		String sel = edit.GetSelection();
		if (sel.GetCount()) {
			ff.find.SetData(sel);
			bool exist_in_list = false;
			for(int i = 0; i < ff.find.GetCount(); i++) {
				if (ff.find.Get(i) == sel) {
					exist_in_list = true;
					break;
				}
			}
			if (!exist_in_list) ff.find.AddList(sel);
		}
		ff.style = replace_mode;
		ff.Ctrl::PopUp(this, false, true, true);
		if (replace_mode == 0)
			ff.find.SetFocus();
		else
			ff.replace.SetFocus();
	}*/
}

void Editor::DoFindInFiles() {
	/*ffound.Clear();
	
	String find = ff.find.GetData();
	if (find.GetCount() == 0) return;
	
	SetBottom(BFINDINFILES);
	
	int replace_type = ff.style;
	String repl = ff.replace.GetData();
	
	int tab = tabs.Get();

	SessionFileCtrl& pfc = tab_ctrls[tab];
	pfc.GetCodeEditorCtrl().StoreFile();
	
	//CodeEditor& edit = pfc.GetEditor();
	CodeEditorCtrl& cec = pfc.GetCodeEditorCtrl();
	String content = cec.GetContent();
	
	Vector<String> lines = Split(content, "\n", false);
	for(int j = 0; j < lines.GetCount(); j++) {
		String line = lines[j];
		
		int k = line.Find(find);
		if (k == -1) continue;
		
		String s;
		s << "\1" << "js";
		s << "\1" << k;
		s << "\1" << find.GetCount();
		s << "\1" << line;
		
		ffound.Add(
			pfc.GetPath(),
			j+1,
			s,
			"");
	}
	
	if (replace_type) {
		content.Replace(find, repl);
		cec.SetContent(content);
		cec.StoreThis();
		cec.LoadFile();
	}
	
	if (tab >= 0 && tab < tabs.GetCount()) tabs.Set(tab);
	*/
}


NAMESPACE_TOPSIDE_END
