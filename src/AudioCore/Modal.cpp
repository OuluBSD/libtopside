#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Modal::Modal( unsigned int modes )
	: mode_count_(modes) {
	if ( mode_count_ == 0 ) {
		LOG("Modal: 'modes' argument to constructor is zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	ratios_.SetCount( mode_count_ );
	radii_.SetCount( mode_count_ );
	filters_ = (BiQuad**) calloc( mode_count_, sizeof(BiQuad*) );

	for (unsigned int i = 0; i < mode_count_; i++ ) {
		filters_[i] = new BiQuad;
		filters_[i]->SetEqualGainZeroes();
	}

	vibrato_.SetFrequency( 6.0 );
	vibrato_gain_ = 0.0;
	directGain_ = 0.0;
	masterGain_ = 1.0;
	base_frequency_ = 440.0;
	this->Clear();
	stickHardness_ =  0.5;
	strike_position_ = 0.561;
}

Modal::~Modal() {
	for ( unsigned int i = 0; i < mode_count_; i++ )
		delete filters_[i];

	free( filters_ );
}

void Modal::Clear() {
	onepole_.Clear();

	for ( unsigned int i = 0; i < mode_count_; i++ )
		filters_[i]->Clear();
}

void Modal::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("Modal::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	base_frequency_ = frequency;

	for ( unsigned int i = 0; i < mode_count_; i++ )
		this->SetRatioAndRadius( i, ratios_[i], radii_[i] );
}

void Modal::SetRatioAndRadius( unsigned int modeIndex, double ratio, double radius ) {
	if ( modeIndex >= mode_count_ ) {
		LOG("Modal::SetRatioAndRadius: modeIndex parameter is greater than number of modes!");
		HandleError( AudioError::WARNING );
		return;
	}

	double nyquist = Audio::GetSampleRate() / 2.0;
	double temp;

	if ( ratio * base_frequency_ < nyquist )
		ratios_[modeIndex] = ratio;
	else {
		temp = ratio;

		while (temp * base_frequency_ > nyquist) temp *= 0.5;

		ratios_[modeIndex] = temp;
		#if defined(flagDEBUG)
		LOG("Modal::SetRatioAndRadius: aliasing would occur here ... correcting.");
		HandleError( AudioError::DEBUG_PRINT );
		#endif
	}

	radii_[modeIndex] = radius;

	if (ratio < 0)
		temp = -ratio;
	else
		temp = ratio * base_frequency_;

	filters_[modeIndex]->SetResonance(temp, radius);
}

void Modal::SetModeGain( unsigned int modeIndex, double gain ) {
	if ( modeIndex >= mode_count_ ) {
		LOG("Modal::SetModeGain: modeIndex parameter is greater than number of modes!");
		HandleError( AudioError::WARNING );
		return;
	}

	filters_[modeIndex]->SetGain( gain );
}

void Modal::Strike( double amplitude ) {
	if ( amplitude < 0.0 || amplitude > 1.0 ) {
		LOG("Modal::strike: amplitude is out of range!");
		HandleError( AudioError::WARNING );
	}

	envelope_.SetRate( 1.0 );
	envelope_.SetTarget( amplitude );
	onepole_.SetPole( 1.0 - amplitude );
	envelope_.Tick();
	wave_->Reset();
	double temp;

	for ( unsigned int i = 0; i < mode_count_; i++ ) {
		if (ratios_[i] < 0)
			temp = -ratios_[i];
		else
			temp = ratios_[i] * base_frequency_;

		filters_[i]->SetResonance(temp, radii_[i]);
	}
}

void Modal::NoteOn( double frequency, double amplitude ) {
	this->Strike( amplitude );
	this->SetFrequency( frequency );
}

void Modal::NoteOff( double amplitude ) {
	this->Damp( 1.0 - (amplitude * 0.03) );
}

void Modal::Damp( double amplitude ) {
	double temp;

	for ( unsigned int i = 0; i < mode_count_; i++ ) {
		if ( ratios_[i] < 0 )
			temp = -ratios_[i];
		else
			temp = ratios_[i] * base_frequency_;

		filters_[i]->SetResonance( temp, radii_[i]*amplitude );
	}
}

NAMESPACE_AUDIO_END
