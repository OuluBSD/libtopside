#ifndef _OpenLib_StepTimer_h_
#define _OpenLib_StepTimer_h_

NAMESPACE_OULU_BEGIN


class StepTimer {
	
	
public:
	
	
	
	void ResetElapsedTime();
	void Tick(Callback cb);
	double GetElapsedSeconds() const;
	
};


NAMESPACE_OULU_END

#endif
