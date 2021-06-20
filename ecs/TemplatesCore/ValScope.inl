NAMESPACE_TOPSIDE_BEGIN


TMPL_VALCORE(bool) PacketTracker::Initialize() {
	if (!active_tracker())
		active_tracker() = this;
	return true;
}

TMPL_VALCORE(void) PacketTracker::Start() {
	
}

TMPL_VALCORE(void) PacketTracker::Update(double dt) {
	
}

TMPL_VALCORE(void) PacketTracker::Stop() {
	
}

TMPL_VALCORE(void) PacketTracker::Uninitialize() {
	if (active_tracker() == this)
		active_tracker() = 0;
	
}

TMPL_VALCORE(void) PacketTracker::Track0(TrackerInfo info, PacketValue& p) {
	ASSERT(p.GetTrackingId() == 0);
	p.SetTrackingId(id_counter++);
	RTLOG(ValSpec::GetName() + "PacketTracker: packet(" + IntStr(p.GetTrackingId()) + ") tracking begins (" + info.ToString() + ") " + p.ToString());
}

TMPL_VALCORE(void) PacketTracker::Checkpoint0(TrackerInfo info, PacketValue& p) {
	RTLOG(ValSpec::GetName() + "PacketTracker: packet(" + IntStr(p.GetTrackingId()) + ") checkpoint (" + info.ToString() + ") " + p.ToString());
	
}

TMPL_VALCORE(void) PacketTracker::StopTracking0(TrackerInfo info, PacketValue& p) {
	RTLOG(ValSpec::GetName() + "PacketTracker: packet(" + IntStr(p.GetTrackingId()) + ") tracking ends (" + info.ToString() + ") " + p.ToString());
	
}


TMPL_VALMACH(void) PacketValue::CheckTracking(TrackerInfo info) {
	using Core = ScopeValCoreT<ValSpec>;
	using PacketTracker = typename Core::PacketTracker;
	
	if (id == 0)
		return;
	
	PacketTracker::Checkpoint(info, *this);
}

TMPL_VALMACH(void) PacketValue::StopTracking(TrackerInfo info) {
	using Core = ScopeValCoreT<ValSpec>;
	using PacketTracker = typename Core::PacketTracker;
	
	if (id == 0)
		return;
	
	PacketTracker::StopTracking(info, *this);
}

NAMESPACE_TOPSIDE_END
