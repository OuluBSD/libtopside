NAMESPACE_TOPSIDE_BEGIN


TMPL_DEVMACH(void) DevStreamState::Clear() {
	time.Set(0);
	total_time.Reset();
	time_us = 0;
	
	#define IFACE(cls, var) var.Clear();
	IFACE_VAR_LIST
	#undef IFACE
}

TMPL_DEVMACH(void) DevStreamState::Reset() {
	total_time.Reset();
	time_us = 0;
	#define IFACE(cls, var) var.Reset();
	IFACE_VAR_LIST
	#undef IFACE
}

TMPL_DEVMACH(void) DevStreamState::UpdateValuesBase() {
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

TMPL_DEVMACH(void) DevStreamState::UpdateValues(TypeCls val_spec) {
	
}

NAMESPACE_TOPSIDE_END
