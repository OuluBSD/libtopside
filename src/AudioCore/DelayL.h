#ifndef _AudioCore_DELAYL_H
#define _AudioCore_DELAYL_H


NAMESPACE_AUDIO_BEGIN


class DelayL : public Filter {
public:

	DelayL( double delay = 0.0, unsigned long max_delay = 4095 );
	~DelayL();
	
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
	double omAlpha_;
	double next_output_;
	bool do_next_out_;
};

inline double DelayL::GetNextOut() {
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

inline void DelayL::SetDelay( double delay ) {
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

	double out_pointer = in_point_ - delay;
	delay_ = delay;

	while ( out_pointer < 0 )
		out_pointer += inputs_.GetCount();

	out_point_ = (long) out_pointer;
	alpha_ = out_pointer - out_point_;
	omAlpha_ = (double) 1.0 - alpha_;

	if ( out_point_ == inputs_.GetCount() ) out_point_ = 0;

	do_next_out_ = true;
}

inline double DelayL::Tick( double input ) {
	inputs_[in_point_++] = input * gain_;

	if ( in_point_ == inputs_.GetCount() )
		in_point_ = 0;

	last_frame_[0] = GetNextOut();
	do_next_out_ = true;

	if ( ++out_point_ == inputs_.GetCount() )
		out_point_ = 0;

	return last_frame_[0];
}

inline AudioFrames& DelayL::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("DelayL::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		inputs_[in_point_++] = *samples * gain_;

		if ( in_point_ == inputs_.GetCount() ) in_point_ = 0;

		*samples = GetNextOut();
		do_next_out_ = true;

		if ( ++out_point_ == inputs_.GetCount() ) out_point_ = 0;
	}

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& DelayL::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("DelayL::Tick(): channel and AudioFrames arguments are incompatible!");
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
		do_next_out_ = true;

		if ( ++out_point_ == inputs_.GetCount() ) out_point_ = 0;
	}

	last_frame_[0] = *(out_samples - out_step);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
