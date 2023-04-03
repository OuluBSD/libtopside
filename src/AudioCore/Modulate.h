#ifndef _AudioCore_MODULATE_H
#define _AudioCore_MODULATE_H


NAMESPACE_AUDIO_BEGIN


class Modulate : public Generator {
public:


	Modulate();
	~Modulate();

	void Reset() {
		last_frame_[0] = 0.0f;
	};

	void SetVibratoRate( float rate ) {
		vibrato_.SetFrequency( rate );
	};

	void SetVibratoGain( float gain ) {
		vibrato_gain_ = gain;
	};

	void SetRandomGain( float gain );

	float GetLastOut() const {
		return last_frame_[0];
	};

	float Tick();
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	void SampleRateChanged( float new_rate, float old_rate );

	SineWave vibrato_;
	Noise noise_;
	OnePole  filter_;
	float vibrato_gain_;
	float random_gain_;
	int noise_rate_;
	int noise_counter_;

};

inline float Modulate::Tick() {
	last_frame_[0] = vibrato_gain_ * vibrato_.Tick();

	if ( noise_counter_++ >= noise_rate_ ) {
		noise_.Tick();
		noise_counter_ = 0;
	}

	last_frame_[0] += filter_.Tick( noise_.GetLastOut() );
	return last_frame_[0];
}

inline AudioFrames& Modulate::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Modulate::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Modulate::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
