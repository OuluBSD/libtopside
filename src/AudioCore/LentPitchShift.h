#ifndef _AudioCore_LENTPITSHIFT_H
#define _AudioCore_LENTPITSHIFT_H


NAMESPACE_AUDIO_BEGIN


class LentPitchShift : public Effect {
public:

	LentPitchShift( float periodRatio = 1.0f, int tMax = RT_BUFFER_SIZE );

	~LentPitchShift() {
		delete window;
		delete dt;
		delete dpt;
		delete cumDt;
	}

	void Clear() override;
	void SetShift( float shift );
	float Tick( float input, int channel = 0 ) override;
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

	void Process();

	AudioFrames inputFrames;
	AudioFrames outputFrames;
	int ptrFrames;
	Delay input_line_;
	int inputPtr;
	Delay outputLine_;
	float outputPtr;
	int tMax_;
	float threshold_;
	int lastPeriod_;
	float* dt;
	float* cumDt;
	float* dpt;
	float env[2];
	float* window;
	float periodRatio_;
	AudioFrames zeroFrame;

};

inline void LentPitchShift::Process() {
	float x_t;
	float x_t_T;
	float coeff;
	int alternativePitch = tMax_;
	lastPeriod_ = tMax_ + 1;
	int delay_;
	int n;

	for ( delay_ = 1; delay_ <= tMax_; delay_++ )
		dt[delay_] = 0.;

	for ( n = 0; n < inputFrames.GetCount(); n++ ) {
		x_t = input_line_.Tick( inputFrames[ n ] );

		for ( delay_ = 1; delay_ <= tMax_; delay_++ ) {
			x_t_T = input_line_.GetTapOut( delay_ );
			coeff = x_t - x_t_T;
			dt[delay_] += coeff * coeff;
		}
	}

	for ( delay_ = 1; delay_ <= tMax_; delay_++ ) {
		cumDt[delay_] = dt[delay_] + cumDt[delay_ - 1];
		dpt[delay_] = dt[delay_] * delay_ / cumDt[delay_];

		if ( dpt[delay_ - 1] - dpt[delay_ - 2] < 0 && dpt[delay_] - dpt[delay_ - 1] > 0 ) {
			if ( dpt[delay_ - 1] < threshold_ ) {
				lastPeriod_ = delay_ - 1;
				break;
			}
			else if ( dpt[alternativePitch] > dpt[delay_ - 1] )
				alternativePitch = delay_ - 1;
		}
	}

	if ( dpt[delay_] - dpt[delay_ - 1] < 0 ) {
		if ( dpt[delay_] < threshold_ )
			lastPeriod_ = delay_;
		else if ( dpt[alternativePitch] > dpt[delay_] )
			alternativePitch = delay_;
	}

	if ( lastPeriod_ == tMax_ + 1 )
		lastPeriod_ = alternativePitch;

	outputLine_.Tick( zeroFrame, outputFrames );

	for ( int n = -(int)lastPeriod_; n < (int)lastPeriod_; n++ )
		window[n + lastPeriod_] = (1 + cos(PI * n / lastPeriod_)) / 2	;

	long M;
	long N;
	float sample;

	for ( ; inputPtr < (int)(tMax_ - lastPeriod_); inputPtr += lastPeriod_ ) {
		while ( outputPtr < inputPtr ) {
			env[1] = fmod( outputPtr + tMax_, 1.0f );
			env[0] = 1.0f - env[1];
			M = tMax_ - inputPtr + lastPeriod_ - 1;
			N = 2 * tMax_ - (int)floor(outputPtr + tMax_) + lastPeriod_ - 1;

			for ( int j = 0; j < 2 * lastPeriod_; j++, M--, N-- ) {
				sample = input_line_.GetTapOut(M) * window[j] / 2.f;
				outputLine_.addTo(env[0] * sample, N);
				outputLine_.addTo(env[1] * sample, N - 1);
			}

			outputPtr = outputPtr + lastPeriod_ * periodRatio_;
		}
	}

	outputPtr -= tMax_;
	inputPtr  -= tMax_;
}


inline float LentPitchShift::Tick( float input, int channel ) {
	float sample;
	inputFrames[ptrFrames] = input;
	sample = outputFrames[ptrFrames++];

	if ( ptrFrames == (int) inputFrames.GetCount() ) {
		ptrFrames = 0;
		Process( );
	}

	return sample;
}

inline AudioFrames& LentPitchShift::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("LentPitchShift::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Tick( *samples );

	return frames;
}

inline AudioFrames& LentPitchShift::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("LentPitchShift::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* in_samples = &in_frames[in_channel];
	float* out_samples = &out_frames[out_channel];
	int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step )
		* out_samples = Tick( *in_samples );

	return in_frames;
}

NAMESPACE_AUDIO_END

#endif

