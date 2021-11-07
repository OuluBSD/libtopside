#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



#ifdef flagGUI


bool SDL2ScreenBase::Initialize(const Script::WorldState& ws) {
	SetFPS(60);
	OBJ_CREATE
	
	OglBuffer& buf = GetBuffer();
	obj->SetShaderFile(ws.Get(".filepath"));
	obj->SetTestImage(ws.Get(".testimage") == "true");
	obj->SetBuffer(buf);
	
	// OglShaderBase duplicate
	for(int i = 0; i < 4; i++) {
		String key = ".buf" + IntStr(i);
		String value = ws.Get(key);
		if (value.IsEmpty())
			;
		else if (value == "volume")
			buf.SetInputVolume(i);
		else if (value == "cubemap")
			buf.SetInputCubemap(i);
		else
			TODO
	}
	
	AddAtomToUpdateList();
	//AtomBase::GetMachine().template Get<AtomSystem>()->AddPolling(AtomBase::AsRefT());
	GetSink()->GetValue(0).SetMaxQueueSize(1);
	return true;
}

void SDL2ScreenBase::Uninitialize() {
	ev = 0;
	obj.Clear();
	RemoveAtomFromUpdateList();
	//AtomBase::GetMachine().template Get<AtomSystem>()->RemovePolling(AtomBase::AsRefT());
}

bool SDL2ScreenBase::IsReady(PacketIO& io) {
	//dword iface_sink_mask = iface.GetSinkMask();
	//bool b = io.active_sink_mask == iface_sink_mask; // wrong here: only primary is required
	bool b = io.sink[0].filled;
	RTLOG("SDL2ScreenBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink_count << ")");
	return b;
}

bool SDL2ScreenBase::ProcessPackets(PacketIO& io) {
	for(int sink_ch = MAX_VDTUPLE_SIZE-1; sink_ch >= 0; sink_ch--) {
		PacketIO::Sink& sink = io.sink[sink_ch];
		Packet& in = sink.p;
		if (!in)
			continue;
		sink.may_remove = true;
		
		RTLOG("SDL2ScreenBase::ProcessPackets: sink #" << sink_ch << ": " << in->ToString());
		
		if (!obj->Recv(sink_ch, in))
			return false;
		
		if (sink_ch == 0)
			obj->Render(*last_cfg);
	}
	
	int src_ch = 0;
	PacketIO::Sink& prim_sink = io.sink[0];
	PacketIO::Source& src = io.src[src_ch];
	Packet& out = src.p;
	src.from_sink_ch = 0;
	out = ReplyPacket(src_ch, prim_sink.p);
	
	
	#if 0
	Format fmt = p->GetFormat();
	if (fmt.vd == VD(OGL,FBO)) {
		PacketValue& val = *p;
		InternalPacketData& data = val.GetData<InternalPacketData>();
		GetBuffer().StoreOutputLink(data);
	}
	#endif
	
	return true;
}


#endif



NAMESPACE_SERIAL_END
