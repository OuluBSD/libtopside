#if defined flagPOSIX && defined flagX11
#include <X11/Xlib.h>
#include <X11/Xatom.h>


void SetSemiTransparent0(double alpha, Display* display, unsigned long win) {
	unsigned long opacity = (unsigned long)(0xFFFFFFFFul * alpha);
	Atom XA_NET_WM_WINDOW_OPACITY = XInternAtom(display, "_NET_WM_WINDOW_OPACITY", False);
	XChangeProperty(display, win, XA_NET_WM_WINDOW_OPACITY, XA_CARDINAL, 32,
	                PropModeReplace, (unsigned char *)&opacity, 1L);
	
}

#endif

