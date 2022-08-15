#ifndef _AudioCore_TWOPOLE_H
#define _AudioCore_TWOPOLE_H


NAMESPACE_AUDIO_BEGIN


class TwoPole : public Filter {
public:

	TwoPole();
	~TwoPole();

	void IgnoreSampleRateChange( bool ignore = true ) {
		IgnoreSampleRateChange_ = ignore;
	};

	void SetB0( double b0 ) {
		b_[0] = b0;
	};
	
	void SetA1( double a1 ) {
		a_[1] = a1;
	};

	void SetA2( double a2 ) {
		a_[2] = a2;
	};

	void SetCoefficients( double b0, double a1, double a2, bool ClearState = false );
	void SetResonance(double frequency, double radius, bool normalize = false);

	double GetLastOut() const {
		return last_frame_[0];
	};

	double Tick( double input );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

	virtual void SampleRateChanged( double new_rate, double old_rate );
	
};

inline double TwoPole::Tick( double input ) {
	inputs_[0] = gain_ * input;
	last_frame_[0] = b_[0] * inputs_[0] - a_[1] * outputs_[1] - a_[2] * outputs_[2];
	outputs_[2] = outputs_[1];
	outputs_[1] = last_frame_[0];
	return last_frame_[0];
}

inline AudioFrames& TwoPole::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("TwoPole::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		inputs_[0] = gain_ * *samples;
		*samples = b_[0] * inputs_[0] - a_[1] * outputs_[1] - a_[2] * outputs_[2];
		outputs_[2] = outputs_[1];
		outputs_[1] = *samples;
	}

	last_frame_[0] = outputs_[1];
	return frames;
}

inline AudioFrames& TwoPole::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("TwoPole::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	unsigned int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( unsigned int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step ) {
		inputs_[0] = gain_ * *in_samples;
		*out_samples = b_[0] * inputs_[0] - a_[1] * outputs_[1] - a_[2] * outputs_[2];
		outputs_[2] = outputs_[1];
		outputs_[1] = *out_samples;
	}

	last_frame_[0] = outputs_[1];
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
