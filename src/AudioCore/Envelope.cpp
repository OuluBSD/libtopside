#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Envelope::Envelope() : Generator() {
	target_ = 0.0;
	value_ = 0.0;
	rate_ = 0.001;
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

void Envelope::SampleRateChanged( double new_rate, double old_rate ) {
	if ( !IgnoreSampleRateChange_ )
		rate_ = old_rate * rate_ / new_rate;
}

void Envelope::SetRate( double rate ) {
	if ( rate < 0.0 ) {
		LOG("Envelope::SetRate: argument must be >= 0.0!");
		HandleError( AudioError::WARNING );
		return;
	}

	rate_ = rate;
}

void Envelope::SetTime( double time ) {
	if ( time <= 0.0 ) {
		LOG("Envelope::SetTime: argument must be > 0.0!");
		HandleError( AudioError::WARNING );
		return;
	}

	rate_ = 1.0 / ( time * Audio::GetSampleRate() );
}

void Envelope::SetTarget( double target ) {
	target_ = target;

	if ( value_ != target_ ) state_ = 1;
}

void Envelope::SetValue( double value ) {
	state_ = 0;
	target_ = value;
	value_ = value;
	last_frame_[0] = value_;
}

NAMESPACE_AUDIO_END
