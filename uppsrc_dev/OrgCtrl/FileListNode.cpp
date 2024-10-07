#include "OrgCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


FileListView::FileListView() {
	
}

void FileListView::Data() {
	
}



FileListCtrl::FileListCtrl() {
	Add(hsplit.SizePos());
	
	CtrlLayout(form);
	
	hsplit.Horz() << files << form;
	
	files.AddColumn("#");
	files.AddColumn("File");
	files.AddIndex("IDX");
	files.ColumnWidths("1 4");
	
	files.WhenBar << [this](Bar& b) {
		b.Add("Add file", THISBACK1(Do, ADD_FILE));
		b.Add("Remove file", THISBACK1(Do, REM_FILE));
	};
	
}

void FileListCtrl::Data() {
	ValueArray arr = view->node->GetArray("files");
	
	for(int i = 0; i < arr.GetCount(); i++) {
		const Value& v = arr[i];
		String name = GetMapValue(v, "name");
		files.Set(i, 0, i);
		files.Set(i, "IDX", i);
		
		EditString* edit = new EditString;
		edit->WhenAction << THISBACK(OnValueChange);
		files.SetCtrl(i, 1, edit);
		edit->SetData(name);
	}
	INHIBIT_CURSOR(files);
	files.SetCount(arr.GetCount());
	if (!files.IsCursor() && files.GetCount())
		files.SetCursor(0);
	
}

void FileListCtrl::OnValueChange() {
	if (!files.IsCursor())
		return;
	int idx = files.Get("IDX");
	int cursor = files.GetCursor();
	EditString& edit = *dynamic_cast<EditString*>(files.GetCtrl(cursor, 1));
	SetArrayMapValue(
		view->node->data.GetAdd("files"),
		idx,
		"name",
		edit.GetData());
}

void FileListCtrl::Do(int fn) {
	Node& n = *view->node;
	Value& fv = n.data.GetAdd("files");
	if (!fv.Is<ValueArray>())
		fv = ValueArray();
	ValueArray arr = fv;
	
	if (fn == ADD_FILE) {
		ValueMap map;
		map.Set("name", "");
		arr.Add(map);
		fv = arr;
		
		PostCallback(THISBACK(Data));
	}
	
	if (fn == REM_FILE) {
		if (!files.IsCursor())
			return;
		int idx = files.Get("IDX");
		if (idx >= 0 && idx < arr.GetCount())
			arr.Remove(idx);
		fv = arr;
		
		PostCallback(THISBACK(Data));
	}
	
	if (fn == SET_FILES) {
		if (!n.owner)
			return;
		Node& owner = *n.owner;
		
		for(int i = 0; i < arr.GetCount(); i++) {
			String name = GetMapValue(arr[i], "name");
			Node& file = owner.GetAddNode(name, NODE_FILE);
		}
		
		org->Data();
	}
	
}

void FileListCtrl::ToolMenu(Bar& bar) {
	bar.Add(t_("Set files"), AppImg::RedRing(), THISBACK1(Do, SET_FILES)).Key(K_F5);
	
}



END_TEXTLIB_NAMESPACE

