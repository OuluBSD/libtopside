#include "PlayEditor.h"

NAMESPACE_TOPSIDE_BEGIN


PlayEditor::PlayEditor() {
	Title("PlayEditor");
	MaximizeBox().MinimizeBox().Sizeable();
	
	CtrlLayout(scriptconf);
	CtrlLayout(sectconf);
	CtrlLayout(lineconf);
	CtrlLayout(st_edit);
	
	Add(part_split.SizePos());
	
	part_split.Horz() << partlist << tabs;
	part_split.SetPos(1500);
	
	partlist.AddColumn("Part");
	partlist.AddColumn("Section");
	partlist.AddColumn("Title");
	partlist.ColumnWidths("1 1 4");
	
	tabs.Add(scriptconf.SizePos(),		"Script");
	tabs.Add(sectconf.SizePos(),		"Section");
	tabs.Add(dialog_split.SizePos(),	"Dialogue");
	tabs.Add(st_split.SizePos(),		"Subtitles");
	tabs.Add(rend_split.SizePos(),		"Renderer");
	
	
	// Dialogue edit
	dialog_split.Vert() << dialog << lineconf;
	dialog_split.SetPos(6600);
	dialog.AddColumn("Actor");
	dialog.AddColumn("Line");
	dialog.ColumnWidths("1 6");
	
	// Subtitles
	st_split.Horz() << st_dialog << st_edit;
	st_split.SetPos(2500);
	st_dialog.AddColumn("Actor");
	st_dialog.AddColumn("Line");
	st_dialog.ColumnWidths("1 3");
	
	// Renderer
	rend_split.Horz() << rend_dialog << rend_ctrl;
	rend_split.SetPos(2500);
	rend_dialog.AddColumn("Actor");
	rend_dialog.AddColumn("Line");
	rend_dialog.ColumnWidths("1 3");
	
	
	PostCallback(THISBACK(Data));
	
	partlist <<= THISBACK(Data);
	tabs <<= THISBACK(TabData);
}

void PlayEditor::Data() {
	int i = 0;
	for (PlayPart& p : script.parts) {
		for (PlaySection& s : p.sections) {
			partlist.Set(i, 0, p.idx);
			partlist.Set(i, 1, s.idx);
			partlist.Set(i, 2, s.title.ToString());
			i++;
		}
	}
	partlist.SetCount(i);
	
	if (i && !partlist.IsCursor())
		partlist.SetCursor(0);
	
	int list_i = partlist.GetCursor();
	int part_i = partlist.Get(list_i, 0);
	int sect_i = partlist.Get(list_i, 1);
	
	ActivateSection(part_i, sect_i);
	
	TabData();
}

bool PlayEditor::ActivateSection(int part_i, int sect_i) {
	if (part_i >= 0 && part_i < script.parts.GetCount()) {
		PlayPart& p = script.parts[part_i];
		if (sect_i >= 0 && sect_i < p.sections.GetCount()) {
			PlaySection& s = p.sections[sect_i];
			if (active_sect != &s) {
				active_part = &p;
				active_sect = &s;
				return true;
			}
		}
	}
	return false;
}

void PlayEditor::TabData() {
	ASSERT(active_part && active_sect);
	
	int tab = tabs.Get();
	
	if (tab == TAB_METASCRIPT) {
		scriptconf.title.SetData(script.title.GetData());
		scriptconf.description.SetData(script.description.GetData());
		scriptconf.disclaimer.SetData(script.disclaimer.GetData());
		scriptconf.author.SetData(script.author.GetData());
	}
	else if (tab == TAB_METASECTION) {
		if (active_sect) {
			sectconf.title.SetData(active_sect->title.GetData());
		}
	}
	else if (tab == TAB_DIALOG) {
		int c = active_sect->dialog.lines.GetCount();
		for(int i = 0; i < c; i++) {
			PlayLine& line = active_sect->dialog.lines[i];
			
			String sents;
			for (PlaySentence& s : line.sents) {
				if (!sents.IsEmpty())
					sents.Cat(' ');
				sents << s.ToString();
			}
			
			Color clr = RandomColor(256-64, 64);
			dialog.Set(i, 0, AttrText().Text(line.id.ToString()).NormalPaper(clr).SetFont(Monospace()));
			dialog.Set(i, 1, AttrText().Text(sents).NormalPaper(clr).SetFont(Monospace()));
		}
		dialog.SetCount(c);
		
		if (dialog.GetCount() && !dialog.IsCursor())
			dialog.SetCursor(0);
		
		if (dialog.IsCursor()) {
			int cursor = dialog.GetCursor();
			
			PlayLine& line = active_sect->dialog.lines[cursor];
			
			String sents;
			for (PlaySentence& s : line.sents) {
				if (!sents.IsEmpty())
					sents.Cat('\n');
				sents << s.ToString();
			}
			
			lineconf.line.SetData(sents);
		}
	}
	else if (tab == TAB_SUBTITLES) {
		int c = script.subtitles.GetCount();
		for(int i = 0; i < c; i++) {
			const PlayScript::Subtitle& st = script.subtitles[i];
			if (!st.line) continue;
			String actor = st.line->id.ToString();
			
			Color clr = RandomColor(256-64, 64);
			st_dialog.Set(i, 0, AttrText().Text(actor.ToString()).NormalPaper(clr).SetFont(Monospace()));
			st_dialog.Set(i, 1, AttrText().Text(st.str).NormalPaper(clr).SetFont(Monospace()));
		}
		st_dialog.SetCount(c);
	}
	else if (tab == TAB_RENDER) {
		int c = active_sect->dialog.lines.GetCount();
		for(int i = 0; i < c; i++) {
			PlayLine& line = active_sect->dialog.lines[i];
			
			String sents;
			for (PlaySentence& s : line.sents) {
				if (!sents.IsEmpty())
					sents.Cat(' ');
				sents << s.ToString();
			}
			
			Color clr = RandomColor(256-64, 64);
			rend_dialog.Set(i, 0, AttrText().Text(line.id.ToString()).NormalPaper(clr).SetFont(Monospace()));
			rend_dialog.Set(i, 1, AttrText().Text(sents).NormalPaper(clr).SetFont(Monospace()));
		}
		rend_dialog.SetCount(c);
	}
}

bool PlayEditor::LoadFile(String path) {
	return Load(UPP::LoadFile(path), path);
}

bool PlayEditor::Load(String content, String path) {
	
	PlayTokenizer t;
	t.WhenMessage << THISBACK(OnMessage);
	if (!t.Process(content, path)) {
		
		return false;
	}
	//t.Dump();
	
	PlayParser p(script);
	p.WhenMessage << THISBACK(OnMessage);
	p.Process(t.GetTokens());
	
	//p.GetResult().Dump();
	LOG(script.ToScript());
	
	script.MakeSubtitles();
	
	return true;
}

void PlayEditor::OnMessage(const ProcMsg& p) {
	
	LOG(p.ToString());
	
}



NAMESPACE_TOPSIDE_END
