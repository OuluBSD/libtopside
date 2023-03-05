#include "GuboCore.h"


NAMESPACE_TOPSIDE_BEGIN


static StaticMutex sGLock;

static thread_local int sGLockLevel = 0;

void EnterGuiMutex()
{
	LLOG(">EnterGuiMutex " << sGLockLevel << ' ' << IsMainThread());
	if(sGLockLevel++ == 0)
		sGLock.Enter();
	LLOG("EnterGuiMutex " << sGLockLevel << ' ' << IsMainThread());
}

void EnterGuiMutex(int n)
{
	LLOG(">EnterGuiMutex: " << n << ' ' << sGLockLevel << ' ' << IsMainThread());
	if(n > 0) {
		if(sGLockLevel == 0)
			sGLock.Enter();
		sGLockLevel += n;
	}
	LLOG("EnterGuiMutex " << sGLockLevel << ' ' << IsMainThread());
}

bool TryEnterGuiMutex()
{
	if(sGLockLevel == 0 && sGLock.TryEnter()) {
		sGLockLevel++;
		return true;
	}
	return false;
}

void LeaveGuiMutex()
{
	LLOG(">LeaveGuiMutex " << sGLockLevel << ' ' << IsMainThread());
	ASSERT(sGLockLevel > 0);
	if(--sGLockLevel == 0)
		sGLock.Leave();
	LLOG("LeaveGuiMutex " << sGLockLevel << ' ' << IsMainThread());
}

int LeaveGuiMutexAll()
{
	LLOG(">LeaveGuiMutexAll " << sGLockLevel << ' ' << IsMainThread());
	int q = sGLockLevel;
	if(q) {
		sGLock.Leave();
		sGLockLevel = 0;
	}
	LLOG("LeaveGuiMutexAll " << q << ' ' << IsMainThread());
	return q;
}

bool ThreadHasGuiLock()
{
	return Thread::IsMain() || sGLockLevel;
}

int  GetGuiLockLevel()
{
	return sGLockLevel;
}



NAMESPACE_TOPSIDE_END
