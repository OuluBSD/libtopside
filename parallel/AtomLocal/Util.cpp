#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN









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
