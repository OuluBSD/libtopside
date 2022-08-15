#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

BeeThree::BeeThree()
	: FM() {
	for ( unsigned int i = 0; i < 3; i++ )
		waves_[i] = new FileLoop( (Audio::GetRawWavePath() + "sinewave.raw").Begin(), true );

	waves_[3] = new FileLoop( (Audio::GetRawWavePath() + "fwavblnk.raw").Begin(), true );
	this->SetRatio( 0, 0.999 );
	this->SetRatio( 1, 1.997 );
	this->SetRatio( 2, 3.006 );
	this->SetRatio( 3, 6.009 );
	gains_[0] = fm_gains_[95];
	gains_[1] = fm_gains_[95];
	gains_[2] = fm_gains_[99];
	gains_[3] = fm_gains_[95];
	adsr_[0]->SetAllTimes( 0.005, 0.003, 1.0, 0.01 );
	adsr_[1]->SetAllTimes( 0.005, 0.003, 1.0, 0.01 );
	adsr_[2]->SetAllTimes( 0.005, 0.003, 1.0, 0.01 );
	adsr_[3]->SetAllTimes( 0.005, 0.001, 0.4, 0.03 );
	twozero_.SetGain( 0.1 );
}

BeeThree::~BeeThree() {
}

void BeeThree::NoteOn( double frequency, double amplitude ) {
	gains_[0] = amplitude * fm_gains_[95];
	gains_[1] = amplitude * fm_gains_[95];
	gains_[2] = amplitude * fm_gains_[99];
	gains_[3] = amplitude * fm_gains_[95];
	this->SetFrequency( frequency );
	this->KeyOn();
}

NAMESPACE_AUDIO_END
