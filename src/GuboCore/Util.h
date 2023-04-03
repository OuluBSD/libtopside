#ifndef _GuboCore_Util_h_
#define _GuboCore_Util_h_

NAMESPACE_TOPSIDE_BEGIN

void EnterGuboMutex();
bool TryEnterGuboMutex();
void LeaveGuboMutex();

int  LeaveGuboMutexAll();
void EnterGuboMutex(int n);

bool ThreadHasGuboLock();
int  GetGuboLockLevel();

struct GuboLock {
	GuboLock()  { EnterGuboMutex(); }
	~GuboLock() { LeaveGuboMutex(); }
};

class GuboUnlock {
	int n;

public:
	GuboUnlock()  { n = LeaveGuboMutexAll(); }
	~GuboUnlock() { EnterGuboMutex(n); }
};

NAMESPACE_TOPSIDE_END

#endif
