#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

OneZero::OneZero( float theZero ) {
	b_.SetCount( 2 );
	inputs_.SetCount( 2, 1, 0.0f );
	this->SetZero( theZero );
}

OneZero::~OneZero() {
}

void OneZero::SetZero( float theZero ) {
	if ( theZero > 0.0f )
		b_[0] = 1.0f / ((float) 1.0f + theZero);
	else
		b_[0] = 1.0f / ((float) 1.0f - theZero);

	b_[1] = -theZero * b_[0];
}

void OneZero::SetCoefficients( float b0, float b1, bool ClearState ) {
	b_[0] = b0;
	b_[1] = b1;

	if ( ClearState ) this->Clear();
}

NAMESPACE_AUDIO_END
