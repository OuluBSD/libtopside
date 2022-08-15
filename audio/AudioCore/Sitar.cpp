#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Sitar::Sitar( double lowest_freq ) {
	if ( lowest_freq <= 0.0 ) {
		LOG("Sitar::Sitar: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	unsigned long GetCount = (unsigned long) ( Audio::GetSampleRate() / lowest_freq + 1 );
	delay_line_.SetMaximumDelay( GetCount );
	delay_ = 0.5 * GetCount;
	delay_line_.SetDelay( delay_ );
	target_delay_ = delay_;
	loop_filter_.SetZero( 0.01 );
	loop_gain_ = 0.999;
	envelope_.SetAllTimes( 0.001, 0.04, 0.0, 0.5 );
	this->Clear();
}

Sitar::~Sitar() {
}

void Sitar::Clear() {
	delay_line_.Clear();
	loop_filter_.Clear();
}

void Sitar::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("Sitar::SetFrequency: parameter is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	target_delay_ = (Audio::GetSampleRate() / frequency);
	delay_ = target_delay_ * (1.0 + (0.05 * noise_.Tick()));
	delay_line_.SetDelay( delay_ );
	loop_gain_ = 0.995 + (frequency * 0.0000005);

	if ( loop_gain_ > 0.9995 ) loop_gain_ = 0.9995;
}

void Sitar::Pluck( double amplitude ) {
	envelope_.KeyOn();
}

void Sitar::NoteOn( double frequency, double amplitude ) {
	this->SetFrequency( frequency );
	this->Pluck( amplitude );
	am_gain_ = 0.1 * amplitude;
}

void Sitar::NoteOff( double amplitude ) {
	if ( amplitude < 0.0 || amplitude > 1.0 ) {
		LOG("Sitar::noteOff: amplitude is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	loop_gain_ = (double) 1.0 - amplitude;
}

NAMESPACE_AUDIO_END
