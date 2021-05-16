#include "AudioCtrl.h"

NAMESPACE_TOPSIDE_BEGIN



INITBLOCK {
	MakeInterfaceCtrlFactory<VideoSource, VideoSourceCtrl>();
}



VideoSourceCtrl::VideoSourceCtrl() {
	Add(audio.SizePos());
	
}

void VideoSourceCtrl::SetInterface(ComponentBaseRef c, ExchangeProviderBaseRef b) {
	
}



NAMESPACE_TOPSIDE_END
