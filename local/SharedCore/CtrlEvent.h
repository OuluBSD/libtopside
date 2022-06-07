#ifndef _CoreAlt_CtrlEvent_h_
#define _CoreAlt_CtrlEvent_h_

NAMESPACE_UPP


enum {
	EVENT_INVALID,
	EVENT_WINDOW_RESIZE,
	EVENT_SHUTDOWN,
	EVENT_KEYDOWN,
	EVENT_KEYUP,
	EVENT_MOUSEMOVE,
	//EVENT_MOUSEDRAG,
	EVENT_MOUSEWHEEL,
	EVENT_MOUSE_EVENT,
	
	
	EVENT_HOLO_CONTROLLER_DETECTED,
	EVENT_HOLO_CONTROLLER_LOST,
	EVENT_HOLO_LOOK,
	EVENT_HOLO_MOVE_FAR_RELATIVE,
	EVENT_HOLO_MOVE_NEAR,
	
	EVENT_TYPE_COUNT
};

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
		
		case EVENT_HOLO_CONTROLLER_DETECTED:	return "Holographic controller detected";
		case EVENT_HOLO_CONTROLLER_LOST:		return "Holographic controller lost";
		case EVENT_HOLO_LOOK:					return "Holographic Look";
		case EVENT_HOLO_MOVE_FAR_RELATIVE:		return "Holographic Move Far (relative)";
		case EVENT_HOLO_MOVE_NEAR:				return "Holographic Move Near";
		
		case EVENT_INVALID:
		case EVENT_TYPE_COUNT:
		default:					return "<invalid>";
	}
}


struct CtrlEvent : Moveable<CtrlEvent> {
	int type = 0;
	union {
		dword value = 0;
		float fvalue;
	};
	int n = 0;
	Point pt;
	Size sz;
	
	// 3D extension
	float position[3] {0,0,0};
	float direction[3] {0,0,0};
	
	RTTI_TYPEIDCLS
	
	void operator=(const CtrlEvent& e) {
		type = e.type;
		value = e.value;
		n = e.n;
		pt.x = e.pt.x;
		pt.y = e.pt.y;
		sz.cx = e.sz.cx;
		sz.cy = e.sz.cy;
	}
	
	void Clear() {
		type = 0;
		value = 0;
		n = 0;
		pt = Point(0,0);
		sz = Size(0,0);
	}
	
	String ToString() const {
		String s;
		s << type << ", " << (int)value << ", " << n << ", (" << pt.x << "," << pt.y << "), [" << sz.cx << "," << sz.cy << "]";
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
