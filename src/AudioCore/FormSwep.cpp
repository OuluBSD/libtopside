#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

FormSwep::FormSwep() {
	frequency_ = 0.0f;
	radius_ = 0.0f;
	targetGain_ = 1.0f;
	targetFrequency_ = 0.0f;
	targetRadius_ = 0.0f;
	deltaGain_ = 0.0f;
	deltaFrequency_ = 0.0f;
	deltaRadius_ = 0.0f;
	sweepState_ = 0.0f;
	sweepRate_ = 0.002;
	dirty_ = false;
	b_.SetCount( 3, 0.0f );
	a_.SetCount( 3, 0.0f );
	a_[0] = 1.0f;
	inputs_.SetCount( 3, 1, 0.0f );
	outputs_.SetCount( 3, 1, 0.0f );
	Audio::AddSampleRateAlert( this );
}

FormSwep::~FormSwep() {
	Audio::RemoveSampleRateAlert( this );
}

void FormSwep::SampleRateChanged( float new_rate, float old_rate ) {
	if ( !IgnoreSampleRateChange_ ) {
		LOG("FormSwep::SampleRateChanged: you may need to recompute filter coefficients!");
		HandleError( AudioError::WARNING );
	}
}

void FormSwep::SetResonance( float frequency, float radius ) {
	#if defined(flagDEBUG)

	if ( frequency < 0.0f || frequency > 0.5f * Audio::GetSampleRate() ) {
		LOG("FormSwep::SetResonance: frequency argument (" << frequency << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( radius < 0.0f || radius >= 1.0f ) {
		LOG("FormSwep::SetResonance: radius argument (" << radius << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	radius_ = radius;
	frequency_ = frequency;
	a_[2] = radius * radius;
	a_[1] = -2.0 * radius * cos( TWO_PI * frequency / Audio::GetSampleRate() );
	b_[0] = 0.5f - 0.5f * a_[2];
	b_[1] = 0.0f;
	b_[2] = -b_[0];
}

void FormSwep::SetStates( float frequency, float radius, float gain ) {
	dirty_ = false;

	if ( frequency_ != frequency || radius_ != radius )
		this->SetResonance( frequency, radius );

	gain_ = gain;
	targetFrequency_ = frequency;
	targetRadius_ = radius;
	targetGain_ = gain;
}

void FormSwep::SetTargets( float frequency, float radius, float gain ) {
	if ( frequency < 0.0f || frequency > 0.5f * Audio::GetSampleRate() ) {
		LOG("FormSwep::SetTargets: frequency argument (" << frequency << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( radius < 0.0f || radius >= 1.0f ) {
		LOG("FormSwep::SetTargets: radius argument (" << radius << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	dirty_ = true;
	StartFrequency_ = frequency_;
	StartRadius_ = radius_;
	StartGain_ = gain_;
	targetFrequency_ = frequency;
	targetRadius_ = radius;
	targetGain_ = gain;
	deltaFrequency_ = frequency - frequency_;
	deltaRadius_ = radius - radius_;
	deltaGain_ = gain - gain_;
	sweepState_ = 0.0f;
}

void FormSwep::SetSweepRate( float rate ) {
	if ( rate < 0.0f || rate > 1.0f ) {
		LOG("FormSwep::SetSweepRate: argument (" << rate << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	sweepRate_ = rate;
}

void FormSwep::SetSweepTime( float time ) {
	if ( time <= 0.0f ) {
		LOG("FormSwep::SetSweepTime: argument (" << time << ") must be > 0.0f!");
		HandleError( AudioError::WARNING );
		return;
	}

	this->SetSweepRate( 1.0f / ( time * Audio::GetSampleRate() ) );
}

NAMESPACE_AUDIO_END
