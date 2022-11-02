#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Flute::Flute( double lowest_freq ) {
	if ( lowest_freq <= 0.0 ) {
		LOG("Flute::Flute: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	unsigned long delay_counts = (unsigned long) ( Audio::GetSampleRate() / lowest_freq );
	bore_delay_.SetMaximumDelay( delay_counts + 1 );
	jet_delay_.SetMaximumDelay( delay_counts + 1 );
	jet_delay_.SetDelay( 49.0 );
	vibrato_.SetFrequency( 5.925 );
	filter_.SetPole( 0.7 - ( 0.1 * 22050.0 / Audio::GetSampleRate() ) );
	dc_block_.SetBlockZero();
	adsr_.SetAllTimes( 0.005, 0.01, 0.8, 0.010 );
	end_reflection = 0.5;
	jetReflection_ = 0.5;
	noise_gain_     = 0.15;
	vibrato_gain_   = 0.05;
	jetRatio_      = 0.32;
	max_pressure_ = 0.0;
	this->Clear();
	this->SetFrequency( 220.0 );
}

Flute::~Flute() {
}

void Flute::Clear() {
	jet_delay_.Clear();
	bore_delay_.Clear();
	filter_.Clear();
	dc_block_.Clear();
}

void Flute::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("Flute::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	last_frequency_ = frequency * 0.66666;
	double delay = Audio::GetSampleRate() / last_frequency_ - filter_.GetPhaseDelay( last_frequency_ ) - 1.0;
	bore_delay_.SetDelay( delay );
	jet_delay_.SetDelay( delay * jetRatio_ );
}

void Flute::SetJetDelay( double aRatio ) {
	jetRatio_ = aRatio;
	jet_delay_.SetDelay( bore_delay_.GetDelay() * aRatio );
}

void Flute::StartBlowing( double amplitude, double rate ) {
	if ( amplitude <= 0.0 || rate <= 0.0 ) {
		LOG("Flute::StartBlowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetAttackRate( rate );
	max_pressure_ = amplitude / (double) 0.8;
	adsr_.KeyOn();
}

void Flute::StopBlowing( double rate ) {
	if ( rate <= 0.0 ) {
		LOG("Flute::StopBlowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetReleaseRate( rate );
	adsr_.KeyOff();
}

void Flute::NoteOn( double frequency, double amplitude ) {
	this->SetFrequency( frequency );
	this->StartBlowing( 1.1 + (amplitude * 0.20), amplitude * 0.02 );
	output_gain_ = amplitude + 0.001;
}

void Flute::NoteOff( double amplitude ) {
	this->StopBlowing( amplitude * 0.02 );
}


void Flute::ControlChange( int number, double value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0, 128.0 ) == false ) {
		LOG("Flute::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double normalizedValue = value * ONE_OVER_128;

	if (number == __SK_JetDelay_)
		this->SetJetDelay( (double) (0.08 + (0.48 * normalizedValue)) );
	else if (number == __SK_NoiseLevel_)
		noise_gain_ = ( normalizedValue * 0.4);
	else if (number == __SK_ModFrequency_)
		vibrato_.SetFrequency( normalizedValue * 12.0);
	else if (number == __SK_ModWheel_)
		vibrato_gain_ = ( normalizedValue * 0.4 );
	else if (number == __SK_AfterTouch_Cont_)
		adsr_.SetTarget( normalizedValue );

	#if defined(flagDEBUG)
	else {
		LOG("Flute::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
