#if X11IMPL
#define ScanCodeName COMBINE(KeySymToTSScancode, ABBR)
#define CLASSNAME COMBINE(ScrX11, ABBR)
#define CONTEXT COMBINE(COMBINE(X11, ABBR), Context)


bool CLASSNAME::EventsBase_Create(One<NativeEventsBase>& dev) {
	dev.Create();
	return true;
}

void CLASSNAME::EventsBase_Destroy(One<NativeEventsBase>& dev) {
	dev.Clear();
}

void CLASSNAME::EventsBase_Visit(NativeEventsBase& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool CLASSNAME::EventsBase_Initialize(NativeEventsBase& ev, AtomBase& a, const Script::WorldState& ws) {
	auto ctx_ = a.GetSpace()->template FindNearestAtomCast<CONTEXT>(1);
	ASSERT(ctx_);
	if (!ctx_) {RTLOG("error: could not find X11 context"); return false;}
	ev.ctx = &*ctx_->dev;
	
	
	return true;
}

bool CLASSNAME::EventsBase_PostInitialize(NativeEventsBase& ev, AtomBase& a) {
	if (!ev.ctx->win) {
		LOG("CLASSNAME::EventsBase_PostInitialize: error: context has no window");
		return false;
	}
	
	return true;
}

bool CLASSNAME::EventsBase_Start(NativeEventsBase& ev, AtomBase& a) {
	
	return true;
}

void CLASSNAME::EventsBase_Stop(NativeEventsBase& ev, AtomBase& a) {
	
}

void CLASSNAME::EventsBase_Uninitialize(NativeEventsBase& ev, AtomBase& a) {
	
}

bool CLASSNAME::EventsBase_Send(NativeEventsBase& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	ASSERT(dev.ev_sendable);
	if (!dev.ev_sendable)
		return false;
	

	Format fmt = out.GetFormat();
	RTLOG("CLASSNAME::EventsBase_Send: " << fmt.ToString());
	
	if (fmt.IsEvent()) {
		out.seq = dev.seq++;
		CtrlEventCollection& dst = out.SetData<CtrlEventCollection>();
		dst <<= dev.ev;
		dev.ev_sendable = false;
	}
	
	return true;
}

bool CLASSNAME::EventsBase_Recv(NativeEventsBase& ev, AtomBase& a, int sink_ch, const Packet&) {
	
	return true;
}

int ConvertX11Keycode(CLASSNAME::NativeEventsBase&, int key);

void X11Events__PutKeyFlags(CLASSNAME::NativeEventsBase& dev, dword& key) {
	if (dev.is_lalt   || dev.is_ralt)		key |= K_ALT;
	if (dev.is_lshift || dev.is_rshift)		key |= K_SHIFT;
	if (dev.is_lctrl  || dev.is_rctrl)		key |= K_CTRL;
}

bool X11Events__Poll(CLASSNAME::NativeEventsBase& dev, AtomBase& a) {
	Vector<UPP::CtrlEvent>& evec = dev.ev;
	evec.SetCount(0);
	evec.Reserve(100);
	
	while (XPending(dev.ctx->display)) {
		UPP::CtrlEvent& e = evec.Add();
		
		XNextEvent(dev.ctx->display, &dev.xev);
		::KeySym xkey;
		Point mouse_pt;
		dword key = 0;
		int mouse_code = 0;
		
		switch (dev.xev.type) {
		
		case KeyPress:
			xkey = XLookupKeysym(&dev.xev.xkey, 0);
			switch (xkey) {
				//case XK_Escape:		break;
				case XK_Alt_L:			dev.is_lalt = true; break;
				case XK_Alt_R:			dev.is_ralt = true; break;
				case XK_Shift_L:		dev.is_lshift = true; break;
				case XK_Shift_R:		dev.is_rshift = true; break;
				case XK_Control_L:		dev.is_lctrl = true; break;
				case XK_Control_R:		dev.is_rctrl = true; break;
				default: break;
			}
			
			key = ConvertX11Keycode(dev, xkey);
			X11Events__PutKeyFlags(dev, key);
			
			e.type = EVENT_KEYDOWN;
			e.value = key;
			e.n = 1;
			e.pt = Point(0,0);
			
			return true;
		
		case KeyRelease:
			xkey = XLookupKeysym(&dev.xev.xkey, 0);
			switch (xkey) {
				//case XK_Escape:		break;
				case XK_Alt_L:			dev.is_lalt = false; break;
				case XK_Alt_R:			dev.is_ralt = false; break;
				case XK_Shift_L:		dev.is_lshift = false; break;
				case XK_Shift_R:		dev.is_rshift = false; break;
				case XK_Control_L:		dev.is_lctrl = false; break;
				case XK_Control_R:		dev.is_rctrl = false; break;
				default: break;
			}
			
			key = ConvertX11Keycode(dev, xkey);
			X11Events__PutKeyFlags(dev, key);
			
			key = key | K_KEYUP;
			
			e.type = EVENT_KEYUP;
			e.value = key;
			e.n = 1;
			e.pt = Point(0,0);
			
			return true;
			
		case MotionNotify:
			mouse_pt = Point(dev.xev.xmotion.x, dev.xev.xmotion.y);
			key = 0;
			X11Events__PutKeyFlags(dev, key);
			
			e.type = EVENT_MOUSEMOVE;
			e.value = key;
			e.pt = mouse_pt;
			
			dev.prev_mouse_pt = mouse_pt;
			return true;
		
			
		case ButtonPress:
		case ButtonRelease:
			mouse_code = 0;
			if (dev.xev.type == ButtonPress) {
				// single click only
				if (1) {
					if (dev.xev.xbutton.button == Button1)
						mouse_code = MOUSE_LEFTDOWN;
					else if (dev.xev.xbutton.button == Button2)
						mouse_code = MOUSE_MIDDLEDOWN;
					else if (dev.xev.xbutton.button == Button3)
						mouse_code = MOUSE_RIGHTDOWN;
				}
			}
			else {
				if (dev.xev.xbutton.button == Button1)
					mouse_code = MOUSE_LEFTUP;
				else if (dev.xev.xbutton.button == Button2)
					mouse_code = MOUSE_MIDDLEUP;
				else if (dev.xev.xbutton.button == Button3)
					mouse_code = MOUSE_RIGHTUP;
			}
		
			
			if (mouse_code) {
				mouse_pt = Point(dev.xev.xbutton.x, dev.xev.xbutton.y);
				X11Events__PutKeyFlags(dev, key);
				
				e.type = EVENT_MOUSE_EVENT;
				e.value = key;
				e.pt = mouse_pt;
				e.n = mouse_code;
				
				dev.prev_mouse_pt = mouse_pt;
				return true;
			}
			break;
			
        case ClientMessage:
            if (dev.xev.xclient.data.l[0] == dev.ctx->wmDeleteMessage) {
                dev.ctx->running = false;
                a.GetMachine().SetNotRunning();
                GetActiveMachine().SetNotRunning();
                XDestroyWindow(dev.ctx->display, dev.ctx->win);
            }
			return true;
			
		default:
			evec.Pop();
		}
	}
	
	return false;
}

bool CLASSNAME::EventsBase_IsReady(NativeEventsBase& dev, AtomBase& a, PacketIO& io) {
	bool b = io.full_src_mask == 0;
	if (b) {
		if (X11Events__Poll(dev, a)) {
			dev.ev_sendable = true;
		}
		else {
			dev.ev_sendable = false;
			b = false;
		}
	}
	RTLOG("CLASSNAME::EventsBase_IsReady: " << (b ? "true" : "false"));
	return b;
}


void CLASSNAME::EventsBase_Finalize(NativeEventsBase& ev, AtomBase& a, RealtimeSourceConfig&) {
	
}

bool CLASSNAME::EventsBase_NegotiateSinkFormat(NativeEventsBase& ev, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	
	return false;
}






static const struct {
    int keycode;
    int scancode;
} ScanCodeName[] = {
    { XK_Return, '\r' },
    { XK_Escape, '\x1B' },
    { XK_BackSpace, '\b' },
    { XK_Tab, '\t' },
    { XK_Caps_Lock, TS_SCANCODE_CAPSLOCK },
    { XK_F1, TS_SCANCODE_F1 },
    { XK_F2, TS_SCANCODE_F2 },
    { XK_F3, TS_SCANCODE_F3 },
    { XK_F4, TS_SCANCODE_F4 },
    { XK_F5, TS_SCANCODE_F5 },
    { XK_F6, TS_SCANCODE_F6 },
    { XK_F7, TS_SCANCODE_F7 },
    { XK_F8, TS_SCANCODE_F8 },
    { XK_F9, TS_SCANCODE_F9 },
    { XK_F10, TS_SCANCODE_F10 },
    { XK_F11, TS_SCANCODE_F11 },
    { XK_F12, TS_SCANCODE_F12 },
    { XK_Print, TS_SCANCODE_PRINTSCREEN },
    { XK_Scroll_Lock, TS_SCANCODE_SCROLLLOCK },
    { XK_Pause, TS_SCANCODE_PAUSE },
    { XK_Insert, TS_SCANCODE_INSERT },
    { XK_Home, TS_SCANCODE_HOME },
    { XK_Prior, TS_SCANCODE_PAGEUP },
    { XK_Delete, TS_SCANCODE_DELETE },
    { XK_End, TS_SCANCODE_END },
    { XK_Next, TS_SCANCODE_PAGEDOWN },
    { XK_Right, TS_SCANCODE_RIGHT },
    { XK_Left, TS_SCANCODE_LEFT },
    { XK_Down, TS_SCANCODE_DOWN },
    { XK_Up, TS_SCANCODE_UP },
    { XK_Num_Lock, TS_SCANCODE_NUMLOCKCLEAR },
    { XK_KP_Divide, TS_SCANCODE_KP_DIVIDE },
    { XK_KP_Multiply, TS_SCANCODE_KP_MULTIPLY },
    { XK_KP_Subtract, TS_SCANCODE_KP_MINUS },
    { XK_KP_Add, TS_SCANCODE_KP_PLUS },
    { XK_KP_Enter, TS_SCANCODE_KP_ENTER },
    { XK_KP_Delete, TS_SCANCODE_KP_PERIOD },
    { XK_KP_End, TS_SCANCODE_KP_1 },
    { XK_KP_Down, TS_SCANCODE_KP_2 },
    { XK_KP_Next, TS_SCANCODE_KP_3 },
    { XK_KP_Left, TS_SCANCODE_KP_4 },
    { XK_KP_Begin, TS_SCANCODE_KP_5 },
    { XK_KP_Right, TS_SCANCODE_KP_6 },
    { XK_KP_Home, TS_SCANCODE_KP_7 },
    { XK_KP_Up, TS_SCANCODE_KP_8 },
    { XK_KP_Prior, TS_SCANCODE_KP_9 },
    { XK_KP_Insert, TS_SCANCODE_KP_0 },
    { XK_KP_Decimal, TS_SCANCODE_KP_PERIOD },
    { XK_KP_1, TS_SCANCODE_KP_1 },
    { XK_KP_2, TS_SCANCODE_KP_2 },
    { XK_KP_3, TS_SCANCODE_KP_3 },
    { XK_KP_4, TS_SCANCODE_KP_4 },
    { XK_KP_5, TS_SCANCODE_KP_5 },
    { XK_KP_6, TS_SCANCODE_KP_6 },
    { XK_KP_7, TS_SCANCODE_KP_7 },
    { XK_KP_8, TS_SCANCODE_KP_8 },
    { XK_KP_9, TS_SCANCODE_KP_9 },
    { XK_KP_0, TS_SCANCODE_KP_0 },
    { XK_KP_Decimal, TS_SCANCODE_KP_PERIOD },
    { XK_Hyper_R, TS_SCANCODE_APPLICATION },
    { XK_KP_Equal, TS_SCANCODE_KP_EQUALS },
    { XK_F13, TS_SCANCODE_F13 },
    { XK_F14, TS_SCANCODE_F14 },
    { XK_F15, TS_SCANCODE_F15 },
    { XK_F16, TS_SCANCODE_F16 },
    { XK_F17, TS_SCANCODE_F17 },
    { XK_F18, TS_SCANCODE_F18 },
    { XK_F19, TS_SCANCODE_F19 },
    { XK_F20, TS_SCANCODE_F20 },
    { XK_F21, TS_SCANCODE_F21 },
    { XK_F22, TS_SCANCODE_F22 },
    { XK_F23, TS_SCANCODE_F23 },
    { XK_F24, TS_SCANCODE_F24 },
    { XK_Execute, TS_SCANCODE_EXECUTE },
    { XK_Help, TS_SCANCODE_HELP },
    { XK_Menu, TS_SCANCODE_MENU },
    { XK_Select, TS_SCANCODE_SELECT },
    { XK_Cancel, TS_SCANCODE_STOP },
    { XK_Redo, TS_SCANCODE_AGAIN },
    { XK_Undo, TS_SCANCODE_UNDO },
    { XK_Find, TS_SCANCODE_FIND },
    { XK_KP_Separator, TS_SCANCODE_KP_COMMA },
    { XK_Sys_Req, TS_SCANCODE_SYSREQ },
    { XK_Control_L, TS_SCANCODE_LCTRL },
    { XK_Shift_L, TS_SCANCODE_LSHIFT },
    { XK_Alt_L, TS_SCANCODE_LALT },
    { XK_Meta_L, TS_SCANCODE_LGUI },
    { XK_Super_L, TS_SCANCODE_LGUI },
    { XK_Control_R, TS_SCANCODE_RCTRL },
    { XK_Shift_R, TS_SCANCODE_RSHIFT },
    { XK_Alt_R, TS_SCANCODE_RALT },
    { XK_ISO_Level3_Shift, TS_SCANCODE_RALT },
    { XK_Meta_R, TS_SCANCODE_RGUI },
    { XK_Super_R, TS_SCANCODE_RGUI },
    { XK_Mode_switch, TS_SCANCODE_MODE },
    { XK_period, TS_SCANCODE_PERIOD },
    { XK_comma, TS_SCANCODE_COMMA },
    { XK_slash, TS_SCANCODE_SLASH },
    { XK_backslash, TS_SCANCODE_BACKSLASH },
    { XK_minus, TS_SCANCODE_MINUS },
    { XK_equal, TS_SCANCODE_EQUALS },
    { XK_space, TS_SCANCODE_SPACE },
    { XK_grave, TS_SCANCODE_GRAVE },
    { XK_apostrophe, TS_SCANCODE_APOSTROPHE },
    { XK_bracketleft, TS_SCANCODE_LEFTBRACKET },
    { XK_bracketright, TS_SCANCODE_RIGHTBRACKET },
};

#define TS_arraysize(array)    (sizeof(array)/sizeof(array[0]))

int ConvertX11Keycode(CLASSNAME::NativeEventsBase& dev, int keycode)
{
    for (int i = 0; i < TS_arraysize(ScanCodeName); ++i) {
        if (keycode == ScanCodeName[i].keycode) {
            return ScanCodeName[i].scancode;
        }
    }
    return keycode;
}

#endif



#if WINIMPL

#endif
