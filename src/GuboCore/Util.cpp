#include "GuboCore.h"

#define LLOG(x)

NAMESPACE_TOPSIDE_BEGIN


static StaticMutex sGLock;

static thread_local int sGLockLevel = 0;

void EnterGuboMutex()
{
	LLOG(">EnterGuboMutex " << sGLockLevel << ' ' << IsMainThread());
	if(sGLockLevel++ == 0)
		sGLock.Enter();
	LLOG("EnterGuboMutex " << sGLockLevel << ' ' << IsMainThread());
}

void EnterGuboMutex(int n)
{
	LLOG(">EnterGuboMutex: " << n << ' ' << sGLockLevel << ' ' << IsMainThread());
	if(n > 0) {
		if(sGLockLevel == 0)
			sGLock.Enter();
		sGLockLevel += n;
	}
	LLOG("EnterGuboMutex " << sGLockLevel << ' ' << IsMainThread());
}

bool TryEnterGuboMutex()
{
	if(sGLockLevel == 0 && sGLock.TryEnter()) {
		sGLockLevel++;
		return true;
	}
	return false;
}

void LeaveGuboMutex()
{
	LLOG(">LeaveGuboMutex " << sGLockLevel << ' ' << IsMainThread());
	ASSERT(sGLockLevel > 0);
	if(--sGLockLevel == 0)
		sGLock.Leave();
	LLOG("LeaveGuboMutex " << sGLockLevel << ' ' << IsMainThread());
}

int LeaveGuboMutexAll()
{
	LLOG(">LeaveGuboMutexAll " << sGLockLevel << ' ' << IsMainThread());
	int q = sGLockLevel;
	if(q) {
		sGLock.Leave();
		sGLockLevel = 0;
	}
	LLOG("LeaveGuboMutexAll " << q << ' ' << IsMainThread());
	return q;
}

bool ThreadHasGuboLock()
{
	return Thread::IsMain() || sGLockLevel;
}

int  GetGuboLockLevel()
{
	return sGLockLevel;
}



NAMESPACE_TOPSIDE_END
