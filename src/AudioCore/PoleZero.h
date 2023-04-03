#ifndef _AudioCore_POLEZERO_H
#define _AudioCore_POLEZERO_H


NAMESPACE_AUDIO_BEGIN


class PoleZero : public Filter {
public:

	PoleZero();
	~PoleZero();

	void SetB0( float b0 ) {
		b_[0] = b0;
	};

	void SetB1( float b1 ) {
		b_[1] = b1;
	};

	void SetA1( float a1 ) {
		a_[1] = a1;
	};

	void SetCoefficients( float b0, float b1, float a1, bool ClearState = false );
	void SetAllpass( float coefficient );
	void SetBlockZero( float thePole = 0.99 );

	float GetLastOut() const {
		return last_frame_[0];
	};

	float Tick( float input );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

};

inline float PoleZero::Tick( float input ) {
	inputs_[0] = gain_ * input;
	last_frame_[0] = b_[0] * inputs_[0] + b_[1] * inputs_[1] - a_[1] * outputs_[1];
	inputs_[1] = inputs_[0];
	outputs_[1] = last_frame_[0];
	return last_frame_[0];
}

inline AudioFrames& PoleZero::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("PoleZero::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
		inputs_[0] = gain_ * *samples;
		*samples = b_[0] * inputs_[0] + b_[1] * inputs_[1] - a_[1] * outputs_[1];
		inputs_[1] = inputs_[0];
		outputs_[1] = *samples;
	}

	last_frame_[0] = outputs_[1];
	return frames;
}

NAMESPACE_AUDIO_END

#endif
