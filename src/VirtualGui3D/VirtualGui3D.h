#ifndef _VirtualGui3D_VirtualGui3D_h_
#define _VirtualGui3D_VirtualGui3D_h_

#include <Draw/Draw.h>
#include <StaticInterface/Screen.h>

#if IS_TS_CORE

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

END_UPP_NAMESPACE

#endif


NAMESPACE_UPP

struct VirtualGui3D : RTTIBase {
	RTTI_DECL0(VirtualGui3D)
	
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

END_UPP_NAMESPACE

#if IS_TS_CORE

NAMESPACE_UPP

class ImageDraw : public SImageDraw {
public:
	ImageDraw(Size sz) : SImageDraw(sz) {}
	ImageDraw(Size sz, int stride) : SImageDraw(sz, stride) {}
	ImageDraw(int cx, int cy) : SImageDraw(cx, cy) {}
	
};



#define GUIPLATFORM_CTRL_TOP_DECLS   Ctrl *owner_window;



#define GUIPLATFORM_PASTECLIP_DECLS \
	bool dnd; \
	friend struct DnDLoop; \

#define GUIPLATFORM_INCLUDE_AFTER <VirtualGui3D/After.h>
#define GUIPLATFORM_INCLUDE_AFTER_ECSLIB <VirtualGui3D/AfterEcsLib.h>


END_UPP_NAMESPACE


#endif
#endif
