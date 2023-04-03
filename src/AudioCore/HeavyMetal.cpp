#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

HeavyMetal::HeavyMetal()
	: FM() {
	for ( int i = 0; i < 3; i++ )
		waves_[i] = new FileLoop( (Audio::GetRawWavePath() + "sinewave.raw").Begin(), true );

	waves_[3] = new FileLoop( (Audio::GetRawWavePath() + "fwavblnk.raw").Begin(), true );
	this->SetRatio(0, 1.0f * 1.000f);
	this->SetRatio(1, 4.0f * 0.999f);
	this->SetRatio(2, 3.0f * 1.001f);
	this->SetRatio(3, 0.5f * 1.002f);
	gains_[0] = fm_gains_[92];
	gains_[1] = fm_gains_[76];
	gains_[2] = fm_gains_[91];
	gains_[3] = fm_gains_[68];
	adsr_[0]->SetAllTimes( 0.001f, 0.001f, 1.0f, 0.01f);
	adsr_[1]->SetAllTimes( 0.001f, 0.010f, 1.0f, 0.50f);
	adsr_[2]->SetAllTimes( 0.010f, 0.005f, 1.0f, 0.20f);
	adsr_[3]->SetAllTimes( 0.030f, 0.010f, 0.2f, 0.20f);
	twozero_.SetGain( 2.0f );
	vibrato_.SetFrequency( 5.5f );
	mod_depth_ = 0.0f;
}

HeavyMetal::~HeavyMetal() {
}

void HeavyMetal::NoteOn( float frequency, float amplitude ) {
	gains_[0] = amplitude * fm_gains_[92];
	gains_[1] = amplitude * fm_gains_[76];
	gains_[2] = amplitude * fm_gains_[91];
	gains_[3] = amplitude * fm_gains_[68];
	this->SetFrequency( frequency );
	this->KeyOn();
}

NAMESPACE_AUDIO_END
