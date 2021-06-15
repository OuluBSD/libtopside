#include "Editor.h"


CodeEdit::CodeEdit() {
	
}

bool CodeEdit::Key(dword key, int count) {
	PostCallback(WhenAnyKey);
	return CodeEditor::Key(key, count);
}

String CodeEdit::GetVariable(int line, int column, int* offset) {
	String content = GetData(); // TODO: fix after U++... not efficient now
	
	int pos = GetPos(line-1) + column;
	const char* content_begin = content.Begin();
	const char* ch = content_begin + pos;
	const char* begin = ch;
	const char* end = content.End();
	int len = content.GetCount();
	begin--;
	while (begin > content_begin && (IsAlpha(*begin) || IsDigit(*begin) || *begin == '_') ) begin--;
	begin++;
	
	if (offset)
		*offset = ch - begin;
	
	while (ch != end && (IsAlpha(*ch) || IsDigit(*ch) || *ch == '_') ) ch++;
	
	String variable;
	while (begin != ch) {
		variable.Cat(*begin); 
		begin++;
	}
	
	return variable;
}












Editor::Editor() {
	Add(tabs.VSizePos().HSizePos());
	
    editortabsize = 4;
	indent_spaces = 0;
	indent_amount = 4;
	show_tabs = 0;
	no_parenthesis_indent = 0;
	hilite_scope = 1;
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
	
	font_height = 11;
	
	
}

Editor::~Editor() {
	CloseAllTabs();
}

void Editor::OpenAndSelect(const String& path, int line, int col) {
	if (!IsOpen(path)) {
		CodeEdit& edit = editors.Add();
		edit.WhenUpdate = THISBACK(SetCurrentChanged);
		
		tabs.Add(edit, GetFileTitle(path));
		tabs.Add(edit);
	    editor_paths.Add(path);
	    changed.Add(false);
	    
	    SetEditor(edit);
	    
	    String content = LoadFile(path);
	    edit.SetData(content);
	}
    Select(path, line, col);
}

void Editor::Select(const String& path, int line, int col) {
	for(int i = 0; i < editor_paths.GetCount(); i++) {
		if (editor_paths[i] == path) {
			tabs.Set(i);
			if (line >= 0 && col >= 0) {
				int pos = editors[i].GetPos(line-1, col-1);
				if (pos >= 0 && pos < editors[i].GetLength())
					editors[i].SetCursor(pos);
				editors[i].SetFocus();
			}
			return;
		}
	}
}

/*void Editor::MoveSelectedLeft() {
	int cur = tabs.Get();
	if (cur < 0) return;
	String path = editor_paths[cur];
	editor_paths.Remove(cur);
	editor_paths.Insert(cur-1, path);
	tabs.Remove(cur);
	tabs.Insert(cur-1, 
}

void Editor::MoveSelectedRight() {
	int cur = tabs.Get();
	if (cur < 0) return;
	
}*/

void Editor::SelectLeft() {
	int cur = tabs.Get();
	if (cur < 0) return;
	if (cur == 0) cur = editors.GetCount()-1;
	else cur--;
	tabs.Set(cur);
}

void Editor::SelectRight() {
	int cur = tabs.Get();
	if (cur < 0) return;
	if (cur == editors.GetCount()-1) cur = 0;
	else cur++;
	tabs.Set(cur);
}

void Editor::CloseSelected() {
	int cur = tabs.Get();
	if (cur < 0) return;
	StoreFile(cur);
	tabs.Remove(cur);
	editor_paths.Remove(cur);
	editors.Remove(cur);
	changed.Remove(cur);
	    
}

void Editor::CloseAllTabs() {
	for(; editors.GetCount(); ) {
		StoreFile(0);
		tabs.Remove(0);
		editor_paths.Remove(0);
		editors.Remove(0);
		changed.Remove(0);
	}
}

void Editor::SetEditor(CodeEdit& codeedit) {
	codeedit.DefaultHlStyles();
	codeedit.Highlight("cpp");
	
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
	
	codeedit.WhenLeftDown = THISBACK(WhenTextCursor);
	codeedit.WhenAnyKey = THISBACK(WhenTextCursor);
	/*codeedit.WhenAction = THISBACK(WhenTextCursor);
	codeedit.WhenState = THISBACK(WhenTextCursor);
	codeedit.WhenUpdate = THISBACK(WhenTextCursor);
	codeedit.WhenAnnotationMove = THISBACK(WhenTextCursor);*/
	
	codeedit.WhenCtrlClick = THISBACK(_WhenCtrlClick);
	
}

void Editor::StoreFile(int i) {
	if (!IsChanged(i)) return;
	String content = editors[i].Get();
	FileOut out(editor_paths[i]);
	out << content;
	SetChanged(i, false);
}

void Editor::StoreCurrentFile() {
	int cur = tabs.Get();
	if (cur < 0) return;
	StoreFile(cur);
}

void Editor::StoreAllFiles() {
	for(int i = 0; i < editors.GetCount(); i++) {
		StoreFile(i);
	}
}


void Editor::SetCurrentChanged() {
	int i = tabs.Get();
	if (i < 0 || i >= editors.GetCount()) return;
	SetChanged(i, true);
}

void Editor::SetChanged(int i, bool value) {
	changed[i] = value;
	
	GuiLock __;
	tabs.GetItem(i).Text(GetFileName(editor_paths[i]));
}

bool Editor::IsChanged(int i) {
	return changed[i];
}


bool Editor::IsOpen(const String& path) {
	for(int i = 0; i < editor_paths.GetCount(); i++) {
		if (editor_paths[i] == path)
			return true;
	}
	return false;
}


/*void Editor::RefreshDecompilation() {
	decomp.Clear();
	
	Decompile(DecompileInstruction);
	
	codeedit.Set(decomp.Get());
}
*/
bool Editor::IsOpenEditor() {
	return editors.GetCount();
}

CodeEdit& Editor::GetOpenEditor() {
	int cur = tabs.Get();
	return editors[cur];
}

void Editor::WhenTextCursor() {
	int cur = tabs.Get();
	CodeEdit& e = editors[cur];
	String path = editor_paths[cur];
	int line = e.GetCursorLine();
	int column = e.GetCursor() - e.GetPos(line);
	line++;
	WhenCursor(path, line, column);	
}

void Editor::_WhenCtrlClick(int pos) {
	int cur = tabs.Get();
	CodeEdit& e = editors[cur];
	String path = editor_paths[cur];
	int line = e.GetLine(pos);
	int column = pos - e.GetPos(line);
	line++;
	WhenCtrlClick(path, line, column);	
}

