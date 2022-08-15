#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

TubeBell::TubeBell()
	: FM() {
	for ( unsigned int i = 0; i < 3; i++ )
		waves_[i] = new FileLoop( (Audio::GetRawWavePath() + "sinewave.raw").Begin(), true );

	waves_[3] = new FileLoop( (Audio::GetRawWavePath() + "fwavblnk.raw").Begin(), true );
	this->SetRatio(0, 1.0   * 0.995);
	this->SetRatio(1, 1.414 * 0.995);
	this->SetRatio(2, 1.0   * 1.005);
	this->SetRatio(3, 1.414 * 1.000);
	gains_[0] = fm_gains_[94];
	gains_[1] = fm_gains_[76];
	gains_[2] = fm_gains_[99];
	gains_[3] = fm_gains_[71];
	adsr_[0]->SetAllTimes( 0.005, 4.0, 0.0, 0.04);
	adsr_[1]->SetAllTimes( 0.005, 4.0, 0.0, 0.04);
	adsr_[2]->SetAllTimes( 0.001, 2.0, 0.0, 0.04);
	adsr_[3]->SetAllTimes( 0.004, 4.0, 0.0, 0.04);
	twozero_.SetGain( 0.5 );
	vibrato_.SetFrequency( 2.0 );
}

TubeBell::~TubeBell() {
}

void TubeBell::NoteOn( double frequency, double amplitude ) {
	gains_[0] = amplitude * fm_gains_[94];
	gains_[1] = amplitude * fm_gains_[76];
	gains_[2] = amplitude * fm_gains_[99];
	gains_[3] = amplitude * fm_gains_[71];
	this->SetFrequency( frequency );
	this->KeyOn();
}

NAMESPACE_AUDIO_END
