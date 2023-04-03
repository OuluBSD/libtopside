#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Modulate::Modulate() {
	vibrato_.SetFrequency( 6.0f );
	vibrato_gain_ = 0.04f;
	noise_rate_ = (int) ( 330.0f * Audio::GetSampleRate() / 22050.0f );
	noise_counter_ = noise_rate_;
	random_gain_ = 0.05f;
	filter_.SetPole( 0.999f );
	filter_.SetGain( random_gain_ );
	Audio::AddSampleRateAlert( this );
}

Modulate::~Modulate() {
	Audio::RemoveSampleRateAlert( this );
}

void Modulate::SampleRateChanged( float new_rate, float old_rate ) {
	if ( !IgnoreSampleRateChange_ )
		noise_rate_ = (int ) ( new_rate * noise_rate_ / old_rate );
}

void Modulate::SetRandomGain( float gain ) {
	random_gain_ = gain;
	filter_.SetGain( random_gain_ );
}

NAMESPACE_AUDIO_END
