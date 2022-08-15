#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

OnePole::OnePole( double thePole ) {
	b_.SetCount( 1 );
	a_.SetCount( 2 );
	a_[0] = 1.0;
	inputs_.SetCount( 1, 1, 0.0 );
	outputs_.SetCount( 2, 1, 0.0 );
	this->SetPole( thePole );
}

OnePole::~OnePole() {
}

void OnePole::SetPole( double thePole ) {
	if ( std::abs( thePole ) >= 1.0 ) {
		LOG("OnePole::SetPole: argument (" << thePole << ") should be less than 1.0!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( thePole > 0.0 )
		b_[0] = (double) (1.0 - thePole);
	else
		b_[0] = (double) (1.0 + thePole);

	a_[1] = -thePole;
}

void OnePole::SetCoefficients( double b0, double a1, bool ClearState ) {
	if ( std::abs( a1 ) >= 1.0 ) {
		LOG("OnePole::SetCoefficients: a1 argument (" << a1 << ") should be less than 1.0!");
		HandleError( AudioError::WARNING );
		return;
	}

	b_[0] = b0;
	a_[1] = a1;

	if ( ClearState ) this->Clear();
}

NAMESPACE_AUDIO_END
