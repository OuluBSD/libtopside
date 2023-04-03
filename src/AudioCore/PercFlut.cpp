#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

PercFlut::PercFlut()
	: FM() {
	for ( int i = 0; i < 3; i++ )
		waves_[i] = new FileLoop( (Audio::GetRawWavePath() + "sinewave.raw").Begin(), true );

	waves_[3] = new FileLoop( (Audio::GetRawWavePath() + "fwavblnk.raw").Begin(), true );
	this->SetRatio(0, 1.50f * 1.000f);
	this->SetRatio(1, 3.00f * 0.995f);
	this->SetRatio(2, 2.99f * 1.005f);
	this->SetRatio(3, 6.00f * 0.997f);
	gains_[0] = fm_gains_[99];
	gains_[1] = fm_gains_[71];
	gains_[2] = fm_gains_[93];
	gains_[3] = fm_gains_[85];
	adsr_[0]->SetAllTimes( 0.05f, 0.05f, fm_sus_levels_[14], 0.05f);
	adsr_[1]->SetAllTimes( 0.02f, 0.50f, fm_sus_levels_[13], 0.50f);
	adsr_[2]->SetAllTimes( 0.02f, 0.30f, fm_sus_levels_[11], 0.05f);
	adsr_[3]->SetAllTimes( 0.02f, 0.05f, fm_sus_levels_[13], 0.01f);
	twozero_.SetGain( 0.0f );
	mod_depth_ = 0.005f;
}

PercFlut::~PercFlut() {
}

void PercFlut::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("PercFlut::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	base_frequency_ = frequency;
}

void PercFlut::NoteOn( float frequency, float amplitude ) {
	gains_[0] = amplitude * fm_gains_[99] * 0.5f;
	gains_[1] = amplitude * fm_gains_[71] * 0.5f;
	gains_[2] = amplitude * fm_gains_[93] * 0.5f;
	gains_[3] = amplitude * fm_gains_[85] * 0.5f;
	this->SetFrequency( frequency );
	this->KeyOn();
}

NAMESPACE_AUDIO_END
