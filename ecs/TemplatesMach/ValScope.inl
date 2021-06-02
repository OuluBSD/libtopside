#define TMPL(x)	template <class Spec> x ScopeValMachT<Spec>::

NAMESPACE_TOPSIDE_BEGIN






TMPL(void) StreamState::Clear() {
	fmt.Clear();
	sink_frame = 0;
	is_sync = 0;
	
	frame_time.Reset();
	total_seconds = 0;
	frame_seconds = 0;
	last_sync_sec = 0;
	frames = 0;
	frames_after_sync = 0;
}

TMPL(void) StreamState::Reset() {
	frame_time.Reset();
	total_seconds = 0;
	frame_seconds = 0;
	last_sync_sec = 0;
	frames = 0;
	frames_after_sync = 0;
}








#undef TMPL

NAMESPACE_TOPSIDE_END
