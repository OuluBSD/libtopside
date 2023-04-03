#include "ParallelMach.h"

NAMESPACE_PARALLEL_BEGIN


#if HAVE_PACKETTRACKER
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
#endif



#if HAVE_PACKETTIMING
MAKE_STATIC(PacketTimingManager, timemgr);


PacketTimingManager::PacketTimingManager() {
	
}

PacketTimingManager::~PacketTimingManager() {
	
}

PacketTimingManager& PacketTimingManager::Local() {
	return timemgr;
}

float PacketTimingManager::Get() const {
	float s = (float)ts.Seconds();
	ASSERT(s > 0.0f);
	return s;
}

#endif


	
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
		buf.EnterWrite();
		Packet n = buf.First();
		buf.RemoveFirst();
		buf.LeaveWrite();
		p.Pick(*n);
		return true;
	}
	
	return false;
}

bool PacketBufferBase::StorePacket(PacketValue& p, double min_time) {
	buf.EnterWrite();
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
	buf.LeaveWrite();
	return found;
}










PacketValue::~PacketValue() {
	data.Clear();
	#if HAVE_PACKETTRACKER
	StopTracking(this);
	#endif
}

void PacketValue::Clear() {
	data.SetCount(0);
	fmt.Clear();
	offset.Clear();
	time = 0;
	custom_data = AsVoidTypeCls();
	#if HAVE_PACKETTRACKER
	id = 0;
	#endif
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
	custom_data = p.custom_data;
	seq = p.seq;
	#if HAVE_PACKETTRACKER
	id = p.id;
	route_descriptor = p.route_descriptor;
	#endif
}

#if HAVE_PACKETTIMINGCHECK
void PacketValue::CheckTiming() {
	float time = timemgr.Get();
	if (limit_time != 0 && time > limit_time) {
		LOG(ToString());
		float overtime = time - limit_time;
		Panic("error: packet took " + DblStr(overtime) + "s too long!");
	}
}

void PacketValue::SetTimingLimit(float duration_sec) {
	begin_time = timemgr.Get();
	limit_time = begin_time + duration_sec;
}
#endif

#if HAVE_PACKETTIMING
void PacketValue::SetAge(float sec) {
	begin_time = sec;
}

void PacketValue::SetBeginTime() {
	begin_time = timemgr.Get();
	ASSERT(begin_time > 0);
}

void PacketValue::CopyTiming(const PacketValue& v) {
	begin_time = v.begin_time;
#if HAVE_PACKETTIMINGCHECK
	limit_time = v.limit_time;
#endif
}

double PacketValue::GetAge() const {
	if (begin_time != 0) {
		float time = timemgr.Get();
		return time - begin_time;
	}
	return 0;
}

double PacketValue::GetBeginTime() const {
	return begin_time;
}

#endif


NAMESPACE_PARALLEL_END
