#include "CommandBridge.h"

#ifdef PLATFORM_POSIX
const char *tshell = "SHELL";
#elif PLATFORM_WIN32
const char *tshell = "ComSpec"; // Alternatively you can use powershell...
#endif

TerminalTab::TerminalTab()
{
	InlineImages().Hyperlinks().WindowOps();
	WhenBell   = [=]()         { BeepExclamation();    };
	WhenOutput = [=](String s) { PtyProcess::Write(s); };
	WhenResize = [=]()         { PtyProcess::SetSize(GetPageSize()); };
	
	String shell = GetEnv(tshell);
	
	Vector<String> args;
	
	Start(shell, Environment(), GetHomeDirectory());
	
	#ifdef flagWIN32
	String msys = "C:\\msys\\msys2_shell.cmd";
	if (FileExists(msys))
		PtyProcess::Write(msys + " -no-start -defterm\r");
	#endif
	
	tc.Set(-1, THISBACK(Process));
}

void TerminalTab::Process() {
	if (!Do()) {
		tc.Kill();
		bridge->CloseTabId(id);
	}
}

bool TerminalTab::Do() {
	WriteUtf8(PtyProcess::Get());
	return PtyProcess::IsRunning();
}

bool TerminalTab::Key(dword key, int count) {
	if (key == K_CTRL_T			||
		key == K_SHIFT_CTRL_W	||
		key == K_CTRL_LEFT		||
		key == K_CTRL_RIGHT)
		return false;
	return  TerminalCtrl::Key(key, count);
}

void TerminalTab::Menu(Bar& bar) {
	StdBar(bar);
}
