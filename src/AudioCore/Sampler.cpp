#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Sampler::Sampler() {
	base_frequency_ = 440.0f;
	attackGain_ = 0.25f;
	loop_gain_ = 0.25f;
}

Sampler::~Sampler() {
	int i;

	for ( i = 0; i < attacks_.GetCount(); i++ ) delete attacks_[i];

	for ( i = 0; i < loops_.GetCount(); i++ ) delete loops_[i];
}

void Sampler::KeyOn() {
	for ( int i = 0; i < attacks_.GetCount(); i++ )
		attacks_[i]->Reset();

	adsr_.KeyOn();
}

void Sampler::KeyOff() {
	adsr_.KeyOff();
}

void Sampler::NoteOff( float amplitude ) {
	this->KeyOff();
}

NAMESPACE_AUDIO_END
