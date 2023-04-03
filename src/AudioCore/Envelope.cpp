#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Envelope::Envelope() : Generator() {
	target_ = 0.0f;
	value_ = 0.0f;
	rate_ = 0.001f;
	state_ = 0;
	Audio::AddSampleRateAlert( this );
}

Envelope::~Envelope() {
	Audio::RemoveSampleRateAlert( this );
}

Envelope& Envelope::operator= ( const Envelope& e ) {
	if ( this != &e ) {
		target_ = e.target_;
		value_ = e.value_;
		rate_ = e.rate_;
		state_ = e.state_;
	}

	return *this;
}

void Envelope::SampleRateChanged( float new_rate, float old_rate ) {
	if ( !IgnoreSampleRateChange_ )
		rate_ = old_rate * rate_ / new_rate;
}

void Envelope::SetRate( float rate ) {
	if ( rate < 0.0f ) {
		LOG("Envelope::SetRate: argument must be >= 0.0f!");
		HandleError( AudioError::WARNING );
		return;
	}

	rate_ = rate;
}

void Envelope::SetTime( float time ) {
	if ( time <= 0.0f ) {
		LOG("Envelope::SetTime: argument must be > 0.0f!");
		HandleError( AudioError::WARNING );
		return;
	}

	rate_ = 1.0f / ( time * Audio::GetSampleRate() );
}

void Envelope::SetTarget( float target ) {
	target_ = target;

	if ( value_ != target_ ) state_ = 1;
}

void Envelope::SetValue( float value ) {
	state_ = 0;
	target_ = value;
	value_ = value;
	last_frame_[0] = value_;
}

NAMESPACE_AUDIO_END
