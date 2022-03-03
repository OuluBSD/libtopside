#include "PlayEditor.h"

NAMESPACE_TOPSIDE_BEGIN


PlayEditor::PlayEditor() : renderer(script), exporter(script) {
	Title("PlayEditor");
	MaximizeBox().MinimizeBox().Sizeable();
	
	AddFrame(menu);
	menu.Set(THISBACK(MainMenu));
	
	CtrlLayout(scriptconf);
	CtrlLayout(sectconf);
	CtrlLayout(lineconf);
	CtrlLayout(st_edit);
	CtrlLayout(rend_ctrl);
	CtrlLayout(exporting);
	
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
	tabs.Add(exporting.SizePos(),		"Exporting");
	
	
	// Meta script
	scriptconf.actors.AddColumn("Id");
	scriptconf.actors.AddColumn("Description");
	scriptconf.actors.ColumnWidths("2 3");
	
	// Dialogue edit
	dialog_split.Vert() << dialog << lineconf;
	dialog_split.SetPos(6600);
	dialog.AddColumn("Actor");
	dialog.AddColumn("Line");
	dialog.ColumnWidths("1 6");
	
	// Subtitles
	st_split.Horz() << st_dialog << st_edit;
	st_split.SetPos(3000);
	st_dialog.AddColumn("Actor");
	st_dialog.AddColumn("Line");
	st_dialog.AddColumn("Time");
	st_dialog.ColumnWidths("1 3 1");
	st_dialog <<= THISBACK(SubtitleData);
	st_edit.tap.WantFocus();
	st_edit.tap <<= THISBACK(SubtitleTap);
	st_edit.stop <<= THISBACK(SubtitleStop);
	
	// Renderer
	rend_split.Horz() << rend_dialog << rend_ctrl;
	rend_split.SetPos(2500);
	rend_dialog.AddColumn("Actor");
	rend_dialog.AddColumn("Line");
	rend_dialog.ColumnWidths("1 3");
	rend_ctrl.time.MinMax(0,1);
	rend_ctrl.time.SetData(0);
	rend_ctrl.time <<= THISBACK(OnTimeSlider);
	rend_ctrl.time.Step(500); // milliseconds
	rend_ctrl.play <<= THISBACK(ToggleRenderPlay);
	
	// Export
	String export_notes =	"ffmpeg -i ../videotrack.mp4 -vf fps=25 \%05d.jpg\n"
							"ffmpeg -i ../videotrack.mp4 -vf fps=25 -qscale:v 2 \%05d.jpg\n"
							"ffmpeg -i ../videotrack.mp4 -vf fps=25 -qmin 1 -qscale:v 1 \%05d.jpg\n"
							"Remove all images before the first frame.\n"
							"\n"
							"ffmpeg -framerate 25 -i %05d.jpg -i ../audiotrack.wav -c:a aac -c:v nvenc_hevc -r 25 ../exported.mp4\n"
							"\n"
							"ffmpeg -framerate 25 -i %05d.jpg -c:v nvenc_hevc -r 25 ../exported-video.mp4\n"
							"ffmpeg -i exported-video.mp4 -i audiotrack.wav -c:v copy -c:a aac -map 0:v:0 -map 1:a:0 exported.mp4\n"
							"\n"
							"cat mylist.txt\n"
							"\tfile '/path/to/file1'\n"
							"\tfile '/path/to/file2'\n"
							"\tfile '/path/to/file3'\n"
							"\n"
							"ffmpeg -f concat -safe 0 -i mylist.txt -c copy output.mp4\n"
							"\n"
							"ffmpeg -i ../audiotrack.wav -f segment -segment_time 10 audio_\%04d.wav\n";
							;
	exporting.hints.SetData(export_notes);
	exporting.start <<= THISBACK(ToggleExporting);
	exporting.prog.Set(0,1);
	exporting.res_h.SetData(1080);
	exporter.WhenEnd << THISBACK(PostOnExportingStop);
	
	PostCallback(THISBACK(Data));
	
	partlist <<= THISBACK(Data);
	tabs <<= THISBACK(TabData);
}

void PlayEditor::MainMenu(Bar& bar) {
	
	bar.Sub("File", [this](Bar& bar) {
		bar.Add("Save file", THISBACK(SaveFile)).Key(K_CTRL_S);
	});
	
}

void PlayEditor::SaveFile() {
	if (script.filepath.IsEmpty())
		return;
	
	String output = "\n\n" + script.ToScript();
	
	FileOut fout(script.filepath);
	if (!fout.IsOpen()) {
		PromptOK("Could not open file for saving");
		return;
	}
	
	fout << output;
	fout.Close();
	
	if (fout.IsError())
		PromptOK("Unknown error while saving the script file");
	
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
	if (list_i < 0) return;
	
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
	
	if (is_subtitle_recording && tab != TAB_SUBTITLES)
		SubtitleStop();
	
	if (tab == TAB_METASCRIPT) {
		scriptconf.title.SetData(script.title.GetData());
		scriptconf.description.SetData(script.description.GetData());
		scriptconf.disclaimer.SetData(script.disclaimer.GetData());
		scriptconf.author.SetData(script.author.GetData());
		
		int c = script.actors.lines.GetCount();
		for(int i = 0; i < c; i++) {
			const PlayLine& pl = script.actors.lines[i];
			Value id = pl.id.name;
			Value str = pl.sents[0].GetData();
			scriptconf.actors.Set(i, 0, id);
			scriptconf.actors.Set(i, 1, str);
		}
		scriptconf.actors.SetCount(c);
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
			
			const PlayScript::Actor& a = script.GetActor(line);
			dialog.Set(i, 0, AttrText().Text(a.name).NormalPaper(a.normal_paper).SetFont(Monospace()));
			dialog.Set(i, 1, AttrText().Text(sents).NormalPaper(a.normal_paper).SetFont(Monospace()));
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
		script.MakeTempPlaySentenceTimes();
		renderer.Clear();
		
		int c = script.subtitles.GetCount();
		for(int i = 0; i < c; i++) {
			const PlayScript::Subtitle& st = script.subtitles[i];
			if (!st.line) continue;
			int t = st.time;
			
			const PlayScript::Actor& a = script.GetActor(*st.line);
			st_dialog.Set(i, 0, AttrText().Text(a.name.ToString()).NormalPaper(a.normal_paper).SetFont(Monospace()));
			st_dialog.Set(i, 1, AttrText().Text(st.str).NormalPaper(a.normal_paper).SetFont(Monospace()));
			st_dialog.Set(i, 2, t >= 0 ? Value(t / 1000) : Value());
		}
		st_dialog.SetCount(c);
		if (!c) return;
		
		SubtitleData();
	}
	else if (tab == TAB_RENDER) {
		script.MakeTempPlaySentenceTimes();
		renderer.Clear();
		
		int c = active_sect->dialog.lines.GetCount();
		for(int i = 0; i < c; i++) {
			PlayLine& line = active_sect->dialog.lines[i];
			
			String sents;
			for (PlaySentence& s : line.sents) {
				if (!sents.IsEmpty())
					sents.Cat(' ');
				sents << s.ToString();
			}
			
			const PlayScript::Actor& a = script.GetActor(line);
			rend_dialog.Set(i, 0, AttrText().Text(a.name).NormalPaper(a.normal_paper).SetFont(Monospace()));
			rend_dialog.Set(i, 1, AttrText().Text(sents).NormalPaper(a.normal_paper).SetFont(Monospace()));
		}
		rend_dialog.SetCount(c);
		
		int last_time = script.GetLastSubtitleTiming();
		if (last_time > 0)
			rend_ctrl.time.MinMax(0, last_time);
		
		OnTimeSlider();
	}
}

void PlayEditor::SubtitleData() {
	if (!st_dialog.IsCursor())
		st_dialog.SetCursor(0);
	
	if (!is_subtitle_recording) {
		int cursor = st_dialog.GetCursor();
		const PlayScript::Subtitle& st = script.subtitles[cursor];
		String st_str = st.str.ToString();
		st_edit.subtitle.SetLabel(st_str);
	}
}

bool PlayEditor::LoadFile(String path) {
	return Load(UPP::LoadFile(path), path);
}

bool PlayEditor::Load(String content, String path) {
	script.filepath = path;
	
	Vector<String> segments = Split(content, "\n<Extension:");
	content = segments[0];
	
	for(int i = 1; i < segments.GetCount(); i++)
		script.LoadExtension(segments[i]);
	
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
	
	script.MakeActors();
	script.MakeSubtitles();
	
	if (!script.CheckReferences()) {
		LOG("Reference checking failed");
		return false;
	}
	
	script.LoadImages();
	
	if (!script.CheckMusical()) {
		LOG("Musical check failed");
		return false;
	}
	
	return true;
}

void PlayEditor::OnMessage(const ProcMsg& p) {
	
	LOG(p.ToString());
	
}

void PlayEditor::SubtitleTap() {
	if (!is_subtitle_recording) {
		if (!st_dialog.IsCursor())
			return;
		
		if (st_edit.fill_hole.Get()) {
			PromptOK("Hole filling feature TODO");
			return;
		}
		
		int cursor = st_dialog.GetCursor();
		const PlayScript::Subtitle& st = script.subtitles[cursor];
		if (st.time >= 0) {
			subtitle_recording_offset = st.time;
			subtitle_recording_cursor = cursor+1;
			is_subtitle_recording = true;
			st_edit.tap.SetFocus();
			st_ts.Reset();
			
			SubtitleUpdate();
			st_tc.Set(-10, THISBACK(SubtitleIteration));
		}
	}
	else {
		PlayScript::Subtitle& st = script.subtitles[subtitle_recording_cursor];
		int time = st_ts.Seconds() * 1000 + subtitle_recording_offset;
		st.time = time;
		st_dialog.Set(subtitle_recording_cursor, 2, time / 1000);
		
		subtitle_recording_cursor++;
		SubtitleUpdate();
	}
}

void PlayEditor::SubtitleUpdate() {
	if (subtitle_recording_cursor >= script.subtitles.GetCount()) {
		SubtitleStop();
		st_edit.subtitle.SetLabel("");
		subtitle_recording_offset = 0;
	}
	else {
		const PlayScript::Subtitle& st = script.subtitles[subtitle_recording_cursor];
		st_edit.subtitle.SetLabel(st.str.ToString());
		st_dialog.SetCursor(subtitle_recording_cursor);
	}
}

void PlayEditor::SubtitleStop() {
	is_subtitle_recording = false;
	st_tc.Kill();
}

void PlayEditor::SubtitleIteration() {
	double elapsed = st_ts.Seconds() * 1000 + subtitle_recording_offset;
	int seconds = (int)(elapsed / 1000);
	int milliseconds = (int)elapsed % 1000;
	int minutes = seconds / 60;
	seconds = seconds % 60;
	int hours = minutes / 60;
	minutes = minutes % 60;
	String s = Format("%01d:%01d:%01d:%03d", hours, minutes, seconds, milliseconds);
	st_edit.time.SetLabel(s);
}

void PlayEditor::OnTimeSlider() {
	int time = rend_ctrl.time.GetData();
	if (time < 0) return;
	
	if (!is_render_play) {
		renderer.Seek(time);
		
		PlayRendererConfig cfg;
		ReadRendererConfig(cfg);
		Image img = renderer.Render(cfg);
		rend_ctrl.frame.SetImage(img);
	}
	else {
		play_begin_time = time;
		rend_ts.Reset();
	}
}

void PlayEditor::ToggleRenderPlay() {
	if (!is_render_play) {
		is_render_play = true;
		if (rend_ctrl.time.GetData() == rend_ctrl.time.GetMax())
			rend_ctrl.time.SetData(0);
		rend_ts.Reset();
		play_begin_time = rend_ctrl.time.GetData();
		rend_ctrl.play.SetLabel("Stop");
		rend_tc.Set(-1000/30, THISBACK(RenderFrameToPlayer));
	}
	else {
		rend_tc.Kill();
		is_render_play = false;
		rend_ctrl.play.SetLabel("Play");
	}
}

void PlayEditor::RenderFrameToPlayer() {
	int time = rend_ts.Seconds() * 1000 + play_begin_time;
	int max_time = rend_ctrl.time.GetMax();
	if (time >= max_time) {
		time = max_time;
		if (is_render_play)
			ToggleRenderPlay();
	}
	
	Event<> tmp_cb;
	Swap(tmp_cb, rend_ctrl.time.WhenAction);
	rend_ctrl.time.SetData(time);
	Swap(tmp_cb, rend_ctrl.time.WhenAction);
	
	renderer.Seek(time);
	
	PlayRendererConfig cfg;
	ReadRendererConfig(cfg);
	Image img = renderer.Render(cfg);
	rend_ctrl.frame.SetImage(img);
}

void PlayEditor::ReadRendererConfig(PlayRendererConfig& cfg) {
	cfg.render_bg = rend_ctrl.render_bg.Get();
	cfg.render_blur = rend_ctrl.render_blur.Get();
	cfg.render_text_bending = rend_ctrl.render_text_bending.Get();
	cfg.render_person = rend_ctrl.render_person.Get();
	cfg.render_notes = rend_ctrl.render_notes.Get();
	cfg.render_person_background = rend_ctrl.render_person_background.Get();
}

void PlayEditor::ToggleExporting() {
	if (!exporter.IsRunning()) {
		Size res;
		res.cy = exporting.res_h.GetData();
		res.cx = (1920.0 / 1080.0) * res.cy;
		exporting.start.SetLabel("Stop");
		script.MakeTempPlaySentenceTimes();
		exporter.SetFrameSize(res);
		exporter.SetLastBlockOnly(exporting.last_block.Get());
		exporter.SetTotalTime(script.GetTotalTime());
		exporter.Start();
		export_tc.Set(-100, THISBACK(OnExportingProgressUpdate));
	}
	else {
		exporter.Stop();
	}
}

void PlayEditor::OnExportingStop() {
	exporting.start.SetLabel("Start");
	export_tc.Kill();
	exporting.prog.Set(0,1);
}

void PlayEditor::OnExportingProgressUpdate() {
	int actual = exporter.GetActual();
	int total = exporter.GetTotal();
	exporting.prog.Set(actual, total);
}


NAMESPACE_TOPSIDE_END
