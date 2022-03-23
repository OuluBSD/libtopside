#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN


bool SDL2EventsBase::Initialize(const Script::WorldState& ws) {
	OBJ_CREATE
	
	AddAtomToUpdateList();
	return true;
}

void SDL2EventsBase::Uninitialize() {
	RemoveAtomFromUpdateList();
	obj.Clear();
}

void SDL2EventsBase::Update(double dt) {
	time += dt;
}

bool SDL2EventsBase::IsReady(PacketIO& io) {
	bool b = io.full_src_mask == 0;
	if (b) {
		if (seq == 0) {
			ev.type = EVENT_WINDOW_RESIZE;
			#ifdef flagSCREEN
			OOSDL2::OglScreen* screen = obj->GetContext()->FindContextConnector<OOSDL2::OglScreen>();
			if (screen) {
				ev.sz = screen->GetSize();
				ev_sendable = true;
			}
			else {
				RTLOG("SDL2EventsBase::IsReady: skipping windows resize, because no screen is in context");
				seq++;
				b = false;
			}
			#endif
		}
		else if (obj->Poll(ev)) {
			ev_sendable = true;
		}
		else {
			ev_sendable = false;
			b = false;
		}
	}
	RTLOG("SDL2EventsBase::IsReady: " << (b ? "true" : "false"));
	return b;
}

bool SDL2EventsBase::ProcessPackets(PacketIO& io) {
	ASSERT(ev_sendable);
	if (!ev_sendable) return false;
	
	PacketIO::Sink& sink = io.sink[0];
	Packet& in = sink.p;
	ASSERT(in); if (!in) return false;
	sink.may_remove = true;
	
	RTLOG("SDL2ImageBase::ProcessPackets: sink #0: " << in->ToString());
	
	if (io.src_count == 1) {
		PacketIO::Source& src = io.src[0];
		Packet& out = src.p;
		src.from_sink_ch = 0;
		
		out = ReplyPacket(0, sink.p);
		
		PacketValue& v = *out;
		v.seq = seq++;
		
		/*Format fmt = v.GetFormat();
		ASSERT(fmt.IsEvent());
		
		v.SetFormat(fmt);*/
		
		UPP::CtrlEvent& dst = v.SetData<UPP::CtrlEvent>();
		dst = ev;
	}
	else {
		ASSERT(io.src_count >= 2);
		PacketIO::Source& prim_src = io.src[0];
		Packet& prim_out = prim_src.p;
		prim_src.from_sink_ch = 0;
		prim_out = ReplyPacket(0, sink.p);
		
		ASSERT(io.src_count >= 2);
		PacketIO::Source& src = io.src[1];
		Packet& out = src.p;
		src.from_sink_ch = 0;
		
		out = ReplyPacket(1, sink.p);
		
		PacketValue& v = *out;
		v.seq = seq++;
		
		/*Format fmt = v.GetFormat();
		ASSERT(fmt.IsEvent());
		
		v.SetFormat(fmt);*/
		
		UPP::CtrlEvent& dst = v.SetData<UPP::CtrlEvent>();
		dst = ev;
	}
	
	ev_sendable = false;
	
	return true;
}


#if 0
bool SDL2EventsBase::ProcessPackets(PacketIO& io) {
	return true;
}
#endif

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
