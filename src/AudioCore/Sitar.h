#ifndef _AudioCore_SITAR_H
#define _AudioCore_SITAR_H


NAMESPACE_AUDIO_BEGIN


class Sitar : public Instrument {
public:

	Sitar( float lowest_freq = 8.0 );
	~Sitar();
	void Clear();
	void SetFrequency( float frequency );
	void Pluck( float amplitude );
	void NoteOn( float frequency, float amplitude );
	void NoteOff( float amplitude );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	DelayA  delay_line_;
	OneZero loop_filter_;
	Noise   noise_;
	ADSR    envelope_;

	float loop_gain_;
	float am_gain_;
	float delay_;
	float target_delay_;

};

inline float Sitar::Tick( int ) {
	if ( fabs(target_delay_ - delay_) > 0.001f ) {
		if ( target_delay_ < delay_ )
			delay_ *= 0.99999f;
		else
			delay_ *= 1.00001f;

		delay_line_.SetDelay( delay_ );
	}

	last_frame_[0] = delay_line_.Tick( loop_filter_.Tick( delay_line_.GetLastOut() * loop_gain_ ) +
									   (am_gain_ * envelope_.Tick() * noise_.Tick()));
	return last_frame_[0];
}

inline AudioFrames& Sitar::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Sitar::Tick(): channel and AudioFrames arguments are incompatible!");
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

