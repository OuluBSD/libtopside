#include "IScreen.h"


#if (defined flagPOSIXDESKTOP && defined flagSCREEN)
NAMESPACE_PARALLEL_BEGIN

struct ScrX11::NativeContext {
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

struct ScrX11::NativeSinkDevice {
    NativeContext* ctx;
    ProgImage pi;
    One<ImageDraw> id;
};

struct ScrX11::NativeEventsBase {
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


bool ScrX11::SinkDevice_Create(NativeSinkDevice*& dev) {
	dev = new NativeSinkDevice;
	return true;
}

void ScrX11::SinkDevice_Destroy(NativeSinkDevice*& dev) {
	delete dev;
}

void ScrX11::SinkDevice_Visit(NativeSinkDevice& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool ScrX11::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	auto ctx_ = a.GetSpace()->template FindNearestAtomCast<X11Context>(1);
	if (!ctx_) {RTLOG("error: could not find X11 context"); return false;}
	auto& ctx = *ctx_->dev;
	dev.ctx = &ctx;
	
	a.SetDependency(&*ctx_);
	
	::Display*& display = ctx.display;	// pointer to X Display structure.
	display = 0;
	int screen_num;						// number of screen to place the window on.
	::Window& win = ctx.win;			// pointer to the newly created window.
	unsigned int display_width,
	             display_height;		// height and width of the X display.
	unsigned int width, height;			// height and width for the new window.
	char *display_name = getenv("DISPLAY"); // address of the X display.
	::GC& gc = ctx.gc;					// GC (graphics context) used for drawing
										// in our window.
	::Visual*& visual = ctx.visual;
	
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
		XSetLineAttributes(display, gc,
		                 line_width, line_style, cap_style, join_style);
		
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
	
	//int bpp = fb->bits_per_pixel / 8;
	
	XSync(display, False);
	
	return true;
}

bool ScrX11::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

bool ScrX11::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

void ScrX11::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	auto& ctx = *dev.ctx;
	
	
	XDestroyWindow(ctx.display, ctx.win);
	
}

void ScrX11::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	a.SetDependency(0);
	
	auto& ctx = *dev.ctx;
	
	//XkbFreeKeyboard(ctx.xkb, XkbAllComponentsMask, True);

	// flush all pending requests to the X server.
	XFlush(ctx.display);
	
	// close the connection to the X server.
	XCloseDisplay(ctx.display);
}

bool ScrX11::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	auto& ctx = *dev.ctx;
	
	Format fmt = in->GetFormat();
	if (fmt.IsVideo()) {
		const Vector<byte>& pixmap = in->Data();
		VideoFormat& vfmt = fmt;
		int frame_sz = vfmt.GetFrameSize();
		ASSERT(pixmap.GetCount() == frame_sz);
		
		int width = vfmt.res[0];
		int height = vfmt.res[1];
		
		ASSERT(ctx.fb);
		ASSERT(!ctx.fb->data);
	    ctx.fb->data = (char*)(const unsigned char*)pixmap.Begin();
	    ctx.fb->bytes_per_line = vfmt.res[0] * vfmt.GetPackedCount();
	    
	    /*int scr_bpp = ctx.fb->bits_per_pixel / 8;
	    int img_bpp = vfmt.GetPackedCount();
	    ASSERT(scr_bpp == img_bpp);*/
	    
	    ASSERT(width == ctx.fb->width);
	    ASSERT(height == ctx.fb->height);
	    if (width != ctx.fb->width || height != ctx.fb->height) {
	        LOG("ScrX11::SinkDevice_ProcessPacket: error: invalid resolution");
	        return false;
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
	        return false;
	    }
	    
		XFlush(ctx.display);
		//XSync(dev.display, False);
		
		ctx.fb->data = 0;
	}
	else if (fmt.IsProg()) {
		Size sz(ctx.fb->width, ctx.fb->height);
		ASSERT(!sz.IsEmpty());
		if (dev.id.IsEmpty()) {
			#if IS_UPP_CORE
			dev.id = new ImageDraw(sz);
			#else
			dev.id.Create(sz, 4);
			#endif
		}
		
		InternalPacketData& data = in->GetData<InternalPacketData>();
		DrawCommand* begin = (DrawCommand*)data.ptr;
		
		#if 1
		{
			DrawCommand* it = begin;
			int i = 0;
			while (it) {
				LOG(i++ << " " << it->ToString());
				it = it->next;
			}
		}
		#endif
		
		while (begin && begin->type != DRAW_BIND_WINDOW) begin = begin->next;
		if (!begin) {
			LOG("HalSdl::CenterVideoSinkDevice_Recv: error: no ptr");
			return false;
		}
		ASSERT(begin->type == DRAW_BIND_WINDOW);
		
		DrawCommand* end = begin;
		while (end) {
			if (end->type == DRAW_UNBIND_WINDOW) {
				end = end->next;
				break;
			}
			end = end->next;
		}
		
		dev.id->DrawRect(sz, Black());
		dev.pi.Paint(begin, end, *dev.id);
		
		#if IS_UPP_CORE
		TODO
		#else
		dev.id->SwapRG();
		
		ASSERT(ctx.fb);
		ASSERT(!ctx.fb->data);
		int bpp = dev.id->GetStride();
		int id_len = dev.id->Data().GetCount();
	    ctx.fb->data = (char*)(const unsigned char*)dev.id->Data().Begin();
	    ctx.fb->bytes_per_line = sz.cx * bpp;
	    
	    /*int scr_bpp = ctx.fb->bits_per_pixel / 8;
	    int img_bpp = bpp;
	    ASSERT(scr_bpp == img_bpp);*/
	    
	    ASSERT(sz.cx == ctx.fb->width);
	    ASSERT(sz.cy == ctx.fb->height);
	    if (sz.cx != ctx.fb->width || sz.cy != ctx.fb->height) {
	        LOG("ScrX11::SinkDevice_ProcessPacket: error: invalid resolution");
	        return false;
	    }
	    
	    int rc = XPutImage(	ctx.display,
							ctx.win,
							ctx.gc,
							ctx.fb,
							0,0,
							0,0,
							sz.cx,
							sz.cy);
	    
	    if (rc == BadMatch) {
	        LOG("ScrX11::SinkDevice_ProcessPacket: error: XPutImage returned BadMatch");
	        ctx.fb->data = 0;
	        return false;
	    }
	    #endif
	    
		XFlush(ctx.display);
		//XSync(dev.display, False);
		
		ctx.fb->data = 0;
		
		return true;
	}
	
	return true;
}

void ScrX11::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	
	
}

bool ScrX11::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}

bool ScrX11::SinkDevice_NegotiateSinkFormat(NativeSinkDevice& dev, AtomBase&, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	TODO
	return false;
}

bool ScrX11::SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase&, PacketIO& io) {
	return true;
}







bool ScrX11::Context_Create(NativeContext*& dev) {
	dev = new NativeContext;
	return true;
}

void ScrX11::Context_Destroy(NativeContext*& dev) {
	delete dev;
}

void ScrX11::Context_Visit(NativeContext& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool ScrX11::Context_Initialize(NativeContext& ctx, AtomBase& a, const Script::WorldState& ws) {
	return true;
}

bool ScrX11::Context_PostInitialize(NativeContext& ctx, AtomBase& a) {
	return true;
}

bool ScrX11::Context_Start(NativeContext& ctx, AtomBase& a) {
	return true;
}

void ScrX11::Context_Stop(NativeContext& ctx, AtomBase& a) {
	
}

void ScrX11::Context_Uninitialize(NativeContext& ctx, AtomBase& a) {
	
}

bool ScrX11::Context_Send(NativeContext& ctx, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return false;
}

bool ScrX11::Context_Recv(NativeContext& ctx, AtomBase& a, int sink_ch, const Packet&) {
	return false;
}

void ScrX11::Context_Finalize(NativeContext& ctx, AtomBase& a, RealtimeSourceConfig&) {
	
}

bool ScrX11::Context_NegotiateSinkFormat(NativeContext& ctx, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	return false;
}

bool ScrX11::Context_IsReady(NativeContext& dev, AtomBase&, PacketIO& io) {
	return true;
}






#define ABBR
#define X11IMPL 1
#include "Impl.inl"
#undef ABBR



NAMESPACE_PARALLEL_END
#endif

