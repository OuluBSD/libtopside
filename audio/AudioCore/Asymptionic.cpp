#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Asymptionic::Asymptionic() {
	value_ = 0.0;
	target_ = 0.0;
	state_ = 0;
	factor_ = exp( -1.0 / ( 0.3 * Audio::GetSampleRate() ) );
	constant_ = 0.0;
	Audio::AddSampleRateAlert( this );
}

Asymptionic::~Asymptionic() {
	Audio::RemoveSampleRateAlert( this );
}

void Asymptionic::SampleRateChanged( double new_rate, double old_rate ) {
	if ( !IgnoreSampleRateChange_ ) {
		double tau = -1.0 / ( std::log( factor_ ) * old_rate );
		factor_ = std::exp( -1.0 / ( tau * new_rate ) );
	}
}

void Asymptionic::KeyOn() {
	this->SetTarget( 1.0 );
}

void Asymptionic::KeyOff() {
	this->SetTarget( 0.0 );
}

void Asymptionic::SetTau( double tau ) {
	if ( tau <= 0.0 ) {
		LOG("Asymptionic::SetTau: negative or zero tau not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	factor_ = std::exp( -1.0 / ( tau * Audio::GetSampleRate() ) );
	constant_ = ( 1.0 - factor_ ) * target_;
}

void Asymptionic::SetTime( double time ) {
	if ( time <= 0.0 ) {
		LOG("Asymptionic::SetTime: negative or zero times not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	double tau = -time / std::log( TARGET_THRESHOLD );
	factor_ = std::exp( -1.0 / ( tau * Audio::GetSampleRate() ) );
	constant_ = ( 1.0 - factor_ ) * target_;
}

void Asymptionic::SetT60( double t60 ) {
	if ( t60 <= 0.0 ) {
		LOG("Asymptionic::SetT60: negative or zero t60 not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	SetTau( t60 / 6.91 );
}

void Asymptionic::SetTarget( double target ) {
	target_ = target;

	if ( value_ != target_ ) state_ = 1;

	constant_ = ( 1.0 - factor_ ) * target_;
}

void Asymptionic::SetValue( double value ) {
	state_ = 0;
	target_ = value;
	value_ = value;
}

NAMESPACE_AUDIO_END

