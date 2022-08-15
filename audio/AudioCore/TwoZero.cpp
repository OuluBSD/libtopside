#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

TwoZero::TwoZero() {
	b_.SetCount( 3, 0.0 );
	inputs_.SetCount( 3, 1, 0.0 );
	b_[0] = 1.0;
	Audio::AddSampleRateAlert( this );
}

TwoZero::~TwoZero() {
	Audio::RemoveSampleRateAlert( this );
}

void TwoZero::SampleRateChanged( double new_rate, double old_rate ) {
	if ( !IgnoreSampleRateChange_ ) {
		LOG("TwoZero::SampleRateChanged: you may need to recompute filter coefficients!");
		HandleError( AudioError::WARNING );
	}
}

void TwoZero::SetCoefficients( double b0, double b1, double b2, bool ClearState ) {
	b_[0] = b0;
	b_[1] = b1;
	b_[2] = b2;

	if ( ClearState ) this->Clear();
}

void TwoZero::SetNotch( double frequency, double radius ) {
	#if defined(flagDEBUG)

	if ( frequency < 0.0 || frequency > 0.5 * Audio::GetSampleRate() ) {
		LOG("TwoZero::SetNotch: frequency argument (" << frequency << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( radius < 0.0 ) {
		LOG("TwoZero::SetNotch: radius argument (" << radius << ") is negative!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	b_[2] = radius * radius;
	b_[1] = -2.0 * radius * cos(TWO_PI * frequency / Audio::GetSampleRate());

	if ( b_[1] > 0.0 )
		b_[0] = 1.0 / ( 1.0 + b_[1] + b_[2] );
	else
		b_[0] = 1.0 / ( 1.0 - b_[1] + b_[2] );

	b_[1] *= b_[0];
	b_[2] *= b_[0];
}

NAMESPACE_AUDIO_END
