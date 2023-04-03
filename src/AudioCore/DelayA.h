#ifndef _AudioCore_DELAYA_H
#define _AudioCore_DELAYA_H


NAMESPACE_AUDIO_BEGIN


class DelayA : public Filter {
public:

	DelayA( float delay = 0.5, int max_delay = 4095 );
	~DelayA();
	void Clear();
	
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
	float coeff_;
	float ap_input_;
	float next_output_;
	bool do_next_out_;
	
};

inline float DelayA::GetNextOut() {
	if ( do_next_out_ ) {
		next_output_ = -coeff_ * last_frame_[0];
		next_output_ += ap_input_ + ( coeff_ * inputs_[out_point_] );
		do_next_out_ = false;
	}

	return next_output_;
}

inline float DelayA::Tick( float input ) {
	inputs_[in_point_++] = input * gain_;

	if ( in_point_ == inputs_.GetCount() )
		in_point_ = 0;

	last_frame_[0] = GetNextOut();
	do_next_out_ = true;
	ap_input_ = inputs_[out_point_++];

	if ( out_point_ == inputs_.GetCount() )
		out_point_ = 0;

	return last_frame_[0];
}

inline AudioFrames& DelayA::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("DelayA::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		inputs_[in_point_++] = *samples * gain_;

		if ( in_point_ == inputs_.GetCount() ) in_point_ = 0;

		*samples = GetNextOut();
		last_frame_[0] = *samples;
		do_next_out_ = true;
		ap_input_ = inputs_[out_point_++];

		if ( out_point_ == inputs_.GetCount() ) out_point_ = 0;
	}

	return frames;
}

inline AudioFrames& DelayA::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("DelayA::Tick(): channel and AudioFrames arguments are incompatible!");
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
		last_frame_[0] = *out_samples;
		do_next_out_ = true;
		ap_input_ = inputs_[out_point_++];

		if ( out_point_ == inputs_.GetCount() ) out_point_ = 0;
	}

	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
