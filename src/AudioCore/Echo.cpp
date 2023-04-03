#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Echo::Echo( int maximum_delay ) : Effect() {
	this->SetMaximumDelay( maximum_delay );
	delay_line_.SetDelay( size_ >> 1 );
	effect_mix_ = 0.5;
	this->Clear();
}

void Echo::Clear() {
	delay_line_.Clear();
	last_frame_[0] = 0.0f;
}

void Echo::SetMaximumDelay( int delay ) {
	if ( delay == 0 ) {
		LOG("Echo::SetMaximumDelay: parameter cannot be zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	size_ = delay;
	delay_line_.SetMaximumDelay( delay );
}

void Echo::SetDelay( int delay ) {
	if ( delay > size_ ) {
		LOG("Echo::SetDelay: parameter is greater than maximum delay GetCount!");
		HandleError( AudioError::WARNING );
		return;
	}

	delay_line_.SetDelay( delay );
}

NAMESPACE_AUDIO_END
