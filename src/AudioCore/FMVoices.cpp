#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

FMVoices::FMVoices()
	: FM() {
	for ( int i = 0; i < 3; i++ )
		waves_[i] = new FileLoop( (Audio::GetRawWavePath() + "sinewave.raw").Begin(), true );

	waves_[3] = new FileLoop( (Audio::GetRawWavePath() + "fwavblnk.raw").Begin(), true );
	this->SetRatio(0, 2.00f);
	this->SetRatio(1, 4.00f);
	this->SetRatio(2, 12.0f);
	this->SetRatio(3, 1.00f);
	gains_[3] = fm_gains_[80];
	adsr_[0]->SetAllTimes( 0.05f, 0.05f, fm_sus_levels_[15], 0.05f);
	adsr_[1]->SetAllTimes( 0.05f, 0.05f, fm_sus_levels_[15], 0.05f);
	adsr_[2]->SetAllTimes( 0.05f, 0.05f, fm_sus_levels_[15], 0.05f);
	adsr_[3]->SetAllTimes( 0.01f, 0.01f, fm_sus_levels_[15], 0.50f);
	twozero_.SetGain( 0.0f );
	mod_depth_ = (float) 0.005f;
	currentVowel_ = 0;
	tilt_[0] = 1.0f;
	tilt_[1] = 0.5f;
	tilt_[2] = 0.2f;
	mods_[0] = 1.0f;
	mods_[1] = 1.1f;
	mods_[2] = 1.1f;
	base_frequency_ = 110.0f;
	this->SetFrequency( 110.0f );
}

FMVoices::~FMVoices() {
}

void FMVoices::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("FMVoices::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float temp, temp2 = 0.0f;
	int tempi = 0;
	int i = 0;

	if (currentVowel_ < 32)	{
		i = currentVowel_;
		temp2 = 0.9f;
	}
	else if (currentVowel_ < 64)	{
		i = currentVowel_ - 32;
		temp2 = 1.0f;
	}
	else if (currentVowel_ < 96)	{
		i = currentVowel_ - 64;
		temp2 = 1.1f;
	}
	else if (currentVowel_ <= 128)	{
		i = currentVowel_ - 96;
		temp2 = 1.2f;
	}

	base_frequency_ = frequency;
	temp = (temp2 * Phonemes::GetFormantFrequency(i, 0) / base_frequency_) + 0.5f;
	tempi = (int) temp;
	this->SetRatio( 0, (float) tempi );
	temp = (temp2 * Phonemes::GetFormantFrequency(i, 1) / base_frequency_) + 0.5f;
	tempi = (int) temp;
	this->SetRatio( 1, (float) tempi );
	temp = (temp2 * Phonemes::GetFormantFrequency(i, 2) / base_frequency_) + 0.5f;
	tempi = (int) temp;
	this->SetRatio( 2, (float) tempi );
	gains_[0] = 1.0f;
	gains_[1] = 1.0f;
	gains_[2] = 1.0f;
}

void FMVoices::NoteOn( float frequency, float amplitude ) {
	this->SetFrequency( frequency );
	tilt_[0] = amplitude;
	tilt_[1] = amplitude * amplitude;
	tilt_[2] = tilt_[1] * amplitude;
	this->KeyOn();
}

void FMVoices::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0f ) == false ) {
		LOG("FMVoices::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if (number == __SK_Breath_)
		gains_[3] = fm_gains_[(int) ( normalizedValue * 99.9f )];
	else if (number == __SK_FootControl_)	{
		currentVowel_ = (int) (normalizedValue * 128.0f);
		this->SetFrequency(base_frequency_);
	}
	else if (number == __SK_ModFrequency_)
		this->SetModulationSpeed( normalizedValue * 12.0f);
	else if (number == __SK_ModWheel_)
		this->SetModulationDepth( normalizedValue );
	else if (number == __SK_AfterTouch_Cont_)	{
		tilt_[0] = normalizedValue;
		tilt_[1] = normalizedValue * normalizedValue;
		tilt_[2] = tilt_[1] * normalizedValue;
	}

	#if defined(flagDEBUG)
	else {
		LOG("FMVoices::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
