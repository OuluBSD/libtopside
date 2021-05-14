#include "AudioCtrl.h"

NAMESPACE_OULU_BEGIN

INITBLOCK {
	MakeInterfaceCtrlFactory<AudioSource, AudioSourceCtrl>();
}



AudioSourceCtrl::AudioSourceCtrl() {
	Add(s.SizePos());
	s.Color(Color(176, 237, 255));
}

void AudioSourceCtrl::SetInterface(ComponentBaseRef c, ExchangeProviderBaseRef b) {
	
}



NAMESPACE_OULU_END
