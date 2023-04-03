#ifndef _AudioCore_IIR_H
#define AUDIO_IIR_H


NAMESPACE_AUDIO_BEGIN


class Iir : public Filter {
public:

	Iir();
	Iir( Vector<float>& bCoefficients, Vector<float>& aCoefficients );
	~Iir();
	void SetCoefficients( Vector<float>& bCoefficients, Vector<float>& aCoefficients, bool ClearState = false );
	void SetNumerator( Vector<float>& bCoefficients, bool ClearState = false );
	void SetDenominator( Vector<float>& aCoefficients, bool ClearState = false );

	float GetLastOut() const {
		return last_frame_[0];
	};

	float Tick( float input );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

};

inline float Iir::Tick( float input ) {
	int i;
	outputs_[0] = 0.0f;
	inputs_[0] = gain_ * input;

	for ( i = b_.GetCount() - 1; i > 0; i-- ) {
		outputs_[0] += b_[i] * inputs_[i];
		inputs_[i] = inputs_[i - 1];
	}

	outputs_[0] += b_[0] * inputs_[0];

	for ( i = a_.GetCount() - 1; i > 0; i-- ) {
		outputs_[0] += -a_[i] * outputs_[i];
		outputs_[i] = outputs_[i - 1];
	}

	last_frame_[0] = outputs_[0];
	return last_frame_[0];
}

inline AudioFrames& Iir::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Iir::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int i;
	int step = frames.GetChannelCount();

	for ( int j = 0; j < frames.GetFrameCount(); j++, samples += step ) {
		outputs_[0] = 0.0f;
		inputs_[0] = gain_ * *samples;

		for ( i = b_.GetCount() - 1; i > 0; i-- ) {
			outputs_[0] += b_[i] * inputs_[i];
			inputs_[i] = inputs_[i - 1];
		}

		outputs_[0] += b_[0] * inputs_[0];

		for ( i = a_.GetCount() - 1; i > 0; i-- ) {
			outputs_[0] += -a_[i] * outputs_[i];
			outputs_[i] = outputs_[i - 1];
		}

		*samples = outputs_[0];
	}

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& Iir::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("Iir::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[out_channel];
	int i;
	int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( int j = 0; j < in_frames.GetFrameCount(); j++, in_samples += in_step, out_samples += out_step ) {
		outputs_[0] = 0.0f;
		inputs_[0] = gain_ * *in_samples;

		for ( i = b_.GetCount() - 1; i > 0; i-- ) {
			outputs_[0] += b_[i] * inputs_[i];
			inputs_[i] = inputs_[i - 1];
		}

		outputs_[0] += b_[0] * inputs_[0];

		for ( i = a_.GetCount() - 1; i > 0; i-- ) {
			outputs_[0] += -a_[i] * outputs_[i];
			outputs_[i] = outputs_[i - 1];
		}

		*out_samples = outputs_[0];
	}

	last_frame_[0] = *(out_samples - out_step);
	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
