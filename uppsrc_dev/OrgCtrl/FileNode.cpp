#include "OrgCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


FileView::FileView() {
	
}

void FileView::Data() {
	
}



FileCtrl::FileCtrl() {
	Add(hsplit.SizePos());
	
	hsplit.Horz() << form << edit;
	CtrlLayout(form);
	
	
}

void FileCtrl::Data() {
	String ext = GetFileExt(view->node->name);
	edit.Highlight(ext.Mid(1));
	
	edit.SetData(view->node->data.GetAdd("content"));
	
}

void FileCtrl::OnValueChange() {
	
}

void FileCtrl::Do(int fn) {
	
}

void FileCtrl::ToolMenu(Bar& bar) {
	bar.Add(t_("Generate code"), AppImg::RedRing(), THISBACK1(Do, GENERATE_CODE)).Key(K_F5);
	
}



END_TEXTLIB_NAMESPACE
