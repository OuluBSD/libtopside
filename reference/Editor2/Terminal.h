#ifndef _Editor_Terminal_h_
#define _Editor_Terminal_h_

#include <CtrlLib/CtrlLib.h>
using namespace UPP;

#include "Builder.h"


class IDE;

class ColorLabel : public Ctrl {
	Color bg, fg;
	String label;
	Callback WhenSelected;
public:
	ColorLabel& WhenSel(Callback cb) {WhenSelected = cb; return *this;}
	void SetLabel(const String& s);
	virtual void Paint(Draw& d);
	virtual void LeftDown(Point p, dword keyflags);
};


class LogItem : public Moveable<LogItem> {
	bool haslocation;
	String where, what;
	int line, col;
public:
	LogItem() {haslocation = 0;}
	bool HasLocation();
	const String& Where() {return where;}
	String What() {return what;}
	int Line() {return line;}
	int Column() {return col;}
	
	void SetError(String where, String what, int line, int col);
	void SetNormal(String where, String what);
};


class GdbInfo : public ParentCtrl {

public:
	ArrayCtrl log;
	DropList calls;
	ProgressIndicator prog;
	GdbInfo();
};

class Console : public ParentCtrl {
	DocEdit edit;
	String content;
public:
	Console();
	void Put(const String& s);
	void Clear() {content = ""; edit.SetData("");}
};

class Terminal : public ParentCtrl {
	IDE* ide;
	
	Splitter main_vert_split, main_horz_split;
	TabCtrl output_tab, dbg_tab;
	
	ProgressIndicator progress;
	
	
	// Builder
	DocEdit builder_log;
	ArrayCtrl builder_msg;
	String builder_log_content;
	
	// Debugger
	ArrayCtrl threads, callstack, locals, thisclass, watches;
	Console console;
	
	
	Array<BuildLogItem> items;
public:
	GdbInfo info;
	
	
	typedef Terminal CLASSNAME;
	Terminal(IDE* ide);
	
	void NewLogItem(BuildLogItem item);
	
	void WhenSelectBuilderMessage();
	
	void BuildLogSet(int id);
	
	void BeginBuild();
	
	
	
	//Log
	bool skip_log_duplicates;
	Vector<LogItem> logitems;
	ArrayMap<int, String> logpaths;
	
	void ClearLog();
	int  Log(const String& where, const String& what);
	void TryLog(String where, String what) {Log(where,what);}
	void PostLog(String where, String what) {PostCallback(THISBACK2(TryLog, where, what));}
	void CompilerLog(String where, String what, String path);
	void PostCompilerLog(String where, String what, String path) {PostCallback(THISBACK3(CompilerLog, where, what, path));}
	void LogError(String where, String what, int line, int col);
	void StdOut(String s) {Log("StdOut", s);}
	void Progress(int actual, int total);
	void SelectLogItem();
	void SetSkipDuplicateLog(bool b) {skip_log_duplicates = b;}
	
	void PostProgramOutput(String s) {PostCallback(THISBACK1(ProgramOutput, s));}
	void ProgramOutput(String s);
	void ClearProgramOutput();
	
	void BuilderOutput(String s);
	
	Callback1<String> WhenSelectFile;
	Callback3<String, int, int> WhenSelectFilePos;
};



#endif
