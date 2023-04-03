#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Sitar::Sitar( float lowest_freq ) {
	if ( lowest_freq <= 0.0f ) {
		LOG("Sitar::Sitar: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	int GetCount = (int) ( Audio::GetSampleRate() / lowest_freq + 1 );
	delay_line_.SetMaximumDelay( GetCount );
	delay_ = 0.5f * GetCount;
	delay_line_.SetDelay( delay_ );
	target_delay_ = delay_;
	loop_filter_.SetZero( 0.01f );
	loop_gain_ = 0.999f;
	envelope_.SetAllTimes( 0.001f, 0.04f, 0.0f, 0.5f );
	this->Clear();
}

Sitar::~Sitar() {
}

void Sitar::Clear() {
	delay_line_.Clear();
	loop_filter_.Clear();
}

void Sitar::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("Sitar::SetFrequency: parameter is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	target_delay_ = (Audio::GetSampleRate() / frequency);
	delay_ = target_delay_ * (1.0f + (0.05f * noise_.Tick()));
	delay_line_.SetDelay( delay_ );
	loop_gain_ = 0.995f + (frequency * 0.0000005f);

	if ( loop_gain_ > 0.9995f ) loop_gain_ = 0.9995f;
}

void Sitar::Pluck( float amplitude ) {
	envelope_.KeyOn();
}

void Sitar::NoteOn( float frequency, float amplitude ) {
	this->SetFrequency( frequency );
	this->Pluck( amplitude );
	am_gain_ = 0.1f * amplitude;
}

void Sitar::NoteOff( float amplitude ) {
	if ( amplitude < 0.0f || amplitude > 1.0f ) {
		LOG("Sitar::noteOff: amplitude is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	loop_gain_ = (float) 1.0f - amplitude;
}

NAMESPACE_AUDIO_END
