#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



#ifdef flagGUI


bool SDL2ScreenBase::AltInitialize(const Script::WorldState& ws) {
	SetFPS(60);
	OBJ_CREATE
	
	OglBuffer& buf = GetBuffer();
	buf.SetBufferId(ws.Get(".name"));
	obj->SetShaderFile(ws.Get(".filepath"));
	obj->SetTestImage(ws.Get(".testimage") == "true");
	obj->SetBuffer(buf);
	
	AtomBase::GetMachine().template Get<AtomSystem>()->AddUpdated(AtomBase::AsRefT());
	return true;
}

void SDL2ScreenBase::AltUninitialize() {
	ev = 0;
	obj.Clear();
	AtomBase::GetMachine().template Get<AtomSystem>()->RemoveUpdated(AtomBase::AsRefT());
}

void SDL2ScreenBase::AltUpdate(double dt) {
	frame_age += dt;
	RTLOG("SDL2ScreenBase::AltUpdate: dt: " << dt << ", frame_age: " << frame_age);
}

void SDL2ScreenBase::AltForward(FwdScope& fwd) {
	AtomTypeCls type = GetType();
	if (type.IsRoleSide())
		return;
	
	const int sink_ch_i = 0;
	
	InterfaceSinkRef sink_iface = GetSink();
	int sink_ch_count = sink_iface->GetSinkCount();
	bool all_sink_filled = true;
	for(int i = 0; i < sink_ch_count; i++) {
		Value& sink_val = sink_iface->GetValue(i);
		if (sink_val.GetQueueSize() == 0) {
			all_sink_filled = false;
			break;
		}
	}
	if (!all_sink_filled)
		return;
	
	RTLOG("SDL2ScreenBase::AltForward: frame_age: " << frame_age);
	
	if (frame_age >= dt) {
		RTLOG("SDL2ScreenBase::AltForward: render");
		if (frame_age >= 2 * dt)
			frame_age = 0;
		else
			frame_age -= dt;
		
		bool fail = false;
		for(int i = 0; i < sink_ch_count; i++) {
			Value& sink_val = sink_iface->GetValue(i);
			PacketBuffer& sink_buf = sink_val.GetBuffer();
			
			Packet p = sink_buf.First();
			sink_buf.RemoveFirst();
			if (!i)
				PacketConsumed(p);
			
			LoadPacket(i, p);
			//if (!obj->Recv(i, p))
			//	fail = true;
		}
		
		if (fail) {
			RTLOG("SDL2ScreenBase::AltForward: error: some packet(s) failed to load");
		}
	}
	else {
		RTLOG("SDL2ScreenBase::AltForward: wait");
	}
	
}

bool SDL2ScreenBase::IsReady(ValDevCls vd) {
	if (frame_age >= dt) {
		RTLOG("SDL2ScreenBase::AltForward: render");
		if (frame_age >= 2 * dt)
			frame_age = 0;
		else
			frame_age -= dt;
		return true;
	}
	return false;
}

void SDL2ScreenBase::LoadPacket(int ch_i, const Packet& p) {
	Format fmt = p->GetFormat();
	if (fmt.vd == VD(ACCEL,VIDEO)) {
		PacketValue& val = *p;
		InternalPacketData& data = val.GetData<InternalPacketData>();
		GetBuffer().LoadOutputLink(data);
	}
	
	obj->Recv(ch_i, p);
}

void SDL2ScreenBase::AltStorePacket(int sink_ch,  int src_ch, Packet& p) {
	RTLOG("SDL2ScreenBase::AltStorePacket");
	if (sink_ch == 0 && src_ch == 0) {
		obj->Render(*last_cfg);
		
	}
	
	#if 0
	Format fmt = p->GetFormat();
	if (fmt.vd == VD(ACCEL,VIDEO)) {
		PacketValue& val = *p;
		InternalPacketData& data = val.GetData<InternalPacketData>();
		GetBuffer().StoreOutputLink(data);
	}
	#endif
}


#endif



NAMESPACE_SERIAL_END
