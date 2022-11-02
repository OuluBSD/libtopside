#include "LocalHMD.h"

#ifdef flagWIN32


NAMESPACE_HMD_BEGIN


double GetTick()
{
	double high, low;
	FILETIME filetime;

	GetSystemTimeAsFileTime(&filetime);

	high = filetime.dwHighDateTime;
	low = filetime.dwLowDateTime;

	return (high * 4294967296.0 + low) / 10000000;
}

static const uint64 NUM_10_000_000 = 10000000;

void InitMonotonic(Context* ctx)
{
	ctx->monotonic_ticks_per_sec = NUM_10_000_000;
}

uint64 GetMonotonic(Context* ctx)
{
	FILETIME filetime;
	GetSystemTimeAsFileTime(&filetime);

	return ((uint64)filetime.dwHighDateTime << 32) | filetime.dwLowDateTime;
}

// TODO higher resolution
void SleepSeconds(double seconds)
{
	Sleep((DWORD)(seconds * 1000));
}

// threads

struct Thread {
	HANDLE handle;
	void* arg;
	unsigned int (*Routine)(void* arg);
};

struct Mutex {
	HANDLE handle;
};

DWORD __stdcall Thread_wrapper(void* t)
{
	Thread* thread = (Thread*)t;
	return thread->routine(thread->arg);
}

Thread* CreateThread(Context* ctx, unsigned int (*routine)(void* arg), void* arg)
{
	Thread* thread = lhmd_alloc(ctx, sizeof(Thread));
	if(!thread)
		return NULL;

	thread->routine = routine;
	thread->arg = arg;

	thread->handle = CreateThread(NULL, 0, Thread_wrapper, thread, 0, NULL);

	return thread;
}

void DestroyThread(Thread* thread)
{
	SleepSeconds(3);
	WaitForSingleObject(thread->handle, INFINITE);
	CloseHandle(thread->handle);
	free(thread);
}

Mutex* CreateMutex(Context* ctx)
{
	Mutex* mutex = lhmd_alloc(ctx, sizeof(Mutex));
	if(!mutex)
		return NULL;
	
	mutex->handle = CreateMutex(NULL, FALSE, NULL);

	return mutex;
}

void DestroyMutex(Mutex* mutex)
{
	CloseHandle(mutex->handle);
	free(mutex);
}

void EnterMutex(Mutex* mutex)
{
	if(mutex)
		WaitForSingleObject(mutex->handle, INFINITE);
}

void LeaveMutex(Mutex* mutex)
{
	if(mutex)
		ReleaseMutex(mutex->handle);
}

int FindEndPoint(char* path, int endpoint)
{
	char comp[8];
	sprintf(comp,"mi_0%d",endpoint);

	if (strstr(path, comp) != NULL) {
		return 1;
	}

	return 0;
}

/// Handling ovr service
static int _enable_ovr_service = 0;

void ToggleOvrService(int state) //State is 0 for Disable, 1 for Enable
{
	SC_HANDLE serviceDbHandle = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
	SC_HANDLE serviceHandle = OpenService(serviceDbHandle, "OVRService", SC_MANAGER_ALL_ACCESS);

	SERVICE_STATUS_PROCESS status;
	DWORD bytesNeeded;
	QueryServiceStatusEx(serviceHandle, SC_STATUS_PROCESS_INFO,(LPBYTE) &status,sizeof(SERVICE_STATUS_PROCESS), &bytesNeeded);

	if (state == 0 || status.dwCurrentState == SERVICE_RUNNING)
	{
		// Stop it
		BOOL b = ControlService(serviceHandle, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS) &status);
		if (b)
		{
			printf("OVRService stopped\n");
			_enable_ovr_service = 1;
		}
		else
			printf("Error: OVRService failed to stop, please try running with Administrator rights\n");
	}
	else if (state == 1 && _enable_ovr_service)
	{
		// Start it
		BOOL b = StartService(serviceHandle, 0, NULL);
		if (b)
			printf("OVRService started\n");
		else
			printf("Error: OVRService failed to start, please try running with Administrator rights\n");
	}
	CloseServiceHandle(serviceHandle);
	CloseServiceHandle(serviceDbHandle);
}


NAMESPACE_HMD_END


#endif
