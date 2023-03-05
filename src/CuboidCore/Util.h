#ifndef _CuboidCoreAlt_Util_h_
#define _CuboidCoreAlt_Util_h_

NAMESPACE_UPP

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


String FromSystemCharset(const String& src);


END_UPP_NAMESPACE

#endif
