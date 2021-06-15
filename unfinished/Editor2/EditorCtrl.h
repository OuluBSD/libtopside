#ifndef _Editor_EditorCtrl_h_
#define _Editor_EditorCtrl_h_



#include <CtrlLib/CtrlLib.h>
#include <CodeEditor/CodeEditor.h>
using namespace UPP;


class CodeEdit : public CodeEditor {
	
public:
	CodeEdit();
	
	virtual bool   Key(dword key, int count);
	
	String GetVariable(int line, int column, int* offset=0);
	
	Callback WhenAnyKey;
};

class Editor : public ParentCtrl {
	TabCtrl tabs;
	Array<CodeEdit> editors;
	Vector<String> editor_paths;
	Vector<bool> changed;
	
	
	int editortabsize, indent_spaces, indent_amount, show_tabs, no_parenthesis_indent, hilite_scope, hilite_bracket;
	int hilite_ifdef, barline, hilite_if_endif, thousands_separator, hline, line_numbers, auto_enclose;
	int mark_lines, bordercolumn, bordercolor, persistent_find_replace, find_replace_restore_pos;
	int font_height;
	
protected:
	
	void SetEditor(CodeEdit& codeedit);
	void StoreFile(int i);
	bool IsOpen(const String& path);
	void WhenTextCursor();
	
	void _WhenCtrlClick(int i);
	
public:
	typedef Editor CLASSNAME;
	Editor();
	~Editor();
	
	
	void OpenAndSelect(const String& path, int line=-1, int col=-1);
	void Select(const String& path, int line=-1, int col=-1);
	
	//void MoveSelectedLeft();
	//void MoveSelectedRight()
	void SelectLeft();
	void SelectRight();
	void CloseSelected();
	void CloseAllTabs();
	
	//void RefreshDecompilation();
	void StoreAllFiles();
	void StoreCurrentFile();
	
	void SetCurrentChanged();
	void SetChanged(int i, bool value);
	bool IsChanged(int i);
	
	
	
	Callback3<String, int, int> WhenCursor, WhenCtrlClick;
	
	
	int GetCount() {return editors.GetCount();}
	String GetPath(int i) {return editor_paths[i];}
	CodeEdit& GetEditor(int i) {return editors[i];}
	int GetOpenTab() {return tabs.Get();}
	bool IsOpenEditor();
	CodeEdit& GetOpenEditor();
	String GetOpenPath() {if (editors.GetCount()==0) return ""; return editor_paths[tabs.Get()];}
};


struct EditorOpenTab : public Moveable<EditorOpenTab> {
	String path;
	int line, col;
	void Serialize(Stream& s) {s % path % line % col;}
};

struct PackageHistory : public Moveable<PackageHistory> {
	Vector<EditorOpenTab> open_tabs;
	ArrayMap<String, unsigned> compiled; // Path to compiled file's hash
	int selected_tab;
	int package_configuration, build_method, build_mode;
	void Serialize(Stream& s) {s % open_tabs % compiled % selected_tab % package_configuration % build_method % build_mode;}
	
};

#endif
