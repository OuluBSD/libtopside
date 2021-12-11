#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN


bool CustomerBase::Initialize(const Script::WorldState& ws) {
	RTLOG("CustomerBase::Initialize");
	
	AtomTypeCls type = GetType();
	
	//if (type.iface.content.val == ValCls::AUDIO)
	//	packet_thrds = 10;
	
	AtomBase::packets_forwarded = 0;
	customer.Create();
	AtomBaseRef r = AtomBase::AsRefT();
	ASSERT(r);
	AtomSystemRef as = AtomBase::GetMachine().template Get<AtomSystem>();
	as->AddCustomer(r);
	
	return true;
}

bool CustomerBase::PostInitialize() {
	packet_thrds = GetSink()->GetValue(0).GetMinPackets();
	
	return true;
}

void CustomerBase::Uninitialize() {
	AtomBaseRef r = AtomBase::AsRefT();
	ASSERT(r);
	AtomBase::GetMachine().template Get<AtomSystem>()->RemoveCustomer(r);
}

void CustomerBase::UpdateConfig(double dt) {
	ASSERT(customer);
	DefaultInterfaceSourceRef src = this->GetSource();
	ASSERT(src);
	if (src) {
		int count = src->GetSourceCount();
		for(int i = 0; i < count; i++) {
			Value& val = src->GetSourceValue(i);
			customer->cfg.Update(dt, val.IsQueueFull());
		}
	}
}

void CustomerBase::Forward(FwdScope& fwd) {
	//RTLOG("CustomerBase::Forward");
	
	while (packet_count < packet_thrds) {
		RTLOG("CustomerBase::Forward: create packet");
		InterfaceSinkRef sink_iface = GetSink();
		
		int sink_count = sink_iface->GetSinkCount();
		ASSERT(sink_count == 1);
		
		Value&			sink_val = sink_iface->GetValue(0);
		PacketBuffer&	sink_buf = sink_val.GetBuffer();
		Format			fmt = sink_val.GetFormat();
		
		off32 init_off(&off_gen, 0);
		Packet p = CreatePacket(init_off);
		p->SetFormat(fmt);
		p->seq = -1;
		
		InternalPacketData& data = p->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = 1;
		
		//PacketTracker::Track(TrackerInfo("CustomerBase::Forward", __FILE__, __LINE__), *p);
		sink_val.GetBuffer().Add(p);
		
		packet_count++;
	}
	
}

bool CustomerBase::ProcessPackets(PacketIO& io) {
	RTLOG("CustomerBase::ProcessPackets");
	
	PacketIO::Sink& sink = io.sink[0];
	PacketIO::Source& src = io.src[0];
	
	ASSERT(sink.p);
	PacketTracker::StopTracking(TrackerInfo("CustomerBase::Forward", __FILE__, __LINE__), *sink.p);
	
	sink.may_remove = true;
	src.from_sink_ch = 0;
	src.p = sink.p;
	src.p->SetFormat(src.val->GetFormat());
	src.p->SetOffset(off_gen.Create());
	
	
	PacketTracker::Track(TrackerInfo("CustomerBase::Forward", __FILE__, __LINE__), *src.p);
	
	return true;
}




JoinerBase::JoinerBase() {
	
}

bool JoinerBase::Initialize(const Script::WorldState& ws) {
	
	return true;
}

void JoinerBase::Uninitialize() {
	
}

bool JoinerBase::IsReady(PacketIO& io) {
	RTLOG("JoinerBase::IsReady: " << BinStr(io.active_sink_mask));
	// require primary and single side channel
	int src_ch_count = GetSink()->GetSinkCount();
	if (!(io.active_sink_mask & 1))
		return false;
	for(int i = 1; i < src_ch_count; i++)
		if (io.active_sink_mask & (1 << i))
			return true;
	return false;
}

bool JoinerBase::ProcessPackets(PacketIO& io) {
	ASSERT(io.active_sink_mask & 0x0001);
	ASSERT(io.nonempty_sinks >= 2);
	ASSERT(io.src_count == 1);
	PacketIO::Sink& prim_sink = io.sink[0];
	
	int side_sink_ch = -1;
	for (int tries = 0; tries < 3; tries++) {
		int sink_ch = scheduler_iter;
		
		scheduler_iter++;
		if (scheduler_iter >= io.sink_count)
			scheduler_iter = 1;
		
		if (io.sink[sink_ch].p) {
			side_sink_ch = sink_ch;
			break;
		}
	}
	
	ASSERT(side_sink_ch >= 0);
	if (side_sink_ch < 0) return false;
	
	PacketIO::Sink& sink = io.sink[side_sink_ch];
	
	RTLOG("JoinerBase::ProcessPackets: forward packet from sink #" << side_sink_ch << " to src #0: " << sink.p->ToString());
	prim_sink.may_remove = true;
	sink.may_remove = true;
	PacketIO::Source& src = io.src[0];
	
	src.from_sink_ch = side_sink_ch;
	src.p = sink.p;
	
	src.p->SetOffset(prim_sink.p->GetOffset());
	
	return true;
}




SplitterBase::SplitterBase() {
	
}

bool SplitterBase::Initialize(const Script::WorldState& ws) {
	
	return true;
}

void SplitterBase::Uninitialize() {
	
}

bool SplitterBase::IsReady(PacketIO& io) {
	bool b = io.full_src_mask == 0;
	
	RTLOG("JoinerBase::IsReady: " << (b ? "true " : "false ") << BinStr(io.full_src_mask));
	
	return b;
}

bool SplitterBase::ProcessPackets(PacketIO& io) {
	ASSERT(io.src_count > 1 && io.sink_count == 1);
	ASSERT(io.active_sink_mask == 0x0001);
	PacketIO::Sink& sink = io.sink[0];
	sink.may_remove = true;
	
	PacketIO::Source& prim_src = io.src[0];
	prim_src.from_sink_ch = 0;
	prim_src.p = ReplyPacket(0, sink.p);
	
	Format in_fmt = sink.p->GetFormat();
	
	InterfaceSourceRef src_iface = GetSource();
	for(int i = 1; i < io.src_count; i++) {
		PacketIO::Source& src = io.src[i];
		Format src_fmt = src_iface->GetSourceValue(i).GetFormat();
		if (src_fmt.IsCopyCompatible(in_fmt)) {
			src.from_sink_ch = 0;
			src.p = sink.p;
		}
		else {
			src.p = CreatePacket(sink.p->GetOffset());
			src.p->SetFormat(src_fmt);
			src.p->CopyRouteData(*sink.p);
			if (Convert(sink.p, src.p)) {
				RTLOG("SplitterBase::ProcessPackets: converted packet: " << src.p->ToString());
			}
			else {
				RTLOG("SplitterBase::ProcessPackets: packet conversion failed from " << sink.p->ToString());
				src.p.Clear();
				return false;
			}
		}
	}
	
	return true;
}

#if 0
void SplitterBase::StorePacket(int sink_ch,  int src_ch, const Packet& in, Packet& out) {
	if (src_ch > 0) {
		Format in_fmt = in->GetFormat();
		Format src_fmt = GetSource()->GetSourceValue(src_ch).GetFormat();
		if (in_fmt.IsCopyCompatible(src_fmt)) {
			out = in;
			RTLOG("SplitterBase::StorePacket: active copy-compatible packet: " << out->ToString());
		}
		else {
			out = CreatePacket(in->GetOffset());
			out->SetFormat(src_fmt);
			if (Convert(in, out)) {
				RTLOG("SplitterBase::StorePacket: active converted packet: " << out->ToString());
				out->CopyRouteData(*in);
				out->AddRouteData(sink_ch);
			}
			else {
				RTLOG("SplitterBase::StorePacket: packet conversion failed from " << in->ToString());
				out.Clear();
			}
		}
	}
	else {
		RTLOG("SplitterBase::StorePacket: default reply");
		out = ReplyPacket(src_ch, in);
	}
}

#endif














TestEventSrcBase::TestEventSrcBase() {
	
}

bool TestEventSrcBase::Initialize(const Script::WorldState& ws) {
	RTLOG("TestEventSrcBase::Initialize");
	return true;
}

void TestEventSrcBase::Uninitialize() {
	RTLOG("TestEventSrcBase::Uninitialize");
	
}

bool TestEventSrcBase::IsReady(PacketIO& io) {
	return true;
}

bool TestEventSrcBase::ProcessPackets(PacketIO& io) {
	TODO
	#if 0
	RTLOG("TestEventSrcBase::ProcessPackets");
	return true;
	#endif
}

#if 0
void TestEventSrcBase::StorePacket(int sink_ch,  int src_ch, const Packet& in, Packet& out) {
	RTLOG("TestEventSrcBase::StorePacket");
	
	TODO
	
	Format fmt = in->GetFormat();
	ASSERT(fmt.vd.val == ValCls::EVENT);
	if (fmt.vd.val == ValCls::EVENT) {
		CtrlEvent& ev = out->SetData<CtrlEvent>();
		RandomizeEvent(ev);
	}
	
}
#endif










EventStateBase::EventStateBase() {
	
}

EnvState& EventStateBase::GetState() const {
	EnvState* s = state.Get();
	ASSERT(s);
	return *s;
}

bool EventStateBase::Initialize(const Script::WorldState& ws) {
	RTLOG("EventStateBase::Initialize");
	
	target = ws.Get(".target");
	if (target.IsEmpty()) {
		LOG("EventStateBase::Initialize: error: target state argument is required");
		return false;
	}
	
	Loop& loop = GetParent();
	state = loop.FindNearestState(target);
	if (!state) {
		LOG("EventStateBase::Initialize: error: state '" << target << "' not found in parent loop: " << loop.GetDeepName());
		return false;
	}
	
	FboKbd::KeyVec& data = state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED);
	data.SetAll(false);
	
	return true;
}

bool EventStateBase::PostInitialize() {
	RTLOG("EventStateBase::PostInitialize");
	
	return true;
}

void EventStateBase::Uninitialize() {
	RTLOG("EventStateBase::Uninitialize");
	
}

bool EventStateBase::IsReady(PacketIO& io) {
	dword iface_sink_mask = iface.GetSinkMask();
	bool b = io.active_sink_mask == iface_sink_mask && io.full_src_mask == 0;
	RTLOG("EventStateBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink_count << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

bool EventStateBase::ProcessPackets(PacketIO& io) {
	RTLOG("EventStateBase::ProcessPackets");
	
	if (io.sink_count == 1) {
		Event(io.sink[0].p->GetData<CtrlEvent>());
		
		PacketIO::Sink& sink = io.sink[0];
		PacketIO::Source& src = io.src[0];
		
		ASSERT(sink.p);
		sink.may_remove = true;
		src.from_sink_ch = 0;
		src.p = ReplyPacket(0, sink.p);
	}
	else {
		TODO
	}
	
	return true;
}

void EventStateBase::Event(const CtrlEvent& e) {
	if (e.type == EVENT_MOUSEMOVE) {
		MouseMove(e.pt, e.value);
	}
	else if (e.type == EVENT_KEYDOWN || e.type == EVENT_KEYUP) {
		Key(e.value, e.n);
	}
	else if (e.type == EVENT_MOUSE_EVENT) {
		switch (e.n) {
			case Ctrl::LEFTDOWN:		LeftDown(e.pt, e.value);break;
			case Ctrl::MIDDLEDOWN:		break;
			case Ctrl::RIGHTDOWN:		break;
			
			case Ctrl::LEFTDOUBLE:		break;
			case Ctrl::MIDDLEDOUBLE:	break;
			case Ctrl::RIGHTDOUBLE:	break;
			
			case Ctrl::LEFTTRIPLE:		break;
			case Ctrl::MIDDLETRIPLE:	break;
			case Ctrl::RIGHTTRIPLE:		break;
			
			case Ctrl::LEFTUP:			LeftUp(e.pt, e.value); break;
			case Ctrl::MIDDLEUP:		break;
			case Ctrl::RIGHTUP:			break;
		}
	}
	else if (e.type == EVENT_WINDOW_RESIZE) {
		Size& video_size = GetState().Set<Size>(SCREEN0_SIZE);
		video_size = e.sz;
	}
	else if (e.type == EVENT_SHUTDOWN) {
		bool& close_window = GetState().Set<bool>(SCREEN0_CLOSE);
		close_window = true;
	}
	else TODO
}

void EventStateBase::LeftDown(Point pt, dword keyflags) {
	EnvState& s = GetState();
	
	SetBool(MOUSE_LEFTDOWN, true);
	
	Point& drag = s.Set<Point>(MOUSE_TOYCOMPAT_DRAG);
	Point& click = s.Set<Point>(MOUSE_TOYCOMPAT_CLICK);
	Size& video_size = s.Set<Size>(SCREEN0_SIZE);
	Point& video_offset = s.Set<Point>(SCREEN0_OFFSET);
	if (video_size.cx > 0 && video_size.cy > 0) {
		drag.x =                 video_offset.x + pt.x;
		drag.y = video_size.cy - video_offset.y - pt.y;
		click.x = +drag.x;
		click.y = -drag.y;
	} else {
		drag.x = 0;
		drag.y = video_size.cy;
		click.x = 0;
		click.y = -drag.y;
	}
}

void EventStateBase::LeftUp(Point pt, dword keyflags) {
	EnvState& s = GetState();
	
	SetBool(MOUSE_LEFTDOWN, false);
	
	Point& drag = s.Set<Point>(MOUSE_TOYCOMPAT_DRAG);
	drag.y = -drag.y; // observed behaviour
}

void EventStateBase::MouseMove(Point pt, dword keyflags) {
	EnvState& s = GetState();
	
	Point& drag = s.Set<Point>(MOUSE_TOYCOMPAT_DRAG);
	Point& click = s.Set<Point>(MOUSE_TOYCOMPAT_CLICK);
	Size& video_size = s.Set<Size>(SCREEN0_SIZE);
	Point& video_offset = s.Set<Point>(SCREEN0_OFFSET);
	if (s.GetBool(MOUSE_LEFTDOWN)) {
		if (video_size.cx > 0 && video_size.cy > 0) {
			drag.x =                 video_offset.x + pt.x;
			drag.y = video_size.cy - video_offset.y - pt.y;
		}
		else {
			drag.x = 0;
			drag.y = video_size.cy;
		}
	}
}

bool EventStateBase::Key(dword key, int count) {
	EnvState& s = GetState();
	
	FboKbd::KeyVec& data = s.Set<FboKbd::KeyVec>(KEYBOARD_PRESSED);
	int& keyboard_iter = s.GetInt(KEYBOARD_STATE_ITER);
	
	bool is_key_down = true;
	bool is_lalt = false;
	bool is_lshift = false;
	bool is_lctrl = false;
	if (key & K_KEYUP) {
		key &= ~K_KEYUP;
		is_key_down = false;
	}
	if (key & K_ALT) {
		key &= ~K_ALT;
		is_lalt = true;
	}
	if (key & K_SHIFT) {
		key &= ~K_SHIFT;
		is_lshift = true;
	}
	if (key & K_CTRL) {
		key &= ~K_CTRL;
		is_lctrl = true;
	}
	
	key = ToUpper(key);
	
	if (key >= 0 && key < FboKbd::key_tex_w) {
		if (key > 0)
			data[key] = is_key_down;
		data[16] = is_lshift;
		data[17] = is_lctrl;
		data[18] = is_lalt;
		keyboard_iter++;
	}
	
	return true;
}


NAMESPACE_SERIAL_END
