#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Moog::Moog() {
	attacks_.Add( new FileWaveIn( (Audio::GetRawWavePath() + "mandpluk.raw").Begin(), true ) );
	loops_.push_back ( new FileLoop( (Audio::GetRawWavePath() + "impuls20.raw").Begin(), true ) );
	loops_.push_back ( new FileLoop( (Audio::GetRawWavePath() + "sinewave.raw").Begin(), true ) );
	loops_[1]->SetFrequency( 6.122 );
	filters_[0].SetTargets( 0.0f, 0.7 );
	filters_[1].SetTargets( 0.0f, 0.7 );
	adsr_.SetAllTimes( 0.001, 1.5, 0.6, 0.250 );
	filter_q_ = 0.85;
	filter_rate_ = 0.0001;
	mod_depth_ = 0.0f;
}

Moog::~Moog() {
}

void Moog::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("Moog::SetFrequency: parameter is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	base_frequency_ = frequency;
	float rate = attacks_[0]->GetSize() * 0.01 * base_frequency_ / Audio::GetSampleRate();
	attacks_[0]->SetRate( rate );
	loops_[0]->SetFrequency( base_frequency_ );
}

void Moog::NoteOn( float frequency, float amplitude ) {
	float temp;
	this->SetFrequency( frequency );
	this->KeyOn();
	attackGain_ = amplitude * 0.5f;
	loop_gain_ = amplitude;
	temp = filter_q_ + 0.05f;
	filters_[0].SetStates( 2000.0f, temp );
	filters_[1].SetStates( 2000.0f, temp );
	temp = filter_q_ + 0.099f;
	filters_[0].SetTargets( frequency, temp );
	filters_[1].SetTargets( frequency, temp );
	filters_[0].SetSweepRate( filter_rate_ * 22050.0f / Audio::GetSampleRate() );
	filters_[1].SetSweepRate( filter_rate_ * 22050.0f / Audio::GetSampleRate() );
}

void Moog::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0 ) == false ) {
		LOG("Moog::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if (number == __SK_FilterQ_)
		filter_q_ = 0.80 + ( 0.1 * normalizedValue );
	else if (number == __SK_FilterSweepRate_)
		filter_rate_ = normalizedValue * 0.0002;
	else if (number == __SK_ModFrequency_)
		this->SetModulationSpeed( normalizedValue * 12.0 );
	else if (number == __SK_ModWheel_)
		this->SetModulationDepth( normalizedValue );
	else if (number == __SK_AfterTouch_Cont_)
		adsr_.SetTarget( normalizedValue );

	#if defined(flagDEBUG)
	else {
		LOG("Moog::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
