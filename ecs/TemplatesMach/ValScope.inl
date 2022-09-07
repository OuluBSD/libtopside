NAMESPACE_TOPSIDE_BEGIN











TMPL_VALMACH(String) PacketValue::ToString() const {
	String s;
	s.Cat('{');
	s << "size: " << data.GetCount();
	s << ", id: " << IntStr64(id);
	s<< ", format: {" << fmt.ToString() << "}";
	
	s.Cat('}');
	return s;
}







TMPL_VALMACH(void) ValStreamState::Clear() {
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

TMPL_VALMACH(void) ValStreamState::Reset() {
	frame_time.Reset();
	total_seconds = 0;
	frame_seconds = 0;
	last_sync_sec = 0;
	frames = 0;
	frames_after_sync = 0;
}

TMPL_VALMACH(void) ValStreamState::Step() {
	frames++;
	frame_time.Reset();
}



NAMESPACE_TOPSIDE_END
