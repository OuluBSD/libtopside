#ifndef _EditorBase_EditorBase_h_
#define _EditorBase_EditorBase_h_

#include <CtrlLib/CtrlLib.h>
#define LAYOUTFILE <EditorBase/Layouts.lay>
#include <CtrlCore/lay.h>
#include <CodeEditor/CodeEditor.h>
#include <Esc/Esc.h>

#include <LocalCtrl/LocalCtrl.h>

#include "Bottom.h"


NAMESPACE_TOPSIDE_BEGIN


class EditorBase;


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

struct ErrorInfo {
	String file;
	int    lineno;
	int    linepos;
	int    kind;
	String message;
	String error_pos;
	
	ErrorInfo() { lineno = linepos = kind = 0; }
};

class EditorExtension {
	
protected:
	friend class EditorBase;
	
	EditorBase* base = 0;
	
public:
	
	
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
	virtual void Save() = 0;
	virtual bool HotKey(dword key) = 0;
	
	virtual void GoToError(const ErrorInfo& f) {}
	
};

class EditorBase : public TopWindow {
	
public:
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
	
protected:
	Splitter hsplit, editor_bottom, hsplit_code;
	ParentCtrl lbar;
	ParentCtrl left, right;
	Mutex lock;
	Vector<ProcMsg> errors;
	
	EditorExtension* active_ext = 0;
	
	
	RightTabs btabs;
	Ptr<Ctrl>   bottomctrl;
	enum Bottoms { BCLOSE, BCONSOLE, BERRORS, BFINDINFILES, BCALC, BDEBUG };
	LineEdit    console;
	ArrayCtrl   ffound;
	ArrayCtrl   error;
	TheCalc      calc;
	StaticRect  bottom;
	bool        removing_notes;
	
	MenuBar		main_menu;
	
	
	void SetupError(ArrayCtrl& error, const char *s);
	void ErrorMenu(Bar& bar);
	void FFoundMenu(Bar& bar);
	void SelError();
	void ShowError();
	void ShowFound();
	void CopyError(bool all);
	void CopyFound(bool all);
	void GoToError(ArrayCtrl& a);
	WString FormatErrorLineEP(String text, const char *ep, int& linecy);
	WString FormatErrorLine(String text, int& linecy);
	
	void SetMenu() {main_menu.Set(THISBACK(Menu));}
	
	// Find in files
	FindInFilesDlg ff;
	void FindInFiles(int replace_mode=0);
	void DoFindInFiles();
	
public:
	
	// State
	typedef enum {
		IDLE,
		COMPILING,
		DEBUGGING,
		RUNNING,
		PAUSED,
	} StateType;
	
	StateType state = IDLE;
	
	// Active project
	UppProject* prj = NULL;
	const UppAssembly* as = NULL;
	UppAssemblyData* asd = NULL;
	Index<String> rec_uses;
	
public:
	typedef EditorBase CLASSNAME;
	EditorBase();
	~EditorBase();
	
	virtual void MainMenu(Bar& b) {}
	
	void SetCtrls(Ctrl& lbar, Ctrl& left, Ctrl& right);
	bool HotKey(dword key);
	void SetExt(EditorExtension& prj_ext);
	void ClearExt();
	void ClearCtrls();
	void Menu(Bar& b) {MainMenu(b);}
	
	void OnMessage(ProcMsg e);
	void ProcessCompiling();
	
	// Project
	void SetProject(UppProject& p, const UppAssembly& as, UppAssemblyData& asd);
	UppProject& GetProject() {ASSERT(prj); return *prj;}
	UppAssemblyData& GetAssemblyData() {ASSERT(asd); return *asd;}
	const UppAssembly& GetAssembly() const {ASSERT(as); return *as;}
	
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
	void WriteConsole(String s);
	void WriteConsoleLine(String s) {WriteConsole(s + "\n");}
};


NAMESPACE_TOPSIDE_END


#include "ProjectEditor.h"


#endif
