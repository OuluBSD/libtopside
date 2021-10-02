#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN







bool SDL2EventsBase::Initialize(const Script::WorldState& ws) {
	OBJ_CREATE
	
	return true;
}

void SDL2EventsBase::Uninitialize() {
	obj.Clear();
	
}

void SDL2EventsBase::Forward(FwdScope& fwd) {
	TODO
}

void SDL2EventsBase::StorePacket(int sink_ch,  int src_ch, Packet& p) {
	TODO
}

void SDL2EventsBase::Update(double dt) {
	TODO
}

bool SDL2EventsBase::LoadPacket(int ch_i, const Packet& p) {
	TODO
	return ch_i == 0;
}

bool SDL2EventsBase::IsReady(ValDevCls vd) {
	TODO
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
