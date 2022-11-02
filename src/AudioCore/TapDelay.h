#ifndef _AudioCore_TAPDELAY_H
#define _AudioCore_TAPDELAY_H


NAMESPACE_AUDIO_BEGIN


class TapDelay : public Filter {
public:

	TapDelay( const Vector<unsigned long>& taps, unsigned long max_delay );
	~TapDelay();

	void SetMaximumDelay( unsigned long delay );
	void SetTapDelays( const Vector<unsigned long>& taps );

	const Vector<unsigned long>& GetTapDelays() const {
		return delays_;
	};

	double GetLastOut( unsigned int tap = 0 ) const;
	AudioFrames& Tick( double input, AudioFrames& outputs );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0 );

protected:

	unsigned long in_point_;
	Vector<unsigned long> out_point_;
	Vector<unsigned long> delays_;

};

inline double TapDelay::GetLastOut( unsigned int tap ) const {
	#if defined(flagDEBUG)

	if ( tap >= last_frame_.GetCount() ) {
		LOG("TapDelay::GetLastOut(): tap argument and number of taps are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[tap];
}

inline AudioFrames& TapDelay::Tick( double input, AudioFrames& outputs ) {
	#if defined(flagDEBUG)

	if ( outputs.GetChannelCount() < out_point_.GetCount() ) {
		LOG("TapDelay::Tick(): number of taps > channels in AudioFrames argument!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	inputs_[in_point_++] = input * gain_;

	if ( in_point_ == inputs_.GetCount() )
		in_point_ = 0;

	double* outs = &outputs[0];

	for ( unsigned int i = 0; i < out_point_.GetCount(); i++ ) {
		*outs++ = inputs_[out_point_[i]];
		last_frame_[i] = *outs;

		if ( ++out_point_[i] == inputs_.GetCount() )
			out_point_[i] = 0;
	}

	return outputs;
}

inline AudioFrames& TapDelay::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("TapDelay::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( frames.GetChannelCount() < out_point_.GetCount() ) {
		LOG("TapDelay::Tick(): number of taps > channels in AudioFrames argument!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &frames[channel];
	double* out_samples = &frames[0];
	std::size_t j;
	unsigned int in_step = frames.GetChannelCount();
	std::size_t out_step = frames.GetChannelCount() - out_point_.GetCount();

	for ( unsigned long i = 0; i < frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
		inputs_[in_point_++] = *in_samples * gain_;

		if ( in_point_ == inputs_.GetCount() ) in_point_ = 0;

		for ( j = 0; j < out_point_.GetCount(); j++ ) {
			*out_samples++ = inputs_[out_point_[j]];

			if ( ++out_point_[j] == inputs_.GetCount() ) out_point_[j] = 0;
		}
	}

	out_samples -= frames.GetChannelCount();

	for ( j = 0; j < out_point_.GetCount(); j++ ) last_frame_[j] = *out_samples++;

	return frames;
}

inline AudioFrames& TapDelay::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() ) {
		LOG("TapDelay::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	if ( out_frames.GetChannelCount() < out_point_.GetCount() ) {
		LOG("TapDelay::Tick(): number of taps > channels in output AudioFrames argument!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[0];
	std::size_t j;
	unsigned int in_step = in_frames.GetChannelCount();
	std::size_t out_step = out_frames.GetChannelCount() - out_point_.GetCount();

	for ( unsigned long i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
		inputs_[in_point_++] = *in_samples * gain_;

		if ( in_point_ == inputs_.GetCount() ) in_point_ = 0;

		for ( j = 0; j < out_point_.GetCount(); j++ ) {
			*out_samples++ = inputs_[out_point_[j]];

			if ( ++out_point_[j] == inputs_.GetCount() ) out_point_[j] = 0;
		}
	}

	out_samples -= out_frames.GetChannelCount();

	for ( j = 0; j < out_point_.GetCount(); j++ ) last_frame_[j] = *out_samples++;

	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
