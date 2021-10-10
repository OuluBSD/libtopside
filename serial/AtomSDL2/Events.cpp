#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN


bool SDL2EventsBase::Initialize(const Script::WorldState& ws) {
	OBJ_CREATE
	
	return true;
}

void SDL2EventsBase::Uninitialize() {
	obj.Clear();
}

void SDL2EventsBase::StorePacket(int sink_ch, int src_ch, const Packet& in, Packet& out) {
	RTLOG("SDL2EventsBase::StorePacket: sink #" << sink_ch << ", src #" << src_ch << ": " << in->ToString());
	
	ASSERT(ev_sendable);
	
	TODO
	
}

void SDL2EventsBase::Update(double dt) {
	TODO
}

bool SDL2EventsBase::LoadPacket(int sink_ch, const Packet& in, Vector<int>& fwd_src_chs) {
	return true;
}

bool SDL2EventsBase::IsReady(dword active_iface_mask) {
	if (obj->Poll(ev)) {
		ev_sendable = true;
		return true;
	}
	else {
		ev_sendable = false;
	}
	return false;
}

CtrlEvent& SDL2EventsBase::AddTmpEvent() {
	static const int ev_sz = sizeof(CtrlEvent);
	int off = tmp_events.GetCount();
	tmp_events.SetCount(off + ev_sz);
	byte* pos = tmp_events.Begin() + off;
	CtrlEvent& ev = *(CtrlEvent*)pos;
	ev.Clear();
	return ev;
}

bool SDL2EventsBase::ReadFrame() {
	if (obj) {
		tmp_events.SetCount(0);
		
		while (true) {
			CtrlEvent& e = AddTmpEvent();
			if (!obj->Poll(e))
				break;
			if (e.type == EVENT_SHUTDOWN) {
				GetMachine().SetNotRunning();
			}
		}
	}
	return !tmp_events.IsEmpty();
}

bool SDL2EventsBase::ProcessFrame() {
	if (!tmp_events.IsEmpty()) {
		TODO
		#if 0
		Packet p = CreatePacket();
		p->SetFormat(EventFormat(AsTypeCls<CenterSpec>(), EventSample::CTRL_EVENT, 1));
		MemSwap(p->Data(), tmp_events);
		value.AddPacket(p);
		#endif
		return true;
	}
	return false;
}


NAMESPACE_SERIAL_END
