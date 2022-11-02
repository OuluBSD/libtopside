#ifndef _AudioCore_PLUCKED_H
#define _AudioCore_PLUCKED_H


NAMESPACE_AUDIO_BEGIN


class Plucked : public Instrument {
public:

	Plucked( double lowest_freq = 10.0 );
	~Plucked();
	void Clear();
	void SetFrequency( double frequency );
	void Pluck( double amplitude );
	void NoteOn( double frequency, double amplitude );
	void NoteOff( double amplitude );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	DelayA   delay_line_;
	OneZero  loop_filter_;
	OnePole  pick_filter_;
	Noise    noise_;

	double loop_gain_;
};

inline double Plucked::Tick( unsigned int ) {
	return last_frame_[0] = 3.0 * delay_line_.Tick( loop_filter_.Tick( delay_line_.GetLastOut() * loop_gain_ ) );
}

inline AudioFrames& Plucked::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Plucked::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int j, step = frames.GetChannelCount() - channel_count;

	if ( channel_count == 1 ) {
		for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
			* samples++ = Tick();
	}
	else {
		for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
			*samples++ = Tick();

			for ( j = 1; j < channel_count; j++ )
				*samples++ = last_frame_[j];
		}
	}

	return frames;
}

NAMESPACE_AUDIO_END

#endif
