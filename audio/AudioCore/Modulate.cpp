#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Modulate::Modulate() {
	vibrato_.SetFrequency( 6.0 );
	vibrato_gain_ = 0.04;
	noise_rate_ = (unsigned int) ( 330.0 * Audio::GetSampleRate() / 22050.0 );
	noise_counter_ = noise_rate_;
	random_gain_ = 0.05;
	filter_.SetPole( 0.999 );
	filter_.SetGain( random_gain_ );
	Audio::AddSampleRateAlert( this );
}

Modulate::~Modulate() {
	Audio::RemoveSampleRateAlert( this );
}

void Modulate::SampleRateChanged( double new_rate, double old_rate ) {
	if ( !IgnoreSampleRateChange_ )
		noise_rate_ = (unsigned int ) ( new_rate * noise_rate_ / old_rate );
}

void Modulate::SetRandomGain( double gain ) {
	random_gain_ = gain;
	filter_.SetGain( random_gain_ );
}

NAMESPACE_AUDIO_END
