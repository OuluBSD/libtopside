#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

PoleZero::PoleZero() {
	b_.SetCount( 2, 0.0 );
	a_.SetCount( 2, 0.0 );
	b_[0] = 1.0;
	a_[0] = 1.0;
	inputs_.SetCount( 2, 1, 0.0 );
	outputs_.SetCount( 2, 1, 0.0 );
}

PoleZero::~PoleZero() {
}

void PoleZero::SetCoefficients( double b0, double b1, double a1, bool ClearState ) {
	if ( std::abs( a1 ) >= 1.0 ) {
		LOG("PoleZero::SetCoefficients: a1 argument (" << a1 << ") should be less than 1.0!");
		HandleError( AudioError::WARNING );
		return;
	}

	b_[0] = b0;
	b_[1] = b1;
	a_[1] = a1;

	if ( ClearState ) this->Clear();
}

void PoleZero::SetAllpass( double coefficient ) {
	if ( std::abs( coefficient ) >= 1.0 ) {
		LOG("PoleZero::SetAllpass: argument (" << coefficient << ") makes filter unstable!");
		HandleError( AudioError::WARNING );
		return;
	}

	b_[0] = coefficient;
	b_[1] = 1.0;
	a_[0] = 1.0;
	a_[1] = coefficient;
}

void PoleZero::SetBlockZero( double thePole ) {
	if ( std::abs( thePole ) >= 1.0 ) {
		LOG("PoleZero::SetBlockZero: argument (" << thePole << ") makes filter unstable!");
		HandleError( AudioError::WARNING );
		return;
	}

	b_[0] = 1.0;
	b_[1] = -1.0;
	a_[0] = 1.0;
	a_[1] = -thePole;
}

NAMESPACE_AUDIO_END
