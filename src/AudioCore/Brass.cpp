#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Brass::Brass( float lowest_freq ) {
	if ( lowest_freq <= 0.0f ) {
		LOG("Brass::Brass: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	int delay_counts = (int) ( Audio::GetSampleRate() / lowest_freq );
	delay_line_.SetMaximumDelay( delay_counts + 1 );
	lip_filter_.SetGain( 0.03f );
	dc_block_.SetBlockZero();
	adsr_.SetAllTimes( 0.005f, 0.001f, 1.0f, 0.010f );
	vibrato_.SetFrequency( 6.137f );
	vibrato_gain_ = 0.0f;
	max_pressure_ = 0.0f;
	lip_target_ = 0.0f;
	this->Clear();
	this->SetFrequency( 220.0f );
}

Brass::~Brass() {
}

void Brass::Clear() {
	delay_line_.Clear();
	lip_filter_.Clear();
	dc_block_.Clear();
}

void Brass::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("Brass::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	slide_target_ = ( Audio::GetSampleRate() / frequency * 2.0f ) + 3.0f;
	delay_line_.SetDelay( slide_target_ );
	lip_target_ = frequency;
	lip_filter_.SetResonance( frequency, 0.997f );
}

void Brass::SetLip( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("Brass::SetLip: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	lip_filter_.SetResonance( frequency, 0.997f );
}

void Brass::StartBlowing( float amplitude, float rate ) {
	if ( amplitude <= 0.0f || rate <= 0.0f ) {
		LOG("Brass::StartBlowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetAttackRate( rate );
	max_pressure_ = amplitude;
	adsr_.KeyOn();
}

void Brass::StopBlowing( float rate ) {
	if ( rate <= 0.0f ) {
		LOG("Brass::StopBlowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetReleaseRate( rate );
	adsr_.KeyOff();
}

void Brass::NoteOn( float frequency, float amplitude ) {
	this->SetFrequency( frequency );
	this->StartBlowing( amplitude, amplitude * 0.001f );
}

void Brass::NoteOff( float amplitude ) {
	this->StopBlowing( amplitude * 0.005f );
}

void Brass::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0f ) == false ) {
		LOG("Brass::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if (number == __SK_LipTension_)	{
		float temp = lip_target_ * powf( 4.0f, (2.0f * normalizedValue) - 1.0f );
		this->SetLip( temp );
	}
	else if (number == __SK_SlideLength_)
		delay_line_.SetDelay( slide_target_ * (0.5f + normalizedValue) );
	else if (number == __SK_ModFrequency_)
		vibrato_.SetFrequency( normalizedValue * 12.0f );
	else if (number == __SK_ModWheel_ )
		vibrato_gain_ = normalizedValue * 0.4f;
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
