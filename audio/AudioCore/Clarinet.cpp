#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Clarinet::Clarinet( double lowest_freq ) {
	if ( lowest_freq <= 0.0 ) {
		LOG("Clarinet::Clarinet: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	unsigned long delay_counts = (unsigned long) ( 0.5 * Audio::GetSampleRate() / lowest_freq );
	delay_line_.SetMaximumDelay( delay_counts + 1 );
	reed_table_.SetOffset( 0.7 );
	reed_table_.SetSlope( -0.3 );
	vibrato_.SetFrequency( 5.735 );
	output_gain_ = 1.0;
	noise_gain_ = 0.2;
	vibrato_gain_ = 0.1;
	this->SetFrequency( 220.0 );
	this->Clear();
}

Clarinet::~Clarinet() {
}

void Clarinet::Clear() {
	delay_line_.Clear();
	filter_.Tick( 0.0 );
}

void Clarinet::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("Clarinet::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double delay = ( Audio::GetSampleRate() / frequency ) * 0.5 - filter_.GetPhaseDelay( frequency ) - 1.0;
	delay_line_.SetDelay( delay );
}

void Clarinet::StartBlowing( double amplitude, double rate ) {
	if ( amplitude <= 0.0 || rate <= 0.0 ) {
		LOG("Clarinet::StartBlowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	envelope_.SetRate( rate );
	envelope_.SetTarget( amplitude );
}

void Clarinet::StopBlowing( double rate ) {
	if ( rate <= 0.0 ) {
		LOG("Clarinet::StopBlowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	envelope_.SetRate( rate );
	envelope_.SetTarget( 0.0 );
}

void Clarinet::NoteOn( double frequency, double amplitude ) {
	this->SetFrequency( frequency );
	this->StartBlowing( 0.55 + (amplitude * 0.30), amplitude * 0.005 );
	output_gain_ = amplitude + 0.001;
}

void Clarinet::NoteOff( double amplitude ) {
	this->StopBlowing( amplitude * 0.01 );
}

void Clarinet::ControlChange( int number, double value ) {
	#if defined(flagDEBUG)

	if ( Audio::inRange( value, 0.0, 128.0 ) == false ) {
		LOG("Clarinet::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double normalizedValue = value * ONE_OVER_128;

	if ( number == __SK_ReedStiffness_ )
		reed_table_.SetSlope( -0.44 + ( 0.26 * normalizedValue ) );
	else if ( number == __SK_NoiseLevel_ )
		noise_gain_ = ( normalizedValue * 0.4 );
	else if ( number == __SK_ModFrequency_ )
		vibrato_.SetFrequency( normalizedValue * 12.0 );
	else if ( number == __SK_ModWheel_ )
		vibrato_gain_ = ( normalizedValue * 0.5 );
	else if ( number == __SK_AfterTouch_Cont_ )
		envelope_.SetValue( normalizedValue );

	#if defined(flagDEBUG)
	else {
		LOG("Clarinet::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
