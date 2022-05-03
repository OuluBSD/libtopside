#include "IScreen.h"

/*#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>*/
		
#if defined flagOGL
NAMESPACE_PARALLEL_BEGIN


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



bool ScrX11Ogl::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	
	if (!dev.ogl.Initialize(a, ws))
		return false;
	
	::Display*& display = dev.display;	// pointer to X Display structure.
	::Window& win = dev.win;			// pointer to the newly created window.
	::XVisualInfo*& visual = dev.visual;
	int screen_num;						// number of screen to place the window on.
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
	screen_num		= DefaultScreen(display);
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
		XSetWindowAttributes& attr = dev.attr;
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
		dev.atomWmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", False);
		XSetWMProtocols(display, win, &dev.atomWmDeleteWindow, 1);
		
		// Create GLX OpenGL context
		typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
		glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
		glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
		if (glXCreateContextAttribsARB == 0) {
			LOG("ScrX11Ogl::SinkDevice_Initialize: warning: glXCreateContextAttribsARB() not found.");
		}
		
		
		// Create OpenGL context
		/*dev.gl_ctx = glXCreateContext(display, visual, NULL, GL_TRUE);
		glXMakeCurrent(display, win, context);*/
		
		int context_attribs[] = {
			GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
			GLX_CONTEXT_MINOR_VERSION_ARB, 2,
			GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			None
		};
		
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
		
		// flush all pending requests to the X server.
		XFlush(display);
	}
	
	
	XSync(display, False);
	
	
	dev.ogl.SetNative(dev.display, dev.win, 0, 0);
	
	if (!dev.ogl.Open(Size(width, height), 4)) {
		LOG("ScrX11Ogl::SinkDevice_Initialize: error: could not open opengl atom");
		return false;
	}
	
	return true;
}

bool ScrX11Ogl::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	return dev.ogl.PostInitialize();
}

bool ScrX11Ogl::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

void ScrX11Ogl::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	
}

void ScrX11Ogl::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	dev.ogl.Uninitialize();
	
	glXDestroyContext(dev.display, dev.gl_ctx);
	XFree(dev.visual);
	XFreeColormap(dev.display, dev.attr.colormap);
	XDestroyWindow(dev.display, dev.win);

	// flush all pending requests to the X server.
	XFlush(dev.display);
	
	// close the connection to the X server.
	XCloseDisplay(dev.display);
}

bool ScrX11Ogl::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase&, int ch_i, const Packet& p) {
	return dev.ogl.Recv(ch_i, p);
}

void ScrX11Ogl::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase&, RealtimeSourceConfig& cfg) {
	dev.ogl.Render(cfg);
}

bool ScrX11Ogl::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, PacketValue& out) {
	/*Format fmt = in.GetFormat();
	
	int width = vfmt.res[0];
	int height = vfmt.res[1];
	
	ASSERT(dev.fb);
	ASSERT(!dev.fb->data);
    dev.fb->data = (char*)(const unsigned char*)pixmap.Begin();
    dev.fb->bytes_per_line = vfmt.res[0] * vfmt.GetPackedCount();
    ASSERT(width == dev.fb->width);
    ASSERT(height == dev.fb->height);
    if (width != dev.fb->width || height != dev.fb->height) {
        LOG("ScrX11::SinkDevice_ProcessPacket: error: invalid resolution");
        return false;
    }
    
    int rc = XPutImage(	dev.display,
						dev.win,
						dev.gc,
						dev.fb,
						0,0,
						0,0,
						width,
						height);
    
    if (rc == BadMatch) {
        LOG("ScrX11::SinkDevice_ProcessPacket: error: XPutImage returned BadMatch");
        dev.fb->data = 0;
        return false;
    }*/
    
    /*if (fmt.IsOrder()) {
        
        TODO
        
    }
    else if (fmt.IsOgl()) {
        TODO
        FboFormat& vfmt = fmt;
		int frame_sz = vfmt.GetFrameSize();
    }
    else {
        TODO
    }
    
	XFlush(dev.display);*/
	//XSync(dev.display, False);
	
	return true;
}

bool ScrX11Ogl::SinkDevice_NegotiateSinkFormat(NativeSinkDevice& dev, AtomBase&, Serial::Link& link, int sink_ch, const Format& new_fmt) {
	return false;
}





NAMESPACE_PARALLEL_END
#endif

