#ifndef _Editor_Debugger_h_
#define _Editor_Debugger_h_

#include <Core/Core.h>
using namespace UPP;


enum {DBG_IDLE, DBG_RUNNING, DBG_PAUSED, DBG_STOPPING};

enum {GDB_STOPPED, GDB_STARTED, GDB_PAUSED};

struct StackItem : public Moveable<StackItem> {
	String call, file;
	int line;
};

class BreakPoint : public Moveable<BreakPoint> {
	String path;
	int line;
	bool added;
	bool deleted;
public:
	
	BreakPoint() : added(0) {}
	
	BreakPoint& Set(const String& path, int line) {this->path = path; this->line = line; return *this;}
	bool IsAdded() {return added;}
	void SetAdded(bool b=true) {added = b;}
	bool IsDeleted() {return deleted;}
	void SetDeleted(bool b=true) {deleted = b;}
	
	const String& GetPath() {return path;}
	String GetLineStr() {return IntStr(line);}
	int GetLine() {return line;}
	
};

class Debugger {
	Array<LocalProcess> pr;
	Thread thrd, gdbthrd;
	int status;
	
	String exepath;
	
	int gdbstatus;
	
	ArrayMap<String, BreakPoint> bpoints;
	
public:	
	Vector<StackItem> stack;
	
	
	Debugger();
	typedef Debugger CLASSNAME;
	
	void Init(String path);
	void Start();
	void Pause();
	void Stop();
	void BochsHandler();
	void QemuHandler();
	void GdbHandler();
	
	void StopGdb(LocalProcess &p);
	void ContinueGdb(LocalProcess &p);
	void SignalBreak(LocalProcess &p);
	
	
	void AddBreakpoint(const String& path, int line);
	void RemoveBreakpoint(const String& path, int line);
	void HandleBreakpoint(String in);
	void WriteAddBreakpoint(BreakPoint& bp);
	void WriteRemoveBreakpoint(BreakPoint& bp);
	
	String breakfile;
	int breakline;
	
	void PauseRoutines();
	void ContinueRoutines(bool wait=1);
	void RefreshStack();
	void RefreshFrame();
	
	bool IsPaused() {return gdbstatus == GDB_PAUSED;}
	
	Callback WhenStopped, WhenPaused, WhenBreak;
	Callback1<String> WhenOutput;
	Callback2<String, String> Log;
	
};

Debugger& GetDebugger();

#endif
