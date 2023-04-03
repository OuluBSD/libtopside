#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

#define __BOTTLE_RADIUS_ 0.999f

BlowBottle::BlowBottle() {
	dc_block_.SetBlockZero();
	vibrato_.SetFrequency( 5.925f );
	vibrato_gain_ = 0.0f;
	resonator_.SetResonance( 500.0f, __BOTTLE_RADIUS_, true );
	adsr_.SetAllTimes( 0.005f, 0.01f, 0.8f, 0.010f );
	noise_gain_ = 20.0f;
	max_pressure_ = 0.0f;
}

BlowBottle::~BlowBottle() {
}

void BlowBottle::Clear() {
	resonator_.Clear();
}

void BlowBottle::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("BlowBottle::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	resonator_.SetResonance( frequency, __BOTTLE_RADIUS_, true );
}

void BlowBottle::StartBlowing( float amplitude, float rate ) {
	if ( amplitude <= 0.0f || rate <= 0.0f ) {
		LOG("BlowBottle::StartBowing: one or more arguments is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetAttackRate( rate );
	max_pressure_ = amplitude;
	adsr_.KeyOn();
}

void BlowBottle::StopBlowing( float rate ) {
	if ( rate <= 0.0f ) {
		LOG("BlowBottle::StopBowing: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	adsr_.SetReleaseRate( rate );
	adsr_.KeyOff();
}

void BlowBottle::NoteOn( float frequency, float amplitude ) {
	this->SetFrequency( frequency );
	StartBlowing( 1.1f + (amplitude * 0.20f), amplitude * 0.02f);
	output_gain_ = amplitude + 0.001f;
}

void BlowBottle::NoteOff( float amplitude ) {
	this->StopBlowing( amplitude * 0.02f );
}

void BlowBottle::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( value < 0 || ( number != 101 && value > 128.0f ) ) {
		LOG("BlowBottle::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if (number == __SK_NoiseLevel_)
		noise_gain_ = normalizedValue * 30.0f;
	else if (number == __SK_ModFrequency_)
		vibrato_.SetFrequency( normalizedValue * 12.0f );
	else if (number == __SK_ModWheel_)
		vibrato_gain_ = normalizedValue * 0.4f;
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
