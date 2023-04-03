#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

PoleZero::PoleZero() {
	b_.SetCount( 2, 0.0f );
	a_.SetCount( 2, 0.0f );
	b_[0] = 1.0f;
	a_[0] = 1.0f;
	inputs_.SetCount( 2, 1, 0.0f );
	outputs_.SetCount( 2, 1, 0.0f );
}

PoleZero::~PoleZero() {
}

void PoleZero::SetCoefficients( float b0, float b1, float a1, bool ClearState ) {
	if ( std::abs( a1 ) >= 1.0f ) {
		LOG("PoleZero::SetCoefficients: a1 argument (" << a1 << ") should be less than 1.0f!");
		HandleError( AudioError::WARNING );
		return;
	}

	b_[0] = b0;
	b_[1] = b1;
	a_[1] = a1;

	if ( ClearState ) this->Clear();
}

void PoleZero::SetAllpass( float coefficient ) {
	if ( std::abs( coefficient ) >= 1.0f ) {
		LOG("PoleZero::SetAllpass: argument (" << coefficient << ") makes filter unstable!");
		HandleError( AudioError::WARNING );
		return;
	}

	b_[0] = coefficient;
	b_[1] = 1.0f;
	a_[0] = 1.0f;
	a_[1] = coefficient;
}

void PoleZero::SetBlockZero( float thePole ) {
	if ( std::abs( thePole ) >= 1.0f ) {
		LOG("PoleZero::SetBlockZero: argument (" << thePole << ") makes filter unstable!");
		HandleError( AudioError::WARNING );
		return;
	}

	b_[0] = 1.0f;
	b_[1] = -1.0f;
	a_[0] = 1.0f;
	a_[1] = -thePole;
}

NAMESPACE_AUDIO_END
