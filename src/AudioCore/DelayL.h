#ifndef _AudioCore_DELAYL_H
#define _AudioCore_DELAYL_H


NAMESPACE_AUDIO_BEGIN


class DelayL : public Filter {
public:

	DelayL( float delay = 0.0f, int max_delay = 4095 );
	~DelayL();
	
	int GetMaximumDelay() {
		return inputs_.GetCount() - 1;
	};

	void SetMaximumDelay( int delay );
	void SetDelay( float delay );

	float GetDelay() const {
		return delay_;
	};

	float GetTapOut( int tap_delay );
	void TapIn( float value, int tap_delay );

	float GetLastOut() const {
		return last_frame_[0];
	};

	float GetNextOut();
	float Tick( float input );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

	int in_point_;
	int out_point_;
	float delay_;
	float alpha_;
	float omAlpha_;
	float next_output_;
	bool do_next_out_;
};

inline float DelayL::GetNextOut() {
	if ( do_next_out_ ) {
		next_output_ = inputs_[out_point_] * omAlpha_;

		if (out_point_ + 1 < inputs_.GetCount())
			next_output_ += inputs_[out_point_ + 1] * alpha_;
		else
			next_output_ += inputs_[0] * alpha_;

		do_next_out_ = false;
	}

	return next_output_;
}

inline void DelayL::SetDelay( float delay ) {
	if ( delay + 1 > inputs_.GetCount() ) {
		LOG("DelayL::SetDelay: argument (" << delay << ") greater than  maximum!");
		HandleError( AudioError::WARNING );
		return;
	}

	if (delay < 0 ) {
		LOG("DelayL::SetDelay: argument (" << delay << ") less than zero!");
		HandleError( AudioError::WARNING );
		return;
	}

	float out_pointer = in_point_ - delay;
	delay_ = delay;

	while ( out_pointer < 0 )
		out_pointer += inputs_.GetCount();

	out_point_ = (long) out_pointer;
	alpha_ = out_pointer - out_point_;
	omAlpha_ = (float) 1.0f - alpha_;

	if ( out_point_ == inputs_.GetCount() ) out_point_ = 0;

	do_next_out_ = true;
}

inline float DelayL::Tick( float input ) {
	inputs_[in_point_++] = input * gain_;

	if ( in_point_ == inputs_.GetCount() )
		in_point_ = 0;

	last_frame_[0] = GetNextOut();
	do_next_out_ = true;

	if ( ++out_point_ == inputs_.GetCount() )
		out_point_ = 0;

	return last_frame_[0];
}

inline AudioFrames& DelayL::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("DelayL::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		inputs_[in_point_++] = *samples * gain_;

		if ( in_point_ == inputs_.GetCount() ) in_point_ = 0;

		*samples = GetNextOut();
		do_next_out_ = true;

		if ( ++out_point_ == inputs_.GetCount() ) out_point_ = 0;
	}

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& DelayL::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("DelayL::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[out_channel];
	int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
		inputs_[in_point_++] = *in_samples * gain_;

		if ( in_point_ == inputs_.GetCount() ) in_point_ = 0;

		*out_samples = GetNextOut();
		do_next_out_ = true;

		if ( ++out_point_ == inputs_.GetCount() ) out_point_ = 0;
	}

	last_frame_[0] = *(out_samples - out_step);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
