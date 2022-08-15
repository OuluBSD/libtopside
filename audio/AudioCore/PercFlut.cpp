#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

PercFlut::PercFlut()
	: FM() {
	for ( unsigned int i = 0; i < 3; i++ )
		waves_[i] = new FileLoop( (Audio::GetRawWavePath() + "sinewave.raw").Begin(), true );

	waves_[3] = new FileLoop( (Audio::GetRawWavePath() + "fwavblnk.raw").Begin(), true );
	this->SetRatio(0, 1.50 * 1.000);
	this->SetRatio(1, 3.00 * 0.995);
	this->SetRatio(2, 2.99 * 1.005);
	this->SetRatio(3, 6.00 * 0.997);
	gains_[0] = fm_gains_[99];
	gains_[1] = fm_gains_[71];
	gains_[2] = fm_gains_[93];
	gains_[3] = fm_gains_[85];
	adsr_[0]->SetAllTimes( 0.05, 0.05, fm_sus_levels_[14], 0.05);
	adsr_[1]->SetAllTimes( 0.02, 0.50, fm_sus_levels_[13], 0.5);
	adsr_[2]->SetAllTimes( 0.02, 0.30, fm_sus_levels_[11], 0.05);
	adsr_[3]->SetAllTimes( 0.02, 0.05, fm_sus_levels_[13], 0.01);
	twozero_.SetGain( 0.0 );
	mod_depth_ = 0.005;
}

PercFlut::~PercFlut() {
}

void PercFlut::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("PercFlut::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	base_frequency_ = frequency;
}

void PercFlut::NoteOn( double frequency, double amplitude ) {
	gains_[0] = amplitude * fm_gains_[99] * 0.5;
	gains_[1] = amplitude * fm_gains_[71] * 0.5;
	gains_[2] = amplitude * fm_gains_[93] * 0.5;
	gains_[3] = amplitude * fm_gains_[85] * 0.5;
	this->SetFrequency( frequency );
	this->KeyOn();
}

NAMESPACE_AUDIO_END
