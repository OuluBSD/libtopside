#include "AudioCtrl.h"

NAMESPACE_OULU_BEGIN

INITBLOCK {
	MakeInterfaceCtrlFactory<MediaSource, MediaSourceCtrl>();
}



MediaSourceCtrl::MediaSourceCtrl() {
	Add(audio.SizePos());
	
}

void MediaSourceCtrl::SetInterface(ComponentBase& c, InterfaceBase& b) {
	
}



NAMESPACE_OULU_END
