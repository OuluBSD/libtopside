#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

BiQuad::BiQuad() : Filter() {
	b_.SetCount( 3, 0.0f );
	a_.SetCount( 3, 0.0f );
	b_[0] = 1.0f;
	a_[0] = 1.0f;
	inputs_.SetCount( 3, 1, 0.0f );
	outputs_.SetCount( 3, 1, 0.0f );
	Audio::AddSampleRateAlert( this );
}

BiQuad::~BiQuad() {
	Audio::RemoveSampleRateAlert( this );
}

void BiQuad::SetCoefficients( float b0, float b1, float b2, float a1, float a2, bool ClearState ) {
	b_[0] = b0;
	b_[1] = b1;
	b_[2] = b2;
	a_[1] = a1;
	a_[2] = a2;

	if ( ClearState ) this->Clear();
}

void BiQuad::SampleRateChanged( float new_rate, float old_rate ) {
	if ( !IgnoreSampleRateChange_ ) {
		LOG("BiQuad::SampleRateChanged: you may need to recompute filter coefficients!");
		HandleError( AudioError::WARNING );
	}
}

void BiQuad::SetResonance( float frequency, float radius, bool normalize ) {
	#if defined(flagDEBUG)

	if ( frequency < 0.0f || frequency > 0.5f * Audio::GetSampleRate() ) {
		LOG("BiQuad::SetResonance: frequency argument (" << frequency << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( radius < 0.0f || radius >= 1.0f ) {
		LOG("BiQuad::SetResonance: radius argument (" << radius << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	a_[2] = radius * radius;
	a_[1] = -2.0f * radius * cos( TWO_PI * frequency / Audio::GetSampleRate() );

	if ( normalize ) {
		b_[0] = 0.5f - 0.5f * a_[2];
		b_[1] = 0.0f;
		b_[2] = -b_[0];
	}
}

void BiQuad::SetNotch( float frequency, float radius ) {
	#if defined(flagDEBUG)

	if ( frequency < 0.0f || frequency > 0.5f * Audio::GetSampleRate() ) {
		LOG("BiQuad::SetNotch: frequency argument (" << frequency << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( radius < 0.0f ) {
		LOG("BiQuad::SetNotch: radius argument (" << radius << ") is negative!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	b_[2] = radius * radius;
	b_[1] = (float) - 2.0f * radius * cos( TWO_PI * (float) frequency / Audio::GetSampleRate() );
}

void BiQuad::SetEqualGainZeroes() {
	b_[0] = 1.0f;
	b_[1] = 0.0f;
	b_[2] = -1.0f;
}

NAMESPACE_AUDIO_END
