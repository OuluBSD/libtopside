#include "IScreen.h"

#if (defined flagLINUX) || (defined flagFREEBSD)
NAMESPACE_PARALLEL_BEGIN

bool ScrX11Glx::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	::Display*& display = dev.display;	// pointer to X Display structure.
	int screen_num;						// number of screen to place the window on.
	::Window& win = dev.win;			// pointer to the newly created window.
	unsigned int display_width,
	             display_height;		// height and width of the X display.
	unsigned int width, height;			// height and width for the new window.
	char *display_name = getenv("DISPLAY"); // address of the X display.
	::GC& gc = dev.gc;					// GC (graphics context) used for drawing
										// in our window.
	::Visual*& visual = dev.visual;
	
	int x = 0;
	int y = 0;
	
	bool reverse_video = false;
	
	// open connection with the X server.
	display = XOpenDisplay(display_name);
	if (display == NULL) {
		LOG("ScrX11Glx::SinkDevice_Initialize: error: cannot connect to X server '" << display_name << "'");
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
	RTLOG("ScrX11Glx::SinkDevice_Initialize: window width - '" << width << "'; height - '" << height << "'");
	
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
			LOG("ScrX11Glx::SinkDevice_Initialize: error: XCreateGC failed");
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
	
	int bpp = 3;
	
	
	GLint majorGLX, minorGLX = 0;
	glXQueryVersion(display, &majorGLX, &minorGLX);
	if (majorGLX <= 1 && minorGLX < 2) {
	    LOG("ScrX11Glx::SinkDevice_Initialize: error: GLX 1.2 or greater is required.");
	    XCloseDisplay(display);
	    return false;
	}
	else {
	    LOG("ScrX11Glx::SinkDevice_Initialize: GLX version: " << majorGLX << "." << minorGLX);
	}
	
	GLint glxAttribs[] = {
		GLX_RGBA,
		GLX_DOUBLEBUFFER,
		GLX_DEPTH_SIZE,     24,
		GLX_STENCIL_SIZE,   8,
		GLX_RED_SIZE,       8,
		GLX_GREEN_SIZE,     8,
		GLX_BLUE_SIZE,      8,
		GLX_SAMPLE_BUFFERS, 0,
		GLX_SAMPLES,        0,
		None
	};
	
	XVisualInfo* glx_visual = glXChooseVisual(display, screen_num, glxAttribs);
	
	if (glx_visual == 0) {
		LOG("ScrX11Glx::SinkDevice_Initialize: error: Could not create correct visual window.");
		XCloseDisplay(display);
		return false;
	}
	
	
	XSync(display, False);
	
	return true;
}

bool ScrX11Glx::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

bool ScrX11Glx::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

void ScrX11Glx::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	
}

void ScrX11Glx::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	// flush all pending requests to the X server.
	XFlush(dev.display);
	
	// close the connection to the X server.
	XCloseDisplay(dev.display);
}

bool ScrX11Glx::SinkDevice_ProcessPacket(NativeSinkDevice& dev, AtomBase& a, PacketValue& in, PacketValue& out) {
	Format fmt = in.GetFormat();
	ASSERT(fmt.IsOgl());
	FboFormat& vfmt = fmt;
	int frame_sz = vfmt.GetFrameSize();
	
	/*int width = vfmt.res[0];
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
    
    if (fmt.IsOrder()) {
        
    }
    else {
        TODO
    }
    
	XFlush(dev.display);
	//XSync(dev.display, False);
	
	return true;
}





NAMESPACE_PARALLEL_END
#endif

