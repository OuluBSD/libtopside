#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN


bool SDL2EventsBase::LocalStream::IsOpen() const {
	TODO
}

bool SDL2EventsBase::LocalStream::Open(int fmt_idx) {
	TODO
}







bool SDL2EventsBase::AltInitialize(const Script::WorldState& ws) {
	OBJ_CREATE
	
	return true;
}

void SDL2EventsBase::AltUninitialize() {
	obj.Clear();
	
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
