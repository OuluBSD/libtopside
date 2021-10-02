#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



#ifdef flagGUI


bool SDL2ScreenBase::Initialize(const Script::WorldState& ws) {
	SetFPS(60);
	OBJ_CREATE
	
	OglBuffer& buf = GetBuffer();
	buf.SetBufferId(ws.Get(".name"));
	obj->SetShaderFile(ws.Get(".filepath"));
	obj->SetTestImage(ws.Get(".testimage") == "true");
	obj->SetBuffer(buf);
	
	AtomBase::GetMachine().template Get<AtomSystem>()->AddUpdated(AtomBase::AsRefT());
	GetSink()->GetValue(0).SetMaxQueueSize(1);
	return true;
}

void SDL2ScreenBase::Uninitialize() {
	ev = 0;
	obj.Clear();
	AtomBase::GetMachine().template Get<AtomSystem>()->RemoveUpdated(AtomBase::AsRefT());
}

#if 0

void SDL2ScreenBase::Update(double dt) {
	frame_age += dt;
	RTLOG("SDL2ScreenBase::Update: dt: " << dt << ", frame_age: " << frame_age);
}

void SDL2ScreenBase::Forward(FwdScope& fwd) {
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
	
	RTLOG("SDL2ScreenBase::Forward: frame_age: " << frame_age);
	
	if (frame_age >= dt) {
		RTLOG("SDL2ScreenBase::Forward: render");
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
			RTLOG("SDL2ScreenBase::Forward: error: some packet(s) failed to load");
		}
	}
	else {
		RTLOG("SDL2ScreenBase::Forward: wait");
	}
	
}

bool SDL2ScreenBase::IsReady(ValDevCls vd) {
	if (frame_age >= dt) {
		RTLOG("SDL2ScreenBase::Forward: render");
		if (frame_age >= 2 * dt)
			frame_age = 0;
		else
			frame_age -= dt;
		return true;
	}
	return false;
}

#endif

/*bool SDL2ScreenBase::PassLoadPacket(int sink_ch, const Packet& p) {
	Format fmt = p->GetFormat();
	return fmt.vd.val == ValCls::VIDEO;
}*/

bool SDL2ScreenBase::LoadPacket(int sink_ch, const Packet& p) {
	RTLOG("SDL2ScreenBase::LoadPacket: sink #" << sink_ch << " " << p->ToString());
	return obj->Recv(sink_ch, p);
}

void SDL2ScreenBase::StorePacket(int sink_ch,  int src_ch, Packet& p) {
	RTLOG("SDL2ScreenBase::StorePacket: " << sink_ch << ", " << src_ch << ": " << p->ToString());
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
