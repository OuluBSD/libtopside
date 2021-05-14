#include "AudioCtrl.h"

NAMESPACE_OULU_BEGIN

INITBLOCK {
	MakeInterfaceCtrlFactory<VideoSource, VideoSourceCtrl>();
}



VideoSourceCtrl::VideoSourceCtrl() {
	Add(audio.SizePos());
	
}

void VideoSourceCtrl::SetInterface(ComponentBaseRef c, ExchangeProviderBaseRef b) {
	
}



NAMESPACE_OULU_END
