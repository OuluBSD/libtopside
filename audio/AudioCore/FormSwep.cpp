#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

FormSwep::FormSwep() {
	frequency_ = 0.0;
	radius_ = 0.0;
	targetGain_ = 1.0;
	targetFrequency_ = 0.0;
	targetRadius_ = 0.0;
	deltaGain_ = 0.0;
	deltaFrequency_ = 0.0;
	deltaRadius_ = 0.0;
	sweepState_ = 0.0;
	sweepRate_ = 0.002;
	dirty_ = false;
	b_.SetCount( 3, 0.0 );
	a_.SetCount( 3, 0.0 );
	a_[0] = 1.0;
	inputs_.SetCount( 3, 1, 0.0 );
	outputs_.SetCount( 3, 1, 0.0 );
	Audio::AddSampleRateAlert( this );
}

FormSwep::~FormSwep() {
	Audio::RemoveSampleRateAlert( this );
}

void FormSwep::SampleRateChanged( double new_rate, double old_rate ) {
	if ( !IgnoreSampleRateChange_ ) {
		LOG("FormSwep::SampleRateChanged: you may need to recompute filter coefficients!");
		HandleError( AudioError::WARNING );
	}
}

void FormSwep::SetResonance( double frequency, double radius ) {
	#if defined(flagDEBUG)

	if ( frequency < 0.0 || frequency > 0.5 * Audio::GetSampleRate() ) {
		LOG("FormSwep::SetResonance: frequency argument (" << frequency << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( radius < 0.0 || radius >= 1.0 ) {
		LOG("FormSwep::SetResonance: radius argument (" << radius << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	radius_ = radius;
	frequency_ = frequency;
	a_[2] = radius * radius;
	a_[1] = -2.0 * radius * cos( TWO_PI * frequency / Audio::GetSampleRate() );
	b_[0] = 0.5 - 0.5 * a_[2];
	b_[1] = 0.0;
	b_[2] = -b_[0];
}

void FormSwep::SetStates( double frequency, double radius, double gain ) {
	dirty_ = false;

	if ( frequency_ != frequency || radius_ != radius )
		this->SetResonance( frequency, radius );

	gain_ = gain;
	targetFrequency_ = frequency;
	targetRadius_ = radius;
	targetGain_ = gain;
}

void FormSwep::SetTargets( double frequency, double radius, double gain ) {
	if ( frequency < 0.0 || frequency > 0.5 * Audio::GetSampleRate() ) {
		LOG("FormSwep::SetTargets: frequency argument (" << frequency << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( radius < 0.0 || radius >= 1.0 ) {
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
	sweepState_ = 0.0;
}

void FormSwep::SetSweepRate( double rate ) {
	if ( rate < 0.0 || rate > 1.0 ) {
		LOG("FormSwep::SetSweepRate: argument (" << rate << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	sweepRate_ = rate;
}

void FormSwep::SetSweepTime( double time ) {
	if ( time <= 0.0 ) {
		LOG("FormSwep::SetSweepTime: argument (" << time << ") must be > 0.0!");
		HandleError( AudioError::WARNING );
		return;
	}

	this->SetSweepRate( 1.0 / ( time * Audio::GetSampleRate() ) );
}

NAMESPACE_AUDIO_END
