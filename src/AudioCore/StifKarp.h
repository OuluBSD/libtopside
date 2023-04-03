#ifndef _AudioCore_STIFKARP_H
#define _AudioCore_STIFKARP_H


NAMESPACE_AUDIO_BEGIN


class StifKarp : public Instrument {
public:

	StifKarp( float lowest_freq = 8.0 );
	~StifKarp();
	void Clear();
	void SetFrequency( float frequency );
	void SetStretch( float stretch );
	void SetPickupPosition( float position );
	void SetBaseLoopGain( float aGain );
	void Pluck( float amplitude );
	void NoteOn( float frequency, float amplitude );
	void NoteOff( float amplitude );
	void ControlChange( int number, float value );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	DelayA  delay_line_;
	DelayL  comb_delay_;
	OneZero filter_;
	Noise   noise_;
	BiQuad  biquad_[4];

	int size_;
	float loop_gain_;
	float base_loop_gain_;
	float last_frequency_;
	float last_length_;
	float stretching_;
	float pluck_amplitude_;
	float pickup_position_;

};

inline float StifKarp::Tick( int ) {
	float temp = delay_line_.GetLastOut() * loop_gain_;

	for (int i = 0; i < 4; i++)
		temp = biquad_[i].Tick(temp);

	temp = filter_.Tick(temp);
	last_frame_[0] = delay_line_.Tick(temp);
	last_frame_[0] = last_frame_[0] - comb_delay_.Tick( last_frame_[0] );
	return last_frame_[0];
}

inline AudioFrames& StifKarp::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("StifKarp::Tick(): channel and AudioFrames arguments are incompatible!");
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
