#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

BiQuad::BiQuad() : Filter() {
	b_.SetCount( 3, 0.0 );
	a_.SetCount( 3, 0.0 );
	b_[0] = 1.0;
	a_[0] = 1.0;
	inputs_.SetCount( 3, 1, 0.0 );
	outputs_.SetCount( 3, 1, 0.0 );
	Audio::AddSampleRateAlert( this );
}

BiQuad::~BiQuad() {
	Audio::RemoveSampleRateAlert( this );
}

void BiQuad::SetCoefficients( double b0, double b1, double b2, double a1, double a2, bool ClearState ) {
	b_[0] = b0;
	b_[1] = b1;
	b_[2] = b2;
	a_[1] = a1;
	a_[2] = a2;

	if ( ClearState ) this->Clear();
}

void BiQuad::SampleRateChanged( double new_rate, double old_rate ) {
	if ( !IgnoreSampleRateChange_ ) {
		LOG("BiQuad::SampleRateChanged: you may need to recompute filter coefficients!");
		HandleError( AudioError::WARNING );
	}
}

void BiQuad::SetResonance( double frequency, double radius, bool normalize ) {
	#if defined(flagDEBUG)

	if ( frequency < 0.0 || frequency > 0.5 * Audio::GetSampleRate() ) {
		LOG("BiQuad::SetResonance: frequency argument (" << frequency << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( radius < 0.0 || radius >= 1.0 ) {
		LOG("BiQuad::SetResonance: radius argument (" << radius << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	a_[2] = radius * radius;
	a_[1] = -2.0 * radius * cos( TWO_PI * frequency / Audio::GetSampleRate() );

	if ( normalize ) {
		b_[0] = 0.5 - 0.5 * a_[2];
		b_[1] = 0.0;
		b_[2] = -b_[0];
	}
}

void BiQuad::SetNotch( double frequency, double radius ) {
	#if defined(flagDEBUG)

	if ( frequency < 0.0 || frequency > 0.5 * Audio::GetSampleRate() ) {
		LOG("BiQuad::SetNotch: frequency argument (" << frequency << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( radius < 0.0 ) {
		LOG("BiQuad::SetNotch: radius argument (" << radius << ") is negative!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	b_[2] = radius * radius;
	b_[1] = (double) - 2.0 * radius * cos( TWO_PI * (double) frequency / Audio::GetSampleRate() );
}

void BiQuad::SetEqualGainZeroes() {
	b_[0] = 1.0;
	b_[1] = 0.0;
	b_[2] = -1.0;
}

NAMESPACE_AUDIO_END
