#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Twang::Twang( float lowest_freq ) {
	if ( lowest_freq <= 0.0f ) {
		LOG("Twang::Twang: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	this->SetLowestFrequency( lowest_freq );
	Vector<float> coefficients;
	coefficients.SetCount( 2, 0.5f );
	loop_filter_.SetCoefficients( coefficients );
	loop_gain_ = 0.995;
	pluck_position_ = 0.4;
	this->SetFrequency( 220.0f );
}

void Twang::Clear() {
	delay_line_.Clear();
	comb_delay_.Clear();
	loop_filter_.Clear();
	last_output_ = 0.0f;
}

void Twang::SetLowestFrequency( float frequency ) {
	int delay_counts = (int) ( Audio::GetSampleRate() / frequency );
	delay_line_.SetMaximumDelay( delay_counts + 1 );
	comb_delay_.SetMaximumDelay( delay_counts + 1 );
}

void Twang::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("Twang::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	frequency_ = frequency;
	float delay = ( Audio::GetSampleRate() / frequency ) - loop_filter_.GetPhaseDelay( frequency );
	delay_line_.SetDelay( delay );
	this->SetLoopGain( loop_gain_ );
	comb_delay_.SetDelay( 0.5f * pluck_position_ * delay );
}

void Twang::SetLoopGain( float loopGain ) {
	if ( loopGain < 0.0f || loopGain >= 1.0f ) {
		LOG("Twang::SetLoopGain: parameter is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	loop_gain_ = loopGain;
	float gain = loop_gain_ + (frequency_ * 0.000005);

	if ( gain >= 1.0f ) gain = 0.99999;

	loop_filter_.SetGain( gain );
}

void Twang::SetPluckPosition( float position ) {
	if ( position < 0.0f || position > 1.0f ) {
		LOG("Twang::SetPluckPosition: argument (" << position << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	pluck_position_ = position;
}

NAMESPACE_AUDIO_END
