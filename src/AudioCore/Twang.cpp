#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Twang::Twang( double lowest_freq ) {
	if ( lowest_freq <= 0.0 ) {
		LOG("Twang::Twang: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	this->SetLowestFrequency( lowest_freq );
	Vector<double> coefficients;
	coefficients.SetCount( 2, 0.5 );
	loop_filter_.SetCoefficients( coefficients );
	loop_gain_ = 0.995;
	pluck_position_ = 0.4;
	this->SetFrequency( 220.0 );
}

void Twang::Clear() {
	delay_line_.Clear();
	comb_delay_.Clear();
	loop_filter_.Clear();
	last_output_ = 0.0;
}

void Twang::SetLowestFrequency( double frequency ) {
	unsigned long delay_counts = (unsigned long) ( Audio::GetSampleRate() / frequency );
	delay_line_.SetMaximumDelay( delay_counts + 1 );
	comb_delay_.SetMaximumDelay( delay_counts + 1 );
}

void Twang::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("Twang::SetFrequency: argument is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	frequency_ = frequency;
	double delay = ( Audio::GetSampleRate() / frequency ) - loop_filter_.GetPhaseDelay( frequency );
	delay_line_.SetDelay( delay );
	this->SetLoopGain( loop_gain_ );
	comb_delay_.SetDelay( 0.5 * pluck_position_ * delay );
}

void Twang::SetLoopGain( double loopGain ) {
	if ( loopGain < 0.0 || loopGain >= 1.0 ) {
		LOG("Twang::SetLoopGain: parameter is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	loop_gain_ = loopGain;
	double gain = loop_gain_ + (frequency_ * 0.000005);

	if ( gain >= 1.0 ) gain = 0.99999;

	loop_filter_.SetGain( gain );
}

void Twang::SetPluckPosition( double position ) {
	if ( position < 0.0 || position > 1.0 ) {
		LOG("Twang::SetPluckPosition: argument (" << position << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	pluck_position_ = position;
}

NAMESPACE_AUDIO_END
