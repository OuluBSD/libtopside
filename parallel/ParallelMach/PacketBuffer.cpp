#include "ParallelMach.h"

NAMESPACE_PARALLEL_BEGIN


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









bool PacketBufferBase::HasPacketOverTime(double time) const {
	//int dbg_i = 0;
	for (Packet& p : buf) {
		if (p->time <= time) {
			//LOG("PacketBufferBase::HasPacketOverTime: #" << dbg_i << ": " << p->time << " <= " << time);
			return true;
		}
		//dbg_i++;
	}
	return false;
}

bool PacketBufferBase::StorePacket(PacketValue& p) {
	if (buf.GetCount()) {
		Packet n = buf.First();
		buf.RemoveFirst();
		p.Pick(*n);
		return true;
	}
	
	return false;
}

bool PacketBufferBase::StorePacket(PacketValue& p, double min_time) {
	int rem_count = 0;
	bool found = false;
	for (Packet& n : buf) {
		rem_count++;
		double t = n->GetTime();
		if (t >= min_time) {
			p.Pick(*n);
			ASSERT(p.GetTime() == t);
			found = true;
			break;
		}
	}
	if (!found && !buf.IsEmpty()) {
		Packet& n = buf.Top();
		p.Pick(*n);
		found = true;
	}
	buf.RemoveFirst(rem_count);
	return found;
}










int PacketValue::GetSizeChannelSamples() const {
	int div = fmt.GetScalar() * fmt.GetSampleSize();
	ASSERT(div > 0);
	return data.GetCount() / div;
}

void PacketValue::Pick(PacketValue& p) {
	Swap(data, p.data);
	p.data.Clear();
	fmt = p.fmt;
	// no offset: offset = p.offset;
	id = p.id;
	custom_data = p.custom_data;
	route_descriptor = p.route_descriptor;
	seq = p.seq;
}






/*void PacketValue::StopTracking(TrackerInfo info) {TODO}
void PacketTracker_Track(const char* fn, const char* file, int line, PacketValue& p) {TODO}
void PacketTracker_Checkpoint(const char* fn, const char* file, int line, PacketValue& p) {TODO}
void PacketTracker_StopTracking(const char* fn, const char* file, int line, PacketValue& p) {TODO}*/

NAMESPACE_PARALLEL_END
