#include "EcsSDL2.h"

NAMESPACE_TOPSIDE_BEGIN


bool SDL2EventsComponent::LocalDeviceStream::IsOpen() const {
	TODO
}

bool SDL2EventsComponent::LocalDeviceStream::Open(int fmt_idx) {
	TODO
}







void SDL2EventsComponent::Initialize() {
	OBJ_CREATE
	
	DeviceSystemRef ev_sys = GetEntity()->GetMachine().Get<DeviceSystem>();
	if (ev_sys)
		ev_sys -> Add(AsRef<DeviceSource>());
}

void SDL2EventsComponent::Uninitialize() {
	obj.Clear();
	
	DeviceSystemRef ev_sys = GetEntity()->GetMachine().Get<DeviceSystem>();
	if (ev_sys)
		ev_sys->Remove(AsRef<DeviceSource>());
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

bool SDL2EventsComponent::ProcessDeviceFrame() {
	if (!tmp_events.IsEmpty()) {
		DevicePacket p = CreateDevicePacket();
		p->SetFormat(DeviceFormat(DeviceSample::S_CTRL_EVENT, 1));
		MemSwap(p->Data(), tmp_events);
		value.AddPacket(p);
		return true;
	}
	return false;
}



NAMESPACE_TOPSIDE_END
