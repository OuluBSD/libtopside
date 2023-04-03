#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Saxofony::Saxofony( float lowest_freq ) {
	if ( lowest_freq <= 0.0f ) {
		LOG("Saxofony::Saxofony: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	int delay_counts = (int) ( Audio::GetSampleRate() / lowest_freq );
	delays_[0].SetMaximumDelay( delay_counts + 1 );
	delays_[1].SetMaximumDelay( delay_counts + 1 );
	position_ = 0.2;
	reed_table_.SetOffset( 0.7 );
	reed_table_.SetSlope( 0.3 );
	vibrato_.SetFrequency( 5.735 );
	output_gain_ = 0.3;
	noise_gain_ = 0.2;
	vibrato_gain_ = 0.1;
	this->SetFrequency( 220.0f );
	this->Clear();
}

Saxofony::~Saxofony() {
}

void Saxofony::Clear() {
	delays_[0].Clear();
	delays_[1].Clear();
	filter_.Clear();
}

void Saxofony::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("Saxofony::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float delay = ( Audio::GetSampleRate() / frequency ) - filter_.GetPhaseDelay( frequency ) - 1.0f;
	delays_[0].SetDelay( (1.0f - position_) * delay );
	delays_[1].SetDelay( position_ * delay );
}

void Saxofony::SetBlowPosition( float position ) {
	if ( position_ == position ) return;

	if ( position < 0.0f ) position_ = 0.0f;
	else if ( position > 1.0f ) position_ = 1.0f;
	else position_ = position;

	float totalDelay = delays_[0].GetDelay();
	totalDelay += delays_[1].GetDelay();
	delays_[0].SetDelay( (1.0f - position_) * totalDelay );
	delays_[1].SetDelay( position_ * totalDelay );
}

void Saxofony::StartBlowing( float amplitude, float rate ) {
	if ( amplitude <= 0.0f || rate <= 0.0f ) {
		LOG("Saxofony::StartBlowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	envelope_.SetRate( rate );
	envelope_.SetTarget( amplitude );
}

void Saxofony::StopBlowing( float rate ) {
	if ( rate <= 0.0f ) {
		LOG("Saxofony::StopBlowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	envelope_.SetRate( rate );
	envelope_.SetTarget( 0.0f );
}

void Saxofony::NoteOn( float frequency, float amplitude ) {
	this->SetFrequency( frequency );
	this->StartBlowing( 0.55 + (amplitude * 0.30), amplitude * 0.005 );
	output_gain_ = amplitude + 0.001f;
}

void Saxofony::NoteOff( float amplitude ) {
	this->StopBlowing( amplitude * 0.01 );
}

void Saxofony::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0 ) == false ) {
		LOG("Saxofony::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if (number == __SK_ReedStiffness_)
		reed_table_.SetSlope( 0.1 + (0.4 * normalizedValue) );
	else if (number == __SK_NoiseLevel_)
		noise_gain_ = ( normalizedValue * 0.4 );
	else if (number == 29)
		vibrato_.SetFrequency( normalizedValue * 12.0 );
	else if (number == __SK_ModWheel_)
		vibrato_gain_ = ( normalizedValue * 0.5f );
	else if (number == __SK_AfterTouch_Cont_)
		envelope_.SetValue( normalizedValue );
	else if (number == 11)
		this->SetBlowPosition( normalizedValue );
	else if (number == 26)
		reed_table_.SetOffset(0.4 + ( normalizedValue * 0.6));

	#if defined(flagDEBUG)
	else {
		LOG("Saxofony::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
