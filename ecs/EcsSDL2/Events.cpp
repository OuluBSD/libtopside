#include "EcsSDL2.h"

NAMESPACE_TOPSIDE_BEGIN


bool SDL2EventsComponent::LocalStream::IsOpen() const {
	TODO
}

bool SDL2EventsComponent::LocalStream::Open(int fmt_idx) {
	TODO
}







void SDL2EventsComponent::Initialize() {
	OBJ_CREATE
	
	EventSystemRef ev_sys = GetEntity()->GetMachine().Get<EventSystem>();
	if (ev_sys)
		ev_sys -> Add(AsRef<EventSource>());
}

void SDL2EventsComponent::Uninitialize() {
	obj.Clear();
	
	EventSystemRef ev_sys = GetEntity()->GetMachine().Get<EventSystem>();
	if (ev_sys)
		ev_sys->Remove(AsRef<EventSource>());
}

CtrlEvent& SDL2EventsComponent::AddTmpEvent() {
	static const int ev_sz = sizeof(CtrlEvent);
	int off = tmp_events.GetCount();
	tmp_events.SetCount(off + ev_sz);
	byte* pos = tmp_events.Begin() + off;
	CtrlEvent& ev = *(CtrlEvent*)pos;
	ev.Clear();
	return ev;
}

bool SDL2EventsComponent::ReadFrame() {
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

bool SDL2EventsComponent::ProcessFrame() {
	if (!tmp_events.IsEmpty()) {
		EventPacket p = CreateEventPacket();
		p->SetFormat(EventFormat(EventSample::CTRL_EVENT, 1));
		MemSwap(p->Data(), tmp_events);
		value.AddPacket(p);
		return true;
	}
	return false;
}



NAMESPACE_TOPSIDE_END
