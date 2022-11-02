#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

ADSR::ADSR() {
	target_ = 0.0;
	value_ = 0.0;
	attack_rate_ = 0.001;
	decay_rate_ = 0.001;
	release_rate_ = 0.005;
	release_time_ = -1.0;
	sustain_level_ = 0.5;
	state_ = IDLE;
	Audio::AddSampleRateAlert( this );
}

ADSR::~ADSR() {
	Audio::RemoveSampleRateAlert( this );
}

void ADSR::SampleRateChanged( double new_rate, double old_rate ) {
	if ( !IgnoreSampleRateChange_ ) {
		attack_rate_ = old_rate * attack_rate_ / new_rate;
		decay_rate_ = old_rate * decay_rate_ / new_rate;
		release_rate_ = old_rate * release_rate_ / new_rate;
	}
}

void ADSR::KeyOn() {
	if ( target_ <= 0.0 ) target_ = 1.0;

	state_ = ATTACK;
}

void ADSR::KeyOff() {
	target_ = 0.0;
	state_ = RELEASE;

	if ( release_time_ > 0.0 )
		release_rate_ = value_ / ( release_time_ * Audio::GetSampleRate() );
}

void ADSR::SetAttackRate( double rate ) {
	if ( rate < 0.0 ) {
		LOG("ADSR::SetAttackRate: argument must be >= 0.0!");
		HandleError( AudioError::WARNING );
		return;
	}

	attack_rate_ = rate;
}

void ADSR::SetAttackTarget( double target ) {
	if ( target < 0.0 ) {
		LOG("ADSR::SetAttackTarget: negative target not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	target_ = target;
}

void ADSR::SetDecayRate( double rate ) {
	if ( rate < 0.0 ) {
		LOG("ADSR::SetDecayRate: negative rates not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	decay_rate_ = rate;
}

void ADSR::SetSustainLevel( double level ) {
	if ( level < 0.0 ) {
		LOG("ADSR::SetSustainLevel: negative level not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	sustain_level_ = level;
}

void ADSR::SetReleaseRate( double rate ) {
	if ( rate < 0.0 ) {
		LOG("ADSR::SetReleaseRate: negative rates not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	release_rate_ = rate;
	release_time_ = -1.0;
}

void ADSR::SetAttackTime( double time ) {
	if ( time <= 0.0 ) {
		LOG("ADSR::SetAttackTime: negative or zero times not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	attack_rate_ = 1.0 / ( time * Audio::GetSampleRate() );
}

void ADSR::SetDecayTime( double time ) {
	if ( time <= 0.0 ) {
		LOG("ADSR::SetDecayTime: negative or zero times not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	decay_rate_ = (1.0 - sustain_level_) / ( time * Audio::GetSampleRate() );
}

void ADSR::SetReleaseTime( double time ) {
	if ( time <= 0.0 ) {
		LOG("ADSR::SetReleaseTime: negative or zero times not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	release_rate_ = sustain_level_ / ( time * Audio::GetSampleRate() );
	release_time_ = time;
}

void ADSR::SetAllTimes( double aTime, double dTime, double sLevel, double rTime ) {
	this->SetAttackTime( aTime );
	this->SetSustainLevel( sLevel );
	this->SetDecayTime( dTime );
	this->SetReleaseTime( rTime );
}

void ADSR::SetTarget( double target ) {
	if ( target < 0.0 ) {
		LOG("ADSR::SetTarget: negative target not allowed!");
		HandleError( AudioError::WARNING );
		return;
	}

	target_ = target;
	this->SetSustainLevel( target_ );

	if ( value_ < target_ ) state_ = ATTACK;

	if ( value_ > target_ ) state_ = DECAY;
}

void ADSR::SetValue( double value ) {
	state_ = SUSTAIN;
	target_ = value;
	value_ = value;
	this->SetSustainLevel( value );
	last_frame_[0] = value;
}

NAMESPACE_AUDIO_END
