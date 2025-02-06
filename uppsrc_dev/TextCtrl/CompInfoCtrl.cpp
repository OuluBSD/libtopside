#include "TextCtrl.h"
#include <TopTool/TopTool.h>


BEGIN_TEXTLIB_NAMESPACE


CompInfoCtrl::CompInfoCtrl() {
	CtrlLayout(*this);
	
	name <<= THISBACK(OnValueChange);
	reference <<= THISBACK(OnValueChange);
	
	scripts.AddColumn(t_("Typeclass & Content"));
	scripts.AddColumn(t_("Script"));
	scripts.ColumnWidths("1 5");
	scripts.AddIndex("IDX");
	
	scripts.WhenCursor << THISBACK(DataScript);
	
	set.WhenAction << THISBACK(SetScript);
	
}

void CompInfoCtrl::ToolMenu(Bar& bar) {
	ToolAppCtrl::ToolMenu(bar);
}

void CompInfoCtrl::Clear() {
	this->name				.Clear();
	
}

void CompInfoCtrl::Data() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	Clear();
	
	if (p.component) {
		Component& s = *p.component;
		
		name.SetData(s.name);
		reference.SetData(s.reference);
	}
	
	
	if (!p.entity) {
		scripts.Clear();
		return;
	}
	
	Entity& a = *p.entity;
	
	int row = 0;
	//const auto& tcs = GetTypeclasses();
	//const auto& cons = GetContents();
	for(int i = 0; i < a.scripts.GetCount(); i++) {
		Script& sc = a.scripts[i];
		String g;// = tcs[sc.typeclass] + ": " + cons[sc.content].key;
		scripts.Set(row, "IDX", i);
		scripts.Set(row, 0, g);
		scripts.Set(row, 1, sc.GetAnyTitle());
		row++;
	}
	INHIBIT_CURSOR(scripts);
	scripts.SetCount(row);
	int cursor = 0;
	if (cursor >= 0 && cursor < scripts.GetCount())
		scripts.SetCursor(cursor);
	
	DataScript();
}

void CompInfoCtrl::DataScript() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	if (!p.entity || !scripts.IsCursor()) {
		scripts_text.Clear();
		return;
	}
	
	Entity& a = *p.entity;
	Script& lyr = a.scripts[scripts.Get("IDX")];
	
	String text = lyr.GetText();
	if (text.GetCount())
		scripts_text.SetData(text);
	else
		scripts_text.SetData("<no scripts>");
}

void CompInfoCtrl::OnValueChange() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	if (p.component && p.editor->components.IsCursor()) {
		Component& s = *p.component;
		
		s.name = name.GetData();
		s.reference = reference.GetData();
		
		int c = p.editor->components.GetCursor();
		p.editor->components.Set(c, 0, s.entity);
		p.editor->components.Set(c, 1, s.name);
	}
}

void CompInfoCtrl::SetScript() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	Component& s = *p.component;
	
	if (!p.entity || !p.component || !scripts.IsCursor()) {
		return;
	}
	
	int l_i = scripts.Get("IDX");
	Script& l = p.entity->scripts[l_i];
	s.scripts_file_title = l.file_title;
}


END_TEXTLIB_NAMESPACE
