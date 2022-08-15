#ifndef _AudioCore_MODULATE_H
#define _AudioCore_MODULATE_H


NAMESPACE_AUDIO_BEGIN


class Modulate : public Generator {
public:


	Modulate();
	~Modulate();

	void Reset() {
		last_frame_[0] = 0.0;
	};

	void SetVibratoRate( double rate ) {
		vibrato_.SetFrequency( rate );
	};

	void SetVibratoGain( double gain ) {
		vibrato_gain_ = gain;
	};

	void SetRandomGain( double gain );

	double GetLastOut() const {
		return last_frame_[0];
	};

	double Tick();
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	void SampleRateChanged( double new_rate, double old_rate );

	SineWave vibrato_;
	Noise noise_;
	OnePole  filter_;
	double vibrato_gain_;
	double random_gain_;
	unsigned int noise_rate_;
	unsigned int noise_counter_;

};

inline double Modulate::Tick() {
	last_frame_[0] = vibrato_gain_ * vibrato_.Tick();

	if ( noise_counter_++ >= noise_rate_ ) {
		noise_.Tick();
		noise_counter_ = 0;
	}

	last_frame_[0] += filter_.Tick( noise_.GetLastOut() );
	return last_frame_[0];
}

inline AudioFrames& Modulate::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Modulate::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Modulate::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
