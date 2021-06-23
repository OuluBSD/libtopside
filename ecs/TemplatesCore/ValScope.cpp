#include "TemplatesCore.h"


NAMESPACE_ECS_BEGIN


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

void PacketTracker::Track0(TrackerInfo info, PacketValue& p) {
	ASSERT(p.GetTrackingId() == 0);
	p.SetTrackingId(id_counter++);
	RTLOG("PacketTracker: packet(" + IntStr(p.GetTrackingId()) + ") tracking begins (" + info.ToString() + ") " + p.ToString());
}

void PacketTracker::Checkpoint0(TrackerInfo info, PacketValue& p) {
	RTLOG("PacketTracker: packet(" + IntStr(p.GetTrackingId()) + ") checkpoint (" + info.ToString() + ") " + p.ToString());
	
}

void PacketTracker::StopTracking0(TrackerInfo info, PacketValue& p) {
	RTLOG("PacketTracker: packet(" + IntStr(p.GetTrackingId()) + ") tracking ends (" + info.ToString() + ") " + p.ToString());
	
}





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

NAMESPACE_ECS_END
