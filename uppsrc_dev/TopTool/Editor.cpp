#include "TopTool.h"

#define COOKIE_DEBUG 0

BEGIN_TEXTLIB_NAMESPACE




ToolEditor::ToolEditor(TopTool* app) : ToolEditorBase("editor", *app) {
	filter_profile_language = true;
	
	Add(hsplit.SizePos());
	
	hsplit.Horz() << menusplit << base;
	hsplit.SetPos(1000);
	
	menusplit.Vert() << page_group_list << page_list << owners << profiles << subsplit;
	int top_total = 10000 * 3 / 5;
	menusplit.SetPos(top_total * 1 / 5, 0);
	menusplit.SetPos(top_total * 2 / 5, 1);
	menusplit.SetPos(top_total * 3 / 5, 2);
	menusplit.SetPos(top_total * 4 / 5, 3);
	menusplit.SetPos(top_total, 4);
	componentsplit.Vert() << snaps << components;
	
	
	scripts.WhenBar << THISBACK(ScriptMenu);
	//profiles.WhenBar << THISBACK(EntityMenu);
	snaps.WhenBar << THISBACK(SnapshotMenu);
	components.WhenBar << THISBACK(SongMenu);
	
	
	
	snaps.AddColumn(t_("Snapshot"));
	snaps.ColumnWidths("3 2");
	snaps <<= THISBACK(DataSnapshot);
	
	components.AddColumn(t_("Song"));
	components <<= THISBACK(DataComponent);
	
	scripts.AddColumn(t_("Script"));
	scripts.AddIndex("IDX");
	scripts <<= THISBACK(DataScript);
	
	
	SetSubMenu(0);
	
	MetaPtrs::Single().db.editor = this;
}

void ToolEditor::SetSubMenu(int i) {
	subsplit.RemoveChild(&componentsplit);
	subsplit.RemoveChild(&scripts);
	
	if (i == 0)
		subsplit.Add(componentsplit.SizePos());
	else
		subsplit.Add(scripts.SizePos());
}

void ToolEditor::InitSimplified() {
	AddItem("Tools", t_("AI Image Generator"), image_gen);
	AddItem("Tools", t_("AI Image aspect ratio fixer"), aspect_fixer);
	AddItem("Entity", t_("Info"), entity_info);
	AddItem("Snapshot", t_("Info"), snap_info);
	AddItem("Component", t_("Info"), comp_info);
	AddItem("Script", t_("Info"), script_info);
	
}

void ToolEditor::Init() {
	LoadLast();
	
	ToolEditorBase::Init();
}

void ToolEditor::DataPage() {
	if (app.skip_data) return;
	
	app.PostStoreLast();
	
	EditorPtrs& p = GetPointers();
	p.editor = this;
	
	ToolEditorBase::DataPage();
	
}

String ToolEditor::GetStatusText() {
	int page = this->page.GetAdd(page_group, 0);
	if (page_group >= 0 && page_group < items.GetCount() && page >= 0 && page < items[page_group].GetCount())
		return items[page_group][page].ctrl->GetStatusText();
	else
		return String();
}

void ToolEditor::MovePageGroup(int d) {
	if (page_group_list.IsCursor()) {
		int c = page_group_list.GetCursor();
		c += d;
		if (c >= 0 && c < page_group_list.GetCount())
			page_group_list.SetCursor(c);
	}
}

void ToolEditor::MovePage(int d) {
	if (page_list.IsCursor()) {
		int c = page_list.GetCursor();
		c += d;
		if (c >= 0 && c < page_list.GetCount())
			page_list.SetCursor(c);
	}
}

void ToolEditor::MovePart(int d) {
	if (parts.IsCursor()) {
		int c = parts.GetCursor();
		c += d;
		if (c >= 0 && c < parts.GetCount())
			parts.SetCursor(c);
	}
}

void ToolEditor::LoadLast() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	p.Zero();
	
	p.pkg_cursor = app.last_pkg;
	p.node_cursor = app.last_node;
	
	for (Entity& a : db.entities) {
		
		if (a.file_title == app.last_entity) {
			p.entity = &a;
			for (Snapshot& r : a.snaps) {
				if (r.file_title == app.last_snapshot) {
					p.release = &r;
					for (Component& s : r.components) {
						if (s.file_title == app.last_component) {
							p.component = &s;
							break;
						}
					}
					break;
				}
			}
			for (Script& s : a.scripts) {
				if (s.file_title == app.last_script) {
					p.script = &s;
					break;
				}
			}
			break;
		}
	}
	
	MetaDatabase& mdb = MetaDatabase::Single();
	MetaPtrs& mp = MetaPtrs::Single();
	for(int i = 0; i < mdb.owners.GetCount(); i++) {
		Owner& o = mdb.owners[i];
		if (o.name == app.last_owner) {
			mp.owner = &o;
			for(int j = 0; j < o.profiles.GetCount(); j++) {
				Profile& p = o.profiles[j];
				if (p.name == app.last_profile) {
					mp.profile = &p;
					break;
				}
			}
			break;
		}
	}
}

void ToolEditor::ViewPageGroup() {
	if (page_group >= page_group_list.GetCount())
		page_group = page_group_list.GetCount()-1;
	if (page_group < 0)
		return;
	
	ToolEditorBase::ViewPageGroup();
	
}

void ToolEditor::Data() {
	DataMeta();
}

void ToolEditor::OnDataSnapshot() {
	MetaPtrs& mp = MetaPtrs::Single();
	EditorPtrs& p = GetPointers();
	if (!mp.profile) {
		p.entity = 0;
		p.release = 0;
		p.component = 0;
		DataPage();
		return;
	}
	
	TextDatabase& db = GetDatabase();
	Entity& e = db.GetAddEntity(*mp.profile);
	
	
	// Song part of the artist
	p.entity = &e;
	Entity& a = *p.entity;
	
	for(int i = 0; i < a.snaps.GetCount(); i++) {
		Snapshot& r = a.snaps[i];
		snaps.Set(i, 0, r.title);
		snaps.Set(i, 1, r.date);
	}
	INHIBIT_ACTION(snaps);
	snaps.SetCount(a.snaps.GetCount());
	
	int cursor = max(0, p.GetActiveSnapshotIndex());
	if (cursor >= 0 && cursor < snaps.GetCount())
		snaps.SetCursor(cursor);
	
	
	// Script part of the artist
	{
		int focus_lyr = p.GetActiveScriptIndex();
		int row = 0, focus_row = -1;
		for(int k = 0; k < a.scripts.GetCount(); k++) {
			Script& sc = a.scripts[k];
			scripts.Set(row, "IDX", k);
			scripts.Set(row, 0, sc.GetAnyTitle());
			if (k == focus_lyr)
				focus_row = row;
			row++;
		}
		INHIBIT_CURSOR(scripts);
		scripts.SetCount(row);
		int cursor = max(0, focus_row);
		if (cursor >= 0 && cursor < scripts.GetCount())
			scripts.SetCursor(cursor);
	}

	DataSnapshot();
	DataScript();
}

void ToolEditor::DataSnapshot() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	if (!snaps.IsCursor() || !p.entity) {
		p.release = 0;
		p.component = 0;
		DataPage();
		return;
	}
	
	p.release = &p.entity->snaps[snaps.GetCursor()];
	Entity& a = *p.entity;
	Snapshot& r = *p.release;
	
	for(int i = 0; i < r.components.GetCount(); i++) {
		Component& s = r.components[i];
		components.Set(i, 0, s.GetAnyTitle(a));
	}
	INHIBIT_ACTION(components);
	components.SetCount(r.components.GetCount());
	
	int cursor = max(0, p.GetActiveComponentIndex());
	if (cursor >= 0 && cursor < components.GetCount())
		components.SetCursor(cursor);
	
	DataComponent();
}

void ToolEditor::DataComponent() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	if (!components.IsCursor() || !p.entity || !p.release) {
		p.component = 0;
		DataPage();
		return;
	}
	
	p.component = &p.release->components[components.GetCursor()];
	Entity& a = *p.entity;
	Snapshot& r = *p.release;
	Component& s = *p.component;
	
	
	/*
	for(int i = 0; i < s.parts.GetCount(); i++) {
		String k;
		int c = 0;
		Color clr = White();
		StaticPart& p = s.parts[i];
		k = p.name;
		clr = GetComponentPartPaperColor(p.type);
		c = p.rhymes.GetCount();
		parts.Set(i, 0, AttrText(k).NormalPaper(clr));
		parts.Set(i, 1, c);
	}
	INHIBIT_ACTION(parts);
	parts.SetCount(s.parts.GetCount());
	
	int cursor = 0;
	if (cursor >= 0 && cursor < parts.GetCount() && !parts.IsCursor())
		parts.SetCursor(cursor);*/
	
	DataPage();
}

void ToolEditor::DataScript() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	if (!scripts.IsCursor()) {
		p.script = 0;
		DataPage();
		return;
	}
	
	Entity& e = *p.entity;
	p.script = &e.scripts[scripts.Get("IDX")];
	
	
	DataPage();
}

void ToolEditor::SnapshotMenu(Bar& bar) {
	bar.Add(t_("Add Snapshot"), THISBACK(AddSnapshot));
	
	if (snaps.IsCursor()) {
		bar.Add(t_("Rename Snapshot"), THISBACK(RenameSnapshot));
		bar.Add(t_("Delete Snapshot"), THISBACK(RemoveSnapshot));
	}
}

void ToolEditor::SongMenu(Bar& bar) {
	bar.Add(t_("Add Song"), THISBACK(AddSong));
	
	if (components.IsCursor()) {
		bar.Add(t_("Rename Song"), THISBACK(RenameSong));
		bar.Add(t_("Delete Song"), THISBACK(RemoveSong));
	}
}

void ToolEditor::ScriptMenu(Bar& bar) {
	bar.Add(t_("Add Script"), THISBACK(AddScript));
	
	if (scripts.IsCursor()) {
		bar.Add(t_("Delete Script"), THISBACK(RemoveScript));
	}
}

void ToolEditor::AddSnapshot() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	MetaPtrs& mp = MetaPtrs::Single();
	if (!p.entity && mp.profile)
		p.entity = &GetDatabase().GetAddEntity(*mp.profile);
	if (!p.entity)
		return;
	Entity& a = *p.entity;
	
	String title;
	bool b = EditTextNotNull(
		title,
		t_("Add Snapshot"),
		t_("Snapshot's title"),
		0
	);
	if (!b) return;
	
	int rel_i = -1;
	for(int i = 0; i < a.snaps.GetCount(); i++) {
		Snapshot& r = a.snaps[i];
		if (r.title == title) {
			rel_i = i;
			break;
		}
	}
	if (rel_i >= 0) {
		PromptOK(DeQtf(t_("Snapshot exist already")));
		return;
	}
	
	Snapshot& r = a.snaps.Add();
	r.file_title = MakeTitle(title);
	r.title = title;
	p.release = &r;
	
	OnDataSnapshot();
}

void ToolEditor::RenameSnapshot() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	if (!p.release)
		return;
	
	String title;
	bool b = EditTextNotNull(
		title,
		t_("Rename Snapshot"),
		t_("Snapshot's title"),
		0
	);
	if (!b) return;
	
	p.release->title = title;
	
	OnDataSnapshot();
}

void ToolEditor::RemoveSnapshot() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	if (!p.entity || !p.release)
		return;
	int idx = p.GetActiveSnapshotIndex();
	if (idx < 0) return;
	p.entity->snaps.Remove(idx);
	OnDataSnapshot();
}

void ToolEditor::AddSong() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	if (!p.entity)
		return;
	Entity& a = *p.entity;
	Snapshot& r = *p.release;
	
	String title;
	bool b = EditTextNotNull(
		title,
		t_("Add Song"),
		t_("Song's title"),
		0
	);
	if (!b) return;
	
	String file_title = MakeTitle(title);
	
	int rel_i = -1;
	for(int i = 0; i < r.components.GetCount(); i++) {
		Component& s = r.components[i];
		if (s.file_title == file_title) {
			rel_i = i;
			break;
		}
	}
	if (rel_i >= 0) {
		PromptOK(DeQtf(t_("Song exist already")));
		return;
	}
	
	Component& s = r.components.Add();
	s.file_title = file_title;
	p.component = &s;
	
	OnDataSnapshot();
}

void ToolEditor::RenameSong() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	if (!p.component)
		return;
	
	String title;
	bool b = EditTextNotNull(
		title,
		t_("Rename Song"),
		t_("Song's title"),
		0
	);
	if (!b) return;
	
	
	TODO //p.component->english_title = title.ToString();
	
	DataSnapshot();
}

void ToolEditor::RemoveSong() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	if (!p.component || !p.release)
		return;
	int idx = p.GetActiveComponentIndex();
	if (idx < 0) return;
	p.release->components.Remove(idx);
	p.component = 0;
	DataSnapshot();
}

void ToolEditor::AddScript() {
	TextDatabase& db = GetDatabase();
	MetaPtrs& mp = MetaPtrs::Single();
	EditorPtrs& p = GetPointers();
	if (!p.entity)
		return;
	
	String title;
	for(int i = 0; i < 8; i++) {
		title.Cat('a' + Random('z' - 'a' + 1));
	}
	
	Script& l = p.entity->scripts.Add();
	l.file_title = MakeTitle(title);
	l.typeclass = 0;
	l.content = 0;
	p.script = &l;
	
	
	if (mp.owner)
		l.copyright = mp.owner->name;
	
	//l.user_structure = GetDefaultScriptStructureString();
	
	Data();
}

void ToolEditor::RemoveScript() {
	
}

TextDatabase& ToolEditor::GetDatabase() {
	return MetaDatabase::Single().db;
}

EditorPtrs& ToolEditor::GetPointers() {
	return MetaPtrs::Single().db;
}


END_TEXTLIB_NAMESPACE

