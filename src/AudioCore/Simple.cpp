#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Simple::Simple() {
	loop_ = new FileLoop( (Audio::GetRawWavePath() + "impuls10.raw").Begin(), true );
	filter_.SetPole( 0.5f );
	base_frequency_ = 440.0f;
	SetFrequency( base_frequency_ );
	loop_gain_ = 0.5;
}

Simple::~Simple() {
	delete loop_;
}

void Simple::KeyOn() {
	adsr_.KeyOn();
}

void Simple::KeyOff() {
	adsr_.KeyOff();
}

void Simple::NoteOn( float frequency, float amplitude ) {
	this->KeyOn();
	this->SetFrequency( frequency );
	filter_.SetGain( amplitude );
}
void Simple::NoteOff( float amplitude ) {
	this->KeyOff();
}

void Simple::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("Simple::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	biquad_.SetResonance( frequency, 0.98, true );
	loop_->SetFrequency( frequency );
}

void Simple::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0 ) == false ) {
		LOG("Simple::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if (number == __SK_Breath_)
		filter_.SetPole( 0.99 * (1.0f - (normalizedValue * 2.0f)) );
	else if (number == __SK_NoiseLevel_)
		loop_gain_ = normalizedValue;
	else if (number == __SK_ModFrequency_) {
		normalizedValue /= 0.2f * Audio::GetSampleRate();
		adsr_.SetAttackRate( normalizedValue );
		adsr_.SetDecayRate( normalizedValue );
		adsr_.SetReleaseRate( normalizedValue );
	}
	else if (number == __SK_AfterTouch_Cont_)
		adsr_.SetTarget( normalizedValue );

	#if defined(flagDEBUG)
	else {
		LOG("Simple::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
