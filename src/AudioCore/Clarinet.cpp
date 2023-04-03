#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Clarinet::Clarinet( float lowest_freq ) {
	if ( lowest_freq <= 0.0f ) {
		LOG("Clarinet::Clarinet: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	int delay_counts = (int) ( 0.5f * Audio::GetSampleRate() / lowest_freq );
	delay_line_.SetMaximumDelay( delay_counts + 1 );
	reed_table_.SetOffset( 0.7f );
	reed_table_.SetSlope( -0.3f );
	vibrato_.SetFrequency( 5.735f );
	output_gain_ = 1.0f;
	noise_gain_ = 0.2f;
	vibrato_gain_ = 0.1f;
	this->SetFrequency( 220.0f );
	this->Clear();
}

Clarinet::~Clarinet() {
}

void Clarinet::Clear() {
	delay_line_.Clear();
	filter_.Tick( 0.0f );
}

void Clarinet::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("Clarinet::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float delay = ( Audio::GetSampleRate() / frequency ) * 0.5f - filter_.GetPhaseDelay( frequency ) - 1.0f;
	delay_line_.SetDelay( delay );
}

void Clarinet::StartBlowing( float amplitude, float rate ) {
	if ( amplitude <= 0.0f || rate <= 0.0f ) {
		LOG("Clarinet::StartBlowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	envelope_.SetRate( rate );
	envelope_.SetTarget( amplitude );
}

void Clarinet::StopBlowing( float rate ) {
	if ( rate <= 0.0f ) {
		LOG("Clarinet::StopBlowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	envelope_.SetRate( rate );
	envelope_.SetTarget( 0.0f );
}

void Clarinet::NoteOn( float frequency, float amplitude ) {
	this->SetFrequency( frequency );
	this->StartBlowing( 0.55f + (amplitude * 0.30f), amplitude * 0.005f );
	output_gain_ = amplitude + 0.001f;
}

void Clarinet::NoteOff( float amplitude ) {
	this->StopBlowing( amplitude * 0.01f );
}

void Clarinet::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0f ) == false ) {
		LOG("Clarinet::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if ( number == __SK_ReedStiffness_ )
		reed_table_.SetSlope( -0.44f + ( 0.26f * normalizedValue ) );
	else if ( number == __SK_NoiseLevel_ )
		noise_gain_ = ( normalizedValue * 0.4f );
	else if ( number == __SK_ModFrequency_ )
		vibrato_.SetFrequency( normalizedValue * 12.0f );
	else if ( number == __SK_ModWheel_ )
		vibrato_gain_ = ( normalizedValue * 0.5f );
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
