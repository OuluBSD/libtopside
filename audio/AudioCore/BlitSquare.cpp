#include "AudioCore.h"



NAMESPACE_AUDIO_BEGIN

BlitSquare:: BlitSquare( double frequency ) {
	if ( frequency <= 0.0 ) {
		LOG("BlitSquare::BlitSquare: argument (" << frequency << ") must be positive!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	harmonic_count_ = 0;
	this->SetFrequency( frequency );
	this->Reset();
}

BlitSquare::~BlitSquare() {
}

void BlitSquare::Reset() {
	phase_ = 0.0;
	last_frame_[0] = 0.0;
	dcb_state_ = 0.0;
	last_blit_output_ = 0;
}

void BlitSquare::SetFrequency( double frequency ) {
	if ( frequency <= 0.0 ) {
		LOG("BlitSquare::SetFrequency: argument (" << frequency << ") must be positive!");
		HandleError( AudioError::WARNING );
		return;
	}

	p_ = 0.5 * Audio::GetSampleRate() / frequency;
	rate_ = PI / p_;
	this->UpdateHarmonics();
}

void BlitSquare::SetHarmonics( unsigned int nHarmonics ) {
	harmonic_count_ = nHarmonics;
	this->UpdateHarmonics();
}

void BlitSquare::UpdateHarmonics() {
	if ( harmonic_count_ <= 0 ) {
		unsigned int maxHarmonics = (unsigned int) floor( 0.5 * p_ );
		m_ = 2 * (maxHarmonics + 1);
	}
	else
		m_ = 2 * (harmonic_count_ + 1);

	a_ = m_ / p_;
}

NAMESPACE_AUDIO_END
