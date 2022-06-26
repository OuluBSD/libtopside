#ifndef _CoreAlt_CtrlEvent_h_
#define _CoreAlt_CtrlEvent_h_

NAMESPACE_UPP


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
	EVENT_HOLO_CONTROLLER_DETECTED,
	EVENT_HOLO_CONTROLLER_LOST,
	EVENT_HOLO_LOOK,
	EVENT_HOLO_MOVE_FAR_RELATIVE,
	EVENT_HOLO_MOVE_NEAR,
	EVENT_HOLO_PRESSED,
	EVENT_HOLO_RELEASED,
	
	EVENT_TYPE_COUNT
} CtrlEventType;

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
		case EVENT_HOLO_CONTROLLER_DETECTED:	return "Holographic controller detected";
		case EVENT_HOLO_CONTROLLER_LOST:		return "Holographic controller lost";
		case EVENT_HOLO_LOOK:					return "Holographic Look";
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

struct ControllerState {
	ControllerSource* source = 0;
	ControllerProperties props;
	
	const ControllerSource& GetSource() const {ASSERT(source); return *source;}
	const ControllerProperties& GetControllerProperties() const {return props;}
	
};

struct CtrlEvent3D {
	
	typedef enum {
		INVALID = -1,
		
		GENERIC,
		TRIGGER,
		TRIGGER_CLICK,
		SQUEEZE,
		MENU,
		HOME,
		ANALOG_X,
		ANALOG_Y,
		ANALOG_PRESS,
		BUTTON_A,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		VOLUME_PLUS,
		VOLUME_MINUS,
		MIC_MUTE,
		
		VALUE_COUNT
	} Value;

	float position[3] {0,0,0};
	float direction[3] {0,0,0};
	
	// VR hmd & controllers
	bool use_lookat = false;
	bool use_view = false;
	float orient[4];
	float l_proj[4][4], l_view[4][4];
	float r_proj[4][4], r_view[4][4];
	
	static const int CTRL_COUNT = 2;
	struct Ctrl {
		bool is_enabled = false;
		bool is_value[VALUE_COUNT];
		float value[VALUE_COUNT];
		float rot[4];
		float pos[3];
	};
	Ctrl ctrl[CTRL_COUNT];
	
};

#define COPY2(dst, from) for(int i = 0; i < 2; i++) dst[i] = from[i]
#define COPY3(dst, from) for(int i = 0; i < 3; i++) dst[i] = from[i]
#define COPY4(dst, from) for(int i = 0; i < 4; i++) dst[i] = from[i]
#define COPY4x4(dst, from) for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) dst[i][j] = from[i][j]
	

struct TransformMatrix;

struct CtrlEvent : Moveable<CtrlEvent> {
	CtrlEventType type = EVENT_INVALID;
	union {
		dword value = 0;
		float fvalue;
	};
	int n = 0;
	Point pt;
	Size sz;
	
	// Device extension
	TransformMatrix* trans = 0;
	//CtrlEvent3D* spatial = 0;
	ControllerState* state = 0;
	
	
	RTTI_TYPEIDCLS
	
	const ControllerState& GetState() const {ASSERT(state); return *state;}
	
	void operator=(const CtrlEvent& e) {
		type = e.type;
		value = e.value;
		n = e.n;
		pt.x = e.pt.x;
		pt.y = e.pt.y;
		sz.cx = e.sz.cx;
		sz.cy = e.sz.cy;
		trans = e.trans;
		//spatial = e.spatial;
		state = e.state;
	}
	
	void Clear() {
		type = EVENT_INVALID;
		value = 0;
		n = 0;
		pt = Point(0,0);
		sz = Size(0,0);
		trans = 0;
		//spatial = 0;
		state = 0;
	}
	
	String ToString() const {
		String s;
		s << GetEventTypeString(type) << ", " << (int)value << ", " << n << ", (" << pt.x << "," << pt.y << "), [" << sz.cx << "," << sz.cy << "]";
		return s;
	}
};

void RandomizeEvent(CtrlEvent& ev);

class EventFrame {
	
public:
	Vector<CtrlEvent> ctrl;
	
	void Reset() {ctrl.SetCount(0);}
};





inline double ResetSeconds(TimeStop& ts) {double s = ts.Seconds(); ts.Reset(); return s;}


END_UPP_NAMESPACE

#endif
