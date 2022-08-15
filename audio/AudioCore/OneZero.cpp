#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

OneZero::OneZero( double theZero ) {
	b_.SetCount( 2 );
	inputs_.SetCount( 2, 1, 0.0 );
	this->SetZero( theZero );
}

OneZero::~OneZero() {
}

void OneZero::SetZero( double theZero ) {
	if ( theZero > 0.0 )
		b_[0] = 1.0 / ((double) 1.0 + theZero);
	else
		b_[0] = 1.0 / ((double) 1.0 - theZero);

	b_[1] = -theZero * b_[0];
}

void OneZero::SetCoefficients( double b0, double b1, bool ClearState ) {
	b_[0] = b0;
	b_[1] = b1;

	if ( ClearState ) this->Clear();
}

NAMESPACE_AUDIO_END
