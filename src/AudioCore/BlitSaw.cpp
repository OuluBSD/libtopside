#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

BlitSaw:: BlitSaw( double frequency ) {
	if ( frequency <= 0.0 ) {
		LOG("BlitSaw::BlitSaw: argument (" << frequency << ") must be positive!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	harmonic_count_ = 0;
	this->Reset();
	this->SetFrequency( frequency );
}

BlitSaw::~BlitSaw() {
}

void BlitSaw::Reset() {
	phase_ = 0.0f;
	state_ = 0.0;
	last_frame_[0] = 0.0;
}

void BlitSaw::SetFrequency( double frequency ) {
	if ( frequency <= 0.0 ) {
		LOG("BlitSaw::SetFrequency: argument (" << frequency << ") must be positive!");
		HandleError( AudioError::WARNING );
		return;
	}

	p_ = Audio::GetSampleRate() / frequency;
	C2_ = 1 / p_;
	rate_ = PI * C2_;
	this->UpdateHarmonics();
}

void BlitSaw::SetHarmonics( unsigned int nHarmonics ) {
	harmonic_count_ = nHarmonics;
	this->UpdateHarmonics();
	state_ = -0.5 * a_;
}

void BlitSaw::UpdateHarmonics() {
	if ( harmonic_count_ <= 0 ) {
		unsigned int maxHarmonics = (unsigned int) floor( 0.5 * p_ );
		m_ = 2 * maxHarmonics + 1;
	}
	else
		m_ = 2 * harmonic_count_ + 1;

	a_ = m_ / p_;
}

NAMESPACE_AUDIO_END
