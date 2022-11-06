#include "IScreen.h"

		
#if (defined flagLINUX) || (defined flagFREEBSD)
NAMESPACE_PARALLEL_BEGIN


struct ScrX11Sw::NativeContext {
    ::Window win;
    ::Display* display;
    ::XImage* fb;
    ::Visual* visual;
    ::GC gc;
    ::XVisualInfo* visual_info;
    ::Atom  atomWmDeleteWindow;
    ::XSetWindowAttributes attr;
    bool running = false;
    ::Atom wmDeleteMessage;
};

struct ScrX11Sw::NativeSinkDevice {
    NativeContext* ctx;
    GfxAccelAtom<X11SwGfx> accel;
    ByteImage accel_buf;
    ByteImage accel_buf_tmp;
    DepthImage accel_zbuf;
    SoftFramebuffer accel_fbo;
};

struct ScrX11Sw::NativeEventsBase {
    NativeContext* ctx;
    int time;
    dword seq;
    UPP::CtrlEvent ev;
    Size sz;
    bool ev_sendable;
    bool is_lalt;
    bool is_ralt;
    bool is_lshift;
    bool is_rshift;
    bool is_lctrl;
    bool is_rctrl;
    Point prev_mouse_pt;
    ::XEvent xev;
};


bool ScrX11Sw::SinkDevice_Create(One<NativeSinkDevice>& dev) {
	dev.Create();
	return true;
}

void ScrX11Sw::SinkDevice_Destroy(One<NativeSinkDevice>& dev) {
	dev.Clear();
}

void ScrX11Sw::SinkDevice_Visit(NativeSinkDevice& dev, AtomBase&, RuntimeVisitor& vis) {
	vis % dev.accel;
}

bool ScrX11Sw::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	auto ctx_ = a.GetSpace()->template FindNearestAtomCast<X11SwContext>(1);
	if (!ctx_) {LOG("error: could not find X11 context"); return false;}
	auto& ctx = *ctx_->dev;
	dev.ctx = &ctx;
	
	::Display*& display = ctx.display;	// pointer to X Display structure.
	int screen_num;						// number of screen to place the window on.
	::Window& win = ctx.win;			// pointer to the newly created window.
	unsigned int display_width,
	             display_height;		// height and width of the X display.
	unsigned int width, height;			// height and width for the new window.
	char *display_name = getenv("DISPLAY"); // address of the X display.
	::GC& gc = ctx.gc;					// GC (graphics context) used for drawing
										// in our window.
	::Visual*& visual = ctx.visual;
	
	display = 0;
	int x = 0;
	int y = 0;
	
	bool reverse_video = false;
	
	// open connection with the X server.
	display = XOpenDisplay(display_name);
	if (display == NULL) {
		LOG("ScrX11::SinkDevice_Initialize: error: cannot connect to X server '" << display_name << "'");
		return false;
	}
	
	// get the geometry of the default screen for our display.
	screen_num = DefaultScreen(display);
	display_width = DisplayWidth(display, screen_num);
	display_height = DisplayHeight(display, screen_num);
	visual = XDefaultVisual(display, screen_num);
	int dplanes = DisplayPlanes(display, screen_num);
	
	// default resolution is 1280x720 for now
	width = 1280;
	height = 720;
	RTLOG("ScrX11::SinkDevice_Initialize: window width - '" << width << "'; height - '" << height << "'");
	
	// create a simple window, as a direct child of the screen's
	// root window. Use the screen's white color as the background
	// color of the window. Place the new window's top-left corner
	// at the given 'x,y' coordinates.
	{
		int screen_num = DefaultScreen(display);
		int win_border_width = 2;
		
		// create a simple window, as a direct child of the screen's
		// root window. Use the screen's black and white colors as
		// the foreground and background colors of the window,
		// respectively. Place the new window's top-left corner at
		// the given 'x,y' coordinates.
		win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
		                          x, y, width, height, win_border_width,
		                          BlackPixel(display, screen_num),
		                          WhitePixel(display, screen_num));
		
		// Enable input
		XSelectInput(display, win, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask);
		//ctx.xkb = XkbGetMap(display, XkbAllClientInfoMask, XkbUseCoreKbd);
		
		dev.ctx->wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
		XSetWMProtocols(display, win, &dev.ctx->wmDeleteMessage, 1);
		
		// make the window actually appear on the screen.
		XMapWindow(display, win);
		
		// flush all pending requests to the X server.
		XFlush(display);
	}
	
	// allocate a new GC (graphics context) for drawing in the window.
	{
		unsigned long valuemask = 0;	// which values in 'values' to
										// check when creating the GC.
		XGCValues values;				// initial values for the GC.
		unsigned int line_width = 2;	// line width for the GC.
		int line_style = LineSolid;		// style for lines drawing and
		int cap_style = CapButt;		// style of the line's edje and
		int join_style = JoinBevel;		// joined lines.
		int screen_num = DefaultScreen(display);
		
		gc = XCreateGC(display, win, valuemask, &values);
		if (gc == 0) {
			LOG("ScrX11::SinkDevice_Initialize: error: XCreateGC failed");
			return false;
		}
		
		// allocate foreground and background colors for this GC.
		if (reverse_video) {
			XSetForeground(display, gc, WhitePixel(display, screen_num));
			XSetBackground(display, gc, BlackPixel(display, screen_num));
		}
		else {
			XSetForeground(display, gc, BlackPixel(display, screen_num));
			XSetBackground(display, gc, WhitePixel(display, screen_num));
		}
		
		// define the style of lines that will be drawn using this GC.
		XSetLineAttributes(display, gc, line_width, line_style, cap_style, join_style);
		
		// define the fill style for the GC. to be 'solid filling'.
		XSetFillStyle(display, gc, FillSolid);
	}
	
	TS::default_width = width;
	TS::default_height = height;
	
	::XImage*& fb = ctx.fb;
	fb = XCreateImage(
		ctx.display,
		visual,
		dplanes,
		ZPixmap,
		0,
		0,
		width,
		height,
		8,
		0// does not work with: width * bpp
	);
	ASSERT(fb);
	
	int bpp = fb->bits_per_pixel / 8;
	
	XSync(display, False);
	
	if (!dev.accel.Initialize(a, ws)) {
		LOG("ScrX11::SinkDevice_Initialize: error: accelerator initialization failed");
		return false;
	}
	
	dev.accel_buf.Set(width, height, bpp, width * bpp, 0);
	dev.accel_buf.LockChannels();
	dev.accel_buf.Zero(Color(125,0,125));
	dev.accel_fbo.SetColor(TEXTYPE_NONE, &dev.accel_buf);
	dev.accel_fbo.SetDepth(&dev.accel_zbuf);
	
	dev.accel.SetNative(ctx.display, ctx.win, 0, &dev.accel_fbo);
	
	if (!dev.accel.Open(Size(width, height), bpp)) {
		LOG("ScrX11Ogl::SinkDevice_Initialize: error: could not open opengl atom");
		return false;
	}
	
	return true;
}

bool ScrX11Sw::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	return dev.accel.PostInitialize();
}

bool ScrX11Sw::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

void ScrX11Sw::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	auto& ctx = *dev.ctx;
	
	XDestroyWindow(ctx.display, ctx.win);
	
}

void ScrX11Sw::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	auto& ctx = *dev.ctx;
	
	dev.accel.Uninitialize();
	
	//XkbFreeKeyboard(ctx.xkb, XkbAllComponentsMask, True);

	// Causes crash:
		//XFree(dev.visual);
		//XFreeColormap(dev.display, dev.attr.colormap);
		
	// flush all pending requests to the X server.
	if (ctx.running) {
		XFlush(ctx.display);
		
		// close the connection to the X server.
		XCloseDisplay(ctx.display);
		ctx.display = 0;
	
	}
	
}

bool ScrX11Sw::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	return dev.accel.Recv(sink_ch, in);
}

void ScrX11Sw::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	auto& ctx = *dev.ctx;
	
	if (!ctx.running)
		return;
	
	dev.accel.Render(cfg);
	
	{
		XWindowAttributes attr;
		XGetWindowAttributes(ctx.display, ctx.win, &attr);
		
		int width = attr.width;
		int height = attr.height;
		int bpp = ctx.fb->bits_per_pixel / 8;
		int len = width * height * bpp;
		
		// TODO: find how to create rgb XImage or support BGRA in full soft render implementation
		// HACK: for now, just swap red and blue
		// NOTE: VERY SLOW!
		ASSERT(dev.accel_buf.channels == bpp);
		ASSERT(ctx.fb);
		ASSERT(!ctx.fb->data);
		#if 1
	    dev.accel_buf_tmp.SetSwapRedBlue(dev.accel_buf, true);
		ASSERT(dev.accel_buf_tmp.GetLength() == len);
		ctx.fb->data = (char*)(const unsigned char*)dev.accel_buf_tmp.Begin();
		#else
	    ctx.fb->data = (char*)(const unsigned char*)dev.accel_buf.Begin();
	    #endif
	    ctx.fb->bytes_per_line = width * bpp;
	    
	    ASSERT(width == ctx.fb->width);
	    ASSERT(height == ctx.fb->height);
	    if (width != ctx.fb->width || height != ctx.fb->height) {
	        LOG("ScrX11::SinkDevice_ProcessPacket: error: invalid resolution");
	        ctx.fb->data = 0;
	        return;
	    }
	    
	    int rc = XPutImage(	ctx.display,
							ctx.win,
							ctx.gc,
							ctx.fb,
							0,0,
							0,0,
							width,
							height);
	    
	    if (rc == BadMatch) {
	        LOG("ScrX11::SinkDevice_ProcessPacket: error: XPutImage returned BadMatch");
	        ctx.fb->data = 0;
	        return;
	    }
	    
		XFlush(ctx.display);
		//XSync(dev.display, False);
		
		ctx.fb->data = 0;
	}
}

bool ScrX11Sw::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}

bool ScrX11Sw::SinkDevice_NegotiateSinkFormat(NativeSinkDevice& dev, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	// accept all valid video formats for now
	if (new_fmt.IsValid() && new_fmt.IsVideo()) {
		ISinkRef sink = a.GetSink();
		Value& val = sink->GetValue(sink_ch);
		val.SetFormat(new_fmt);
		return true;
	}
	return false;
}

bool ScrX11Sw::SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase&, PacketIO& io) {
	return true;
}





bool ScrX11Sw::Context_Create(One<NativeContext>& dev) {
	dev.Create();
	return true;
}

void ScrX11Sw::Context_Destroy(One<NativeContext>& dev) {
	dev.Clear();
}

void ScrX11Sw::Context_Visit(NativeContext& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool ScrX11Sw::Context_Initialize(NativeContext& ctx, AtomBase& a, const Script::WorldState& ws) {
	ctx.running = true;
	return true;
}

bool ScrX11Sw::Context_PostInitialize(NativeContext& ctx, AtomBase& a) {
	return true;
}

bool ScrX11Sw::Context_Start(NativeContext& ctx, AtomBase& a) {
	return true;
}

void ScrX11Sw::Context_Stop(NativeContext& ctx, AtomBase& a) {
	
}

void ScrX11Sw::Context_Uninitialize(NativeContext& ctx, AtomBase& a) {
	
}

bool ScrX11Sw::Context_Send(NativeContext& ctx, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return false;
}

bool ScrX11Sw::Context_Recv(NativeContext& ctx, AtomBase& a, int sink_ch, const Packet&) {
	return false;
}

void ScrX11Sw::Context_Finalize(NativeContext& ctx, AtomBase& a, RealtimeSourceConfig&) {
	
}

bool ScrX11Sw::Context_NegotiateSinkFormat(NativeContext& ctx, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	return false;
}

bool ScrX11Sw::Context_IsReady(NativeContext& dev, AtomBase&, PacketIO& io) {
	return true;
}






bool ScrX11Sw::EventsBase_Create(One<NativeEventsBase>& dev) {
	dev.Create();
	return true;
}

void ScrX11Sw::EventsBase_Destroy(One<NativeEventsBase>& dev) {
	dev.Clear();
}

void ScrX11Sw::EventsBase_Visit(NativeEventsBase& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool ScrX11Sw::EventsBase_Initialize(NativeEventsBase& ev, AtomBase& a, const Script::WorldState& ws) {
	auto ctx_ = a.GetSpace()->template FindNearestAtomCast<X11SwContext>(1);
	ASSERT(ctx_);
	if (!ctx_) {RTLOG("error: could not find X11 context"); return false;}
	ev.ctx = &*ctx_->dev;
	
	
	return true;
}

bool ScrX11Sw::EventsBase_PostInitialize(NativeEventsBase& ev, AtomBase& a) {
	if (!ev.ctx->win) {
		LOG("ScrX11Sw::EventsBase_PostInitialize: error: context has no window");
		return false;
	}
	
	return true;
}

bool ScrX11Sw::EventsBase_Start(NativeEventsBase& ev, AtomBase& a) {
	
	return true;
}

void ScrX11Sw::EventsBase_Stop(NativeEventsBase& ev, AtomBase& a) {
	
}

void ScrX11Sw::EventsBase_Uninitialize(NativeEventsBase& ev, AtomBase& a) {
	
}

bool ScrX11Sw::EventsBase_Send(NativeEventsBase& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	ASSERT(dev.ev_sendable);
	if (!dev.ev_sendable)
		return false;
	

	Format fmt = out.GetFormat();
	RTLOG("ScrX11Sw::EventsBase_Send: " << fmt.ToString());
	
	if (fmt.IsEvent()) {
		out.seq = dev.seq++;
		UPP::CtrlEvent& dst = out.SetData<UPP::CtrlEvent>();
		dst = dev.ev;
		dev.ev_sendable = false;
	}
	
	return true;
}

bool ScrX11Sw::EventsBase_Recv(NativeEventsBase& ev, AtomBase& a, int sink_ch, const Packet&) {
	
	return true;
}

int ConvertX11Keycode(ScrX11Sw::NativeEventsBase&, int key);

void X11Events__PutKeyFlags(ScrX11Sw::NativeEventsBase& dev, dword& key) {
	if (dev.is_lalt   || dev.is_ralt)		key |= K_ALT;
	if (dev.is_lshift || dev.is_rshift)		key |= K_SHIFT;
	if (dev.is_lctrl  || dev.is_rctrl)		key |= K_CTRL;
}

bool X11Events__Poll(ScrX11Sw::NativeEventsBase& dev, AtomBase& a) {
	UPP::CtrlEvent& e = dev.ev;
	
	if (XPending(dev.ctx->display)) {
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
		}
		
	}
	
	return false;
}

bool ScrX11Sw::EventsBase_IsReady(NativeEventsBase& dev, AtomBase& a, PacketIO& io) {
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
	RTLOG("ScrX11Sw::EventsBase_IsReady: " << (b ? "true" : "false"));
	return b;
}


void ScrX11Sw::EventsBase_Finalize(NativeEventsBase& ev, AtomBase& a, RealtimeSourceConfig&) {
	
}

bool ScrX11Sw::EventsBase_NegotiateSinkFormat(NativeEventsBase& ev, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	
	return false;
}






static const struct {
    int keycode;
    int scancode;
} KeySymToTSScancode[] = {
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

int ConvertX11Keycode(ScrX11Sw::NativeEventsBase& dev, int keycode)
{
    for (int i = 0; i < TS_arraysize(KeySymToTSScancode); ++i) {
        if (keycode == KeySymToTSScancode[i].keycode) {
            return KeySymToTSScancode[i].scancode;
        }
    }
    return keycode;
}

NAMESPACE_PARALLEL_END
#endif

