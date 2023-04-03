#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Resonate::Resonate() {
	pole_frequency_ = 4000.0f;
	pole_radius_ = 0.95;
	filter_.SetResonance( pole_frequency_, pole_radius_, true );
	zero_frequency_ = 0.0f;
	zero_radius_ = 0.0f;
}

Resonate::~Resonate() {
}

void Resonate::NoteOn( float frequency, float amplitude ) {
	adsr_.SetTarget( amplitude );
	this->KeyOn();
	this->SetResonance( frequency, pole_radius_ );
}

void Resonate::NoteOff( float amplitude ) {
	this->KeyOff();
}

void Resonate::SetResonance( float frequency, float radius ) {
	if ( frequency < 0.0f ) {
		LOG("Resonate::SetResonance: frequency parameter is less than zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( radius < 0.0f || radius >= 1.0f ) {
		LOG("Resonate::SetResonance: radius parameter is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	pole_frequency_ = frequency;
	pole_radius_ = radius;
	filter_.SetResonance( pole_frequency_, pole_radius_, true );
}

void Resonate::SetNotch( float frequency, float radius ) {
	if ( frequency < 0.0f ) {
		LOG("Resonate::SetNotch: frequency parameter is less than zero ... Setting to 0.0f!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( radius < 0.0f ) {
		LOG("Resonate::SetNotch: radius parameter is less than 0.0f!");
		HandleError( AudioError::WARNING );
		return;
	}

	zero_frequency_ = frequency;
	zero_radius_ = radius;
	filter_.SetNotch( zero_frequency_, zero_radius_ );
}

void Resonate::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0 ) == false ) {
		LOG("Resonate::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if (number == 2)
		SetResonance( normalizedValue * Audio::GetSampleRate() * 0.5, pole_radius_ );
	else if (number == 4)
		SetResonance( pole_frequency_, normalizedValue * 0.9999 );
	else if (number == 11)
		this->SetNotch( normalizedValue * Audio::GetSampleRate() * 0.5, zero_radius_ );
	else if (number == 1)
		this->SetNotch( zero_frequency_, normalizedValue );
	else if (number == __SK_AfterTouch_Cont_)
		adsr_.SetTarget( normalizedValue );

	#if defined(flagDEBUG)
	else {
		LOG("Resonate::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
