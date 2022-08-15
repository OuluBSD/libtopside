#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Blit:: Blit( double frequency ) {
	if ( frequency <= 0.0 ) {
		LOG("Blit::Blit: argument (" << frequency << ") must be positive!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	harmonic_count_ = 0;
	this->SetFrequency( frequency );
	this->Reset();
}

Blit::~Blit() {
}

void Blit::Reset() {
	phase_ = 0.0;
	last_frame_[0] = 0.0;
}

void Blit::SetFrequency( double frequency ) {
	if ( frequency <= 0.0 ) {
		LOG("Blit::SetFrequency: argument (" << frequency << ") must be positive!");
		HandleError( AudioError::WARNING );
		return;
	}

	p_ = Audio::GetSampleRate() / frequency;
	rate_ = PI / p_;
	this->UpdateHarmonics();
}

void Blit::SetHarmonics( unsigned int nHarmonics ) {
	harmonic_count_ = nHarmonics;
	this->UpdateHarmonics();
}

void Blit::UpdateHarmonics() {
	if ( harmonic_count_ <= 0 ) {
		unsigned int maxHarmonics = (unsigned int) floor( 0.5 * p_ );
		m_ = 2 * maxHarmonics + 1;
	}
	else
		m_ = 2 * harmonic_count_ + 1;
}

NAMESPACE_AUDIO_END
