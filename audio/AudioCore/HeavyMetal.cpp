#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

HeavyMetal::HeavyMetal()
	: FM() {
	for ( unsigned int i = 0; i < 3; i++ )
		waves_[i] = new FileLoop( (Audio::GetRawWavePath() + "sinewave.raw").Begin(), true );

	waves_[3] = new FileLoop( (Audio::GetRawWavePath() + "fwavblnk.raw").Begin(), true );
	this->SetRatio(0, 1.0 * 1.000);
	this->SetRatio(1, 4.0 * 0.999);
	this->SetRatio(2, 3.0 * 1.001);
	this->SetRatio(3, 0.5 * 1.002);
	gains_[0] = fm_gains_[92];
	gains_[1] = fm_gains_[76];
	gains_[2] = fm_gains_[91];
	gains_[3] = fm_gains_[68];
	adsr_[0]->SetAllTimes( 0.001, 0.001, 1.0, 0.01);
	adsr_[1]->SetAllTimes( 0.001, 0.010, 1.0, 0.50);
	adsr_[2]->SetAllTimes( 0.010, 0.005, 1.0, 0.20);
	adsr_[3]->SetAllTimes( 0.030, 0.010, 0.2, 0.20);
	twozero_.SetGain( 2.0 );
	vibrato_.SetFrequency( 5.5 );
	mod_depth_ = 0.0;
}

HeavyMetal::~HeavyMetal() {
}

void HeavyMetal::NoteOn( double frequency, double amplitude ) {
	gains_[0] = amplitude * fm_gains_[92];
	gains_[1] = amplitude * fm_gains_[76];
	gains_[2] = amplitude * fm_gains_[91];
	gains_[3] = amplitude * fm_gains_[68];
	this->SetFrequency( frequency );
	this->KeyOn();
}

NAMESPACE_AUDIO_END
