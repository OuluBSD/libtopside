#include "Editor.h"


NAMESPACE_TOPSIDE_BEGIN


Editor::Editor() {
	editortabsize = 4;
	indent_spaces = 0;
	indent_amount = 4;
	show_tabs = 0;
	no_parenthesis_indent = 0;
	hilite_scope = 2;
	hilite_bracket = 1;
	hilite_ifdef = 1;
	barline = 1;
	hilite_if_endif = 1;
	thousands_separator = 1;
	hline = 1;
	line_numbers = 1;
	auto_enclose = 1;
	mark_lines = 0;
	bordercolumn = 1;
	bordercolor = 1;
	persistent_find_replace = 1;
	find_replace_restore_pos = 0;
	font_height = 15;
	
	
	Title("Code Editor");
	Sizeable().MaximizeBox();
	Maximize();
	
	Add(hsplit.Horz().SizePos());
	hsplit << vsplit.Vert() << editor_bottom;
	hsplit.SetPos(1700);
	
	editor_bottom.Vert();
	editor_bottom << hsplit_code.Horz() << bottom;
	editor_bottom.SetPos(8000);
	bottom.SetFrame(btabs);
	bottom.Add(console.SizePos().SetFrame(NullFrame()));
	bottom.Add(error.SizePos().SetFrame(NullFrame()));
	bottom.Add(ffound.SizePos().SetFrame(NullFrame()));
	bottom.Add(calc.SizePos().SetFrame(NullFrame()));
	btabs <<= THISBACK(SyncBottom);
	BTabs();
	SwapBottom();
	
	SetupError(error, "Message");
	error.AddIndex("NOTES");
	error.ColumnWidths("207 41 834");
	error.WhenBar = THISBACK(ErrorMenu);
	
	SetupError(ffound, "Source");
	ffound.ColumnWidths("207 41 834");
	ffound.ColumnAt(0).SetDisplay(Single<FoundFileDisplay>());
	ffound.ColumnAt(2).SetDisplay(Single<FoundDisplay>());
	ffound.WhenBar = THISBACK(FFoundMenu);
	
	error.WhenSel = THISBACK(SelError);
	error.WhenLeftClick = THISBACK(ShowError);
	ffound.WhenSel = ffound.WhenLeftClick = THISBACK(ShowFound);
	
	ff.WhenSearch = THISBACK(DoFindInFiles);
	
	
	
	vsplit << projects << files;
	projects.Columns(2);
	files.Columns(2);
	projects.WhenAction << THISBACK(DataProjectFiles);
	files.WhenLeftClick << THISBACK(OpenSelectedFile);
	
	hsplit_code << left << left_tree_split;//right;
	InitEditor(left);
	InitEditor(right);
	
	left_tree_split.Vert();
	left_tree_split << left_object_tree << left_node_tree;
	
	left_object_tree.SetFont(Monospace(12));
	left_node_tree.SetFont(Monospace(12));
	
	PostCallback(THISBACK(Init));
	PostCallback(THISBACK(Data));
	PostCallback(THISBACK(Compile));
}

Editor::~Editor() {
	SaveFile();
}

void Editor::SetProject(UppProject& p, UppAssemblyData& ad) {
	this->ad = &ad;
	prj = &p;
	prj->GetRecursiveUses(rec_uses, ad);
}

void Editor::Data() {
	int i = 0;
	if (projects.IsCursor()) i = projects.GetCursor();
	projects.Clear();
	for(int i = 0; i < rec_uses.GetCount(); i++)
		projects.Add(rec_uses[i]);
	if (i >= 0) projects.SetCursor(i);
	
	DataProjectFiles();
}

void Editor::DataProjectFiles() {
	int i = 0;
	i = projects.GetCursor();
	UppProject& prj = ad->GetProject(rec_uses[i]);
	
	i = 0;
	if (files.IsCursor()) i = files.GetCursor();
	files.Clear();
	for(int i = 0; i < prj.GetFileCount(); i++) {
		String file = prj.GetFile(i);
		Image img = NativePathIcon(file, false);
		files.Add(file, img);
	}
	if (i >= 0) files.SetCursor(i);
}

void Editor::OpenSelectedFile() {
	int i = 0;
	i = projects.GetCursor();
	UppProject& prj = ad->GetProject(rec_uses[i]);
	String dir = GetFileDirectory(prj.GetFilePath());
	
	i = 0;
	if (files.IsCursor()) i = files.GetCursor();
	
	if (i >= 0 && i < prj.GetFileCount()) {
		String file = prj.GetFile(i);
		String path = AppendFileName(dir, file);
		SetTabFile(right.HasFocus(), path, -1, -1);
	}
	
}

void Editor::SetTabFile(int i, String path, int line, int col) {
	String& active_path = i ? right_path : left_path;
	CodeEditor& edit = i ? right : left;
	
	if (active_path != path) {
		if (active_path.GetCount()) {
			String content = edit.GetData();
			FileOut fout(active_path);
			fout << content;
		}
		String content = LoadFile(path);
		active_path = path;
		edit.SetData(content);
	}
	if (line >= 0)
		edit.SetCursor(edit.GetPos(line, col));
}

void Editor::Init() {
	
}

void Editor::InitEditor(CodeEditor& codeedit) {
	String highlight = "cpp";
	
	codeedit.DefaultHlStyles();
	codeedit.Highlight(highlight);
	
	codeedit.TabSize(editortabsize);
	codeedit.IndentSpaces(indent_spaces);
	codeedit.IndentAmount(indent_amount);
	codeedit.ShowTabs(show_tabs);
	codeedit.ShowLineEndings(show_tabs);
	codeedit.NoParenthesisIndent(no_parenthesis_indent);
	codeedit.HiliteScope(hilite_scope);
	codeedit.HiliteBracket(hilite_bracket);
	codeedit.HiliteIfDef(hilite_ifdef);
	codeedit.BarLine(barline);
	codeedit.HiliteIfEndif(hilite_if_endif);
	codeedit.ThousandsSeparator(thousands_separator);
	codeedit.ShowCurrentLine(hline ? HighlightSetup::GetHlStyle(HighlightSetup::SHOW_LINE).color : (Color)Null);
	codeedit.LineNumbers(line_numbers);
	codeedit.AutoEnclose(auto_enclose);
	codeedit.MarkLines(mark_lines);
	//codeedit.BorderColumn(bordercolumn, bordercolor);
	codeedit.PersistentFindReplace(persistent_find_replace);
	codeedit.FindReplaceRestorePos(find_replace_restore_pos);
	
	codeedit.SetFont(Monospace(font_height));
	
	//codeedit.WhenLeftDown = THISBACK(WhenTextCursor);
	//codeedit.WhenAnyKey = THISBACK(WhenTextCursor);
	/*codeedit.WhenAction = THISBACK(WhenTextCursor);
	codeedit.WhenState = THISBACK(WhenTextCursor);
	codeedit.WhenUpdate = THISBACK(WhenTextCursor);
	codeedit.WhenAnnotationMove = THISBACK(WhenTextCursor);*/
	
	//codeedit.WhenCtrlClick = THISBACK(CtrlClick);
	//codeedit.WhenTip = THISBACK(EditorTip);
}

void Editor::Compile() {
	if (state != IDLE) return;
	
}

void Editor::ProcessCompiling() {
	{
		GuiLock __;
		error.Clear();
		btabs.SetCursor(2);
		SyncBottom();
	}
	SaveFile();
	
	
	
}

void Editor::OnMessage(ProcMsg e) {
	lock.Enter();
	errors.Add(e);
	lock.Leave();
	
	GuiLock __;
	SyncBottom();
	
	Color bg = White();
	if (e.severity == PROCMSG_ERROR)			bg = Color(255, 182, 176);
	else if (e.severity == PROCMSG_WARNING)		bg = Color(255, 255, 180);
	
	ErrorInfo ei;
	ei.file = e.file;
	ei.lineno = e.line;
	ei.linepos = e.col;
	ei.kind = e.severity;
	ei.message = e.msg;
	
	error.Add(e.file, e.line, AttrText(e.GetSeverityString() + ": " + e.msg).NormalPaper(bg), RawToValue(ei));
}

void Editor::FocusLine(ArrayCtrl* list) {
	
}

void Editor::NewFile() {
	
}

void Editor::SaveFile() {
	for(int i = 0; i < 2; i++) {
		String& active_path = i ? right_path : left_path;
		CodeEditor& edit = i ? right : left;
		
		if (active_path.GetCount()) {
			String content = edit.GetData();
			FileOut fout(active_path);
			fout << content;
		}
	}
}

void Editor::OpenLog() {
	
}

void Editor::Execute() {
	state = COMPILING;
	ProcessCompiling();
	
}

void Editor::DebugFile() {
	state = COMPILING;
	ProcessCompiling();
	
}

void Editor::StopDebug() {
	
}

void Editor::Continue() {
	
}

bool Editor::IsRunning() {
	return state == DEBUGGING || state == RUNNING;
}

bool Editor::IsPaused() {
	return state == PAUSED;
}

void Editor::FindInFiles(bool b) {
	
}


bool Editor::HotKey(dword key) {
	if (key == (K_CTRL | K_N)) {PostCallback(THISBACK(NewFile)); return true;}
	if (key == (K_CTRL | K_S)) {PostCallback(THISBACK(SaveFile)); return true;}
	if (key == K_ESCAPE) {SwapBottom(); return true;}
	if (key == K_F5) {
		
		if (!IsRunning()) {
			DebugFile(); return true;
		}
		else if (IsPaused()) {
			Continue(); return true;
		}
		else {
			StopDebug(); return true;
		}
	}
	if (key == (K_CTRL | K_F5) ) {Execute(); return true;}
	if (key == (K_CTRL | K_SHIFT | K_F)) {FindInFiles(0); return true;}
	if (key == (K_CTRL | K_SHIFT | K_R)) {FindInFiles(1); return true;}
	//if (key == (K_CTRL | K_SHIFT | K_W)) {CloseTab(); return true;}
	//if (key == (K_CTRL | K_ALT   | K_W)) {CloseAllTabs(); return true;}
	//if (key == (K_CTRL | K_ALT | K_LEFT)) {PreviousTab(); return true;}
	//if (key == (K_CTRL | K_ALT | K_RIGHT)) {NextTab(); return true;}
	if (key == (K_ALT | K_L)) {OpenLog(); return true;}
	/*if (key == K_F2) {SwitchPreviewMode(); return true;}
	if (key == (K_CTRL | K_1)) {SetPreviewMode(PREV_MAIN);   return true;}
	if (key == (K_CTRL | K_2)) {SetPreviewMode(PREV_HSPLIT); return true;}
	if (key == (K_CTRL | K_3)) {SetPreviewMode(PREV_TOPWND); return true;}
	if (key == (K_CTRL | K_4)) {SetPreviewMode(PREV_HIDDEN); return true;}
	if (key == (K_CTRL | K_J)) {path.SetEdit(); return true;}*/
	return false;
}


NAMESPACE_TOPSIDE_END
