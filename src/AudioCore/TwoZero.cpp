#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

TwoZero::TwoZero() {
	b_.SetCount( 3, 0.0f );
	inputs_.SetCount( 3, 1, 0.0f );
	b_[0] = 1.0f;
	Audio::AddSampleRateAlert( this );
}

TwoZero::~TwoZero() {
	Audio::RemoveSampleRateAlert( this );
}

void TwoZero::SampleRateChanged( float new_rate, float old_rate ) {
	if ( !IgnoreSampleRateChange_ ) {
		LOG("TwoZero::SampleRateChanged: you may need to recompute filter coefficients!");
		HandleError( AudioError::WARNING );
	}
}

void TwoZero::SetCoefficients( float b0, float b1, float b2, bool ClearState ) {
	b_[0] = b0;
	b_[1] = b1;
	b_[2] = b2;

	if ( ClearState ) this->Clear();
}

void TwoZero::SetNotch( float frequency, float radius ) {
	#if defined(flagDEBUG)

	if ( frequency < 0.0f || frequency > 0.5f * Audio::GetSampleRate() ) {
		LOG("TwoZero::SetNotch: frequency argument (" << frequency << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( radius < 0.0f ) {
		LOG("TwoZero::SetNotch: radius argument (" << radius << ") is negative!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	b_[2] = radius * radius;
	b_[1] = -2.0 * radius * cos(TWO_PI * frequency / Audio::GetSampleRate());

	if ( b_[1] > 0.0f )
		b_[0] = 1.0f / ( 1.0f + b_[1] + b_[2] );
	else
		b_[0] = 1.0f / ( 1.0f - b_[1] + b_[2] );

	b_[1] *= b_[0];
	b_[2] *= b_[0];
}

NAMESPACE_AUDIO_END
