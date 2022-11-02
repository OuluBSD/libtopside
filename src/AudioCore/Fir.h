#ifndef _AudioCore_FIR_H
#define _AudioCore_FIR_H


NAMESPACE_AUDIO_BEGIN


class Fir : public Filter {
public:

	Fir();
	Fir( Vector<double>& coefficients );
	~Fir();

	void SetCoefficients( Vector<double>& coefficients, bool ClearState = false );
	
	double GetLastOut() const {
		return last_frame_[0];
	};

	double Tick( double input );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

};

inline double Fir::Tick( double input ) {
	last_frame_[0] = 0.0;
	inputs_[0] = gain_ * input;

	for ( unsigned int i = (unsigned int)(b_.GetCount()) - 1; i > 0; i-- ) {
		last_frame_[0] += b_[i] * inputs_[i];
		inputs_[i] = inputs_[i - 1];
	}

	last_frame_[0] += b_[0] * inputs_[0];
	return last_frame_[0];
}

inline AudioFrames& Fir::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Fir::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int i, step = frames.GetChannelCount();

	for ( unsigned int j = 0; j < frames.GetFrameCount(); j++, samples += step ) {
		inputs_[0] = gain_ * *samples;
		*samples = 0.0;

		for ( i = (unsigned int)b_.GetCount() - 1; i > 0; i-- ) {
			*samples += b_[i] * inputs_[i];
			inputs_[i] = inputs_[i - 1];
		}

		*samples += b_[0] * inputs_[0];
	}

	last_frame_[0] = *(samples - step);
	return frames;
}

inline AudioFrames& Fir::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("Fir::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	unsigned int i, in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( unsigned int j = 0; j < in_frames.GetFrameCount(); j++, in_samples += in_step, out_samples += out_step ) {
		inputs_[0] = gain_ * *in_samples;
		*out_samples = 0.0;

		for ( i = (unsigned int)b_.GetCount() - 1; i > 0; i-- ) {
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
