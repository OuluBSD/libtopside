#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

FM::FM( int operators )
	: nOperators_(operators) {
	if ( nOperators_ == 0 ) {
		LOG("FM::FM: Number of operators must be greater than zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	twozero_.SetB2( -1.0f );
	twozero_.SetGain( 0.0f );
	vibrato_.SetFrequency( 6.0 );
	int j;
	adsr_.SetCount( nOperators_ );
	waves_.SetCount( nOperators_ );

	for (j = 0; j < nOperators_; j++ ) {
		ratios_.Add( 1.0f );
		gains_.Add( 1.0f );
		adsr_[j] = new ADSR();
	}

	mod_depth_ = 0.0f;
	control1_ = 1.0f;
	control2_ = 1.0f;
	base_frequency_ = 440.0f;
	int i;
	float temp = 1.0f;

	for (i = 99; i >= 0; i--) {
		fm_gains_[i] = temp;
		temp *= 0.933033f;
	}

	temp = 1.0f;

	for (i = 15; i >= 0; i--) {
		fm_sus_levels_[i] = temp;
		temp *= 0.707101f;
	}

	temp = 8.498186f;

	for (i = 0; i < 32; i++) {
		fm_attr_times_[i] = temp;
		temp *= 0.707101f;
	}
}

FM::~FM() {
	for (int i = 0; i < nOperators_; i++ ) {
		delete waves_[i];
		delete adsr_[i];
	}
}

void FM::LoadWaves( const char** filenames ) {
	for (int i = 0; i < nOperators_; i++ )
		waves_[i] = new FileLoop( filenames[i], true );
}

void FM::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("FM::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	base_frequency_ = frequency;

	for ( int i = 0; i < nOperators_; i++ )
		waves_[i]->SetFrequency( base_frequency_ * ratios_[i] );
}

void FM::SetRatio( int waveIndex, float ratio ) {
	if ( waveIndex >= nOperators_ ) {
		LOG("FM:setRatio: waveIndex parameter is greater than the number of operators!");
		HandleError( AudioError::WARNING );
		return;
	}

	ratios_[waveIndex] = ratio;

	if (ratio > 0.0f)
		waves_[waveIndex]->SetFrequency( base_frequency_ * ratio );
	else
		waves_[waveIndex]->SetFrequency( ratio );
}

void FM::SetGain( int waveIndex, float gain ) {
	if ( waveIndex >= nOperators_ ) {
		LOG("FM::SetGain: waveIndex parameter is greater than the number of operators!");
		HandleError( AudioError::WARNING );
		return;
	}

	gains_[waveIndex] = gain;
}

void FM::KeyOn() {
	for ( int i = 0; i < nOperators_; i++ )
		adsr_[i]->KeyOn();
}

void FM::KeyOff() {
	for ( int i = 0; i < nOperators_; i++ )
		adsr_[i]->KeyOff();
}

void FM::NoteOff( float amplitude ) {
	this->KeyOff();
}

void FM::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0f ) == false ) {
		LOG("FM::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if (number == __SK_Breath_)
		this->SetControl1( normalizedValue );
	else if (number == __SK_FootControl_)
		this->SetControl2( normalizedValue );
	else if (number == __SK_ModFrequency_)
		this->SetModulationSpeed( normalizedValue * 12.0f);
	else if (number == __SK_ModWheel_)
		this->SetModulationDepth( normalizedValue );
	else if (number == __SK_AfterTouch_Cont_)	{
		adsr_[1]->SetTarget( normalizedValue );
		adsr_[3]->SetTarget( normalizedValue );
	}

	#if defined(flagDEBUG)
	else {
		LOG("FM::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
