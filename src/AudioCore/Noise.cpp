#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Noise::Noise( int seed ) {
	this->SetSeed( seed );
}

void Noise::SetSeed( int seed ) {
	if ( seed == 0 )
		srand( (int) GetSysTime().Get() );
	else
		srand( seed );
}

NAMESPACE_AUDIO_END
