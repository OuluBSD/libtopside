#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Asymptionic::Asymptionic() {
	value_ = 0.0f;
	target_ = 0.0f;
	state_ = 0;
	factor_ = exp( -1.0f / ( 0.3f * Audio::GetSampleRate() ) );
	constant_ = 0.0f;
	Audio::AddSampleRateAlert( this );
}

Asymptionic::~Asymptionic() {
	Audio::RemoveSampleRateAlert( this );
}

void Asymptionic::SampleRateChanged( float new_rate, float old_rate ) {
	if ( !IgnoreSampleRateChange_ ) {
		float tau = -1.0f / ( std::log( factor_ ) * old_rate );
		factor_ = std::exp( -1.0f / ( tau * new_rate ) );
	}
}

void Asymptionic::KeyOn() {
	this->SetTarget( 1.0f );
}

void Asymptionic::KeyOff() {
	this->SetTarget( 0.0f );
}

void Asymptionic::SetTau( float tau ) {
	if ( tau <= 0.0f ) {
		LOG("Asymptionic::SetTau: negative or zero tau not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	factor_ = std::exp( -1.0f / ( tau * Audio::GetSampleRate() ) );
	constant_ = ( 1.0f - factor_ ) * target_;
}

void Asymptionic::SetTime( float time ) {
	if ( time <= 0.0f ) {
		LOG("Asymptionic::SetTime: negative or zero times not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	float tau = -time / std::log( TARGET_THRESHOLD );
	factor_ = std::exp( -1.0f / ( tau * Audio::GetSampleRate() ) );
	constant_ = ( 1.0f - factor_ ) * target_;
}

void Asymptionic::SetT60( float t60 ) {
	if ( t60 <= 0.0f ) {
		LOG("Asymptionic::SetT60: negative or zero t60 not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	SetTau( t60 / 6.91f );
}

void Asymptionic::SetTarget( float target ) {
	target_ = target;

	if ( value_ != target_ ) state_ = 1;

	constant_ = ( 1.0f - factor_ ) * target_;
}

void Asymptionic::SetValue( float value ) {
	state_ = 0;
	target_ = value;
	value_ = value;
}

NAMESPACE_AUDIO_END

