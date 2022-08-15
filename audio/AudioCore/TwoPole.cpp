#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

TwoPole::TwoPole() {
	b_.SetCount( 1 );
	a_.SetCount( 3 );
	inputs_.SetCount( 1, 1, 0.0 );
	outputs_.SetCount( 3, 1, 0.0 );
	b_[0] = 1.0;
	a_[0] = 1.0;
	Audio::AddSampleRateAlert( this );
}

TwoPole::~TwoPole() {
	Audio::RemoveSampleRateAlert( this );
}

void TwoPole::SampleRateChanged( double new_rate, double old_rate ) {
	if ( !IgnoreSampleRateChange_ ) {
		LOG("TwoPole::SampleRateChanged: you may need to recompute filter coefficients!");
		HandleError( AudioError::WARNING );
	}
}

void TwoPole::SetResonance( double frequency, double radius, bool normalize ) {
	#if defined(flagDEBUG)

	if ( frequency < 0.0 || frequency > 0.5 * Audio::GetSampleRate() ) {
		LOG("TwoPole::SetResonance: frequency argument (" << frequency << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( radius < 0.0 || radius >= 1.0 ) {
		LOG("TwoPole::SetResonance: radius argument (" << radius << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	a_[2] = radius * radius;
	a_[1] = (double) - 2.0 * radius * cos(TWO_PI * frequency / Audio::GetSampleRate());

	if ( normalize ) {
		double real = 1 - radius + (a_[2] - radius) * cos(TWO_PI * 2 * frequency / Audio::GetSampleRate());
		double imag = (a_[2] - radius) * sin(TWO_PI * 2 * frequency / Audio::GetSampleRate());
		b_[0] = sqrt( pow(real, 2) + pow(imag, 2) );
	}
}

void TwoPole::SetCoefficients( double b0, double a1, double a2, bool ClearState ) {
	b_[0] = b0;
	a_[1] = a1;
	a_[2] = a2;

	if ( ClearState ) this->Clear();
}

NAMESPACE_AUDIO_END
