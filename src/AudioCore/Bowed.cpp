#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Bowed::Bowed( double lowest_freq ) {
	if ( lowest_freq <= 0.0 ) {
		LOG("Bowed::Bowed: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	unsigned long delay_counts = (unsigned long) ( Audio::GetSampleRate() / lowest_freq );
	neck_delay_.SetMaximumDelay( delay_counts + 1 );
	neck_delay_.SetDelay( 100.0 );
	bridge_delay_.SetMaximumDelay( delay_counts + 1 );
	bridge_delay_.SetDelay( 29.0 );
	bowTable_.SetSlope( 3.0 );
	bowTable_.SetOffset( 0.001);
	bow_down_ = false;
	max_velocity_ = 0.25;
	vibrato_.SetFrequency( 6.12723 );
	vibrato_gain_ = 0.0;
	string_filter_.SetPole( 0.75 - (0.2 * 22050.0 / Audio::GetSampleRate()) );
	string_filter_.SetGain( 0.95 );
	body_filters_[0].SetCoefficients( 1.0,  1.5667, 0.3133, -0.5509, -0.3925 );
	body_filters_[1].SetCoefficients( 1.0, -1.9537, 0.9542, -1.6357, 0.8697 );
	body_filters_[2].SetCoefficients( 1.0, -1.6683, 0.8852, -1.7674, 0.8735 );
	body_filters_[3].SetCoefficients( 1.0, -1.8585, 0.9653, -1.8498, 0.9516 );
	body_filters_[4].SetCoefficients( 1.0, -1.9299, 0.9621, -1.9354, 0.9590 );
	body_filters_[5].SetCoefficients( 1.0, -1.9800, 0.9888, -1.9867, 0.9923 );
	adsr_.SetAllTimes( 0.02, 0.005, 0.9, 0.01 );
	betaRatio_ = 0.127236;
	this->SetFrequency( 220.0 );
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

void Bowed::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("Bowed::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	base_delay_ = Audio::GetSampleRate() / frequency - 4.0;

	if ( base_delay_ <= 0.0 ) base_delay_ = 0.3;

	bridge_delay_.SetDelay( base_delay_ * betaRatio_ );
	neck_delay_.SetDelay( base_delay_ * (1.0 - betaRatio_) );
}

void Bowed::StartBowing( double amplitude, double rate ) {
	if ( amplitude <= 0.0 || rate <= 0.0 ) {
		LOG("Bowed::StartBowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetAttackRate( rate );
	adsr_.KeyOn();
	max_velocity_ = 0.03 + ( 0.2 * amplitude );
	bow_down_ = true;
}

void Bowed::StopBowing( double rate ) {
	if ( rate <= 0.0 ) {
		LOG("Bowed::StopBowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetReleaseRate( rate );
	adsr_.KeyOff();
}

void Bowed::NoteOn( double frequency, double amplitude ) {
	this->StartBowing( amplitude, amplitude * 0.001 );
	this->SetFrequency( frequency );
}

void Bowed::NoteOff( double amplitude ) {
	this->StopBowing( (1.0 - amplitude) * 0.005 );
}

void Bowed::ControlChange( int number, double value ) {
	#if defined(flagDEBUG)

	if ( value < 0 || ( number != 101 && value > 128.0 ) ) {
		LOG("Bowed::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double normalizedValue = value * ONE_OVER_128;

	if ( number == __SK_BowPressure_ ) {
		if ( normalizedValue > 0.0 ) bow_down_ = true;
		else bow_down_ = false;

		bowTable_.SetSlope( 5.0 - (4.0 * normalizedValue) );
	}
	else if ( number == __SK_BowPosition_ ) {
		betaRatio_ = normalizedValue;
		bridge_delay_.SetDelay( base_delay_ * betaRatio_ );
		neck_delay_.SetDelay( base_delay_ * (1.0 - betaRatio_) );
	}
	else if ( number == __SK_ModFrequency_ )
		vibrato_.SetFrequency( normalizedValue * 12.0 );
	else if ( number == __SK_ModWheel_ )
		vibrato_gain_ = ( normalizedValue * 0.4 );
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
