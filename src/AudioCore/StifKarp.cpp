#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

StifKarp::StifKarp( float lowest_freq ) {
	if ( lowest_freq <= 0.0f ) {
		LOG("StifKarp::StifKarp: argument is less than or equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	int delay_counts = (int) ( Audio::GetSampleRate() / lowest_freq );
	delay_line_.SetMaximumDelay( delay_counts + 1 );
	comb_delay_.SetMaximumDelay( delay_counts + 1 );
	pluck_amplitude_ = 0.3f;
	pickup_position_ = 0.4f;
	stretching_ = 0.9999f;
	base_loop_gain_ = 0.995f;
	loop_gain_ = 0.999f;
	this->Clear();
	this->SetFrequency( 220.0f );
}

StifKarp::~StifKarp() {
}

void StifKarp::Clear() {
	delay_line_.Clear();
	comb_delay_.Clear();
	filter_.Clear();
}

void StifKarp::SetFrequency( float frequency ) {
	#if defined(flagDEBUG)

	if ( frequency <= 0.0f ) {
		LOG("StifKarp::SetFrequency: parameter is less than or equal to zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	last_frequency_ = frequency;
	last_length_ = Audio::GetSampleRate() / last_frequency_;
	float delay = last_length_ - 0.5f;
	delay_line_.SetDelay( delay );
	loop_gain_ = base_loop_gain_ + (frequency * 0.000005f);

	if (loop_gain_ >= 1.0f) loop_gain_ = 0.99999f;

	SetStretch(stretching_);
	comb_delay_.SetDelay( 0.5f * pickup_position_ * last_length_ );
}

void StifKarp::SetStretch( float stretch ) {
	stretching_ = stretch;
	float coefficient;
	float freq = last_frequency_ * 2.0f;
	float dFreq = ( (0.5f * Audio::GetSampleRate()) - freq ) * 0.25f;
	float temp = 0.5f + (stretch * 0.5f);

	if ( temp > 0.9999f ) temp = 0.9999f;

	for ( int i = 0; i < 4; i++ )	{
		coefficient = temp * temp;
		biquad_[i].SetA2( coefficient );
		biquad_[i].SetB0( coefficient );
		biquad_[i].SetB2( 1.0f );
		coefficient = -2.0f * temp * cos(TWO_PI * freq / Audio::GetSampleRate());
		biquad_[i].SetA1( coefficient );
		biquad_[i].SetB1( coefficient );
		freq += dFreq;
	}
}

void StifKarp::SetPickupPosition( float position ) {
	if ( position < 0.0f || position > 1.0f ) {
		LOG("StifKarp::SetPickupPosition: parameter is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	pickup_position_ = position;
	comb_delay_.SetDelay( 0.5f * pickup_position_ * last_length_ );
}

void StifKarp::SetBaseLoopGain( float aGain ) {
	base_loop_gain_ = aGain;
	loop_gain_ = base_loop_gain_ + (last_frequency_ * 0.000005f);

	if ( loop_gain_ > 0.99999f ) loop_gain_ = (float) 0.99999f;
}

void StifKarp::Pluck( float amplitude ) {
	if ( amplitude < 0.0f || amplitude > 1.0f ) {
		LOG("StifKarp::pluck: amplitude is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	pluck_amplitude_ = amplitude;

	for ( int i = 0; i < size_; i++ )
		delay_line_.Tick( (delay_line_.GetLastOut() * 0.6f) + 0.4f * noise_.Tick() * pluck_amplitude_ );
}

void StifKarp::NoteOn( float frequency, float amplitude ) {
	this->SetFrequency( frequency );
	this->Pluck( amplitude );
}

void StifKarp::NoteOff( float amplitude ) {
	if ( amplitude < 0.0f || amplitude > 1.0f ) {
		LOG("StifKarp::noteOff: amplitude is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	loop_gain_ =  (1.0f - amplitude) * 0.5f;
}

void StifKarp::ControlChange( int number, float value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0f, 128.0f ) == false ) {
		LOG("Clarinet::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	float normalizedValue = value * ONE_OVER_128;

	if (number == __SK_PickPosition_)
		this->SetPickupPosition( normalizedValue );
	else if (number == __SK_StringDamping_)
		this->SetBaseLoopGain( 0.97f + (normalizedValue * 0.03f) );
	else if (number == __SK_StringDetune_)
		this->SetStretch( 0.9f + (0.1f * (1.0f - normalizedValue)) );

	#if defined(flagDEBUG)
	else {
		LOG("StifKarp::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END
