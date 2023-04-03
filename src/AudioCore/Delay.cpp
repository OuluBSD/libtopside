#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Delay::Delay( int delay, int max_delay ) {
	if ( delay > max_delay ) {
		LOG("Delay::Delay: max_delay must be > than delay argument!\n");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( ( max_delay + 1 ) > inputs_.GetCount() )
		inputs_.SetCount( max_delay + 1, 1, 0.0f );

	in_point_ = 0;
	this->SetDelay( delay );
}

Delay::~Delay() {
}

void Delay::SetMaximumDelay( int delay ) {
	if ( delay < inputs_.GetCount() ) return;

	inputs_.SetCount( delay + 1 );
}

void Delay::SetDelay( int delay ) {
	if ( delay > inputs_.GetCount() - 1 ) {
		LOG("Delay::SetDelay: argument (" << delay << ") greater than maximum!\n");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( in_point_ >= delay ) out_point_ = in_point_ - delay;
	else out_point_ = inputs_.GetCount() + in_point_ - delay;

	delay_ = delay;
}

float Delay::GetEnergy() const {
	int i;
	float e = 0;

	if ( in_point_ >= out_point_ ) {
		for ( i = out_point_; i < in_point_; i++ ) {
			float t = inputs_[i];
			e += t * t;
		}
	}
	else {
		for ( i = out_point_; i < inputs_.GetCount(); i++ ) {
			float t = inputs_[i];
			e += t * t;
		}

		for ( i = 0; i < in_point_; i++ ) {
			float t = inputs_[i];
			e += t * t;
		}
	}

	return e;
}

float Delay::GetTapOut( int tap_delay ) {
	long tap = in_point_ - tap_delay - 1;

	while ( tap < 0 )
		tap += inputs_.GetCount();

	return inputs_[tap];
}

void Delay::TapIn( float value, int tap_delay ) {
	long tap = in_point_ - tap_delay - 1;

	while ( tap < 0 )
		tap += inputs_.GetCount();

	inputs_[tap] = value;
}

float Delay::addTo( float value, int tap_delay ) {
	long tap = in_point_ - tap_delay - 1;

	while ( tap < 0 )
		tap += inputs_.GetCount();

	return inputs_[tap] += value;
}

NAMESPACE_AUDIO_END
