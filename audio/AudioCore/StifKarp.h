#ifndef _AudioCore_STIFKARP_H
#define _AudioCore_STIFKARP_H


NAMESPACE_AUDIO_BEGIN


class StifKarp : public Instrument {
public:

	StifKarp( double lowest_freq = 8.0 );
	~StifKarp();
	void Clear();
	void SetFrequency( double frequency );
	void SetStretch( double stretch );
	void SetPickupPosition( double position );
	void SetBaseLoopGain( double aGain );
	void Pluck( double amplitude );
	void NoteOn( double frequency, double amplitude );
	void NoteOff( double amplitude );
	void ControlChange( int number, double value );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	DelayA  delay_line_;
	DelayL  comb_delay_;
	OneZero filter_;
	Noise   noise_;
	BiQuad  biquad_[4];

	unsigned long size_;
	double loop_gain_;
	double base_loop_gain_;
	double last_frequency_;
	double last_length_;
	double stretching_;
	double pluck_amplitude_;
	double pickup_position_;

};

inline double StifKarp::Tick( unsigned int ) {
	double temp = delay_line_.GetLastOut() * loop_gain_;

	for (int i = 0; i < 4; i++)
		temp = biquad_[i].Tick(temp);

	temp = filter_.Tick(temp);
	last_frame_[0] = delay_line_.Tick(temp);
	last_frame_[0] = last_frame_[0] - comb_delay_.Tick( last_frame_[0] );
	return last_frame_[0];
}

inline AudioFrames& StifKarp::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("StifKarp::Tick(): channel and AudioFrames arguments are incompatible!");
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
