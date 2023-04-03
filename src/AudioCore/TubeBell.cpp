#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

TubeBell::TubeBell()
	: FM() {
	for ( int i = 0; i < 3; i++ )
		waves_[i] = new FileLoop( (Audio::GetRawWavePath() + "sinewave.raw").Begin(), true );

	waves_[3] = new FileLoop( (Audio::GetRawWavePath() + "fwavblnk.raw").Begin(), true );
	this->SetRatio(0, 1.0f   * 0.995f);
	this->SetRatio(1, 1.414 * 0.995f);
	this->SetRatio(2, 1.0f   * 1.005f);
	this->SetRatio(3, 1.414f * 1.000f);
	gains_[0] = fm_gains_[94];
	gains_[1] = fm_gains_[76];
	gains_[2] = fm_gains_[99];
	gains_[3] = fm_gains_[71];
	adsr_[0]->SetAllTimes( 0.005f, 4.0f, 0.0f, 0.04f);
	adsr_[1]->SetAllTimes( 0.005f, 4.0f, 0.0f, 0.04f);
	adsr_[2]->SetAllTimes( 0.001f, 2.0f, 0.0f, 0.04f);
	adsr_[3]->SetAllTimes( 0.004f, 4.0f, 0.0f, 0.04f);
	twozero_.SetGain( 0.5f );
	vibrato_.SetFrequency( 2.0f );
}

TubeBell::~TubeBell() {
}

void TubeBell::NoteOn( float frequency, float amplitude ) {
	gains_[0] = amplitude * fm_gains_[94];
	gains_[1] = amplitude * fm_gains_[76];
	gains_[2] = amplitude * fm_gains_[99];
	gains_[3] = amplitude * fm_gains_[71];
	this->SetFrequency( frequency );
	this->KeyOn();
}

NAMESPACE_AUDIO_END
