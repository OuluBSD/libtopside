#include <Core/Core.h>


NAMESPACE_UPP


void RandomizeEvent(CtrlEvent& ev) {
	ev.Clear();
	ev.type = (CtrlEventType)(1+Random(EVENT_TYPE_COUNT-1)); // skip first,
	
	switch (ev.type) {
		case EVENT_WINDOW_RESIZE:
			ev.pt = Point(Random(640), Random(480));
			ev.sz = Size(320 + Random(640), 240 + Random(480));
			break;
			
		case EVENT_SHUTDOWN:
			break;
			
		case EVENT_KEYDOWN:
			ev.value = Random(128);
			break;
			
		case EVENT_KEYUP:
			ev.value = Random(128);
			break;
			
		case EVENT_MOUSEMOVE:
			ev.pt = Point(Random(640), Random(480));
			break;
			
		//case EVENT_MOUSEDRAG:
		
		case EVENT_MOUSEWHEEL:
			ev.n = -10 + Random(20);
			break;
			
		case EVENT_MOUSE_EVENT:
			break;
			
		case EVENT_INVALID:
		case EVENT_TYPE_COUNT:
		default:
			break;
	}
	
}


END_UPP_NAMESPACE
