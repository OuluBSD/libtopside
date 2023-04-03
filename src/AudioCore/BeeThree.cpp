#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

BeeThree::BeeThree()
	: FM() {
	for ( int i = 0; i < 3; i++ )
		waves_[i] = new FileLoop( (Audio::GetRawWavePath() + "sinewave.raw").Begin(), true );

	waves_[3] = new FileLoop( (Audio::GetRawWavePath() + "fwavblnk.raw").Begin(), true );
	this->SetRatio( 0, 0.999f );
	this->SetRatio( 1, 1.997f );
	this->SetRatio( 2, 3.006f );
	this->SetRatio( 3, 6.009f );
	gains_[0] = fm_gains_[95];
	gains_[1] = fm_gains_[95];
	gains_[2] = fm_gains_[99];
	gains_[3] = fm_gains_[95];
	adsr_[0]->SetAllTimes( 0.005f, 0.003f, 1.0f, 0.01f );
	adsr_[1]->SetAllTimes( 0.005f, 0.003f, 1.0f, 0.01f );
	adsr_[2]->SetAllTimes( 0.005f, 0.003f, 1.0f, 0.01f );
	adsr_[3]->SetAllTimes( 0.005f, 0.001f, 0.4f, 0.03f );
	twozero_.SetGain( 0.1f );
}

BeeThree::~BeeThree() {
}

void BeeThree::NoteOn( float frequency, float amplitude ) {
	gains_[0] = amplitude * fm_gains_[95];
	gains_[1] = amplitude * fm_gains_[95];
	gains_[2] = amplitude * fm_gains_[99];
	gains_[3] = amplitude * fm_gains_[95];
	this->SetFrequency( frequency );
	this->KeyOn();
}

NAMESPACE_AUDIO_END
