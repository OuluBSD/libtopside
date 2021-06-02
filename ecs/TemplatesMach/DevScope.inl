NAMESPACE_TOPSIDE_BEGIN


TMPL_DEVMACH(void) DevStream::Clear() {
	time.Set(0);
	total_time.Reset();
	time_us = 0;
	
	#define IFACE(cls, var) var.Clear();
	IFACE_VAR_LIST
	#undef IFACE
}

TMPL_DEVMACH(void) DevStream::Reset() {
	total_time.Reset();
	time_us = 0;
	#define IFACE(cls, var) var.Reset();
	IFACE_VAR_LIST
	#undef IFACE
}


NAMESPACE_TOPSIDE_END
