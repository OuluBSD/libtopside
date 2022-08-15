#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Noise::Noise( unsigned int seed ) {
	this->SetSeed( seed );
}

void Noise::SetSeed( unsigned int seed ) {
	if ( seed == 0 )
		srand( (unsigned int) GetSysTime().Get() );
	else
		srand( seed );
}

NAMESPACE_AUDIO_END
