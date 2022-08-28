#ifndef _AudioCore_DELAYA_H
#define _AudioCore_DELAYA_H


NAMESPACE_AUDIO_BEGIN


class DelayA : public Filter {
public:

	DelayA( double delay = 0.5, unsigned long max_delay = 4095 );
	~DelayA();
	void Clear();
	
	unsigned long GetMaximumDelay() {
		return inputs_.GetCount() - 1;
	};

	void SetMaximumDelay( unsigned long delay );
	void SetDelay( double delay );

	double GetDelay() const {
		return delay_;
	};

	double GetTapOut( unsigned long tap_delay );
	void TapIn( double value, unsigned long tap_delay );

	double GetLastOut() const {
		return last_frame_[0];
	};

	double GetNextOut();
	double Tick( double input );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

	unsigned long in_point_;
	unsigned long out_point_;
	double delay_;
	double alpha_;
	double coeff_;
	double ap_input_;
	double next_output_;
	bool do_next_out_;
	
};

inline double DelayA::GetNextOut() {
	if ( do_next_out_ ) {
		next_output_ = -coeff_ * last_frame_[0];
		next_output_ += ap_input_ + ( coeff_ * inputs_[out_point_] );
		do_next_out_ = false;
	}

	return next_output_;
}

inline double DelayA::Tick( double input ) {
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

inline AudioFrames& DelayA::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("DelayA::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
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

inline AudioFrames& DelayA::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("DelayA::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	unsigned int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( unsigned int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
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