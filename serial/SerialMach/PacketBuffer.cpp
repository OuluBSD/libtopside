#include "SerialMach.h"

NAMESPACE_SERIAL_BEGIN


String TrackerInfo::ToString() const {
	String s;
	
	if (handler_cls)
		s << "@" << handler_cls->GetDynamicName();
	if (handler_fn)
		s << "::" << handler_fn;
	
	if (file && line)
		s << " (" << file << ":" << IntStr(line) << ")";
	else if (file)
		s << " (" << file << ")";
	
	if (s.IsEmpty())
		s = "<no info>";
	return s;
}




void ValStreamState::Clear() {
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

void ValStreamState::Reset() {
	frame_time.Reset();
	total_seconds = 0;
	frame_seconds = 0;
	last_sync_sec = 0;
	frames = 0;
	frames_after_sync = 0;
}

void ValStreamState::Step() {
	frames++;
	frame_time.Reset();
}










void PacketBufferBase::StorePacket(Packet& p) {
	if (buf.GetCount()) {
		Packet n = buf.First();
		buf.RemoveFirst();
		
		n->SetOffset(p->GetOffset());
		p = n;
	}
}











int PacketValue::GetSizeChannelSamples() const {
	int div = fmt.GetArea() * fmt.GetSampleSize();
	ASSERT(div > 0);
	return data.GetCount() / div;
}



NAMESPACE_SERIAL_END
