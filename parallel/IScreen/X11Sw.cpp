#include "IScreen.h"

#if (defined flagLINUX) || (defined flagFREEBSD)
NAMESPACE_PARALLEL_BEGIN

bool ScrX11Sw::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	
	if (!dev.accel.Initialize(a, ws))
		return false;
	
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
	
	int bpp = 3;
	
	::XImage*& fb = dev.fb;
	fb = XCreateImage(
		dev.display,
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
	
	XSync(display, False);
	
	dev.accel_buf.Set(width, height, bpp, width * bpp, 0);
	dev.accel_buf.Randomize();
	dev.accel_fbo.SetColor(TEXTYPE_NONE, &dev.accel_buf);
	dev.accel_fbo.SetDepth(&dev.accel_zbuf);
	
	dev.accel.SetNative(dev.display, dev.win, 0, &dev.accel_fbo);
	
	if (!dev.accel.Open(Size(width, height), 4)) {
		LOG("ScrX11Ogl::SinkDevice_Initialize: error: could not open opengl atom");
		return false;
	}
	
	return true;
}

bool ScrX11Sw::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

bool ScrX11Sw::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

void ScrX11Sw::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	
	XDestroyWindow(dev.display, dev.win);
	
}

void ScrX11Sw::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	dev.accel.Uninitialize();
	
	// Causes crash:
		//XFree(dev.visual);
		//XFreeColormap(dev.display, dev.attr.colormap);
		
	// flush all pending requests to the X server.
	XFlush(dev.display);
	
	// close the connection to the X server.
	XCloseDisplay(dev.display);
	dev.display = 0;
	
}

bool ScrX11Sw::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	return dev.accel.Recv(sink_ch, in);
}

void ScrX11Sw::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	dev.accel.Render(cfg);
	
	{
		XWindowAttributes attr;
		XGetWindowAttributes(dev.display, dev.win, &attr);
		
		int width = attr.width;
		int height = attr.height;
		int bpp = attr.depth / 8;
		int len = width * height * bpp;
		ASSERT(dev.accel_buf.GetSize() == len);
		
		ASSERT(dev.fb);
		ASSERT(!dev.fb->data);
	    dev.fb->data = (char*)(const unsigned char*)dev.accel_buf.Begin();
	    dev.fb->bytes_per_line = width * bpp;
	    ASSERT(width == dev.fb->width);
	    ASSERT(height == dev.fb->height);
	    if (width != dev.fb->width || height != dev.fb->height) {
	        LOG("ScrX11::SinkDevice_ProcessPacket: error: invalid resolution");
	        dev.fb->data = 0;
	        return;
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
	        return;
	    }
	    
		XFlush(dev.display);
		//XSync(dev.display, False);
		
		dev.fb->data = 0;
	}
}

bool ScrX11Sw::SinkDevice_ProcessPacket(NativeSinkDevice& dev, AtomBase& a, PacketValue& in, PacketValue& out) {
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





NAMESPACE_PARALLEL_END
#endif
