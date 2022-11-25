#ifndef _VirtualGui3D_VirtualGui3D_h_
#define _VirtualGui3D_VirtualGui3D_h_

#include <Draw/Draw.h>
#include <StaticInterface/Screen.h>


NAMESPACE_UPP


struct VirtualGui3D;


class SystemDraw : public DrawProxy {
public:
	RTTI_DECL1(SystemDraw, DrawProxy)
	
	bool    CanSetSurface()                         { return false; }
	static void Flush()                             {}
};

enum KM {
	KM_NONE  = 0x00,

	KM_LSHIFT= 0x01,
	KM_RSHIFT= 0x02,
	KM_LCTRL = 0x04,
	KM_RCTRL = 0x08,
	KM_LALT  = 0x10,
	KM_RALT  = 0x20,

	KM_CAPS  = 0x40,
	KM_NUM   = 0x80,
	
	KM_CTRL = KM_LCTRL | KM_RCTRL,
	KM_SHIFT = KM_LSHIFT | KM_RSHIFT,
	KM_ALT = KM_LALT | KM_RALT,
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

struct VirtualGui3D {
	virtual bool        Poll(UPP::CtrlEvent& e) = 0;
	virtual Size        GetSize() = 0;
	virtual void        SetTitle(String title) = 0;
	virtual SystemDraw& BeginDraw() = 0;
	virtual void        CommitDraw() = 0;
	virtual uint32      GetTickCount() = 0;
	virtual void        WaitEvent(int ms) = 0;
	virtual void        WakeUpGuiThread() = 0;
	virtual bool        IsWaitingEvent() = 0;
	
};

extern VirtualGui3D* VirtualGui3DPtr;

class ImageDraw : public SImageDraw {
public:
	ImageDraw(Size sz) : SImageDraw(sz) {}
	ImageDraw(Size sz, int stride) : SImageDraw(sz, stride) {}
	ImageDraw(int cx, int cy) : SImageDraw(cx, cy) {}
	
};


struct VirtualCtrl : RTTIBase {
	RTTI_DECL0(VirtualCtrl)
	
	
	/*enum {
		UNKNOWN,
		LEFT_DOWN,
		LEFT_DOUBLE,
		LEFT_TRIPLE,
		LEFT_DRAG,
		LEFT_HOLD,
		LEFT_REPEAT,
		LEFT_UP,
		RIGHT_DOWN,
		RIGHT_DOUBLE,
		RIGHT_TRIPLE,
		RIGHT_DRAG,
		RIGHT_HOLD,
		RIGHT_REPEAT,
		RIGHT_UP,
		MIDDLE_DOWN,
		MIDDLE_DOUBLE,
		MIDDLE_TRIPLE,
		MIDDLE_DRAG,
		MIDDLE_HOLD,
		MIDDLE_REPEAT,
		MIDDLE_UP,
	};
	
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
		ACTION        = 0xF0,

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

		RIGHTDOWN     = RIGHT|DOWN,
		RIGHTDOUBLE   = RIGHT|DOUBLE,
		RIGHTREPEAT   = RIGHT|REPEAT,
		RIGHTUP       = RIGHT|UP,
		RIGHTDRAG     = RIGHT|DRAG,
		RIGHTHOLD     = RIGHT|HOLD,
		RIGHTTRIPLE   = RIGHT|TRIPLE,

		MIDDLEDOWN     = MIDDLE|DOWN,
		MIDDLEDOUBLE   = MIDDLE|DOUBLE,
		MIDDLEREPEAT   = MIDDLE|REPEAT,
		MIDDLEUP       = MIDDLE|UP,
		MIDDLEDRAG     = MIDDLE|DRAG,
		MIDDLEHOLD     = MIDDLE|HOLD,
		MIDDLETRIPLE   = MIDDLE|TRIPLE
	};*/
	
};

#define GUIPLATFORM_CTRL_TOP_DECLS   Ctrl *owner_window;



#define GUIPLATFORM_PASTECLIP_DECLS \
	bool dnd; \
	friend struct DnDLoop; \

#define GUIPLATFORM_INCLUDE_AFTER <VirtualGui3D/After.h>
#define GUIPLATFORM_INCLUDE_AFTER_ECSLIB <VirtualGui3D/AfterEcsLib.h>


END_UPP_NAMESPACE


#endif
