#ifndef _AudioCore_NOISE_H
#define _AudioCore_NOISE_H


NAMESPACE_AUDIO_BEGIN


class Noise : public Generator {
public:

	Noise( unsigned int seed = 0 );
	void SetSeed( unsigned int seed = 0 );

	double GetLastOut() const {
		return last_frame_[0];
	};

	double Tick();
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

};

inline double Noise::Tick() {
	return last_frame_[0] = (double) ( 2.0 * rand() / (RAND_MAX + 1.0) - 1.0 );
}

inline AudioFrames& Noise::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Noise::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = (double) ( 2.0 * rand() / (RAND_MAX + 1.0) - 1.0 );

	last_frame_[0] = *(samples - step);
	return frames;
}

NAMESPACE_AUDIO_END

#endif
