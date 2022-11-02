#include "SerialCore.h"


NAMESPACE_PARALLEL_BEGIN

#if HAVE_PACKETTRACKER
void PacketValue::CheckTracking(TrackerInfo info) {
	if (id == 0)
		return;
	
	PacketTracker::Checkpoint(info, *this);
}

void PacketValue::StopTracking(TrackerInfo info) {
	if (id == 0)
		return;
	
	PacketTracker::StopTracking(info, *this);
}
#endif

String PacketValue::ToString() const {
	String s;
	s.Cat('{');
	s << "offset: " << offset.ToString();
	s << ", size: " << data.GetCount();
	#if HAVE_PACKETTRACKER
	s << ", id: " << IntStr64(id);
	#endif
	s << ", format: {" << fmt.ToString() << "}";
	
	s.Cat('}');
	return s;
}

String PacketValue::ToStringWithHash() const {
	String s;
	s.Cat('{');
	s << "offset: " << offset.ToString();
	s << ", size: " << data.GetCount();
	#if HAVE_PACKETTRACKER
	s << ", id: " << IntStr64(id);
	#endif
	s << ", format: {" << fmt.ToString() << "}";
	s << ", hash: " << IntStr64(GetDataHash());
	
	s.Cat('}');
	return s;
}

hash_t PacketValue::GetDataHash() const {
	return data.GetHashValue();
}

#if HAVE_OPENGL

bool PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

#endif


NAMESPACE_PARALLEL_END

NAMESPACE_SERIAL_BEGIN


bool PacketTracker::Initialize() {
	if (!active_tracker())
		active_tracker() = this;
	return true;
}

void PacketTracker::Start() {
	
}

void PacketTracker::Update(double dt) {
	
}

void PacketTracker::Stop() {
	
}

void PacketTracker::Uninitialize() {
	if (active_tracker() == this)
		active_tracker() = 0;
	
}

#if HAVE_PACKETTRACKER
void PacketTracker::Track0(TrackerInfo info, PacketValue& p) {
	ASSERT(p.GetTrackingId() == 0);
	p.SetTrackingId(id_counter++);
	RTLOG("PacketTracker: packet(" + p.GetOffset().ToString() + "," + IntStr(p.GetTrackingId()) + ") tracking begins (" + info.ToString() + ") " + p.ToString());
}

void PacketTracker::Checkpoint0(TrackerInfo info, PacketValue& p) {
	RTLOG("PacketTracker: packet(" + p.GetOffset().ToString() + "," + IntStr(p.GetTrackingId()) + ") checkpoint (" + info.ToString() + ") " + p.ToString());
	
}

void PacketTracker::StopTracking0(TrackerInfo info, PacketValue& p) {
	RTLOG("PacketTracker: packet(" + p.GetOffset().ToString() + "," + IntStr(p.GetTrackingId()) + ") tracking ends (" + info.ToString() + ") " + p.ToString());
	p.SetTrackingId(0);
}

#endif


#if HAVE_PACKETTRACKER
void PacketTracker_Track(const char* fn, const char* file, int line, PacketValue& p) {
	PacketTracker::Track(TrackerInfo(fn, file, line), p);
}

void PacketTracker_Checkpoint(const char* fn, const char* file, int line, PacketValue& p) {
	PacketTracker::Checkpoint(TrackerInfo(fn, file, line), p);
}

void PacketTracker_StopTracking(const char* fn, const char* file, int line, PacketValue& p) {
	PacketTracker::StopTracking(TrackerInfo(fn, file, line), p);
}
#else
void PacketTracker_Track(const char* fn, const char* file, int line, PacketValue& p) {}
void PacketTracker_Checkpoint(const char* fn, const char* file, int line, PacketValue& p) {}
void PacketTracker_StopTracking(const char* fn, const char* file, int line, PacketValue& p) {}
#endif



NAMESPACE_SERIAL_END
