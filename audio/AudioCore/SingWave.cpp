#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

SingWave::SingWave( String file_name, bool raw ) {
	wave_.OpenFile( file_name, raw );
	rate_ = 1.0;
	sweepRate_ = 0.001;
	modulator_.SetVibratoRate( 6.0 );
	modulator_.SetVibratoGain( 0.04 );
	modulator_.SetRandomGain( 0.005 );
	this->SetFrequency( 75.0 );
	pitchEnvelope_.SetRate( 1.0 );
	this->Tick();
	this->Tick();
	pitchEnvelope_.SetRate( sweepRate_ * rate_ );
}

SingWave::~SingWave() {
}

void SingWave::SetFrequency( double frequency ) {
	double temp = rate_;
	rate_ = wave_.GetSize() * frequency / Audio::GetSampleRate();
	temp -= rate_;

	if ( temp < 0) temp = -temp;

	pitchEnvelope_.SetTarget( rate_ );
	pitchEnvelope_.SetRate( sweepRate_ * temp );
}

NAMESPACE_AUDIO_END
