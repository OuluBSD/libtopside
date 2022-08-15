#ifndef _AudioCore_SITAR_H
#define _AudioCore_SITAR_H


NAMESPACE_AUDIO_BEGIN


class Sitar : public Instrument {
public:

	Sitar( double lowest_freq = 8.0 );
	~Sitar();
	void Clear();
	void SetFrequency( double frequency );
	void Pluck( double amplitude );
	void NoteOn( double frequency, double amplitude );
	void NoteOff( double amplitude );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	DelayA  delay_line_;
	OneZero loop_filter_;
	Noise   noise_;
	ADSR    envelope_;

	double loop_gain_;
	double am_gain_;
	double delay_;
	double target_delay_;

};

inline double Sitar::Tick( unsigned int ) {
	if ( fabs(target_delay_ - delay_) > 0.001 ) {
		if ( target_delay_ < delay_ )
			delay_ *= 0.99999;
		else
			delay_ *= 1.00001;

		delay_line_.SetDelay( delay_ );
	}

	last_frame_[0] = delay_line_.Tick( loop_filter_.Tick( delay_line_.GetLastOut() * loop_gain_ ) +
									   (am_gain_ * envelope_.Tick() * noise_.Tick()));
	return last_frame_[0];
}

inline AudioFrames& Sitar::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Sitar::Tick(): channel and AudioFrames arguments are incompatible!");
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

