#include "TemplatesMach.h"


NAMESPACE_ECS_BEGIN


void DevStreamState::Clear() {
	time.Set(0);
	total_time.Reset();
	time_us = 0;
	
	TODO
	/*#define IFACE(cls, var) var.Clear();
	IFACE_VAR_LIST
	#undef IFACE*/
}

void DevStreamState::Reset() {
	total_time.Reset();
	time_us = 0;
	
	TODO
	/*#define IFACE(cls, var) var.Reset();
	IFACE_VAR_LIST
	#undef IFACE*/
}

void DevStreamState::UpdateValuesBase() {
	time = GetSysTime();
	#ifdef flagWIN32
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		time_us = time.wMilliseconds * 1000;
	}
	#else
	{
		struct timeval start;
		gettimeofday(&start, NULL);
		time_us = start.tv_usec;
	}
	#endif
}

void DevStreamState::UpdateValues(TypeCls val_spec) {
	
}

/*#define DEV(x) \
	using x##Source		= typename ScopeDevMachT<x##Spec>::DevSource; \
	using x##SourceRef	= typename ScopeDevMachT<x##Spec>::DevSourceRef; \
	using x##Sink		= typename ScopeDevMachT<x##Spec>::DevSink; \
	using x##SinkRef	= typename ScopeDevMachT<x##Spec>::DevSinkRef;
DEV_LIST
#undef DEV*/

NAMESPACE_ECS_END
