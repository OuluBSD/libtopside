#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Plucked::Plucked( double lowest_freq ) {
	if ( lowest_freq <= 0.0 ) {
		LOG("Plucked::Plucked: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	unsigned long delays = (unsigned long) ( Audio::GetSampleRate() / lowest_freq );
	delay_line_.SetMaximumDelay( delays + 1 );
	this->SetFrequency( 220.0 );
}

Plucked::~Plucked() {
}

void Plucked::Clear() {
	delay_line_.Clear();
	loop_filter_.Clear();
	pick_filter_.Clear();
}

void Plucked::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("Plucked::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double delay = ( Audio::GetSampleRate() / frequency ) - loop_filter_.GetPhaseDelay( frequency );
	delay_line_.SetDelay( delay );
	loop_gain_ = 0.995 + (frequency * 0.000005);

	if ( loop_gain_ >= 1.0 ) loop_gain_ = 0.99999;
}

void Plucked::Pluck( double amplitude ) {
	if ( amplitude < 0.0 || amplitude > 1.0 ) {
		LOG("Plucked::pluck: amplitude is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	pick_filter_.SetPole( 0.999 - (amplitude * 0.15) );
	pick_filter_.SetGain( amplitude * 0.5 );

	for ( unsigned long i = 0; i < delay_line_.GetDelay(); i++ )
		delay_line_.Tick( 0.6 * delay_line_.GetLastOut() + pick_filter_.Tick( noise_.Tick() ) );
}

void Plucked::NoteOn( double frequency, double amplitude ) {
	this->SetFrequency( frequency );
	this->Pluck( amplitude );
}

void Plucked::NoteOff( double amplitude ) {
	if ( amplitude < 0.0 || amplitude > 1.0 ) {
		LOG("Plucked::noteOff: amplitude is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	loop_gain_ = 1.0 - amplitude;
}

NAMESPACE_AUDIO_END
