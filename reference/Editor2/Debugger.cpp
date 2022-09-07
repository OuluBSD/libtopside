#include "Debugger.h"


Debugger& GetDebugger() {return Single<Debugger>();}


Debugger::Debugger() {
	
}

void Debugger::Init(String path) {
	exepath = path;
	
	/*
#if defined(flagPOSIX)
	as.Parse(path);
#endif
	*/
	
	gdbstatus = GDB_STOPPED;
	
}

void Debugger::Start() {
	LOG("Debugger Start");
	
	
	if (gdbstatus == GDB_STOPPED) {
		pr.Clear();
		pr.SetCount(2);
		//if (as.Parse(exepath)) return;
		
		//thrd.Run(THISBACK(BochsHandler));
		//thrd.Run(THISBACK(QemuHandler));
		//Sleep(100);
		thrd.Run(THISBACK(GdbHandler));
	}
	else if (gdbstatus == GDB_PAUSED) {
		gdbstatus = GDB_STARTED;
	}
}

void Debugger::Pause() {
	//gdbstatus = GDB_PAUSED;
	if (gdbstatus == GDB_STARTED)
		SignalBreak( pr[1] );
	//PauseRoutines();
	//WhenPaused.Execute();
}

void Debugger::Stop() {
	status = DBG_STOPPING;
	if (gdbstatus == GDB_STARTED) {
		pr[0].Kill();
		StopGdb(pr[1]);
	}
	gdbstatus = GDB_STOPPED;
	status = DBG_IDLE;
}

void Debugger::StopGdb(LocalProcess &p) {
	if (p.IsRunning()) {
		SignalBreak(p);
		String s;
		s.Cat('q');
		s.Cat('\n');
		p.Write(s);
		Sleep(100);
		String out;
		p.Read(out);
		LOG(out);
		Sleep(200);
	}
	
	if (p.IsRunning())
		p.Kill();

	gdbstatus = GDB_STOPPED;
	WhenStopped();
	Log("Dbg", "Stopped");
}

void Debugger::ContinueGdb(LocalProcess &p) {
	p.Write("c\n");
}

void Debugger::SignalBreak(LocalProcess &p) {
	String cmd, out;
	cmd = "kill -2 " + IntStr(p.GetPid());
	LOG(cmd);
	Sys(cmd, out);
}

void Debugger::BochsHandler() {
	pr.Clear();
	LocalProcess& p = pr.Add();
	
	String bochconf = AppendFileName( ConfigFile("Files"), "bochs.conf");
	String cmd = "bochs -q -f " + bochconf;
	LOG("    " << cmd);
	
	p.Start(cmd);
	
	String out, s;
	p.Write("c\n");
	while (p.IsRunning() && status != DBG_STOPPING) {
		if (p.Read(s) && s.GetCount()) {
			LOG(s);
			out += s;
		}
	}
	
	StopGdb(p);
	
	
	//Sys(cmd, out);
	//LOG(out);
}

void Debugger::QemuHandler() {
	LocalProcess& p = pr[0];
	
	String cmd = "qemu-system-i386 -s -S -kernel " + exepath;
	LOG("    " << cmd);
	
	p.Start(cmd);
	
	String out, s;
	while (p.IsRunning() && status != DBG_STOPPING) {
		if (p.Read(s) && s.GetCount()) {
			LOG(s);
			out += s;
		}
	}
	
}

#define WAITENTRY while (1) {if (p.Read(s) && s.Find("(gdb)") != -1) break;}

void Debugger::GdbHandler() {
	String out, s;
	
	gdbstatus = GDB_STARTED;
	
	LocalProcess& p = pr[1];
	
	//String cmd = "gdb --init-eval-command=\"target remote localhost:1234\""; // --interpreter=mi2 
	//cmd += " --init-eval-command=\"symbol-file " + exepath + "\"";
	
	// TODO: this is bad, quick, lazy solution... get the path from build method
	String cmd = "gdb \"" + exepath + "\"";
	LOG(cmd);
	
	p.Start(cmd);
	WAITENTRY
	
	// Set breakpoints
	for(int i = 0; i < bpoints.GetCount(); i++)
		bpoints[i].SetAdded(0);
	ContinueRoutines();
	
	p.Write("r\n");
	//p.Write("c\n");
	while (p.IsRunning() && status != DBG_STOPPING) {
		if (p.Read(s) && s.GetCount()) {
			LOG(s);
			WhenOutput(s);
			out += s;
			if (s.Find("Breakpoint") != -1) {
				LOG("Break");
				HandleBreakpoint(s);
				WAITENTRY
				PauseRoutines();
				if (stack.GetCount()==0) 
					break;
				WhenPaused();
			}
			else if (gdbstatus == GDB_STARTED && s.Find("(gdb)") != -1) {
				PauseRoutines();
				if (stack.GetCount()==0) 
					break;
				WhenPaused();
			}
			
			if (gdbstatus == GDB_PAUSED) {
				while (gdbstatus == GDB_PAUSED) {Sleep(100);}
				if (status != DBG_STOPPING) {
					ContinueRoutines();
					ContinueGdb(pr[1]);
				}
			}
			
		}
	}
	
	if (gdbstatus != GDB_STOPPED) StopGdb(p);
	
}

void Debugger::WriteAddBreakpoint(BreakPoint& bp) {
	LocalProcess& p = pr[1];
	p.Write("break " + bp.GetPath() + ":" + bp.GetLineStr() + "\n");
	bp.SetAdded();
	Log("Debugger", "Added break " + GetFileName(bp.GetPath()) + ":" + bp.GetLineStr());
}

void Debugger::WriteRemoveBreakpoint(BreakPoint& bp) {
	LocalProcess& p = pr[1];
	p.Write("clear " + bp.GetPath() + ":" + bp.GetLineStr() + "\n");
	bp.SetAdded();
	Log("Debugger", "Removed break " + GetFileName(bp.GetPath()) + ":" + bp.GetLineStr());
}

void Debugger::PauseRoutines() {
	
	RefreshStack();
	
	RefreshFrame();
	
	gdbstatus = GDB_PAUSED;
	Log("Dbg", "Paused");
}

void Debugger::ContinueRoutines(bool wait) {
	LocalProcess& p = pr[1];
	String s;
	for(int i = 0; i < bpoints.GetCount(); i++) {
		BreakPoint& bp = bpoints[i];
		// Remove breakpoint from debugger
		if (bp.IsDeleted() && bp.IsAdded()) {
			WriteRemoveBreakpoint(bp);
			if (wait) {WAITENTRY}
		}
		// Add breakpoint to debugger
		else if (!bp.IsDeleted() && !bp.IsAdded()) {
			WriteAddBreakpoint(bp);
			if (wait) {WAITENTRY}
		}
	}
	
	gdbstatus = GDB_STARTED;
	Log("Dbg", "Continuing");
}

void Debugger::RefreshFrame() {
	LocalProcess& p = pr[1];
	p.Write("info locals\n");
	LOG("info locals");
	
	String s, out = "";
	while (1) {
		if (p.Read(s) && s.GetCount()) {
			out += s;
			if (s.Find("(gdb)") != -1) break;
		}
	}
	LOG(out);
	
	
}

void Debugger::RefreshStack() {
	String s, out;
	
	LocalProcess& p = pr[1];
	
	// info stack
	p.Write("info stack\n");
	LOG("info stack");
	
	while (1) {
		if (p.Read(s) && s.GetCount()) {
			out += s;
			if (s.Find("(gdb)") != -1) break;
		}
	}
	LOG(out);
	
	
/*
0: #0  multiboot_main (mboot_ptr=0x9500)
1:     at /home/sblo/MyApps/LittleKernel/main.cpp:79
2: #1  0x00100257 in start ()
*/
	stack.Clear();
	Vector<String> lines = Split(out, "\n");
	//StackItem* si = 0;
	for(int i = 0; i < lines.GetCount(); i++ ) {
		LOG(i << ": " << lines[i]);
		String& line = lines[i];
		
		int a = line.Find(" at ");
		if (a >= 0) {
			String l = line.Mid(a+4);
			int a = l.ReverseFind(":");
			StackItem& si = stack.Add();
			si.file = l.Mid(0,a);
			si.line = StrInt(l.Mid(a+1));
		}
		
		/*
		if (line.Left(1) == "#") {
			si = &stack.Add();
			si->line = -1;
			int a = line.Find(" ");
			String l = line.Mid(a+2);
			if (l.Left(2) == "0x") {
				String addr = TrimHex(l);
				if (as.addr.Find(addr) != -1) {
					AddrToFile &a2f = as.addr.Get(addr);
					si->file = as.data.GetKey( a2f.fileid );
					si->line = as.data[ a2f.fileid ].GetKey( a2f.lineid ) - 1;
				}
			}
			si->call = l;
			
		}
		else if (line.Left(7) == "    at ") {
			String l = line.Mid(7);
			int a = l.ReverseFind(":");
			si->file = l.Mid(0,a);
			si->line = StrInt(l.Mid(a+1));
		}*/
		
	}
}

void Debugger::AddBreakpoint(const String& path, int line) {
	String name = path + ":" + IntStr(line);
	int i = bpoints.Find(name);
	BreakPoint& bp = i == -1 ? bpoints.Add(name).Set(path,line) : bpoints[i];
	bp.SetDeleted(0);
}

void Debugger::RemoveBreakpoint(const String& path, int line) {
	String name = path + ":" + IntStr(line);
	int i = bpoints.Find(name);
	BreakPoint& bp = i == -1 ? bpoints.Add(name).Set(path,line) : bpoints[i];
	bp.SetDeleted(1);
}




void Debugger::HandleBreakpoint(String in) {
	breakfile = "";
	breakline = 0;
	Vector<String> lines = Split(in, "\n");
	

	LOG(in);
	for(int i = 0; i < lines.GetCount(); i++ ) {
		String& line = lines[i];
		if (line.Left(10) == "Breakpoint") {
			int a = line.Find(" at ");
			if (a >= 0) {
				String where = line.Mid(a+4);
				a = where.ReverseFind(":");
				breakline = StrInt(where.Mid(a+1));
				breakfile = where.Left(a);
				break;
			}
		}
		/*if (line.Left(7) == "    at ") {
			String l = line.Mid(7);
			int a = l.Find(":");
			breakfile = l.Mid(0,a);
			breakline = StrInt(l.Mid(a+1));
			break;
		}*/
		
	}
	Log("Dbg", "Breakpoint at " + breakfile + " : " + IntStr(breakline));
	WhenBreak();
}

