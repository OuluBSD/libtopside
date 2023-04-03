#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Blit:: Blit( float frequency ) {
	if ( frequency <= 0.0f ) {
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
	phase_ = 0.0f;
	last_frame_[0] = 0.0f;
}

void Blit::SetFrequency( float frequency ) {
	if ( frequency <= 0.0f ) {
		LOG("Blit::SetFrequency: argument (" << frequency << ") must be positive!");
		HandleError( AudioError::WARNING );
		return;
	}

	p_ = Audio::GetSampleRate() / frequency;
	rate_ = PI / p_;
	this->UpdateHarmonics();
}

void Blit::SetHarmonics( int nHarmonics ) {
	harmonic_count_ = nHarmonics;
	this->UpdateHarmonics();
}

void Blit::UpdateHarmonics() {
	if ( harmonic_count_ <= 0 ) {
		int maxHarmonics = (int) floor( 0.5f * p_ );
		m_ = 2 * maxHarmonics + 1;
	}
	else
		m_ = 2 * harmonic_count_ + 1;
}

NAMESPACE_AUDIO_END
