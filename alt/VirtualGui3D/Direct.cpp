#include <SerialLib/SerialLib.h>


NAMESPACE_TOPSIDE_BEGIN

//uint32 DirectWindow::prev_ticks;


DirectWindow::DirectWindow() {
	
}



void DirectWindow::Initialize() {
	ASSERT(!scr);
	EntityRef e = GetEntity();
	scr = e->FindDisplaySink();
}

void DirectWindow::Uninitialize() {
	if (scr)
		WhenClose();
	
	
	scr.Clear();
}




NAMESPACE_TOPSIDE_END
