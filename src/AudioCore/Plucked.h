#ifndef _AudioCore_PLUCKED_H
#define _AudioCore_PLUCKED_H


NAMESPACE_AUDIO_BEGIN


class Plucked : public Instrument {
public:

	Plucked( float lowest_freq = 10.0f );
	~Plucked();
	void Clear();
	void SetFrequency( float frequency );
	void Pluck( float amplitude );
	void NoteOn( float frequency, float amplitude );
	void NoteOff( float amplitude );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	DelayA   delay_line_;
	OneZero  loop_filter_;
	OnePole  pick_filter_;
	Noise    noise_;

	float loop_gain_;
};

inline float Plucked::Tick( int ) {
	return last_frame_[0] = 3.0f * delay_line_.Tick( loop_filter_.Tick( delay_line_.GetLastOut() * loop_gain_ ) );
}

inline AudioFrames& Plucked::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Plucked::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int j, step = frames.GetChannelCount() - channel_count;

	if ( channel_count == 1 ) {
		for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
			* samples++ = Tick();
	}
	else {
		for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
			*samples++ = Tick();

			for ( j = 1; j < channel_count; j++ )
				*samples++ = last_frame_[j];
		}
	}

	return frames;
}

NAMESPACE_AUDIO_END

#endif
