#ifndef _AudioCore_CUBIC_H
#define _AudioCore_CUBIC_H


NAMESPACE_AUDIO_BEGIN


class Cubic : public Function {
public:

	Cubic() : a1_(0.5), a2_(0.5), a3_(0.5), gain_(1.0f), threshold_(1.0f) {};

	void SetA1( float a1 ) {
		a1_ = a1;
	};

	void SetA2( float a2 )  {
		a2_ = a2;
	};

	void SetA3( float a3 )  {
		a3_ = a3;
	};

	void SetGain( float gain ) {
		gain_ = gain;
	};

	void SetThreshold( float threshold ) {
		threshold_ = threshold;
	};

	float Tick( float input );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

	float a1_;
	float a2_;
	float a3_;
	float gain_;
	float threshold_;
};

inline float Cubic::Tick( float input ) {
	float in_squared = input * input;
	float in_cubed = in_squared * input;
	last_frame_[0] = gain_ * (a1_ * input + a2_ * in_squared + a3_ * in_cubed);

	if ( fabs( last_frame_[0] ) > threshold_ )
		last_frame_[0] = ( last_frame_[0] < 0 ? -threshold_ : threshold_ );

	return last_frame_[0];
}

inline AudioFrames& Cubic::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Cubic::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Tick( *samples );

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& Cubic::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("Cubic::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[out_channel];
	int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step )
		* out_samples = Tick( *in_samples );

	last_frame_[0] = *(out_samples - out_step);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
