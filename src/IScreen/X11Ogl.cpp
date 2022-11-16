#include "IScreen.h"


		
#if defined flagPOSIX && defined flagOGL
NAMESPACE_PARALLEL_BEGIN

struct ScrX11Ogl::NativeContext {
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

struct ScrX11Ogl::NativeSinkDevice {
    NativeContext* ctx;
    ::GLXContext gl_ctx;
    GfxAccelAtom<X11OglGfx> accel;
};

struct ScrX11Ogl::NativeEventsBase {
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


GfxAccelAtom<X11OglGfx>& Get_ScrX11Ogl_Ogl(One<ScrX11Ogl::NativeSinkDevice>& dev) {
	return dev->accel;
}


bool X11Ogl_IsExtensionSupported(const char *extList, const char *extension) {
	const char *start;
	const char *where, *terminator;
	
	/* Extension names should not have spaces. */
	where = strchr(extension, ' ');
	if (where || *extension == '\0')
		return false;
		
	/* It takes a bit of care to be fool-proof about parsing the
	 OpenGL extensions string. Don't be fooled by sub-strings,
	 etc. */
	for (start = extList;;) {
		where = strstr(start, extension);
		
		if (!where) {
			break;
		}
		
		terminator = where + strlen(extension);
		
		if (where == start || *(where - 1) == ' ') {
			if (*terminator == ' ' || *terminator == '\0') {
				return true;
			}
		}
		
		start = terminator;
	}
	
	return false;
}



typedef struct {
	unsigned long   flags;
	unsigned long   functions;
	unsigned long   decorations;
	long            input_mode;
	unsigned long   status;
} Hints;

bool ScrX11Ogl::SinkDevice_Create(One<NativeSinkDevice>& dev) {
	dev.Create();
	return true;
}

void ScrX11Ogl::SinkDevice_Destroy(One<NativeSinkDevice>& dev) {
	dev.Clear();
}

void ScrX11Ogl::SinkDevice_Visit(NativeSinkDevice& dev, AtomBase&, RuntimeVisitor& vis) {
	vis % dev.accel;
}

bool ScrX11Ogl::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	auto ctx_ = a.GetSpace()->template FindNearestAtomCast<X11OglContext>(1);
	if (!ctx_) { LOG("error: could not find X11 context"); return false;}
	auto& ctx = *ctx_->dev;
	dev.ctx = &ctx;
	
	bool is_borderless = ws.IsTrue(".borderless");
	bool is_fullscreen = ws.IsTrue(".fullscreen");
	bool print_modes = ws.IsTrue(".print_modes");
	bool find_vr = ws.IsTrue(".find.vr.screen");
	int screen_idx = ws.GetInt(".screen", -1);
	
	if (!dev.accel.Initialize(a, ws)) {
		LOG("ScrX11Ogl::SinkDevice_Initialize: error: accelerator initialization failed");
		return false;
	}
	
	::Display*& display = ctx.display;	// pointer to X Display structure.
	::Window& win = ctx.win;			// pointer to the newly created window.
	::XVisualInfo*& visual = ctx.visual_info;
	unsigned int display_width,
	             display_height;		// height and width of the X display.
	unsigned int width, height;			// height and width for the new window.
	char *display_name = getenv("DISPLAY"); // address of the X display.
	
	int x = 0;
	int y = 0;
	
	bool reverse_video = false;
	
	// open connection with the X server.
	display = XOpenDisplay(display_name);
	if (display == NULL) {
		LOG("ScrX11Ogl::SinkDevice_Initialize: error: cannot connect to X server '" << display_name << "'");
		return false;
	}
	int screen_num = DefaultScreen(display);
	
	
	// Borderless & fullscreen X11 window (https://www.tonyobryan.com/index.php?article=9)
	// Used for secondary display fullscreen
	Hints     hints;
    ::Atom    hints_property;
    hints.flags = 2;        // Specify that we're changing the window decorations.
	hints.decorations = 0;  // 0 (false) means that window decorations should go bye-bye.
	hints_property = XInternAtom(display,"_MOTIF_WM_HINTS", True);
	
	
	GLint majorGLX, minorGLX = 0;
	glXQueryVersion(display, &majorGLX, &minorGLX);
	if (majorGLX <= 1 && minorGLX < 2) {
	    LOG("ScrX11Ogl::SinkDevice_Initialize: error: GLX 1.2 or greater is required.");
	    XCloseDisplay(display);
	    return false;
	}
	else {
	    LOG("ScrX11Ogl::SinkDevice_Initialize: GLX version: " << majorGLX << "." << minorGLX);
	}
	
	
	GLint glx_attribs[] = {
		GLX_X_RENDERABLE    , True,
		GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
		GLX_RENDER_TYPE     , GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
		GLX_RED_SIZE        , 8,
		GLX_GREEN_SIZE      , 8,
		GLX_BLUE_SIZE       , 8,
		GLX_ALPHA_SIZE      , 8,
		GLX_DEPTH_SIZE      , 24,
		GLX_STENCIL_SIZE    , 8,
		GLX_DOUBLEBUFFER    , True,
		None
	};

	
	// choose display
	int fbcount;
	GLXFBConfig* fbc = glXChooseFBConfig(display, screen_num, glx_attribs, &fbcount);
	if (fbc == 0) {
		LOG("ScrX11Ogl::SinkDevice_Initialize: error: failed to retrieve framebuffer.");
		XCloseDisplay(display);
		return false;
	}

	// Pick the FB config/visual with the most samples per pixel
	int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;
	for (int i = 0; i < fbcount; ++i) {
		XVisualInfo *vi = glXGetVisualFromFBConfig( display, fbc[i] );
		if ( vi != 0) {
			int samp_buf, samples;
			glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
			glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLES       , &samples  );

			if ( best_fbc < 0 || (samp_buf && samples > best_num_samp) ) {
				best_fbc = i;
				best_num_samp = samples;
			}
			if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
				worst_fbc = i;
			worst_num_samp = samples;
		}
		XFree(vi);
	}
	GLXFBConfig bestFbc = fbc[best_fbc];
	XFree(fbc); // Make sure to free this!
	
	
	// get the geometry of the default screen for our display.
	display_width	= DisplayWidth(display, screen_num);
	display_height	= DisplayHeight(display, screen_num);
	int dplanes		= DisplayPlanes(display, screen_num);
	
	visual			= glXGetVisualFromFBConfig( display, bestFbc );
	if (visual == 0) {
		LOG("ScrX11Ogl::SinkDevice_Initialize: error: Could not create correct visual window.");
		XCloseDisplay(display);
		return false;
	}
	
	if (screen_num != visual->screen) {
		LOG("ScrX11Ogl::SinkDevice_Initialize: error: screen_num(" << screen_num << ") does not match visual->screen(" << visual->screen << ").");
		XCloseDisplay(display);
		return false;
	}
	
	// default resolution is 1280x720 for now
	width = 1280;
	height = 720;
	RTLOG("ScrX11Ogl::SinkDevice_Initialize: window width - '" << width << "'; height - '" << height << "'");
	
	// create a simple window, as a direct child of the screen's
	// root window. Use the screen's white color as the background
	// color of the window. Place the new window's top-left corner
	// at the given 'x,y' coordinates.
	{
		int screen_num = DefaultScreen(display);
		int win_border_width = 2;
		
		// Set window attributes
		XSetWindowAttributes& attr = ctx.attr;
		attr.border_pixel = BlackPixel(display, screen_num);
		attr.background_pixel = WhitePixel(display, screen_num);
		attr.override_redirect = True;
		attr.colormap = XCreateColormap(display, RootWindow(display, screen_num), visual->visual, AllocNone);
		attr.event_mask = ExposureMask;
		
		// Open window
		win = XCreateWindow(
			display, RootWindow(display, screen_num),
			x, y, width, height,
			win_border_width, visual->depth,
			InputOutput, visual->visual,
			CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
			&attr);
		
		// Redirect Close
		ctx.atomWmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", False);
		XSetWMProtocols(display, win, &ctx.atomWmDeleteWindow, 1);
		
		// Enable input
		XSelectInput(display, win, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask);
		//ctx.xkb = XkbGetMap(display, XkbAllClientInfoMask, XkbUseCoreKbd);
		
		dev.ctx->wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
		XSetWMProtocols(display, win, &dev.ctx->wmDeleteMessage, 1);
		
		// Create GLX OpenGL context
		typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
		glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
		glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
		if (glXCreateContextAttribsARB == 0) {
			LOG("ScrX11Ogl::SinkDevice_Initialize: warning: glXCreateContextAttribsARB() not found.");
		}
		
		// Create OpenGL context
		#if CPU_ARM
		// gles 2.0
		int context_attribs[] = {
			GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
			GLX_CONTEXT_MINOR_VERSION_ARB, 0,
			GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_ES_PROFILE_BIT_EXT | GLX_CONTEXT_ES2_PROFILE_BIT_EXT,
			None
		};
		#else
		// opengl 4.2
		int context_attribs[] = {
			GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
			GLX_CONTEXT_MINOR_VERSION_ARB, 2,
			GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			None
		};
		#endif
		
		dev.gl_ctx = 0;
		const char *glxExts = glXQueryExtensionsString( display,  screen_num );
		LOG("ScrX11Ogl::SinkDevice_Initialize: Late extensions:");
		Vector<String> ext_list = Split(glxExts, " ");
		for (const String& s : ext_list) {LOG("\t" << s);}
		
		if (!X11Ogl_IsExtensionSupported( glxExts, "GLX_ARB_create_context")) {
			LOG("ScrX11Ogl::SinkDevice_Initialize: warning: GLX_ARB_create_context not supported");
			dev.gl_ctx = glXCreateNewContext( display, bestFbc, GLX_RGBA_TYPE, 0, True );
		}
		else {
			dev.gl_ctx = glXCreateContextAttribsARB( display, bestFbc, 0, true, context_attribs );
		}
		XSync( display, False );
		
		
		// Verifying that context is a direct context
		if (!glXIsDirect (display, dev.gl_ctx)) {
			LOG("ScrX11Ogl::SinkDevice_Initialize: warning: indirect GLX rendering context obtained");
		}
		else {
			LOG("ScrX11Ogl::SinkDevice_Initialize: direct GLX rendering context obtained");
		}
		glXMakeCurrent(display, win, dev.gl_ctx);

		
		LOG("GL Vendor: " << (const char*)glGetString(GL_VENDOR));
		LOG("GL Renderer: " << (const char*)glGetString(GL_RENDERER));
		LOG("GL Version: " << (const char*)glGetString(GL_VERSION));
		LOG("GL Shading Language: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
		
		
		// Glew
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			LOG("Glew error: " << (const char*)glewGetErrorString(err));
			return false;
		}
		
	
		// make the window actually appear on the screen.
		XMapWindow(display, win);
		
		// Configure borderless & fullscreen related properties
		if ((find_vr || screen_idx >= 0) && is_fullscreen) {
			Index<Rect> screens;
			XRRScreenResources *xrrr = XRRGetScreenResources(display, win);
		    XRRCrtcInfo *xrrci;
		    int i;
		    int ncrtc = xrrr->ncrtc;
		    for (i = 0; i < ncrtc; ++i) {
		        xrrci = XRRGetCrtcInfo(display, xrrr, xrrr->crtcs[i]);
		        if (xrrci->width > 0 && xrrci->height > 0) {
		            if (find_vr && xrrci->width == 1440*2 && xrrci->height == 1440)
		                screen_idx = screens.GetCount();
					screens.FindAdd(RectC(xrrci->x, xrrci->y, xrrci->width, xrrci->height));
		        }
		        //LOG("\tscreen " << i << ": " << xrrci->width << "x" << xrrci->height << "," << xrrci->x << "," << xrrci->y);
		        XRRFreeCrtcInfo(xrrci);
		    }
		    XRRFreeScreenResources(xrrr);
		    
		    DUMPC(screens);
		    if (screen_idx < 0 || screen_idx >= screens.GetCount()) {
		        LOG("ScrX11Ogl::SinkDevice_Initialize: error: screen index out of range");
				return false;
		    }
		    Rect r = screens[screen_idx];
			LOG("ScrX11Ogl::SinkDevice_Initialize: info: moving x11 window to " << AsString(r));
			
			int mode_count = 0;
			XF86VidModeModeInfo** modes = 0;
			XF86VidModeGetAllModeLines(display, screen_num, &mode_count, &modes);
			if (!mode_count) {
				LOG("ScrX11Ogl::SinkDevice_Initialize: error: could not get video modes");
				return false;
			}
			if (print_modes) {
				for(int i = 0; i < mode_count; i++) {
					XF86VidModeModeInfo* mode = modes[i];
					LOG("XF86 mode " << i << ":\n"
						"\tdotclock: " << (int)mode->dotclock << "\n"
						"\thdisplay: " << (int)mode->hdisplay << "\n"
						"\thsyncstart: " << (int)mode->hsyncstart << "\n"
						"\thsyncend: " << (int)mode->hsyncend << "\n"
						"\thtotal: " << (int)mode->htotal << "\n"
						"\thskew: " << (int)mode->hskew << "\n"
						"\tvdisplay: " << (int)mode->vdisplay << "\n"
						"\tvsyncstart: " << (int)mode->vsyncstart << "\n"
						"\tvsyncend: " << (int)mode->vsyncend << "\n"
						"\tvtotal: " << (int)mode->vtotal << "\n"
						"\tflags: " << (int)mode->flags << "\n"
						"\tprivsize: " << (int)mode->privsize << "\n");
				}
			}
			XF86VidModeModeInfo* video_mode = modes[0];
			XChangeProperty(display, win, hints_property, hints_property, 32, PropModeReplace, (unsigned char *)&hints, 5);
			XF86VidModeSwitchToMode(display, screen_num, video_mode);
			if (is_fullscreen) {
				int x = r.left;
				int y = r.top;
				width = r.GetWidth();
				height = r.GetHeight();
				XF86VidModeSetViewPort(display, screen_num, 0, 0);
				XMoveResizeWindow(display, win, x, y, width, height);
				XMapRaised(display, win);
			}
			//XGrabPointer(display, win, True, 0, GrabModeAsync, GrabModeAsync, win, 0L, CurrentTime);
			//XGrabKeyboard(display, win, False, GrabModeAsync, GrabModeAsync, CurrentTime);
		}
		else if (is_fullscreen) {
			::Atom wm_state = XInternAtom (display, "_NET_WM_STATE", true );
			::Atom wm_fullscreen = XInternAtom (display, "_NET_WM_STATE_FULLSCREEN", true );
			
			XChangeProperty(display, win, wm_state, ((::Atom) 4), 32,
			    PropModeReplace, (unsigned char *)&wm_fullscreen, 1);
		}
		
		// flush all pending requests to the X server.
		XFlush(display);
	}
	
	TS::default_width = width;
	TS::default_height = height;
	
	XSync(display, False);
	
	
	dev.accel.SetNative(ctx.display, ctx.win, 0, 0);
	
	if (!dev.accel.Open(Size(width, height), 4, true)) {
		LOG("ScrX11Ogl::SinkDevice_Initialize: error: could not open opengl atom");
		return false;
	}
	
	return true;
}

bool ScrX11Ogl::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	return dev.accel.PostInitialize();
}

bool ScrX11Ogl::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

void ScrX11Ogl::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	
}

void ScrX11Ogl::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	auto& ctx = *dev.ctx;
	
	dev.accel.Uninitialize();
	
	//XkbFreeKeyboard(ctx.xkb, XkbAllComponentsMask, True);

	glXDestroyContext(ctx.display, dev.gl_ctx);
	XFree(ctx.visual_info);
	XFreeColormap(ctx.display, ctx.attr.colormap);
	XDestroyWindow(ctx.display, ctx.win);

	if (ctx.running) {
		// flush all pending requests to the X server.
		XFlush(ctx.display);
		
		// close the connection to the X server.
		XCloseDisplay(ctx.display);
	}
}

bool ScrX11Ogl::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase&, int ch_i, const Packet& p) {
	return dev.accel.Recv(ch_i, p);
}

void ScrX11Ogl::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase&, RealtimeSourceConfig& cfg) {
	auto& ctx = *dev.ctx;
	
	if (!ctx.running)
		return;
	
}

bool ScrX11Ogl::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	
	dev.accel.Render(cfg);
	
	return true;
}

bool ScrX11Ogl::SinkDevice_NegotiateSinkFormat(NativeSinkDevice& dev, AtomBase&, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	return false;
}

bool ScrX11Ogl::SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase&, PacketIO& io) {
	return true;
}





bool ScrX11Ogl::Context_Create(One<NativeContext>& dev) {
	dev.Create();
	return true;
}

void ScrX11Ogl::Context_Destroy(One<NativeContext>& dev) {
	dev.Clear();
}

void ScrX11Ogl::Context_Visit(NativeContext& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool ScrX11Ogl::Context_Initialize(NativeContext& ctx, AtomBase& a, const Script::WorldState& ws) {
	ctx.running = true;
	return true;
}

bool ScrX11Ogl::Context_PostInitialize(NativeContext& ctx, AtomBase& a) {
	return true;
}

bool ScrX11Ogl::Context_Start(NativeContext& ctx, AtomBase& a) {
	return true;
}

void ScrX11Ogl::Context_Stop(NativeContext& ctx, AtomBase& a) {
	
}

void ScrX11Ogl::Context_Uninitialize(NativeContext& ctx, AtomBase& a) {
	
}

bool ScrX11Ogl::Context_Send(NativeContext& ctx, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return false;
}

bool ScrX11Ogl::Context_Recv(NativeContext& ctx, AtomBase& a, int sink_ch, const Packet&) {
	return false;
}

void ScrX11Ogl::Context_Finalize(NativeContext& ctx, AtomBase& a, RealtimeSourceConfig&) {
	
}

bool ScrX11Ogl::Context_NegotiateSinkFormat(NativeContext& ctx, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	return false;
}

bool ScrX11Ogl::Context_IsReady(NativeContext& dev, AtomBase&, PacketIO& io) {
	return true;
}


bool ScrX11Ogl::EventsBase_Create(One<NativeEventsBase>& dev) {
	dev.Create();
	return true;
}

void ScrX11Ogl::EventsBase_Destroy(One<NativeEventsBase>& dev) {
	dev.Clear();
}

void ScrX11Ogl::EventsBase_Visit(NativeEventsBase& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool ScrX11Ogl::EventsBase_Initialize(NativeEventsBase& ev, AtomBase& a, const Script::WorldState& ws) {
	auto ctx_ = a.GetSpace()->template FindNearestAtomCast<X11OglContext>(1);
	ASSERT(ctx_);
	if (!ctx_) {RTLOG("error: could not find X11 context"); return false;}
	ev.ctx = &*ctx_->dev;
	
	
	return true;
}

bool ScrX11Ogl::EventsBase_PostInitialize(NativeEventsBase& ev, AtomBase& a) {
	if (!ev.ctx->win) {
		LOG("ScrX11Ogl::EventsBase_PostInitialize: error: context has no window");
		return false;
	}
	
	return true;
}

bool ScrX11Ogl::EventsBase_Start(NativeEventsBase& ev, AtomBase& a) {
	
	return true;
}

void ScrX11Ogl::EventsBase_Stop(NativeEventsBase& ev, AtomBase& a) {
	
}

void ScrX11Ogl::EventsBase_Uninitialize(NativeEventsBase& ev, AtomBase& a) {
	
}

bool ScrX11Ogl::EventsBase_Send(NativeEventsBase& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	ASSERT(dev.ev_sendable);
	if (!dev.ev_sendable)
		return false;
	

	Format fmt = out.GetFormat();
	RTLOG("ScrX11Ogl::EventsBase_Send: " << fmt.ToString());
	
	if (fmt.IsEvent()) {
		out.seq = dev.seq++;
		UPP::CtrlEvent& dst = out.SetData<UPP::CtrlEvent>();
		dst = dev.ev;
		dev.ev_sendable = false;
	}
	
	return true;
}

bool ScrX11Ogl::EventsBase_Recv(NativeEventsBase& ev, AtomBase& a, int sink_ch, const Packet&) {
	
	return true;
}

int ConvertX11Keycode(ScrX11Ogl::NativeEventsBase&, int key);

void X11Events__PutKeyFlags(ScrX11Ogl::NativeEventsBase& dev, dword& key) {
	if (dev.is_lalt   || dev.is_ralt)		key |= K_ALT;
	if (dev.is_lshift || dev.is_rshift)		key |= K_SHIFT;
	if (dev.is_lctrl  || dev.is_rctrl)		key |= K_CTRL;
}

bool X11Events__Poll(ScrX11Ogl::NativeEventsBase& dev, AtomBase& a) {
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

bool ScrX11Ogl::EventsBase_IsReady(NativeEventsBase& dev, AtomBase& a, PacketIO& io) {
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
	RTLOG("ScrX11Ogl::EventsBase_IsReady: " << (b ? "true" : "false"));
	return b;
}


void ScrX11Ogl::EventsBase_Finalize(NativeEventsBase& ev, AtomBase& a, RealtimeSourceConfig&) {
	
}

bool ScrX11Ogl::EventsBase_NegotiateSinkFormat(NativeEventsBase& ev, AtomBase& a, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	
	return false;
}






static const struct {
    int keycode;
    int scancode;
} KeySymToTSScancodeOGL[] = {
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

int ConvertX11Keycode(ScrX11Ogl::NativeEventsBase& dev, int keycode)
{
    for (int i = 0; i < TS_arraysize(KeySymToTSScancodeOGL); ++i) {
        if (keycode == KeySymToTSScancodeOGL[i].keycode) {
            return KeySymToTSScancodeOGL[i].scancode;
        }
    }
    return keycode;
}


NAMESPACE_PARALLEL_END
#endif

