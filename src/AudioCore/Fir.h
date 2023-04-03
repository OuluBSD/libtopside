#ifndef _AudioCore_FIR_H
#define _AudioCore_FIR_H


NAMESPACE_AUDIO_BEGIN


class Fir : public Filter {
public:

	Fir();
	Fir( Vector<float>& coefficients );
	~Fir();

	void SetCoefficients( Vector<float>& coefficients, bool ClearState = false );
	
	float GetLastOut() const {
		return last_frame_[0];
	};

	float Tick( float input );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

};

inline float Fir::Tick( float input ) {
	last_frame_[0] = 0.0f;
	inputs_[0] = gain_ * input;

	for ( int i = (int)(b_.GetCount()) - 1; i > 0; i-- ) {
		last_frame_[0] += b_[i] * inputs_[i];
		inputs_[i] = inputs_[i - 1];
	}

	last_frame_[0] += b_[0] * inputs_[0];
	return last_frame_[0];
}

inline AudioFrames& Fir::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Fir::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int i, step = frames.GetChannelCount();

	for ( int j = 0; j < frames.GetFrameCount(); j++, samples += step ) {
		inputs_[0] = gain_ * *samples;
		*samples = 0.0f;

		for ( i = (int)b_.GetCount() - 1; i > 0; i-- ) {
			*samples += b_[i] * inputs_[i];
			inputs_[i] = inputs_[i - 1];
		}

		*samples += b_[0] * inputs_[0];
	}

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& Fir::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("Fir::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[out_channel];
	int i, in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( int j = 0; j < in_frames.GetFrameCount(); j++, in_samples += in_step, out_samples += out_step ) {
		inputs_[0] = gain_ * *in_samples;
		*out_samples = 0.0f;

		for ( i = (int)b_.GetCount() - 1; i > 0; i-- ) {
			*out_samples += b_[i] * inputs_[i];
			inputs_[i] = inputs_[i - 1];
		}

		*out_samples += b_[0] * inputs_[0];
	}

	last_frame_[0] = *(out_samples - out_step);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
