#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

ADSR::ADSR() {
	target_ = 0.0f;
	value_ = 0.0f;
	attack_rate_ = 0.001f;
	decay_rate_ = 0.001f;
	release_rate_ = 0.005f;
	release_time_ = -1.0f;
	sustain_level_ = 0.5f;
	state_ = IDLE;
	Audio::AddSampleRateAlert( this );
}

ADSR::~ADSR() {
	Audio::RemoveSampleRateAlert( this );
}

void ADSR::SampleRateChanged( float new_rate, float old_rate ) {
	if ( !IgnoreSampleRateChange_ ) {
		attack_rate_ = old_rate * attack_rate_ / new_rate;
		decay_rate_ = old_rate * decay_rate_ / new_rate;
		release_rate_ = old_rate * release_rate_ / new_rate;
	}
}

void ADSR::KeyOn() {
	if ( target_ <= 0.0f ) target_ = 1.0f;

	state_ = ATTACK;
}

void ADSR::KeyOff() {
	target_ = 0.0f;
	state_ = RELEASE;

	if ( release_time_ > 0.0f )
		release_rate_ = value_ / ( release_time_ * Audio::GetSampleRate() );
}

void ADSR::SetAttackRate( float rate ) {
	if ( rate < 0.0f ) {
		LOG("ADSR::SetAttackRate: argument must be >= 0.0f!");
		HandleError( AudioError::WARNING );
		return;
	}

	attack_rate_ = rate;
}

void ADSR::SetAttackTarget( float target ) {
	if ( target < 0.0f ) {
		LOG("ADSR::SetAttackTarget: negative target not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	target_ = target;
}

void ADSR::SetDecayRate( float rate ) {
	if ( rate < 0.0f ) {
		LOG("ADSR::SetDecayRate: negative rates not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	decay_rate_ = rate;
}

void ADSR::SetSustainLevel( float level ) {
	if ( level < 0.0f ) {
		LOG("ADSR::SetSustainLevel: negative level not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	sustain_level_ = level;
}

void ADSR::SetReleaseRate( float rate ) {
	if ( rate < 0.0f ) {
		LOG("ADSR::SetReleaseRate: negative rates not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	release_rate_ = rate;
	release_time_ = -1.0f;
}

void ADSR::SetAttackTime( float time ) {
	if ( time <= 0.0f ) {
		LOG("ADSR::SetAttackTime: negative or zero times not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	attack_rate_ = 1.0f / ( time * Audio::GetSampleRate() );
}

void ADSR::SetDecayTime( float time ) {
	if ( time <= 0.0f ) {
		LOG("ADSR::SetDecayTime: negative or zero times not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	decay_rate_ = (1.0f - sustain_level_) / ( time * Audio::GetSampleRate() );
}

void ADSR::SetReleaseTime( float time ) {
	if ( time <= 0.0f ) {
		LOG("ADSR::SetReleaseTime: negative or zero times not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	release_rate_ = sustain_level_ / ( time * Audio::GetSampleRate() );
	release_time_ = time;
}

void ADSR::SetAllTimes( float aTime, float dTime, float sLevel, float rTime ) {
	this->SetAttackTime( aTime );
	this->SetSustainLevel( sLevel );
	this->SetDecayTime( dTime );
	this->SetReleaseTime( rTime );
}

void ADSR::SetTarget( float target ) {
	if ( target < 0.0f ) {
		LOG("ADSR::SetTarget: negative target not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	target_ = target;
	this->SetSustainLevel( target_ );

	if ( value_ < target_ ) state_ = ATTACK;

	if ( value_ > target_ ) state_ = DECAY;
}

void ADSR::SetValue( float value ) {
	state_ = SUSTAIN;
	target_ = value;
	value_ = value;
	this->SetSustainLevel( value );
	last_frame_[0] = value;
}

NAMESPACE_AUDIO_END
