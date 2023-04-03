#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Bowed::Bowed( float lowest_freq ) {
	if ( lowest_freq <= 0.0f ) {
		LOG("Bowed::Bowed: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	int delay_counts = (int) ( Audio::GetSampleRate() / lowest_freq );
	neck_delay_.SetMaximumDelay( delay_counts + 1 );
	neck_delay_.SetDelay( 100.0f );
	bridge_delay_.SetMaximumDelay( delay_counts + 1 );
	bridge_delay_.SetDelay( 29.0f );
	bowTable_.SetSlope( 3.0 );
	bowTable_.SetOffset( 0.001f);
	bow_down_ = false;
	max_velocity_ = 0.25f;
	vibrato_.SetFrequency( 6.12723f );
	vibrato_gain_ = 0.0f;
	string_filter_.SetPole( 0.75f - (0.2f * 22050.0f / Audio::GetSampleRate()) );
	string_filter_.SetGain( 0.95f );
	body_filters_[0].SetCoefficients( 1.0f,  1.5667f, 0.3133f, -0.5509f, -0.3925f );
	body_filters_[1].SetCoefficients( 1.0f, -1.9537f, 0.9542f, -1.6357f, 0.8697f );
	body_filters_[2].SetCoefficients( 1.0f, -1.6683f, 0.8852f, -1.7674f, 0.8735f );
	body_filters_[3].SetCoefficients( 1.0f, -1.8585f, 0.9653f, -1.8498f, 0.9516f );
	body_filters_[4].SetCoefficients( 1.0f, -1.9299f, 0.9621f, -1.9354f, 0.9590f );
	body_filters_[5].SetCoefficients( 1.0f, -1.9800f, 0.9888f, -1.9867f, 0.9923f );
	adsr_.SetAllTimes( 0.02f, 0.005f, 0.9f, 0.01f );
	betaRatio_ = 0.127236f;
	this->SetFrequency( 220.0f );
	this->Clear();
}

Bowed::~Bowed() {
}

void Bowed::Clear() {
	neck_delay_.Clear();
	bridge_delay_.Clear();
	string_filter_.Clear();

	for ( int i = 0; i < 6; i++ ) body_filters_[i].Clear();
}

void Bowed::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("Bowed::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	base_delay_ = Audio::GetSampleRate() / frequency - 4.0f;

	if ( base_delay_ <= 0.0f ) base_delay_ = 0.3f;

	bridge_delay_.SetDelay( base_delay_ * betaRatio_ );
	neck_delay_.SetDelay( base_delay_ * (1.0f - betaRatio_) );
}

void Bowed::StartBowing( float amplitude, float rate ) {
	if ( amplitude <= 0.0f || rate <= 0.0f ) {
		LOG("Bowed::StartBowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetAttackRate( rate );
	adsr_.KeyOn();
	max_velocity_ = 0.03f + ( 0.2f * amplitude );
	bow_down_ = true;
}

void Bowed::StopBowing( float rate ) {
	if ( rate <= 0.0f ) {
		LOG("Bowed::StopBowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetReleaseRate( rate );
	adsr_.KeyOff();
}

void Bowed::NoteOn( float frequency, float amplitude ) {
	this->StartBowing( amplitude, amplitude * 0.001f );
	this->SetFrequency( frequency );
}

void Bowed::NoteOff( float amplitude ) {
	this->StopBowing( (1.0f - amplitude) * 0.005f );
}

void Bowed::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( value < 0 || ( number != 101 && value > 128.0f ) ) {
		LOG("Bowed::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if ( number == __SK_BowPressure_ ) {
		if ( normalizedValue > 0.0f ) bow_down_ = true;
		else bow_down_ = false;

		bowTable_.SetSlope( 5.0f - (4.0f * normalizedValue) );
	}
	else if ( number == __SK_BowPosition_ ) {
		betaRatio_ = normalizedValue;
		bridge_delay_.SetDelay( base_delay_ * betaRatio_ );
		neck_delay_.SetDelay( base_delay_ * (1.0f - betaRatio_) );
	}
	else if ( number == __SK_ModFrequency_ )
		vibrato_.SetFrequency( normalizedValue * 12.0f );
	else if ( number == __SK_ModWheel_ )
		vibrato_gain_ = ( normalizedValue * 0.4f );
	else if ( number == 100 )
		adsr_.SetTarget( normalizedValue );
	else if ( number == 101 )
		this->SetFrequency( value );
	else if (number == __SK_AfterTouch_Cont_)
		adsr_.SetTarget( normalizedValue );

	#if defined(flagDEBUG)
	else {
		LOG("Bowed::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
