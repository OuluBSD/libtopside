#include "IScreen.h"

		
#if (defined flagPOSIXDESKTOP && defined flagSCREEN)
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
    Vector<UPP::CtrlEvent> ev;
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


bool ScrX11Sw::SinkDevice_Create(NativeSinkDevice*& dev) {
	dev = new NativeSinkDevice;
	return true;
}

void ScrX11Sw::SinkDevice_Destroy(NativeSinkDevice*& dev) {
	delete dev;
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





bool ScrX11Sw::Context_Create(NativeContext*& dev) {
	dev = new NativeContext;
	return true;
}

void ScrX11Sw::Context_Destroy(NativeContext*& dev) {
	delete dev;
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






#define ABBR Sw
#define X11IMPL 1
#include "Impl.inl"
#undef ABBR


NAMESPACE_PARALLEL_END
#endif

