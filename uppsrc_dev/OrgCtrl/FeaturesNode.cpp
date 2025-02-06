#include "OrgCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


FeaturesView::FeaturesView() {
	
}

void FeaturesView::Data() {
	
}



FeaturesCtrl::FeaturesCtrl() {
	Add(hsplit.SizePos());
	
	CtrlLayout(form);
	
	hsplit.Horz() << form << features;
	
	features.AddColumn("#");
	features.AddColumn("Feature");
	features.AddIndex("IDX");
	features.ColumnWidths("1 4");
	
	features.WhenBar << [this](Bar& b) {
		b.Add("Add feature", THISBACK1(Do, ADD_FEATURE));
		b.Add("Remove feature", THISBACK1(Do, REM_FEATURE));
	};
	
}

void FeaturesCtrl::Data() {
	Node& n = *view->node;
	Value& fv = n.data.GetAdd("features");
	if (!fv.Is<ValueArray>())
		fv = ValueArray();
	ValueArray arr = fv;
	
	for(int i = 0; i < arr.GetCount(); i++) {
		features.Set(i, 0, i);
		features.Set(i, 1, arr[i]);
		features.Set(i, "IDX", i);
		
		EditString* edit = new EditString;
		edit->WhenAction << THISBACK(OnValueChange);
		features.SetCtrl(i, 1, edit);
		edit->SetData(arr[i]);
	}
	INHIBIT_CURSOR(features);
	features.SetCount(arr.GetCount());
	if (!features.IsCursor() && features.GetCount())
		features.SetCursor(0);
	
	
}

void FeaturesCtrl::OnValueChange() {
	if (!features.IsCursor())
		return;
	Node& n = *view->node;
	Value& fv = n.data.GetAdd("features");
	if (!fv.Is<ValueArray>())
		fv = ValueArray();
	ValueArray arr = fv;
	int cursor = features.GetCursor();
	EditString& edit = dynamic_cast<EditString&>(*features.GetCtrl(cursor, 1));
	int idx = features.Get("IDX");
	arr.Set(idx, edit.GetData());
	fv = arr;
	
	//PostCallback(THISBACK(Data));
}

void FeaturesCtrl::Do(int fn) {
	Node& n = *view->node;
	Value& fv = n.data.GetAdd("features");
	if (!fv.Is<ValueArray>())
		fv = ValueArray();
	ValueArray arr = fv;
	
	if (fn == ADD_FEATURE) {
		arr.Add("");
		fv = arr;
		
		PostCallback(THISBACK(Data));
	}
	
	if (fn == REM_FEATURE) {
		if (!features.IsCursor())
			return;
		int idx = features.Get("IDX");
		if (idx >= 0 && idx < arr.GetCount())
			arr.Remove(idx);
		fv = arr;
		
		PostCallback(THISBACK(Data));
	}
	
}




END_TEXTLIB_NAMESPACE

