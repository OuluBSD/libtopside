#ifndef _AudioCore_GRANULATE_H
#define _AudioCore_GRANULATE_H


NAMESPACE_AUDIO_BEGIN


class Granulate : public Generator, Moveable<Granulate> {
public:

	Granulate();
	Granulate( int voice_count, String file_name, bool type_raw = false );
	~Granulate();

	void OpenFile( String file_name, bool type_raw = false );
	void Reset();
	void SetVoices( int voice_count = 1 );
	void SetStretch( int stretchFactor = 1 );
	void SetGrainParameters( int duration = 30, int rampPercent = 50,
							 int offset = 0, int delay = 0 );
	void SetRandomFactor( float randomness = 0.1 );
	float GetLastOut( int channel = 0 );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

	enum GrainState {
		GRAIN_STOPPED,
		GRAIN_FADEIN,
		GRAIN_SUSTAIN,
		GRAIN_FADEOUT
	};

protected:

	struct Grain : Moveable<Grain> {
		float eScaler;
		float eRate;
		int attackCount;
		int sustainCount;
		int decayCount;
		int delayCount;
		int counter;

		float pointer;
		int StartPointer;
		int repeats;
		GrainState state;


		Grain()
			: eScaler(0.0f), eRate(0.0f), attackCount(0), sustainCount(0), decayCount(0),
			  delayCount(0), counter(0), pointer(0), StartPointer(0), repeats(0), state(GRAIN_STOPPED) {}
	};

	void CalculateGrain( Granulate::Grain& grain );

	AudioFrames data_;
	Vector<Grain> grains_;
	Noise noise;

	float g_pointer_;

	int g_duration_;
	int g_ramp_percent_;
	int g_delay_;
	int g_stretch_;
	int stretch_counter_;
	int g_offset_;
	float g_random_factor_;
	float gain_;

};

inline float Granulate::GetLastOut( int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= last_frame_.GetChannelCount() ) {
		LOG("Granulate::GetLastOut(): channel argument is invalid!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[channel];
}

inline AudioFrames& Granulate::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Granulate::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int j, step = frames.GetChannelCount() - channel_count;

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		*samples++ = Tick();

		for ( j = 1; j < channel_count; j++ )
			*samples++ = last_frame_[j];
	}

	return frames;
}


NAMESPACE_AUDIO_END

#endif
