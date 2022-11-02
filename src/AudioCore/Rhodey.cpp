#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Rhodey::Rhodey()
	: FM() {
	for ( unsigned int i = 0; i < 3; i++ )
		waves_[i] = new FileLoop( (Audio::GetRawWavePath() + "sinewave.raw").Begin(), true );

	waves_[3] = new FileLoop( (Audio::GetRawWavePath() + "fwavblnk.raw").Begin(), true );
	this->SetRatio(0, 1.0);
	this->SetRatio(1, 0.5);
	this->SetRatio(2, 1.0);
	this->SetRatio(3, 15.0);
	gains_[0] = fm_gains_[99];
	gains_[1] = fm_gains_[90];
	gains_[2] = fm_gains_[99];
	gains_[3] = fm_gains_[67];
	adsr_[0]->SetAllTimes( 0.001, 1.50, 0.0, 0.04);
	adsr_[1]->SetAllTimes( 0.001, 1.50, 0.0, 0.04);
	adsr_[2]->SetAllTimes( 0.001, 1.00, 0.0, 0.04);
	adsr_[3]->SetAllTimes( 0.001, 0.25, 0.0, 0.04);
	twozero_.SetGain( 1.0 );
}

Rhodey::~Rhodey() {
}

void Rhodey::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("Rhodey::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	base_frequency_ = frequency * 2.0;

	for (unsigned int i = 0; i < nOperators_; i++ )
		waves_[i]->SetFrequency( base_frequency_ * ratios_[i] );
}

void Rhodey::NoteOn( double frequency, double amplitude ) {
	gains_[0] = amplitude * fm_gains_[99];
	gains_[1] = amplitude * fm_gains_[90];
	gains_[2] = amplitude * fm_gains_[99];
	gains_[3] = amplitude * fm_gains_[67];
	this->SetFrequency( frequency );
	this->KeyOn();
}

NAMESPACE_AUDIO_END
