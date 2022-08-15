#ifndef _AudioCore_IIR_H
#define AUDIO_IIR_H


NAMESPACE_AUDIO_BEGIN


class Iir : public Filter {
public:

	Iir();
	Iir( Vector<double>& bCoefficients, Vector<double>& aCoefficients );
	~Iir();
	void SetCoefficients( Vector<double>& bCoefficients, Vector<double>& aCoefficients, bool ClearState = false );
	void SetNumerator( Vector<double>& bCoefficients, bool ClearState = false );
	void SetDenominator( Vector<double>& aCoefficients, bool ClearState = false );

	double GetLastOut() const {
		return last_frame_[0];
	};

	double Tick( double input );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

};

inline double Iir::Tick( double input ) {
	size_t i;
	outputs_[0] = 0.0;
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

inline AudioFrames& Iir::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Iir::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	size_t i;
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int j = 0; j < frames.GetFrameCount(); j++, samples += step ) {
		outputs_[0] = 0.0;
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

inline AudioFrames& Iir::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("Iir::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	size_t i;
	unsigned int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( unsigned int j = 0; j < in_frames.GetFrameCount(); j++, in_samples += in_step, out_samples += out_step ) {
		outputs_[0] = 0.0;
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
