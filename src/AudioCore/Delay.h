#ifndef _AudioCore_DELAY_H
#define _AudioCore_DELAY_H


NAMESPACE_AUDIO_BEGIN


class Delay : public Filter {
public:

	Delay( int delay = 0, int max_delay = 4095 );
	~Delay();

	int GetMaximumDelay() {
		return inputs_.GetCount() - 1;
	};

	void SetMaximumDelay( int delay );
	void SetDelay( int delay );

	int GetDelay() const {
		return delay_;
	};

	float GetTapOut( int tap_delay );
	void TapIn( float value, int tap_delay );
	float addTo( float value, int tap_delay );
	
	float GetLastOut() const {
		return last_frame_[0];
	};

	float GetNextOut() {
		return inputs_[out_point_];
	};

	float GetEnergy() const;
	float Tick( float input );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

	int in_point_;
	int out_point_;
	int delay_;
	
};

inline float Delay::Tick( float input ) {
	inputs_[in_point_++] = input * gain_;

	if ( in_point_ == inputs_.GetCount() )
		in_point_ = 0;

	last_frame_[0] = inputs_[out_point_++];

	if ( out_point_ == inputs_.GetCount() )
		out_point_ = 0;

	return last_frame_[0];
}

inline AudioFrames& Delay::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Delay::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		inputs_[in_point_++] = *samples * gain_;

		if ( in_point_ == inputs_.GetCount() ) in_point_ = 0;

		*samples = inputs_[out_point_++];

		if ( out_point_ == inputs_.GetCount() ) out_point_ = 0;
	}

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& Delay::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("Delay::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[out_channel];
	int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
		inputs_[in_point_++] = *in_samples * gain_;

		if ( in_point_ == inputs_.GetCount() ) in_point_ = 0;

		*out_samples = inputs_[out_point_++];

		if ( out_point_ == inputs_.GetCount() ) out_point_ = 0;
	}

	last_frame_[0] = *(out_samples - out_step);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
