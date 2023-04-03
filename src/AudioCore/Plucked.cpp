#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Plucked::Plucked( float lowest_freq ) {
	if ( lowest_freq <= 0.0f ) {
		LOG("Plucked::Plucked: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	int delays = (int) ( Audio::GetSampleRate() / lowest_freq );
	delay_line_.SetMaximumDelay( delays + 1 );
	this->SetFrequency( 220.0f );
}

Plucked::~Plucked() {
}

void Plucked::Clear() {
	delay_line_.Clear();
	loop_filter_.Clear();
	pick_filter_.Clear();
}

void Plucked::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("Plucked::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float delay = ( Audio::GetSampleRate() / frequency ) - loop_filter_.GetPhaseDelay( frequency );
	delay_line_.SetDelay( delay );
	loop_gain_ = 0.995 + (frequency * 0.000005);

	if ( loop_gain_ >= 1.0f ) loop_gain_ = 0.99999;
}

void Plucked::Pluck( float amplitude ) {
	if ( amplitude < 0.0f || amplitude > 1.0f ) {
		LOG("Plucked::pluck: amplitude is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	pick_filter_.SetPole( 0.999 - (amplitude * 0.15) );
	pick_filter_.SetGain( amplitude * 0.5f );

	for ( int i = 0; i < delay_line_.GetDelay(); i++ )
		delay_line_.Tick( 0.6 * delay_line_.GetLastOut() + pick_filter_.Tick( noise_.Tick() ) );
}

void Plucked::NoteOn( float frequency, float amplitude ) {
	this->SetFrequency( frequency );
	this->Pluck( amplitude );
}

void Plucked::NoteOff( float amplitude ) {
	if ( amplitude < 0.0f || amplitude > 1.0f ) {
		LOG("Plucked::noteOff: amplitude is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	loop_gain_ = 1.0f - amplitude;
}

NAMESPACE_AUDIO_END
