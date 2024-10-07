#include "TextCtrl.h"
#include <TopTool/TopTool.h>


BEGIN_TEXTLIB_NAMESPACE


EntityInfoCtrl::EntityInfoCtrl() {
	CtrlLayout(*this);
	
	name <<= THISBACK(OnValueChange);
	
}

void EntityInfoCtrl::Clear() {
	this->name.Clear();
}

void EntityInfoCtrl::Data() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	Clear();
	
	if (p.entity) {
		Entity& a = *p.entity;
			
		this->name.SetData(a.name);
	}
	
	
}

void EntityInfoCtrl::OnValueChange() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	MetaPtrs& mp = MetaPtrs::Single();
	
	if (p.entity && p.editor->profiles.IsCursor()) {
		Entity& o = *p.entity;
		ASSERT(o.profile == mp.profile);
		o.name = this->name.GetData();
	}
}


END_TEXTLIB_NAMESPACE
