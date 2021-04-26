#include "FusionCore.h"

NAMESPACE_OULU_BEGIN


void FusionControllerSink::Initialize() {
	data_res = Size(256, 256);
	data.SetCount(data_res.cx * data_res.cy, 0);
	stream.Clear();
	
	FusionComponent::Initialize();
	
}

void FusionControllerSink::Uninitialize() {
	
	FusionComponent::Uninitialize();
}

void FusionControllerSink::Reset() {
	// pass
}

void FusionControllerSink::PreProcess() {
#ifdef flagOPENGL
	if (changed && data.GetCount() && color_buf[0] > 0) {
		changed = false;
		glBindTexture(GL_TEXTURE_2D, color_buf[0]);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data_res.cx, data_res.cy, GL_RED, GL_UNSIGNED_BYTE, data.Begin());
		glBindTexture(GL_TEXTURE_2D, 0);
	}
#endif
}

void FusionControllerSink::ClearData() {
	// pass
}

void FusionControllerSink::UpdateTexBuffers() {
	auto* stream = Stream();
	if (stream) {
		ClearTex();
		if (data_res.cx > 0 && data_res.cy > 0) {
#ifdef flagOPENGL
			Ogl_CreateTex(
				data_res, 1,
				0, 0,
				FusionComponentInput::FILTER_NEAREST,
				FusionComponentInput::WRAP_CLAMP);
#endif
		}
	}
}

bool FusionControllerSink::LoadResources() {
	// pass
	return true;
}

bool FusionControllerSink::LoadAsInput(const FusionComponentInput& in) {
	const char* fn_name = "LoadAsInput";
	Entity& e = GetEntity();
	Machine& m = e.GetMachine();
	Ref<EventSystem> ev_sys = m.TryGet<EventSystem>();
	if (ev_sys.IsEmpty())
		return false;
	
	String err;
	
	cfg.SetHeader(in);
	stream.sz = data_res;
	stream.depth = 0;
	
	TODO
	#if 0
	Ref<Connector> conn = GetEntity().GetConnector();
	if (!conn) {
		OnError(fn_name, "entity doesn't have Connector component");
		return false;
	}
	
	if (in.GetFusionType() == FusionComponentInput::KEYBOARD) {
		bool found_any = false;
		for (ControllerSource* src : ev_sys->GetSources()) {
			if (src->IsSupportedKeyboard()) {
				if (src->LinkManually(*this)) {
					conn->SetUpdateInterfaces(true);
					
					UpdateTexBuffers();
					return true;
				}
				else {
					err = "couldn't link MultiMediaComponent to FusionMediaSink";
				}
			}
		}
		if (found_any)
			return true;
		
		err = "could not find any keyboard sources";
	}
	else {
		err = "unsupported type";
	}
	#endif
	
	if (err.IsEmpty()) err = "unknown error";
	OnError(fn_name, err);
	return false;
}

void FusionControllerSink::RecvController(const EventFrame& e) {
	for (const CtrlEvent& ev : e.ctrl)
		Event(ev);
}

void FusionControllerSink::Event(const CtrlEvent& e) {
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
}

void FusionControllerSink::LeftDown(Point pt, dword keyflags) {
	FusionStream* s = Stream();
	if (!s) return;
	
	is_left_down = true;
	
	Point& drag = s->mouse_toycompat_drag;
	Point& click = s->mouse_toycompat_click;
	if (s->video_size.cx > 0 && s->video_size.cy > 0) {
		drag.x =                    s->video_offset.x + pt.x;
		drag.y = s->video_size.cy - s->video_offset.y - pt.y;
		click.x = +drag.x;
		click.y = -drag.y;
	} else {
		drag.x = 0;
		drag.y = s->video_size.cy;
		click.x = 0;
		click.y = -drag.y;
	}
}

void FusionControllerSink::LeftUp(Point pt, dword keyflags) {
	FusionStream* s = Stream();
	if (!s) return;
	
	is_left_down = false;
	
	Point& drag = s->mouse_toycompat_drag;
	drag.y = -drag.y; // observed behaviour
}

void FusionControllerSink::MouseMove(Point pt, dword keyflags) {
	FusionStream* s = Stream();
	if (!s) return;
	
	Point& drag = s->mouse_toycompat_drag;
	Point& click = s->mouse_toycompat_click;
	if (is_left_down) {
		if (s->video_size.cx > 0 && s->video_size.cy > 0) {
			drag.x =                    s->video_offset.x + pt.x;
			drag.y = s->video_size.cy - s->video_offset.y - pt.y;
		}
		else {
			drag.x = 0;
			drag.y = s->video_size.cy;
		}
	}
}

bool FusionControllerSink::Key(dword key, int count) {
	
	if (data.GetCount()) {
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
		
		if (key >= 0 && key < key_tex_w) {
			if (key > 0)
				data[key] = is_key_down;
			data[16] = is_lshift;
			data[17] = is_lctrl;
			data[18] = is_lalt;
			changed = true;
		}
	}
	
	return true;
}



NAMESPACE_OULU_END
