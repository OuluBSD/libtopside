#include "SoftPhysTests.h"

NAMESPACE_TOPSIDE_BEGIN


#ifdef flagWIN32

double GetMilliseconds() {
	static LARGE_INTEGER s_frequency;
	static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
	if (s_use_qpc) {
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return (double)((1000LL * now.QuadPart) / s_frequency.QuadPart);
	}
	else {
		return GetTickCount();
	}
}

#else

double GetMilliseconds() {
	struct timeval  tv;
	gettimeofday(&tv, NULL);
	static double begin_time;
	double time_in_mill =
	         (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
	
	if (begin_time == 0)
		begin_time = time_in_mill;
	return time_in_mill - begin_time;
}

#endif


NAMESPACE_TOPSIDE_END


#if 0
CONSOLE_APP_MAIN {
	using namespace UPP;
	using namespace TS;
	
	LOG("---- SoftPhysTests Begin ----");
	if (CommandLine().GetCount() != 1)
		return;
	
	int test_i = StrInt(CommandLine()[0]);
	
	One<TestBase> test;
	if      (test_i == 0)	test = new ParticleTest();
	else if (test_i == 1)	test = new ManyTest();
	else if (test_i == 2)	test = new ClothTest();
	else return;
	
	
	test->Initialize(1280, 720);
	
	
	TimeStop ts;
	double timestep = 1.0 / 60.0;
	double total = 0;
	int iter = 0;
	while (total < 5.0) {
		if (ts.Seconds() < timestep)
			continue;
		double dt = ts.ResetSeconds();
		total += dt;
		LOG("Iter " << iter << " time " << total << " update");
		
		test->Update(dt);
		
		test->RenderBegin();
		test->Render();
		test->RenderEnd();
		
		iter++;
	}
	
	test->Shutdown();
	test.Clear();
	
	LOG("---- SoftPhysTests End ----");
}

#endif
