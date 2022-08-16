#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Brass::Brass( double lowest_freq ) {
	if ( lowest_freq <= 0.0 ) {
		LOG("Brass::Brass: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	unsigned long delay_counts = (unsigned long) ( Audio::GetSampleRate() / lowest_freq );
	delay_line_.SetMaximumDelay( delay_counts + 1 );
	lip_filter_.SetGain( 0.03 );
	dc_block_.SetBlockZero();
	adsr_.SetAllTimes( 0.005, 0.001, 1.0, 0.010 );
	vibrato_.SetFrequency( 6.137 );
	vibrato_gain_ = 0.0;
	max_pressure_ = 0.0;
	lip_target_ = 0.0;
	this->Clear();
	this->SetFrequency( 220.0 );
}

Brass::~Brass() {
}

void Brass::Clear() {
	delay_line_.Clear();
	lip_filter_.Clear();
	dc_block_.Clear();
}

void Brass::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("Brass::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	slide_target_ = ( Audio::GetSampleRate() / frequency * 2.0 ) + 3.0;
	delay_line_.SetDelay( slide_target_ );
	lip_target_ = frequency;
	lip_filter_.SetResonance( frequency, 0.997 );
}

void Brass::SetLip( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("Brass::SetLip: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	lip_filter_.SetResonance( frequency, 0.997 );
}

void Brass::StartBlowing( double amplitude, double rate ) {
	if ( amplitude <= 0.0 || rate <= 0.0 ) {
		LOG("Brass::StartBlowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetAttackRate( rate );
	max_pressure_ = amplitude;
	adsr_.KeyOn();
}

void Brass::StopBlowing( double rate ) {
	if ( rate <= 0.0 ) {
		LOG("Brass::StopBlowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetReleaseRate( rate );
	adsr_.KeyOff();
}

void Brass::NoteOn( double frequency, double amplitude ) {
	this->SetFrequency( frequency );
	this->StartBlowing( amplitude, amplitude * 0.001 );
}

void Brass::NoteOff( double amplitude ) {
	this->StopBlowing( amplitude * 0.005 );
}

void Brass::ControlChange( int number, double value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0, 128.0 ) == false ) {
		LOG("Brass::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double normalizedValue = value * ONE_OVER_128;

	if (number == __SK_LipTension_)	{
		double temp = lip_target_ * pow( 4.0, (2.0 * normalizedValue) - 1.0 );
		this->SetLip( temp );
	}
	else if (number == __SK_SlideLength_)
		delay_line_.SetDelay( slide_target_ * (0.5 + normalizedValue) );
	else if (number == __SK_ModFrequency_)
		vibrato_.SetFrequency( normalizedValue * 12.0 );
	else if (number == __SK_ModWheel_ )
		vibrato_gain_ = normalizedValue * 0.4;
	else if (number == __SK_AfterTouch_Cont_)
		adsr_.SetTarget( normalizedValue );

	#if defined(flagDEBUG)
	else {
		LOG("Brass::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
