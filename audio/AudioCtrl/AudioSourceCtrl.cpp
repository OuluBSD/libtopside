#include "AudioCtrl.h"

NAMESPACE_TOPSIDE_BEGIN


INITBLOCK {
	MakeInterfaceCtrlFactory<AudioSource, AudioSourceCtrl>();
}



AudioSourceCtrl::AudioSourceCtrl() {
	Add(s.SizePos());
	s.Color(Color(176, 237, 255));
}

void AudioSourceCtrl::SetInterface(ComponentBaseRef c, ExchangeProviderBaseRef b) {
	
}



NAMESPACE_TOPSIDE_END
