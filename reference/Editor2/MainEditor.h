#ifndef _Editor_MainEditor_h_
#define _Editor_MainEditor_h_

#include <CtrlLib/CtrlLib.h>
using namespace UPP;

#include "Terminal.h"
#include "Navigator.h"
#include "EditorCtrl.h"
#include "Assist.h"
#include "Debugger.h"

class IDE : public TopWindow {
	Project* project;
	
	MenuBar menu;
	ToolBar tool;
	Splitter main_horz_split, main_vert_split, run_horz_split;
	Terminal terminal;
	NavigatorCtrl navigator;
	Editor editor;
	Assist assist;
	DocEdit serial_out;
	
	String path;
	
	// Permanent
	String default_path;
	Vector<String> recent_projects;
	
	// Toolbar
	DropList package_configurations, build_methods, build_mode;
	
	Debugger dbg;
	
protected:
	
	
public:
	typedef IDE CLASSNAME;
	
	IDE();
	~IDE();
	
	Project& GetProject() {return *project;}
	Editor& GetEditor() {return editor;}
	
	void ShowTerminal();
	void HideTerminal();
	
	void RefreshPackageConfigurations();
	void RefreshBuilderMethods();
	
	void Serialize(Stream& s);
	void StoreThis();
	void LoadThis();
	
	
	void MainBar(Bar& bar);
	
	void File(Bar& bar);
	void View(Bar& bar);
	void Project(Bar& bar);
	void Build(Bar& bar);
	void Debug(Bar& bar);
	void MethodMenu(Bar& bar);
	void Setup(Bar& bar);
	
	void Find();
	void SwitchTerminalVisibility();
	
	void BuildProject();
	void BuildAllProject();
	void FindNextError();
	void FindPreviousError();
	
	void SetMainPackage();
	void Save();
	void Exit();
	
	void WrapperWizard();
	//void PopupAssist();
	
	void CloseAllFiles();
	
	void Restart();
	void EnterDebugger();
	
	void BreakNow();
	void StartDebug();
	void StepInto();
	void StepOver();
	void StepOut();
	void RunTo();
	void Continue();
	
	void SwitchManagerVisibility();
	
	void StartDebugger();
	void PostStartDebugger() {PostCallback(THISBACK(StartDebugger));}
	
	void PostBreakNow() {PostCallback(THISBACK(BreakNow));}
	
	void ToolBar(Bar& bar);
	
	//void Status(const String& s);
	
	void WhenEditorCursor(String path, int line, int column);
	void WhenEditorCtrlClick(String path, int line, int column);
	
	
	
	// Building
	void Start();
	void Pause();
	void Stop();
	
	
	// Package histories
	ArrayMap<String, PackageHistory> histories;
	void StoreHistory();
	void LoadHistory();
	void UpdateHistory();
	PackageHistory& GetOpenHistory();
	void SetCompiled(String path, unsigned hash);
	void GetCompiled(String path, unsigned* hash);
	
	
	// Project manager
	Thread builder_thrd;
	enum {STATUS_EDITING, STATUS_COMPILING, STATUS_LINKING, STATUS_DEBUGGING, STATUS_DEBUGBREAK};
	int status;
	String prjpath, exepath, open_package;
	
	void Make();
	void Rebuild();
	void RunPackage();
	void ChangeStatus(int status_code);
	int  BuildPackage();
	void TryBuildPackage() {BuildPackage();}
	void SelectFile(String path) {editor.OpenAndSelect(path); UpdateHistory();}
	void SelectFilePos(String path, int line, int pos) {editor.OpenAndSelect(path, line, pos); UpdateHistory();}
	
	
	// Setup
	void BuildMethods();
	//void BuildMethod();
	//void SetMethod(int id);
	
	void LoadProject(class Project& prj);
	
	
	
	
	// OLD
	void ToggleBreakpoint();
	void ClearBreakpoints();
	
	void ParseClangOutput(String &e);
	
	
	void SetExe(String path) {exepath = path; dbg.Init(path);}
	void SetProject(String path) {prjpath = path;}
	
	void EditorAction();
};


#endif
