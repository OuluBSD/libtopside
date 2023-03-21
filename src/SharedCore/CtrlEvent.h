#ifndef _CoreAlt_CtrlEvent_h_
#define _CoreAlt_CtrlEvent_h_

NAMESPACE_UPP

enum {
	HOLO_CALIB_FOV,
	HOLO_CALIB_SCALE,
	HOLO_CALIB_EYE_DIST,
	HOLO_CALIB_X,
	HOLO_CALIB_Y,
	HOLO_CALIB_Z,
	HOLO_CALIB_YAW,
	HOLO_CALIB_PITCH,
	HOLO_CALIB_ROLL,
};

typedef enum {
	EVENT_INVALID,
	EVENT_WINDOW_RESIZE,
	EVENT_SHUTDOWN,
	EVENT_KEYDOWN,
	EVENT_KEYUP,
	EVENT_MOUSEMOVE,
	//EVENT_MOUSEDRAG,
	EVENT_MOUSEWHEEL,
	EVENT_MOUSE_EVENT,
	
	
	EVENT_HOLO_STATE,
	EVENT_HOLO_LOOK,
	EVENT_HOLO_CALIB,
	
	EVENT_HOLO_CONTROLLER_DETECTED,
	EVENT_HOLO_CONTROLLER_LOST,
	EVENT_HOLO_MOVE_FAR_RELATIVE,
	EVENT_HOLO_MOVE_NEAR,
	EVENT_HOLO_MOVE_CONTROLLER,
	EVENT_HOLO_PRESSED,
	EVENT_HOLO_RELEASED,
	EVENT_HOLO_UPDATED,
	
	EVENT_TYPE_COUNT
} GeomEventType;


inline String GetEventTypeString(int event) {
	switch (event) {
		case EVENT_WINDOW_RESIZE:	return "Window Resize";
		case EVENT_SHUTDOWN:		return "Shutdown";
		case EVENT_KEYDOWN:			return "Key Down";
		case EVENT_KEYUP:			return "Key Up";
		case EVENT_MOUSEMOVE:		return "Mouse Move";
		//case EVENT_MOUSEDRAG:		return "Mouse Drag";
		case EVENT_MOUSEWHEEL:		return "Mouse Wheel";
		case EVENT_MOUSE_EVENT:		return "Mouse Event";
		
		case EVENT_HOLO_STATE:					return "Holographic full state";
		case EVENT_HOLO_LOOK:					return "Holographic Look";
		case EVENT_HOLO_CALIB:					return "Holographic Calibration";
		
		case EVENT_HOLO_CONTROLLER_DETECTED:	return "Holographic controller detected";
		case EVENT_HOLO_CONTROLLER_LOST:		return "Holographic controller lost";
		case EVENT_HOLO_MOVE_FAR_RELATIVE:		return "Holographic Move Far (relative)";
		case EVENT_HOLO_MOVE_NEAR:				return "Holographic Move Near";
		case EVENT_HOLO_PRESSED:				return "Holographi controller button pressed";
		case EVENT_HOLO_RELEASED:				return "Holographi controller button released";
		
		case EVENT_INVALID:
		case EVENT_TYPE_COUNT:
		default:					return "<invalid>";
	}
}


struct ControllerSource : RTTIBase {
	RTTI_DECL0(ControllerSource);
	virtual ~ControllerSource() {}
	
	//virtual bool GetLocation(float* matrix4x4) const {return false;}
	virtual void GetVelocity(float* v3) const = 0;
	virtual void GetAngularVelocity(float* v3) const = 0;
	
};

struct ControllerProperties {
	typedef enum {
		LEFT,
		UP,
		RIGHT,
		DOWN,
		
		A0, // cross
		A1, // rectangle
		A2, // circle
		A3, // triangle
		
		L1, // lower shoulder
		L2, // higher shoulder
		R1, // lower shoulder
		R2, // higher shoulder
		
		SELECT,
		START,
		HOME,
		
		BUTTON_COUNT,
		
		CROSS		= A0,
		RECTANGLE	= A1,
		CIRCLE		= A2,
		TRIANGLE	= A3,
	} Button;
	
	bool pressed[BUTTON_COUNT] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0};
	float touchpad[2][2] = {{0,0},{0,0}};
	float thumbstick[2][2] = {{0,0},{0,0}};
	float touchpad_travel[2] = {0,0};
	float touchpad_pressure[2] = {0,0};
	float shoulder_high[2] = {0,0};
	float shoulder_low[2] = {0,0};
	
	float GetTouchpadX(int i=0) const {return touchpad[i][0];}
	float GetTouchpadY(int i=0) const {return touchpad[i][1];}
	float GetThumbstickX(int i=0) const {return thumbstick[i][0];}
	float GetThumbstickY(int i=0) const {return thumbstick[i][1];}
	bool IsGrasped(int i=0) const {return shoulder_low[i] != 0.0f;}
	bool IsTouchpadTouched(int i=0) const {return touchpad_pressure[i] != 0.0f;}
	bool IsTouchpadPressed(int i=0) const {return touchpad_travel[i] != 0.0f;}
	bool IsSelectPressed() const {return pressed[SELECT];}
	
};

struct ControllerState;
struct TransformMatrix;
struct ControllerMatrix;

#define COPY2(dst, from) for(int i = 0; i < 2; i++) dst[i] = from[i]
#define COPY3(dst, from) for(int i = 0; i < 3; i++) dst[i] = from[i]
#define COPY4(dst, from) for(int i = 0; i < 4; i++) dst[i] = from[i]
#define COPY3x3(dst, from) for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) (dst)[i][j] = (from)[i][j]
#define COPY4x4(dst, from) for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) (dst)[i][j] = (from)[i][j]
	


struct GeomEvent : Moveable<GeomEvent> {
	GeomEventType type = EVENT_INVALID;
	union {
		dword value = 0;
		float fvalue;
	};
	int n = 0;
	Point pt;
	float pt3[3];
	Size sz;
	
	// Device extension
	TransformMatrix* trans = 0;
	ControllerMatrix* ctrl = 0;
	ControllerState* state = 0;
	
	
	RTTI_TYPEIDCLS
	
	const ControllerState& GetState() const {ASSERT(state); return *state;}
	const ControllerMatrix& GetControllerMatrix() const {ASSERT(ctrl); return *ctrl;}
	
	void operator=(const GeomEvent& e) {
		type = e.type;
		value = e.value;
		n = e.n;
		pt.x = e.pt.x;
		pt.y = e.pt.y;
		sz.cx = e.sz.cx;
		sz.cy = e.sz.cy;
		trans = e.trans;
		ctrl = e.ctrl;
		state = e.state;
		for(int i = 0; i < 3; i++) pt3[i] = e.pt3[i];
	}
	
	void Clear() {
		type = EVENT_INVALID;
		value = 0;
		n = 0;
		pt = Point(0,0);
		sz = Size(0,0);
		trans = 0;
		ctrl = 0;
		state = 0;
		for(int i = 0; i < 3; i++) pt3[i] = 0;
	}
	
	String ToString() const {
		String s;
		s << GetEventTypeString(type) << ", " << (int)value << ", " << n << ", (" << pt.x << "," << pt.y << "), [" << sz.cx << "," << sz.cy << "]";
		return s;
	}
};

struct GeomEventCollection : Vector<GeomEvent>, RTTIBase {
	RTTI_DECL0(GeomEventCollection)
	
};

void RandomizeEvent(GeomEvent& ev);

class EventFrame {
	
public:
	GeomEventCollection ctrl;
	
	void Reset() {ctrl.SetCount(0);}
};


typedef GeomEventType CtrlEventType;
typedef GeomEvent CtrlEvent;
typedef GeomEventCollection CtrlEventCollection;



inline double ResetSeconds(TimeStop& ts) {double s = ts.Seconds(); ts.Reset(); return s;}



#include "Keycodes.inl"


END_UPP_NAMESPACE

#endif
