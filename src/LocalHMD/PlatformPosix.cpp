#include "LocalHMD.h"

#ifdef flagPOSIX


NAMESPACE_HMD_BEGIN


// Use clock_gettime if the system implements posix realtime timers
#ifndef CLOCK_MONOTONIC
double GetTick()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return (double)now.tv_sec * 1.0 + (double)now.tv_usec / 1000000.0;
}
#else
double GetTick()
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	return (double)now.tv_sec * 1.0 + (double)now.tv_nsec / 1000000000.0;
}
#endif

#ifndef CLOCK_MONOTONIC

static const uint64 NUM_1_000_000 = 1000000;

void InitMonotonic(Context* ctx)
{
	ctx->monotonic_ticks_per_sec = NUM_1_000_000;
}

uint64 GetMonotonic(Context* ctx)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return now.tv_sec * NUM_1_000_000 + now.tv_usec;
}

#else

static const uint64 NUM_1_000_000_000 = 1000000000;

void InitMonotonic(Context* ctx)
{
		struct timespec ts;
		if (clock_getres(CLOCK_MONOTONIC, &ts) !=  0) {
			ctx->monotonic_ticks_per_sec = NUM_1_000_000_000;
			return;
		}

		ctx->monotonic_ticks_per_sec =
			ts.tv_nsec >= 1000 ?
			NUM_1_000_000_000 :
			NUM_1_000_000_000 / ts.tv_nsec;
}

uint64 GetMonotonic(Context* ctx)
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);

	return ConvertMonotonic(
		now.tv_sec * NUM_1_000_000_000 + now.tv_nsec,
		NUM_1_000_000_000,
		ctx->monotonic_ticks_per_sec);
}

#endif

void SleepSeconds(double seconds)
{
	struct timespec sleepfor;

	sleepfor.tv_sec = (time_t)seconds;
	sleepfor.tv_nsec = (long)((seconds - sleepfor.tv_sec) * 1000000000.0);

	nanosleep(&sleepfor, NULL);
}

// threads
struct Thread
{
	pthread_t thrd;
	unsigned int (*Routine)(void* arg);
	void* arg;
};

static void* pthread_wrapper(void* arg)
{
	Thread* my_thread = (Thread*)arg;
	my_thread->Routine(my_thread->arg);
	return NULL;
}

Thread* CreateThread(Context* ctx, unsigned int (*Routine)(void* arg), void* arg)
{
	Thread* thrd = (Thread*)lhmd_alloc(ctx, sizeof(Thread));
	if(thrd == NULL)
		return NULL;

	thrd->arg = arg;
	thrd->Routine = Routine;

	int ret = pthread_create(&thrd->thrd, NULL, pthread_wrapper, thrd);

	if(ret != 0){
		free(thrd);
		thrd = NULL;
	}

	return thrd;
}

Mutex* CreateMutex(Context* ctx)
{
	pthread_mutex_t* mutex = (pthread_mutex_t*)lhmd_alloc(ctx, sizeof(pthread_mutex_t));
	if(mutex == NULL)
		return NULL;

	int ret = pthread_mutex_init(mutex, NULL);

	if(ret != 0){
		free(mutex);
		mutex = NULL;
	}

	return (Mutex*)mutex;
}

void DestroyThread(Thread* thrd)
{
	pthread_join(thrd->thrd, NULL);
	free(thrd);
}

void DestroyMutex(Mutex* mutex)
{
	pthread_mutex_destroy((pthread_mutex_t*)mutex);
	free(mutex);
}

void EnterMutex(Mutex* mutex)
{
	if(mutex)
		pthread_mutex_lock((pthread_mutex_t*)mutex);
}

void LeaveMutex(Mutex* mutex)
{
	if(mutex)
		pthread_mutex_unlock((pthread_mutex_t*)mutex);
}

/// Handling ovr service
void ToggleOvrService(int state) //State is 0 for Disable, 1 for Enable
{
	//Empty implementation
}

int FindEndPoint(char* path, int endpoint)
{
	char comp[6];
	sprintf(comp,":0%d",endpoint);
	if (strstr(path, comp) != NULL) {
		return 1;
	}
	return 0;
}


NAMESPACE_HMD_END


#endif
