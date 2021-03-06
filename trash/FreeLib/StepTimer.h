#ifndef _FreeLib_StepTimer_h_
#define _FreeLib_StepTimer_h_

NAMESPACE_TOPSIDE_BEGIN


class StepTimer {
	
	
public:
	
	void ResetElapsedTime();
	void Tick(Callback cb);
	double GetElapsedSeconds() const;
	
};


NAMESPACE_TOPSIDE_END

#endif
