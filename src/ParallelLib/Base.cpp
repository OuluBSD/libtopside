#include "ParallelLib.h"
#include <Geometry/Geometry.h>
#include <SerialCore/SerialCore.h>

NAMESPACE_PARALLEL_BEGIN


bool CustomerBase::Initialize(const Script::WorldState& ws) {
	RTLOG("CustomerBase::Initialize");
	
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

bool CustomerBase::Recv(int sink_ch, const Packet& in) {
	// pass
	return true;
}

bool CustomerBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
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
	ValDevCls main_vd = type.iface.src.channels[0].vd;
	if (main_vd.dev != DevCls::CENTER) {
		RTLOG("RollingValueBase::Initialize: error: invalid device");
		return false;
	}
	if (main_vd.val == ValCls::AUDIO) {
		internal_fmt = GetDefaultFormat(main_vd);
		internal_fmt.aud.SetSampleRate(777);
		this->SetQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
	}
	else if (main_vd.val == ValCls::VIDEO)
		internal_fmt.SetVideo(DevCls::CENTER, LightSampleFD::U8_LE_ABC, TS::default_width, TS::default_height, 60, 1);
	else
		TODO;
	
	int src_ch = FindSourceWithValDev(VD(CENTER,AUDIO));
	if (src_ch < 0)
		return false;
	
	GetSource()->GetSourceValue(src_ch).SetFormat(internal_fmt);
	
	time = 0;
	return true;
}

bool RollingValueBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	ASSERT(internal_fmt.IsValid());
	
	RTLOG("RollingValueBase::Send: time=" << time);
	
	if (internal_fmt.IsAudio()) {
		int sz = internal_fmt.GetFrameSize();
		Vector<byte>& data = out.Data();
		data.SetCount(sz);
		AudioFormat& afmt = internal_fmt;
		if (afmt.type == TS::Serial::BinarySample::FLT_LE) {
			float* f = (float*)(byte*)data.Begin();
			float* end = f + sz / sizeof(float);
			while (f != end)
				*f++ = rolling_value++ / 255.0f * 2.0f - 1.0f;
		}
		else if (afmt.type == TS::Serial::BinarySample::U16_LE) {
			uint16* f = (uint16*)(byte*)data.Begin();
			uint16* end = f + sz / sizeof(uint16);
			while (f != end)
				*f++ = rolling_value++;
		}
		time += internal_fmt.GetFrameSeconds();
		
		out.time = time;
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
	dbg_limit = ws.GetInt(".dbg_limit", 100);
	
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

bool VoidSinkBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	Panic("Not implemented");
	return false;
}

bool VoidSinkBase::Consume(const void* data, int len) {
	RTLOG("VoidSinkBase::Consume: " << HexStr((size_t)data) << ", len=" << len);
	
	if (fmt.IsAudio()) {
		//ASSERT(out.seq == rolling_value);
		
		AudioFormat& afmt = fmt;
		
		// Verify data
		bool fail = false;
		int dbg_i = 0, dbg_count = 0;
		if (afmt.type == TS::Serial::BinarySample::FLT_LE) {
			float* it = (float*)data;
			float* end = (float*)((byte*)data + len);
			dbg_count = (int)(end - it);
			for (; it != end; ++it, ++dbg_i) {
				float f0 = *it;
				double f1 = rolling_value++ / 255.0 * 2.0 - 1.0;
				if (!IsClose(f0, f1))
					fail = true;
			}
		}
		else if (afmt.type == TS::Serial::BinarySample::U16_LE) {
			uint16* it = (uint16*)data;
			uint16* end = (uint16*)((byte*)data + len);
			dbg_count = (int)(end - it);
			for (; it != end; ++it, ++dbg_i) {
				uint16 u0 = *it;
				uint16 u1 = rolling_value++;
				if (u0 != u1)
					fail = true;
			}
		}
		else {
			LOG("VoidSinkBase::Consume: error: invalid audio format");
		}
		dbg_total_samples += dbg_count;
		dbg_total_bytes += dbg_count * 4;
		dbg_iter++;
		
		if (fail || (dbg_limit > 0 && dbg_iter >= dbg_limit)) {
			GetMachine().SetNotRunning();
			LOG("VoidSinkBase::Consume: stops. total-samples=" << dbg_total_samples << ", total-bytes=" << dbg_total_bytes);
			if (!fail) {LOG("VoidSinkBase::Consume: success!");}
			else       {LOG("VoidSinkBase::Consume: fail :(");}
			if (fail) GetMachine().SetFailed("VoidSinkBase error");
		}
		
		RTLOG("VoidSinkBase::Consume: successfully verified frame");
	}
	
	return true;
}

bool VoidSinkBase::NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) {
	if (new_fmt.IsAudio())
		return true;
	return false;
}

















bool VoidPollerSinkBase::Initialize(const Script::WorldState& ws) {
	RTLOG("VoidPollerSinkBase::Initialize");
	dbg_limit = ws.GetInt(".dbg_limit", 100);
	dt = 1.0/60.0;
	//GetSink()->GetValue(0).SetMinQueueSize(5);
	AddAtomToUpdateList();
	return true;
}

void VoidPollerSinkBase::Uninitialize() {
	LOG("VoidPollerSinkBase::Uninitialize: " << HexStr(this));
	LOG("VoidPollerSinkBase::Uninitialize: total-samples=" << dbg_total_samples << ", total-bytes=" << dbg_total_bytes);
	if (dbg_limit > 0 && dbg_total_samples < dbg_limit)
		fail = true;
	if (!fail) {LOG("VoidPollerSinkBase::Uninitialize: success!");}
	else       {LOG("VoidPollerSinkBase::Uninitialize: fail :(");}
	if (fail) GetMachine().SetFailed("VoidPollerSinkBase error");
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

bool VoidPollerSinkBase::Recv(int sink_ch, const Packet& p) {
	const PacketValue& in = *p;
	
	#if HAVE_PACKETTRACKER
	uint64 route_desc = in.GetRouteDescriptor();
	RTLOG("VoidPollerSinkBase::Recv: sink #0: " << in.ToString() << ", descriptor " << HexStr(route_desc));
	#else
	RTLOG("VoidPollerSinkBase::Recv: sink #0: " << in.ToString());
	#endif
	
	Parallel::Format fmt = in.GetFormat();
	if (fmt.IsAudio()) {
		Serial::AudioFormat& afmt = fmt;
		
		#if HAVE_PACKETTRACKER
		int i = thrds.Find(route_desc);
		if (i < 0) {
			i = thrds.GetCount();
			thrds.Add(route_desc);
			RTLOG("VoidPollerSinkBase::Recv: creating new thread for route " + IntStr64(route_desc));
		}
		#else
		if (thrds.IsEmpty()) thrds.Add(0);
		int i = 0;
		#endif
		
		Thread& t = thrds[i];
		
		const Vector<byte>& data = in.GetData();
		if (data.IsEmpty()) {
			LOG("VoidPollerSinkBase::Recv: error: thrd #" << i << " empty data");
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
				if (!IsClose(f0, f1)) {
					fail = true;
					break;
				}
			}
			dbg_total_samples += dbg_count;
			dbg_total_bytes += dbg_count * 4;
			
			RTLOG("VoidPollerSinkBase::Recv: thrd #" << i << " successfully verified frame size " << data.GetCount());
		}
		else if (afmt.type == TS::Serial::BinarySample::U16_LE) {
			uint16* it = (uint16*)(void*)data.begin();
			uint16* end = (uint16*)(void*)data.end();
			int dbg_i = 0;
			int dbg_count = (int)(end - it);
			for (; it != end; ++it, ++dbg_i) {
				uint16 u0 = *it;
				uint16 u1 = t.rolling_value++;
				if (u0 != u1) {
					fail = true;
					break;
				}
			}
			dbg_total_samples += dbg_count;
			dbg_total_bytes += dbg_count * 4;
			
			RTLOG("VoidPollerSinkBase::Recv: thrd #" << i << " successfully verified frame size " << data.GetCount());
		}
		else {
			LOG("VoidPollerSinkBase::Recv: error: thrd #" << i << " invalid audio format");
			fail = true;
		}
		
		if (dbg_limit > 0 && t.rolling_value >= dbg_limit) {
			GetMachine().SetNotRunning();
			LOG("VoidPollerSinkBase::Recv: stops");
		}
	}
	else {
		RTLOG("VoidPollerSinkBase::Recv: error: unexpected packet " << in.ToString());
		fail = true;
	}
	
	return !fail;
}

bool VoidPollerSinkBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}






#ifdef flagSCREEN

EventStateBase* EventStateBase::latest;
Vector<BinderIfaceEvents*> EventStateBase::binders;

EventStateBase::EventStateBase() {
	latest = this;
}

EnvState& EventStateBase::GetState() const {
	EnvState* s = state.Get();
	ASSERT(s);
	return *s;
}

bool EventStateBase::Initialize(const Script::WorldState& ws) {
	RTLOG("EventStateBase::Initialize");
	
	dbg_limit = ws.GetInt(".dbg_limit", 0);
	if (dbg_limit)
		dbg_print = true;
	
	target = ws.GetString(".target");
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
	
	state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED).SetAll(false);
	state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED_PREVIOUS).SetAll(false);
	
	
	return true;
}

bool EventStateBase::PostInitialize() {
	RTLOG("EventStateBase::PostInitialize");
	
	return true;
}

void EventStateBase::Uninitialize() {
	RTLOG("EventStateBase::Uninitialize");
	
}

void EventStateBase::Update(double dt) {
	FboKbd::KeyVec& data = state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED);
	FboKbd::KeyVec& prev = state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED_PREVIOUS);
	prev = data;
	
}

bool EventStateBase::IsReady(PacketIO& io) {
	dword iface_sink_mask = iface.GetSinkMask();
	bool b = io.active_sink_mask == iface_sink_mask && io.full_src_mask == 0;
	RTLOG("EventStateBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sinks.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

bool EventStateBase::Recv(int sink_ch, const Packet& p) {
	RTLOG("EventStateBase::Recv");
	const PacketValue& in = *p;
	
	Format fmt = in.GetFormat();
	if (fmt.vd.val == ValCls::EVENT) {
		if (in.IsData<CtrlEvent>()) {
			const CtrlEvent& ev = in.GetData<CtrlEvent>();
			Event(ev);
			
			for (BinderIfaceEvents* e : binders)
				e->Dispatch(ev);
		}
		else if (in.IsData<CtrlEventCollection>()) {
			const CtrlEventCollection& evec = in.GetData<CtrlEventCollection>();
			for (const CtrlEvent& ev : evec) {
				Event(ev);
				
				for (BinderIfaceEvents* e : binders)
					e->Dispatch(ev);
			}
		}
		else TODO
	}
	else TODO
	
	return true;
}

bool EventStateBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	RTLOG("EventStateBase::Send");
	return true;
}

void EventStateBase::Event(const CtrlEvent& e) {
	if (dbg_print) {
		LOG(e.ToString());
		if (dbg_limit > 0 && ++dbg_iter > dbg_limit)
			GetMachine().SetNotRunning();
	}
	
	if (e.type == EVENT_INVALID) {
		ASSERT_(0, "EventStateBase::Event: error: sender sent invalid event packet");
	}
	else if (e.type == EVENT_MOUSEMOVE) {
		MouseMove(e.pt, e.value);
	}
	else if (e.type == EVENT_MOUSEWHEEL) {
		MouseWheel(e.pt, e.n, e.value);
	}
	else if (e.type == EVENT_KEYDOWN || e.type == EVENT_KEYUP) {
		Key(e.value, e.n);
	}
	else if (e.type == EVENT_MOUSE_EVENT) {
		switch (e.n) {
			case MOUSE_LEFTDOWN:		LeftDown(e.pt, e.value); break;
			/*case MOUSE_MIDDLEDOWN:		MiddleDown(e.pt, e.value); break;
			case MOUSE_RIGHTDOWN:		RightDown(e.pt, e.value);  break;
			
			case MOUSE_LEFTDOUBLE:		LeftDouble(e.pt, e.value); break;
			case MOUSE_MIDDLEDOUBLE:	MiddleDouble(e.pt, e.value); break;
			case MOUSE_RIGHTDOUBLE:		RightDouble(e.pt, e.value); break;
			
			case MOUSE_LEFTTRIPLE:		LeftTriple(e.pt, e.value); break;
			case MOUSE_MIDDLETRIPLE:	MiddleTriple(e.pt, e.value); break;
			case MOUSE_RIGHTTRIPLE:		RightTriple(e.pt, e.value); break;*/
			
			case MOUSE_LEFTUP:			LeftUp(e.pt, e.value); break;
			/*case MOUSE_MIDDLEUP:		MiddleUp(e.pt, e.value); break;
			case MOUSE_RIGHTUP:			RightUp(e.pt, e.value); break;*/
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
	else if (e.type == EVENT_HOLO_STATE) {
		ASSERT(e.trans || e.ctrl);
		EnvState& s = GetState();
		if (e.trans) {
			s.Set<TransformMatrix>(HMD_CAMERA) = *e.trans;
		}
		
		if (e.ctrl) {
			s.Set<ControllerMatrix>(HMD_CONTROLLER) = *e.ctrl;
		}
		
		
		#if 0
		for(int c = 0; c < ControllerMatrix::CTRL_COUNT; c++) {
			ControllerMatrix::Ctrl& ctrl = e3.ctrl[c];
			if (!ctrl.is_enabled)
				continue;
			
			quat rot;
			vec3 pos;
			COPY4(rot.data, ctrl.rot);
			COPY3(pos.data, ctrl.pos);
			//LOG("EventStateBase::Event: ctrl #" << c << ": rotation " << rot.ToString() << ", position " << pos.ToString());
			
			for(int i = 0; i < ControllerMatrix::VALUE_COUNT; i++) {
				ControllerMatrix::Value t = (ControllerMatrix::Value)i;
				
				if (ctrl.is_value[t]) {
					float f = ctrl.value[t];
					if (i == ControllerMatrix::TRIGGER) {
						// what even is this?
					}
					else TODO
				}
			}
		}
		#endif
	}
	else if(e.type == EVENT_HOLO_LOOK ||
			e.type == EVENT_HOLO_CALIB ||
			e.type == EVENT_HOLO_CONTROLLER_DETECTED ||
			e.type == EVENT_HOLO_CONTROLLER_LOST ||
			e.type == EVENT_HOLO_MOVE_FAR_RELATIVE ||
			e.type == EVENT_HOLO_MOVE_NEAR ||
			e.type == EVENT_HOLO_MOVE_CONTROLLER ||
			e.type == EVENT_HOLO_PRESSED ||
			e.type == EVENT_HOLO_RELEASED ||
			e.type == EVENT_HOLO_UPDATED) {
		// TODO, but pass
	}
	else TODO
}

void EventStateBase::MouseWheel(Point pt, int zdelta, dword keyflags) {
	EnvState& s = GetState();
	
	SetInt(MOUSE_MOUSEWHEEL, zdelta);
	int& mouse_iter = s.GetInt(MOUSE_STATE_ITER);
	mouse_iter++;
	
	Point& pos = s.Set<Point>(MOUSE_POSITION);
	const Size& video_size = s.Set<Size>(SCREEN0_SIZE);
	const Point& video_offset = s.Set<Point>(SCREEN0_OFFSET);
	pos.x =                 video_offset.x + pt.x;
	pos.y = video_size.cy - video_offset.y - pt.y;
}

void EventStateBase::LeftDown(Point pt, dword keyflags) {
	EnvState& s = GetState();
	
	SetBool(MOUSE_LEFTDOWN, true);
	
	Point& drag = s.Set<Point>(MOUSE_TOYCOMPAT_DRAG);
	Point& click = s.Set<Point>(MOUSE_TOYCOMPAT_CLICK);
	const Size& video_size = s.Set<Size>(SCREEN0_SIZE);
	const Point& video_offset = s.Set<Point>(SCREEN0_OFFSET);
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
	const Size& video_size = s.Set<Size>(SCREEN0_SIZE);
	const Point& video_offset = s.Set<Point>(SCREEN0_OFFSET);
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
	
	key = ToLower(key);
	
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


void EventStateBase::AddBinder(BinderIfaceEvents* iface) {
	VectorFindAdd(binders, iface);
}
                                      
void EventStateBase::RemoveBinder(BinderIfaceEvents* iface) {
	VectorRemoveKey(binders, iface);
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
	
	bool succ = sent_count >= 2;
	if (succ) {LOG("TestEventSrcBase::Uninitialize: success! " << sent_count << " packets sent");}
	else       {LOG("TestEventSrcBase::Uninitialize: fail :(");}
	if (!succ) GetMachine().SetFailed("TestEventSrcBase error");
}

bool TestEventSrcBase::IsReady(PacketIO& io) {
	return true;
}

bool TestEventSrcBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	RTLOG("TestEventSrcBase::Send");
	Format out_fmt = out.GetFormat();
	
	ASSERT(out_fmt.vd.val == ValCls::EVENT);
	if (out_fmt.vd.val == ValCls::EVENT) {
		CtrlEvent& ev = out.SetData<CtrlEvent>();
		RandomizeEvent(ev);
		ev.trans = &trans;
		ev.ctrl = &ctrl;
		sent_count++;
		return true;
	}
	
	return false;
}









NAMESPACE_PARALLEL_END
