#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN


#ifdef flagSCREEN


bool SDL2SwScreenBase::Initialize(const Script::WorldState& ws) {
	SetFPS(60);
	OBJ_CREATE
	
	AddAtomToUpdateList();
	GetSink()->GetValue(0).SetMaxQueueSize(1);
	return true;
}

void SDL2SwScreenBase::Uninitialize() {
	ev = 0;
	obj.Clear();
	RemoveAtomFromUpdateList();
}

bool SDL2SwScreenBase::ProcessPackets(PacketIO& io) {
	PacketIO::Sink& sink = io.sink[0];
	PacketIO::Source& src = io.src[0];
	Packet& in = sink.p;
	Packet& out = src.p;
	sink.may_remove = true;
	src.from_sink_ch = 0;
	out = ReplyPacket(0, sink.p);
	
	RTLOG("SDL2SwScreenBase::ProcessPackets: sink #0 " << in->ToString());
	
	if (!obj->Recv(0, in))
		return false;
	
	obj->Render();
	
	return true;
}


#endif


NAMESPACE_SERIAL_END
