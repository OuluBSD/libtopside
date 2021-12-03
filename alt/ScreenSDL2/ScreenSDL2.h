#ifndef _ScreenSDL2_ScreenSDL2_h_
#define _ScreenSDL2_ScreenSDL2_h_

#include <Draw/Draw.h>
// Not here: #include <OOSDL2/OOSDL2.h>


#ifndef flagSCREEN
	#error ScreenSDL2 requires SCREEN flag
#endif


NAMESPACE_UPP


class SystemDraw : public DrawProxy {
public:
	RTTI_DECL1(SystemDraw, DrawProxy)
	
	bool    CanSetSurface()                         { return false; }
	static void Flush()                             {}
};

class ImageDraw : public SImageDraw {
public:
	ImageDraw() {}
	ImageDraw(Size sz) : SImageDraw(sz) {}
	ImageDraw(int cx, int cy) : SImageDraw(cx, cy) {}
	
};



enum {
	K_DELTA        = 0x010000,

	K_ALT          = 0x080000,
	K_SHIFT        = 0x040000,
	K_CTRL         = 0x020000,

	K_KEYUP        = 0x100000,

	K_MOUSEMIDDLE  = 0x200000,
	K_MOUSERIGHT   = 0x400000,
	K_MOUSELEFT    = 0x800000,
	K_MOUSEDOUBLE  = 0x1000000,
	K_MOUSETRIPLE  = 0x2000000,

	K_SHIFT_CTRL = K_SHIFT|K_CTRL,

#ifdef PLATFORM_COCOA
	K_OPTION       = 0x4000000,
#endif

	IK_DBL_CLICK   = 0x40000001, // this is just to get the info that the entry is equal to dbl-click to the menu
	
	K_MOUSE_FORWARD = 0x80000001,
	K_MOUSE_BACKWARD = 0x80000002,
};


class Ctrl : public Pte<Ctrl> {
	
public:
	
	enum PlacementConstants {
		CENTER   = 0,
		MIDDLE   = 0,
		LEFT     = 1,
		RIGHT    = 2,
		TOP      = 1,
		BOTTOM   = 2,
		SIZE     = 3,

		MINSIZE  = -16380,
		MAXSIZE  = -16381,
		STDSIZE  = -16382,
	};
	
	enum MouseEvents {
		BUTTON        = 0x0F,
		ACTION        = 0xFF0,

		MOUSEENTER    = 0x10,
		MOUSEMOVE     = 0x20,
		MOUSELEAVE    = 0x30,
		CURSORIMAGE   = 0x40,
		MOUSEWHEEL    = 0x50,

		DOWN          = 0x80,
		UP            = 0x90,
		DOUBLE        = 0xa0,
		REPEAT        = 0xb0,
		DRAG          = 0xc0,
		HOLD          = 0xd0,
		TRIPLE        = 0xe0,
		PEN           = 0xf0,
		PENLEAVE      = 0x100,

		LEFTDOWN      = LEFT|DOWN,
		LEFTDOUBLE    = LEFT|DOUBLE,
		LEFTREPEAT    = LEFT|REPEAT,
		LEFTUP        = LEFT|UP,
		LEFTDRAG      = LEFT|DRAG,
		LEFTHOLD      = LEFT|HOLD,
		LEFTTRIPLE    = LEFT|TRIPLE,

		MIDDLEDOWN     = MIDDLE|DOWN,
		MIDDLEDOUBLE   = MIDDLE|DOUBLE,
		MIDDLEREPEAT   = MIDDLE|REPEAT,
		MIDDLEUP       = MIDDLE|UP,
		MIDDLEDRAG     = MIDDLE|DRAG,
		MIDDLEHOLD     = MIDDLE|HOLD,
		MIDDLETRIPLE   = MIDDLE|TRIPLE,
		
		RIGHTDOWN     = RIGHT|DOWN,
		RIGHTDOUBLE   = RIGHT|DOUBLE,
		RIGHTREPEAT   = RIGHT|REPEAT,
		RIGHTUP       = RIGHT|UP,
		RIGHTDRAG     = RIGHT|DRAG,
		RIGHTHOLD     = RIGHT|HOLD,
		RIGHTTRIPLE   = RIGHT|TRIPLE
	};
	
};






END_UPP_NAMESPACE


#endif
