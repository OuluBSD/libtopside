#ifndef _AudioCore_NOISE_H
#define _AudioCore_NOISE_H


NAMESPACE_AUDIO_BEGIN


class Noise : public Generator {
public:

	Noise( int seed = 0 );
	void SetSeed( int seed = 0 );

	float GetLastOut() const {
		return last_frame_[0];
	};

	float Tick();
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

};

inline float Noise::Tick() {
	return last_frame_[0] = (float) ( 2.0 * rand() / (RAND_MAX + 1.0) - 1.0 );
}

inline AudioFrames& Noise::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Noise::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = (float) ( 2.0 * rand() / (RAND_MAX + 1.0) - 1.0 );

	last_frame_[0] = *(samples - step);
	return frames;
}

NAMESPACE_AUDIO_END

#endif
