#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

FMVoices::FMVoices()
	: FM() {
	for ( unsigned int i = 0; i < 3; i++ )
		waves_[i] = new FileLoop( (Audio::GetRawWavePath() + "sinewave.raw").Begin(), true );

	waves_[3] = new FileLoop( (Audio::GetRawWavePath() + "fwavblnk.raw").Begin(), true );
	this->SetRatio(0, 2.00);
	this->SetRatio(1, 4.00);
	this->SetRatio(2, 12.0);
	this->SetRatio(3, 1.00);
	gains_[3] = fm_gains_[80];
	adsr_[0]->SetAllTimes( 0.05, 0.05, fm_sus_levels_[15], 0.05);
	adsr_[1]->SetAllTimes( 0.05, 0.05, fm_sus_levels_[15], 0.05);
	adsr_[2]->SetAllTimes( 0.05, 0.05, fm_sus_levels_[15], 0.05);
	adsr_[3]->SetAllTimes( 0.01, 0.01, fm_sus_levels_[15], 0.5);
	twozero_.SetGain( 0.0 );
	mod_depth_ = (double) 0.005;
	currentVowel_ = 0;
	tilt_[0] = 1.0;
	tilt_[1] = 0.5;
	tilt_[2] = 0.2;
	mods_[0] = 1.0;
	mods_[1] = 1.1;
	mods_[2] = 1.1;
	base_frequency_ = 110.0;
	this->SetFrequency( 110.0 );
}

FMVoices::~FMVoices() {
}

void FMVoices::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("FMVoices::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double temp, temp2 = 0.0;
	int tempi = 0;
	unsigned int i = 0;

	if (currentVowel_ < 32)	{
		i = currentVowel_;
		temp2 = 0.9;
	}
	else if (currentVowel_ < 64)	{
		i = currentVowel_ - 32;
		temp2 = 1.0;
	}
	else if (currentVowel_ < 96)	{
		i = currentVowel_ - 64;
		temp2 = 1.1;
	}
	else if (currentVowel_ <= 128)	{
		i = currentVowel_ - 96;
		temp2 = 1.2;
	}

	base_frequency_ = frequency;
	temp = (temp2 * Phonemes::GetFormantFrequency(i, 0) / base_frequency_) + 0.5;
	tempi = (int) temp;
	this->SetRatio( 0, (double) tempi );
	temp = (temp2 * Phonemes::GetFormantFrequency(i, 1) / base_frequency_) + 0.5;
	tempi = (int) temp;
	this->SetRatio( 1, (double) tempi );
	temp = (temp2 * Phonemes::GetFormantFrequency(i, 2) / base_frequency_) + 0.5;
	tempi = (int) temp;
	this->SetRatio( 2, (double) tempi );
	gains_[0] = 1.0;
	gains_[1] = 1.0;
	gains_[2] = 1.0;
}

void FMVoices::NoteOn( double frequency, double amplitude ) {
	this->SetFrequency( frequency );
	tilt_[0] = amplitude;
	tilt_[1] = amplitude * amplitude;
	tilt_[2] = tilt_[1] * amplitude;
	this->KeyOn();
}

void FMVoices::ControlChange( int number, double value ) {
	#if defined(flagDEBUG)

	if ( Audio::inRange( value, 0.0, 128.0 ) == false ) {
		LOG("FMVoices::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double normalizedValue = value * ONE_OVER_128;

	if (number == __SK_Breath_)
		gains_[3] = fm_gains_[(int) ( normalizedValue * 99.9 )];
	else if (number == __SK_FootControl_)	{
		currentVowel_ = (int) (normalizedValue * 128.0);
		this->SetFrequency(base_frequency_);
	}
	else if (number == __SK_ModFrequency_)
		this->SetModulationSpeed( normalizedValue * 12.0);
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
