#ifndef _CtrlCoreAlt_Util_h_
#define _CtrlCoreAlt_Util_h_

NAMESPACE_UPP

void EnterGuiMutex();
bool TryEnterGuiMutex();
void LeaveGuiMutex();

int  LeaveGuiMutexAll();
void EnterGuiMutex(int n);

bool ThreadHasGuiLock();
int  GetGuiLockLevel();

struct GuiLock {
	GuiLock()  { EnterGuiMutex(); }
	~GuiLock() { LeaveGuiMutex(); }
};

class GuiUnlock {
	int n;

public:
	GuiUnlock()  { n = LeaveGuiMutexAll(); }
	~GuiUnlock() { EnterGuiMutex(n); }
};


String FromSystemCharset(const String& src);


END_UPP_NAMESPACE

#endif
