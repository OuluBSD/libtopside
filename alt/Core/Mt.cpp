#include "Core.h"

#if defined flagWIN32
	#include <synchapi.h>
#endif

NAMESPACE_UPP_BEGIN

bool Thread::shutdown;
AtomicInt Thread::thrd_count;


void thread_runner(Callback* cb) {
	cb->Execute();
	RunThreadExitBlocks();
}

void Thread::Run(Callback cb) {
	this->cb = cb;
	t = new std_thread(thread_runner, &this->cb);
}

void Thread::ShutdownThreads() {
	shutdown = true;
	while (thrd_count > 0)
		Sleep(10);
}

int& __ThreadId() {
	static thread_local int id;
	return id;
}

void Thread::SetThreadId(int i) {__ThreadId() = i;}
int  Thread::GetThreadId() {return __ThreadId();}
bool Thread::IsMain() {return __ThreadId() == MAIN_THREAD_ID;}
void __ForceSetThreadId(int i) {__ThreadId() = i;}

void Sleep(int ms) {
#if defined(flagWIN32)
	::Sleep(ms);
#elif defined(flagPOSIX)
	usleep(ms * 1000);
#endif
}

NAMESPACE_UPP_END
