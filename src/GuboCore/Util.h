#ifndef _GuboCore_Util_h_
#define _GuboCore_Util_h_

NAMESPACE_TOPSIDE_BEGIN

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

NAMESPACE_TOPSIDE_END

#endif
