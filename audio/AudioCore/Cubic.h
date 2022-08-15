#ifndef _AudioCore_CUBIC_H
#define _AudioCore_CUBIC_H


NAMESPACE_AUDIO_BEGIN


class Cubic : public Function {
public:

	Cubic() : a1_(0.5), a2_(0.5), a3_(0.5), gain_(1.0), threshold_(1.0) {};

	void SetA1( double a1 ) {
		a1_ = a1;
	};

	void SetA2( double a2 )  {
		a2_ = a2;
	};

	void SetA3( double a3 )  {
		a3_ = a3;
	};

	void SetGain( double gain ) {
		gain_ = gain;
	};

	void SetThreshold( double threshold ) {
		threshold_ = threshold;
	};

	double Tick( double input );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

	double a1_;
	double a2_;
	double a3_;
	double gain_;
	double threshold_;
};

inline double Cubic::Tick( double input ) {
	double in_squared = input * input;
	double in_cubed = in_squared * input;
	last_frame_[0] = gain_ * (a1_ * input + a2_ * in_squared + a3_ * in_cubed);

	if ( fabs( last_frame_[0] ) > threshold_ )
		last_frame_[0] = ( last_frame_[0] < 0 ? -threshold_ : threshold_ );

	return last_frame_[0];
}

inline AudioFrames& Cubic::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Cubic::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Tick( *samples );

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& Cubic::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("Cubic::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	unsigned int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( unsigned int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step )
		* out_samples = Tick( *in_samples );

	last_frame_[0] = *(out_samples - out_step);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
