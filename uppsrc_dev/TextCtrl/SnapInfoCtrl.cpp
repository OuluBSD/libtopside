#include "TextCtrl.h"
#include <TopTool/TopTool.h>


BEGIN_TEXTLIB_NAMESPACE


SnapInfoCtrl::SnapInfoCtrl() {
	CtrlLayout(*this);
	
	title <<= THISBACK(OnValueChange);
	date <<= THISBACK(OnValueChange);
	
}

void SnapInfoCtrl::Clear() {
	this->title		.Clear();
	this->date		.Clear();
}

void SnapInfoCtrl::Data() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	Clear();
	
	if (p.release) {
		Snapshot& r = *p.release;
		
		title.SetData(r.title);
		date.SetData(r.date);
	}
	
}

void SnapInfoCtrl::OnValueChange() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	if (p.release && p.editor && p.editor->snaps.IsCursor()) {
		Snapshot& r = *p.release;
		
		r.title = title.GetData();
		r.date = date.GetData();
		
		int c = p.editor->snaps.GetCursor();
		p.editor->snaps.Set(c, 0, r.title);
	}
	
}


END_TEXTLIB_NAMESPACE
