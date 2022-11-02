#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

#define __BOTTLE_RADIUS_ 0.999

BlowBottle::BlowBottle() {
	dc_block_.SetBlockZero();
	vibrato_.SetFrequency( 5.925 );
	vibrato_gain_ = 0.0;
	resonator_.SetResonance( 500.0, __BOTTLE_RADIUS_, true );
	adsr_.SetAllTimes( 0.005, 0.01, 0.8, 0.010 );
	noise_gain_ = 20.0;
	max_pressure_ = 0.0;
}

BlowBottle::~BlowBottle() {
}

void BlowBottle::Clear() {
	resonator_.Clear();
}

void BlowBottle::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("BlowBottle::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	resonator_.SetResonance( frequency, __BOTTLE_RADIUS_, true );
}

void BlowBottle::StartBlowing( double amplitude, double rate ) {
	if ( amplitude <= 0.0 || rate <= 0.0 ) {
		LOG("BlowBottle::StartBowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetAttackRate( rate );
	max_pressure_ = amplitude;
	adsr_.KeyOn();
}

void BlowBottle::StopBlowing( double rate ) {
	if ( rate <= 0.0 ) {
		LOG("BlowBottle::StopBowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetReleaseRate( rate );
	adsr_.KeyOff();
}

void BlowBottle::NoteOn( double frequency, double amplitude ) {
	this->SetFrequency( frequency );
	StartBlowing( 1.1 + (amplitude * 0.20), amplitude * 0.02);
	output_gain_ = amplitude + 0.001;
}

void BlowBottle::NoteOff( double amplitude ) {
	this->StopBlowing( amplitude * 0.02 );
}

void BlowBottle::ControlChange( int number, double value ) {
	#if defined(flagDEBUG)

	if ( value < 0 || ( number != 101 && value > 128.0 ) ) {
		LOG("BlowBottle::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double normalizedValue = value * ONE_OVER_128;

	if (number == __SK_NoiseLevel_)
		noise_gain_ = normalizedValue * 30.0;
	else if (number == __SK_ModFrequency_)
		vibrato_.SetFrequency( normalizedValue * 12.0 );
	else if (number == __SK_ModWheel_)
		vibrato_gain_ = normalizedValue * 0.4;
	else if (number == __SK_AfterTouch_Cont_)
		adsr_.SetTarget( normalizedValue );

	#if defined(flagDEBUG)
	else {
		LOG("BlowBottle::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
