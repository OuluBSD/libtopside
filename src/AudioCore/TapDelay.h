#ifndef _AudioCore_TAPDELAY_H
#define _AudioCore_TAPDELAY_H


NAMESPACE_AUDIO_BEGIN


class TapDelay : public Filter {
public:

	TapDelay( const Vector<int>& taps, int max_delay );
	~TapDelay();

	void SetMaximumDelay( int delay );
	void SetTapDelays( const Vector<int>& taps );

	const Vector<int>& GetTapDelays() const {
		return delays_;
	};

	float GetLastOut( int tap = 0 ) const;
	AudioFrames& Tick( float input, AudioFrames& outputs );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0 );

protected:

	int in_point_;
	Vector<int> out_point_;
	Vector<int> delays_;

};

inline float TapDelay::GetLastOut( int tap ) const {
	#if defined(flagDEBUG)

	if ( tap >= last_frame_.GetCount() ) {
		LOG("TapDelay::GetLastOut(): tap argument and number of taps are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[tap];
}

inline AudioFrames& TapDelay::Tick( float input, AudioFrames& outputs ) {
	#if defined(flagDEBUG)

	if ( outputs.GetChannelCount() < out_point_.GetCount() ) {
		LOG("TapDelay::Tick(): number of taps > channels in AudioFrames argument!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	inputs_[in_point_++] = input * gain_;

	if ( in_point_ == inputs_.GetCount() )
		in_point_ = 0;

	float* outs = &outputs[0];

	for ( int i = 0; i < out_point_.GetCount(); i++ ) {
		*outs++ = inputs_[out_point_[i]];
		last_frame_[i] = *outs;

		if ( ++out_point_[i] == inputs_.GetCount() )
			out_point_[i] = 0;
	}

	return outputs;
}

inline AudioFrames& TapDelay::Tick( AudioFrames& frames, int channel ) {
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
	float* in_samples = &frames[channel];
	float* out_samples = &frames[0];
	int j;
	int in_step = frames.GetChannelCount();
	int out_step = frames.GetChannelCount() - out_point_.GetCount();

	for ( long i = 0; i < frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
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

inline AudioFrames& TapDelay::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel ) {
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
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[0];
	int j;
	int in_step = in_frames.GetChannelCount();
	int out_step = out_frames.GetChannelCount() - out_point_.GetCount();

	for ( int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
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
