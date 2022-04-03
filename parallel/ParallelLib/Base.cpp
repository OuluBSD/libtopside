#include "ParallelLib.h"


NAMESPACE_PARALLEL_BEGIN


bool CustomerBase::Initialize(const Script::WorldState& ws) {
	RTLOG("CustomerBase::Initialize");
	
	/*AtomTypeCls type = GetType();
	if (type.iface.content.val == ValCls::AUDIO)
		packet_thrds = 10;*/
	
	customer.Create();
	
	return true;
}

bool CustomerBase::PostInitialize() {
	packet_thrds = GetSink()->GetValue(0).GetMinPackets();
	
	return true;
}

void CustomerBase::Uninitialize() {
	
}

void CustomerBase::UpdateConfig(double dt) {
	ASSERT(customer);
	DefaultInterfaceSourceRef src = this->GetSource();
	ASSERT(src);
	if (src) {
		int count = src->GetSourceCount();
		bool any_full = false;
		for(int i = 0; i < count; i++) {
			Value& val = src->GetSourceValue(i);
			any_full = any_full || val.IsQueueFull();
		}
		customer->cfg.Update(dt, any_full);
	}
}

bool CustomerBase::ProcessPacket(PacketValue& in, PacketValue& out) {
	// pass
	return true;
}

bool CustomerBase::IsForwardReady() {
	return packet_count < packet_thrds;
}

void CustomerBase::ForwardPacket(PacketValue& in, PacketValue& out) {
	InternalPacketData& data = out.template SetData<InternalPacketData>();
	data.pos = 0;
	data.count = 1;
	
	packet_count++;
}












bool RollingValueBase::Initialize(const Script::WorldState& ws) {
	AtomTypeCls type = ((AtomBase*)this)->GetType();
	ValDevCls main_vd = type.iface.src();
	if (main_vd.dev != DevCls::CENTER) {
		RTLOG("RollingValueBase::Initialize: error: invalid device");
		return false;
	}
	if (main_vd.val == ValCls::AUDIO)
		internal_fmt.SetAudio(DevCls::CENTER, SoundSample::U8_LE, 2, 44100, 777);
	else if (main_vd.val == ValCls::VIDEO)
		internal_fmt.SetVideo(DevCls::CENTER, LightSampleFD::U8_LE_ABC, 1280, 720, 60, 1);
	else
		TODO;
	
	int src_ch = FindSourceWithValDev(VD(CENTER,AUDIO));
	if (src_ch < 0)
		return false;
	
	GetSource()->GetSourceValue(src_ch).SetFormat(internal_fmt);
	
	time = 0;
	return true;
}

bool RollingValueBase::ProcessPacket(PacketValue& in, PacketValue& out) {
	ASSERT(internal_fmt.IsValid());
	
	RTLOG("RollingValueBase::ProcessPacket: time=" << time);
	
	if (internal_fmt.IsAudio()) {
		int sz = internal_fmt.GetFrameSize();
		Vector<byte>& data = out.Data();
		data.SetCount(sz);
		for(byte& dst : data)
			dst = rolling_value++;
		
		time += internal_fmt.GetFrameSeconds();
	}
	else if (internal_fmt.IsVideo()) {
		TODO
	}
	else {
		Panic("invalid internal format");
		return false;
	}
	return true;
}







bool VoidSinkBase::Initialize(const Script::WorldState& ws) {
	//DUMP(ws);
	String dbg_limit_str = ws.Get(".dbg_limit");
	if (!dbg_limit_str.IsEmpty())
		dbg_limit = ScanInt(dbg_limit_str);
	
	return true;
}

bool VoidSinkBase::PostInitialize() {
	InterfaceSinkRef sink = GetSink();
	const int sink_ch_i = sink->GetSinkCount() - 1;
	Value& sink_value = sink->GetValue(sink_ch_i);
	fmt = sink_value.GetFormat();
	
	return true;
}

void VoidSinkBase::Uninitialize() {
	
}

bool VoidSinkBase::ProcessPacket(PacketValue& in, PacketValue& out) {
	Panic("Not implemented");
	return false;
}

bool VoidSinkBase::Consume(const void* data, int len) {
	
	if (fmt.IsAudio()) {
		AudioFormat& afmt = fmt;
		
		// Verify data
		bool fail = false;
		if (afmt.type == TS::Serial::BinarySample::FLT_LE) {
			float* it = (float*)data;
			float* end = (float*)((byte*)data + len);
			int dbg_i = 0;
			int dbg_count = (int)(end - it);
			for (; it != end; ++it, ++dbg_i) {
				float f0 = *it;
				double f1 = rolling_value++ / 255.0 * 2.0 - 1.0;
				if (!IsClose(f0, f1))
					fail = true;
			}
			dbg_total_samples += dbg_count;
			dbg_total_bytes += dbg_count * 4;
			dbg_iter++;
			
			if (fail || (dbg_limit > 0 && dbg_iter >= dbg_limit)) {
				GetMachine().SetNotRunning();
				LOG("IntervalPipeLink::IntervalSinkProcess: stops. total-samples=" << dbg_total_samples << ", total-bytes=" << dbg_total_bytes);
				if (!fail) {LOG("IntervalPipeLink::IntervalSinkProcess: success!");}
				else       {LOG("IntervalPipeLink::IntervalSinkProcess: fail :(");}
			}
			
			RTLOG("IntervalPipeLink::IntervalSinkProcess: successfully verified frame");
		}
		else {
			LOG("IntervalPipeLink::IntervalSinkProcess: error: invalid audio format");
		}
	}
	
	return true;
}


















bool VoidPollerSinkBase::Initialize(const Script::WorldState& ws) {
	RTLOG("VoidPollerSinkBase::Initialize");
	dt = 1.0/60.0;
	GetSink()->GetValue(0).SetMinQueueSize(5);
	AddAtomToUpdateList();
	return true;
}

void VoidPollerSinkBase::Uninitialize() {
	LOG("VoidPollerSinkBase::Uninitialize: " << HexStr(this));
	LOG("VoidPollerSinkBase::Uninitialize: total-samples=" << dbg_total_samples << ", total-bytes=" << dbg_total_bytes);
	if (!dbg_total_samples)
		fail = true;
	if (!fail) {LOG("VoidPollerSinkBase::Uninitialize: success!");}
	else       {LOG("VoidPollerSinkBase::Uninitialize: fail :(");}
	RemoveAtomFromUpdateList();
}

void VoidPollerSinkBase::Update(double dt) {
	ts += dt;
	RTLOG("VoidPollerSinkBase::Update: dt=" + DblStr(dt) + ", ts=" << DblStr(ts));
	if (ts >= dt)
		PostContinueForward();
}

bool VoidPollerSinkBase::IsReady(PacketIO& io) {
	bool b = false;
	if (ts >= dt) {
		ts = 0;
		b = true;
	}
	RTLOG("VoidPollerSinkBase::IsReady: " << (b ? "true " : "false ") << BinStr(io.active_sink_mask));
	return b;
}

bool VoidPollerSinkBase::ProcessPacket(PacketValue& in, PacketValue& out) {
	uint64 route_desc = out.GetRouteDescriptor();
	
	RTLOG("VoidPollerSinkBase::ProcessPacket: sink #0: " << in.ToString() << ", descriptor " << HexStr(route_desc));
	
	Parallel::Format fmt = in.GetFormat();
	if (fmt.IsAudio()) {
		Serial::AudioFormat& afmt = fmt;
		
		int i = thrds.Find(route_desc);
		if (i < 0) {
			i = thrds.GetCount();
			thrds.Add(route_desc);
			RTLOG("VoidPollerSinkBase::ProcessPacket: creating new thread for route " + IntStr64(route_desc));
		}
		
		Thread& t = thrds[i];
		const Vector<byte>& data = in.GetData();
		if (data.IsEmpty()) {
			LOG("VoidPollerSinkBase::ProcessPacket: error: thrd #" << i << " empty data");
			fail = true;
		}
		else if (afmt.type == TS::Serial::BinarySample::FLT_LE) {
			float* it = (float*)(void*)data.begin();
			float* end = (float*)(void*)data.end();
			int dbg_i = 0;
			int dbg_count = (int)(end - it);
			for (; it != end; ++it, ++dbg_i) {
				float f0 = *it;
				double f1 = t.rolling_value++ / 255.0 * 2.0 - 1.0;
				ASSERT(IsClose(f0, f1));
				if (!IsClose(f0, f1)) {
					fail = true;
					break;
				}
			}
			dbg_total_samples += dbg_count;
			dbg_total_bytes += dbg_count * 4;
			
			RTLOG("VoidPollerSinkBase::ProcessPacket: thrd #" << i << " successfully verified frame size " << data.GetCount());
		}
		else {
			LOG("VoidPollerSinkBase::ProcessPacket: error: thrd #" << i << " invalid audio format");
			fail = true;
		}
	}
	else {
		RTLOG("VoidPollerSinkBase::ProcessPacket: error: unexpected packet " << in.ToString());
		fail = true;
	}
	
	return true;
}







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
	
	Space& s = GetParent();
	state = s.FindNearestState(target);
	if (!state) {
		LOG("EventStateBase::Initialize: error: state '" << target << "' not found in parent space: " << s.GetDeepName());
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

bool EventStateBase::ProcessPacket(PacketValue& in, PacketValue& out) {
	RTLOG("EventStateBase::ProcessPacket");
	
	TODO
	
	/*if (io.sink_count == 1) {
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
	}*/
	
	return true;
}

void EventStateBase::Event(const CtrlEvent& e) {
	/*if (e.type == EVENT_MOUSEMOVE) {
		MouseMove(e.pt, e.value);
	}
	else if (e.type == EVENT_MOUSEWHEEL) {
		TODO
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
	else*/ TODO
}

void EventStateBase::LeftDown(Point pt, dword keyflags) {
	EnvState& s = GetState();
	
	TODO
	/*SetBool(MOUSE_LEFTDOWN, true);
	
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
	}*/
}

void EventStateBase::LeftUp(Point pt, dword keyflags) {
	EnvState& s = GetState();
	
	TODO
	/*SetBool(MOUSE_LEFTDOWN, false);
	
	Point& drag = s.Set<Point>(MOUSE_TOYCOMPAT_DRAG);
	drag.y = -drag.y;*/ // observed behaviour
}

void EventStateBase::MouseMove(Point pt, dword keyflags) {
	EnvState& s = GetState();
	
	TODO
	/*Point& drag = s.Set<Point>(MOUSE_TOYCOMPAT_DRAG);
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
	}*/
}

bool EventStateBase::Key(dword key, int count) {
	EnvState& s = GetState();
	
	TODO
	/*FboKbd::KeyVec& data = s.Set<FboKbd::KeyVec>(KEYBOARD_PRESSED);
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
	*/
	return true;
}










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

bool TestEventSrcBase::ProcessPacket(PacketValue& in, PacketValue& out) {
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









NAMESPACE_PARALLEL_END
