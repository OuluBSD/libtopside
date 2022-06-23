#ifndef _LocalHMD_PLATFORM_H
#define _LocalHMD_PLATFORM_H


NAMESPACE_HMD_BEGIN


double GetTick();
void ToggleOvrService(int state);

//typedef struct Thread Thread;
//typedef struct Mutex Mutex;
struct Thread;
struct Mutex;

Mutex* CreateMutex(Context* ctx);
void DestroyMutex(Mutex* mutex);

void EnterMutex(Mutex* mutex);
void LeaveMutex(Mutex* mutex);

Thread* CreateThread(Context* ctx, unsigned int (*Routine)(void* arg), void* arg);
void DestroyThread(Thread* thread);

// String functions

int FindEndPoint(char* path, int endpoint);


NAMESPACE_HMD_END


#endif
