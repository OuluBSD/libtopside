#ifndef _Editor_Editor_h
#define _Editor_Editor_h

#include <CtrlLib/CtrlLib.h>
#include <CodeEditor/CodeEditor.h>
using namespace UPP;
#define LAYOUTFILE <Editor/Layouts.lay>
#include <CtrlCore/lay.h>

#include <Local/Local.h>
#include <LocalCtrl/LocalCtrl.h>
#include <Esc/Esc.h>


#include "Bottom.h"
#include "Terminal.h"


NAMESPACE_TOPSIDE_BEGIN


struct FindInFilesDlg : WithFindInFilesLayout<ParentCtrl> {
	WString itext;
	
	virtual bool Key(dword key, int count);
	
	void Setup(bool replace);
	void Sync();
	void DoClose(bool search) {Close(); if (search) WhenSearch();}

	typedef FindInFilesDlg CLASSNAME;
	
	FindInFilesDlg();
	
	Callback WhenSearch;
	
};

class Editor : public TopWindow {
	Splitter vsplit, hsplit, editor_bottom, hsplit_code;
	ColumnList projects;
	FileList files;
	
	CodeEditor left, right;
	int editortabsize, indent_spaces, indent_amount, show_tabs, no_parenthesis_indent, hilite_scope, hilite_bracket;
	int hilite_ifdef, barline, hilite_if_endif, thousands_separator, hline, line_numbers, auto_enclose;
	int mark_lines, bordercolumn, bordercolor, persistent_find_replace, find_replace_restore_pos;
	int font_height;
	
	
	// State
	typedef enum {
		IDLE,
		COMPILING,
		DEBUGGING,
		RUNNING,
		PAUSED,
	} StateType;
	StateType state = IDLE;
	
	
	// Debugging GUI
	DocEdit left_object_tree;
	DocEdit left_node_tree;
	Splitter left_tree_split;
	
	
	// Active project
	UppProject* prj = NULL;
	UppAssemblyData* ad = NULL;
	String left_path, right_path;
	
	Index<String> rec_uses;
	
	
	// Compiling
	Vector<ProcMsg> errors;
	Mutex lock;
	
	
	
	
	
	// Bottom
	struct FoundDisplay : Display {
		virtual void Paint(Draw& w, const Rect& r, const Value& q, Color ink, Color paper, dword style) const;
	};
	struct TopAlignedDisplay : Display {
		virtual void Paint(Draw& w, const Rect& r, const Value& q, Color ink, Color paper, dword style) const;
	};
	struct FoundFileDisplay : Display {
		virtual void Paint(Draw& w, const Rect& r, const Value& q, Color ink, Color paper, dword style) const;
		virtual Size GetStdSize(const Value& q) const;
	};
	struct ErrorInfo {
		String file;
		int    lineno;
		int    linepos;
		int    kind;
		String message;
		String error_pos;
		
		ErrorInfo() { lineno = linepos = kind = 0; }
	};
	RightTabs btabs;
	Ptr<Ctrl>   bottomctrl;
	enum Bottoms { BCLOSE, BCONSOLE, BERRORS, BFINDINFILES, BCALC, BDEBUG };
	LineEdit    console;
	ArrayCtrl   ffound;
	ArrayCtrl   error;
	TheCalc      calc;
	StaticRect  bottom;
	bool        removing_notes;
	void SetupError(ArrayCtrl& error, const char *s);
	void ErrorMenu(Bar& bar);
	void FFoundMenu(Bar& bar);
	void SelError();
	void ShowError();
	void ShowFound();
	void CopyError(bool all);
	void CopyFound(bool all);
	void GoToError(const ErrorInfo& f);
	void GoToError(ArrayCtrl& a);
	WString FormatErrorLineEP(String text, const char *ep, int& linecy);
	WString FormatErrorLine(String text, int& linecy);
	
	
	// Find in files
	FindInFilesDlg ff;
	void FindInFiles(int replace_mode=0);
	void DoFindInFiles();
	
public:
	typedef Editor CLASSNAME;
	Editor();
	~Editor();
	
	bool HotKey(dword key);
	
	void Init();
	void InitEditor(CodeEditor& edit);
	void SetProject(UppProject& p, UppAssemblyData& ad);
	void Data();
	void DataProjectFiles();
	void OpenSelectedFile();
	void Compile();
	void ProcessCompiling();
	void NewFile();
	void SaveFile();
	void OpenLog();
	void SetTabFile(int i, String path, int line, int col);
	
	
	void OnMessage(ProcMsg e);
	
	
	// Debugger
	void FocusLine(ArrayCtrl* list);
	void Execute();
	void DebugFile();
	void StopDebug();
	void Continue();
	bool IsRunning();
	bool IsPaused();
	void FindInFiles(bool b);
	
	// Bottom
	void BTabs();
	void SyncBottom();
	void SetBottom(int i);
	void ShowBottom(int i);
	void ToggleBottom(int i);
	bool IsBottomShown() const;
	void SwapBottom();
	void HideBottom();
	void IdeSetBottom(Ctrl& ctrl);
	void IdeRemoveBottom(Ctrl& ctrl);
	void IdeActivateBottom();
	void ClearConsole() {GuiLock __; console.Clear();}
	
};


NAMESPACE_TOPSIDE_END

#endif
