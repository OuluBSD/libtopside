#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

StifKarp::StifKarp( double lowest_freq ) {
	if ( lowest_freq <= 0.0 ) {
		LOG("StifKarp::StifKarp: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	unsigned long delay_counts = (unsigned long) ( Audio::GetSampleRate() / lowest_freq );
	delay_line_.SetMaximumDelay( delay_counts + 1 );
	comb_delay_.SetMaximumDelay( delay_counts + 1 );
	pluck_amplitude_ = 0.3;
	pickup_position_ = 0.4;
	stretching_ = 0.9999;
	base_loop_gain_ = 0.995;
	loop_gain_ = 0.999;
	this->Clear();
	this->SetFrequency( 220.0 );
}

StifKarp::~StifKarp() {
}

void StifKarp::Clear() {
	delay_line_.Clear();
	comb_delay_.Clear();
	filter_.Clear();
}

void StifKarp::SetFrequency( double frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0 ) {
		LOG("StifKarp::SetFrequency: parameter is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	last_frequency_ = frequency;
	last_length_ = Audio::GetSampleRate() / last_frequency_;
	double delay = last_length_ - 0.5;
	delay_line_.SetDelay( delay );
	loop_gain_ = base_loop_gain_ + (frequency * 0.000005);

	if (loop_gain_ >= 1.0) loop_gain_ = 0.99999;

	SetStretch(stretching_);
	comb_delay_.SetDelay( 0.5 * pickup_position_ * last_length_ );
}

void StifKarp::SetStretch( double stretch ) {
	stretching_ = stretch;
	double coefficient;
	double freq = last_frequency_ * 2.0;
	double dFreq = ( (0.5 * Audio::GetSampleRate()) - freq ) * 0.25;
	double temp = 0.5 + (stretch * 0.5);

	if ( temp > 0.9999 ) temp = 0.9999;

	for ( int i = 0; i < 4; i++ )	{
		coefficient = temp * temp;
		biquad_[i].SetA2( coefficient );
		biquad_[i].SetB0( coefficient );
		biquad_[i].SetB2( 1.0 );
		coefficient = -2.0 * temp * cos(TWO_PI * freq / Audio::GetSampleRate());
		biquad_[i].SetA1( coefficient );
		biquad_[i].SetB1( coefficient );
		freq += dFreq;
	}
}

void StifKarp::SetPickupPosition( double position ) {
	if ( position < 0.0 || position > 1.0 ) {
		LOG("StifKarp::SetPickupPosition: parameter is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	pickup_position_ = position;
	comb_delay_.SetDelay( 0.5 * pickup_position_ * last_length_ );
}

void StifKarp::SetBaseLoopGain( double aGain ) {
	base_loop_gain_ = aGain;
	loop_gain_ = base_loop_gain_ + (last_frequency_ * 0.000005);

	if ( loop_gain_ > 0.99999 ) loop_gain_ = (double) 0.99999;
}

void StifKarp::Pluck( double amplitude ) {
	if ( amplitude < 0.0 || amplitude > 1.0 ) {
		LOG("StifKarp::pluck: amplitude is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	pluck_amplitude_ = amplitude;

	for ( unsigned long i = 0; i < size_; i++ )
		delay_line_.Tick( (delay_line_.GetLastOut() * 0.6) + 0.4 * noise_.Tick() * pluck_amplitude_ );
}

void StifKarp::NoteOn( double frequency, double amplitude ) {
	this->SetFrequency( frequency );
	this->Pluck( amplitude );
}

void StifKarp::NoteOff( double amplitude ) {
	if ( amplitude < 0.0 || amplitude > 1.0 ) {
		LOG("StifKarp::noteOff: amplitude is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	loop_gain_ =  (1.0 - amplitude) * 0.5;
}

void StifKarp::ControlChange( int number, double value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0, 128.0 ) == false ) {
		LOG("Clarinet::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double normalizedValue = value * ONE_OVER_128;

	if (number == __SK_PickPosition_)
		this->SetPickupPosition( normalizedValue );
	else if (number == __SK_StringDamping_)
		this->SetBaseLoopGain( 0.97 + (normalizedValue * 0.03) );
	else if (number == __SK_StringDetune_)
		this->SetStretch( 0.9 + (0.1 * (1.0 - normalizedValue)) );

	#if defined(flagDEBUG)
	else {
		LOG("StifKarp::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
