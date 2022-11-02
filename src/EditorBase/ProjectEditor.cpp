#include "EditorBase.h"

NAMESPACE_TOPSIDE_BEGIN


ProjectEditorExt::ProjectEditorExt() {
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
	
	
	vsplit.Vert() << projects << files;
	
	projects.Columns(2);
	files.Columns(2);
	projects.WhenAction << THISBACK(DataProjectFiles);
	files.WhenLeftClick << THISBACK(OpenSelectedFile);
	
	
	InitEditor(left);
	InitEditor(right);
	
	
	left_tree_split.Vert();
	left_tree_split << left_object_tree << left_node_tree;
	
	left_object_tree.SetFont(Monospace(12));
	left_node_tree.SetFont(Monospace(12));
	
	
	prj_icon = RescaleBicubic(StreamRaster::LoadFileAny(ShareDirFile("imgs/icons/package.png")), Size(16,16));
	
}

ProjectEditorExt::~ProjectEditorExt() {
	SaveFile();
}

void ProjectEditorExt::Activate() {
	base->SetCtrls(vsplit, left, left_tree_split);
	
	PostCallback(THISBACK(Init));
	PostCallback(THISBACK(Data));
	PostCallback(THISBACK(Compile));
}

void ProjectEditorExt::Deactivate() {
	
}

bool ProjectEditorExt::HotKey(dword key) {
	if (key == (K_CTRL | K_N)) {PostCallback(THISBACK(NewFile)); return true;}
	if (key == (K_CTRL | K_S)) {PostCallback(THISBACK(SaveFile)); return true;}
	if (key == (K_ALT | K_L)) {OpenLog(); return true;}
	
	return false;
}

void ProjectEditorExt::Data() {
	const auto& rec_uses = base->rec_uses;
	
	
	int i = 0;
	if (projects.IsCursor()) i = projects.GetCursor();
	projects.Clear();
	for(int i = 0; i < rec_uses.GetCount(); i++)
		projects.Add(rec_uses[i], prj_icon);
	if (i >= 0) projects.SetCursor(i);
	
	DataProjectFiles();
}

void ProjectEditorExt::DataProjectFiles() {
	const auto& rec_uses = base->rec_uses;
	const auto& asd = base->asd;
	
	int i = 0;
	i = projects.GetCursor();
	if (i < 0)
		return;
	UppProject& prj = asd->GetProject(rec_uses[i]);
	
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

void ProjectEditorExt::OpenSelectedFile() {
	const auto& rec_uses = base->rec_uses;
	const auto& asd = base->asd;
	
	int i = 0;
	i = projects.GetCursor();
	if (i < 0)
		return;
	UppProject& prj = asd->GetProject(rec_uses[i]);
	String dir = GetFileDirectory(prj.GetFilePath());
	
	i = 0;
	if (files.IsCursor()) i = files.GetCursor();
	
	if (i >= 0 && i < prj.GetFileCount()) {
		String file = prj.GetFile(i);
		String path = AppendFileName(dir, file);
		SetTabFile(right.HasFocus(), path, -1, -1);
	}
	
}

void ProjectEditorExt::SetTabFile(int i, String path, int line, int col) {
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

void ProjectEditorExt::Init() {
	
}

void ProjectEditorExt::InitEditor(CodeEditor& codeedit) {
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

void ProjectEditorExt::Compile() {
	if (base->state != EditorBase::IDLE) return;
	
}

String ProjectEditorExt::JoinFiles() {
	const auto& rec_uses = base->rec_uses;
	const auto& asd = base->asd;
	String out;
	
	for(int i = 0; i < rec_uses.GetCount(); i++) {
		UppProject& upp = asd->GetProject(rec_uses[i]);
		String dir = GetFileDirectory(upp.GetFilePath());
		
		for(int j = 0; j < upp.GetFileCount(); j++) {
			String file = AppendFileName(dir, upp.GetFile(j));
			String ext = GetFileExt(file);
			if (ext == ".h") {
				String file_content = LoadFile(file);
				out << "#line 0 \"" << file << "\"\n";
				out << file_content << "\n";
			}
		}
		
		for(int j = 0; j < upp.GetFileCount(); j++) {
			String file = AppendFileName(dir, upp.GetFile(j));
			String ext = GetFileExt(file);
			if (ext == ".cpp") {
				String file_content = LoadFile(file);
				out << "#line 0 \"" << file << "\"\n";
				out << file_content << "\n";
			}
		}
	}
	
	return out;
}

void ProjectEditorExt::NewFile() {
	
}

void ProjectEditorExt::SaveFile() {
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

void ProjectEditorExt::OpenLog() {
	
}

void ProjectEditorExt::GoToError(const ErrorInfo& f) {
	if(IsNull(f.file))
		return;
	
	SetTabFile(right.HasFocus(), f.file, f.lineno-1, f.linepos-1);
}


NAMESPACE_TOPSIDE_END
