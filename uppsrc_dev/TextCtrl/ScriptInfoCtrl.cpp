#include "TextCtrl.h"
#include <TopTool/TopTool.h>


BEGIN_TEXTLIB_NAMESPACE


ScriptInfoCtrl::ScriptInfoCtrl() {
	CtrlLayout(*this);
	
	copyright <<= THISBACK(OnValueChange);
	
}

void ScriptInfoCtrl::Clear() {
	this->copyright			.Clear();
}

void ScriptInfoCtrl::Data() {
	MetaDatabase& mdb = MetaDatabase::Single();
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	Clear();
	
	
	if (p.script) {
		Script& l = *p.script;
		
		copyright.SetData(l.copyright);
	}
}

void ScriptInfoCtrl::OnValueChange() {
	MetaDatabase& mdb = MetaDatabase::Single();
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	if (p.script && p.editor->scripts.IsCursor()) {
		Script& l = *p.script;
		
		l.copyright = copyright.GetData();
		
		int c = p.editor->scripts.GetCursor();
		p.editor->scripts.Set(c, 0, l.GetAnyTitle());
	}
}

void ScriptInfoCtrl::ToolMenu(Bar& bar) {
	
}

END_TEXTLIB_NAMESPACE
