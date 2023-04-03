#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

OnePole::OnePole( float thePole ) {
	b_.SetCount( 1 );
	a_.SetCount( 2 );
	a_[0] = 1.0f;
	inputs_.SetCount( 1, 1, 0.0f );
	outputs_.SetCount( 2, 1, 0.0f );
	this->SetPole( thePole );
}

OnePole::~OnePole() {
}

void OnePole::SetPole( float thePole ) {
	if ( std::abs( thePole ) >= 1.0f ) {
		LOG("OnePole::SetPole: argument (" << thePole << ") should be less than 1.0f!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( thePole > 0.0f )
		b_[0] = (float) (1.0f - thePole);
	else
		b_[0] = (float) (1.0f + thePole);

	a_[1] = -thePole;
}

void OnePole::SetCoefficients( float b0, float a1, bool ClearState ) {
	if ( std::abs( a1 ) >= 1.0f ) {
		LOG("OnePole::SetCoefficients: a1 argument (" << a1 << ") should be less than 1.0f!");
		HandleError( AudioError::WARNING );
		return;
	}

	b_[0] = b0;
	a_[1] = a1;

	if ( ClearState ) this->Clear();
}

NAMESPACE_AUDIO_END
