#ifndef _AudioCore_GRANULATE_H
#define _AudioCore_GRANULATE_H


NAMESPACE_AUDIO_BEGIN


class Granulate : public Generator, Moveable<Granulate> {
public:

	Granulate();
	Granulate( unsigned int voice_count, String file_name, bool type_raw = false );
	~Granulate();

	void OpenFile( String file_name, bool type_raw = false );
	void Reset();
	void SetVoices( unsigned int voice_count = 1 );
	void SetStretch( unsigned int stretchFactor = 1 );
	void SetGrainParameters( unsigned int duration = 30, unsigned int rampPercent = 50,
							 int offset = 0, unsigned int delay = 0 );
	void SetRandomFactor( double randomness = 0.1 );
	double GetLastOut( unsigned int channel = 0 );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

	enum GrainState {
		GRAIN_STOPPED,
		GRAIN_FADEIN,
		GRAIN_SUSTAIN,
		GRAIN_FADEOUT
	};

protected:

	struct Grain : Moveable<Grain> {
		double eScaler;
		double eRate;
		unsigned long attackCount;
		unsigned long sustainCount;
		unsigned long decayCount;
		unsigned long delayCount;
		unsigned long counter;

		double pointer;
		unsigned long StartPointer;
		unsigned int repeats;
		GrainState state;


		Grain()
			: eScaler(0.0), eRate(0.0), attackCount(0), sustainCount(0), decayCount(0),
			  delayCount(0), counter(0), pointer(0), StartPointer(0), repeats(0), state(GRAIN_STOPPED) {}
	};

	void CalculateGrain( Granulate::Grain& grain );

	AudioFrames data_;
	Vector<Grain> grains_;
	Noise noise;

	double g_pointer_;

	unsigned int g_duration_;
	unsigned int g_ramp_percent_;
	unsigned int g_delay_;
	unsigned int g_stretch_;
	unsigned int stretch_counter_;
	int g_offset_;
	double g_random_factor_;
	double gain_;

};

inline double Granulate::GetLastOut( unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= last_frame_.GetChannelCount() ) {
		LOG("Granulate::GetLastOut(): channel argument is invalid!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[channel];
}

inline AudioFrames& Granulate::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Granulate::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int j, step = frames.GetChannelCount() - channel_count;

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		*samples++ = Tick();

		for ( j = 1; j < channel_count; j++ )
			*samples++ = last_frame_[j];
	}

	return frames;
}


NAMESPACE_AUDIO_END

#endif
