#ifndef _AudioCore_TWOZERO_H
#define _AudioCore_TWOZERO_H


NAMESPACE_AUDIO_BEGIN


class TwoZero : public Filter {
public:

	TwoZero();
	~TwoZero();

	void IgnoreSampleRateChange( bool ignore = true ) {
		IgnoreSampleRateChange_ = ignore;
	};

	void SetB0( double b0 ) {
		b_[0] = b0;
	};

	void SetB1( double b1 ) {
		b_[1] = b1;
	};

	void SetB2( double b2 ) {
		b_[2] = b2;
	};

	void SetCoefficients( double b0, double b1, double b2, bool ClearState = false );
	void SetNotch( double frequency, double radius );

	double GetLastOut() const {
		return last_frame_[0];
	};

	double Tick( double input );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

	void SampleRateChanged( double new_rate, double old_rate );
};

inline double TwoZero::Tick( double input ) {
	inputs_[0] = gain_ * input;
	last_frame_[0] = b_[2] * inputs_[2] + b_[1] * inputs_[1] + b_[0] * inputs_[0];
	inputs_[2] = inputs_[1];
	inputs_[1] = inputs_[0];
	return last_frame_[0];
}

inline AudioFrames& TwoZero::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("TwoZero::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		inputs_[0] = gain_ * *samples;
		*samples = b_[2] * inputs_[2] + b_[1] * inputs_[1] + b_[0] * inputs_[0];
		inputs_[2] = inputs_[1];
		inputs_[1] = inputs_[0];
	}

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& TwoZero::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("TwoZero::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	unsigned int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( unsigned int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
		inputs_[0] = gain_ * *in_samples;
		*out_samples = b_[2] * inputs_[2] + b_[1] * inputs_[1] + b_[0] * inputs_[0];
		inputs_[2] = inputs_[1];
		inputs_[1] = inputs_[0];
	}

	last_frame_[0] = *(out_samples - out_step);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
