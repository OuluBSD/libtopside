#ifndef _AudioCore_FORMSWEP_H
#define _AudioCore_FORMSWEP_H


NAMESPACE_AUDIO_BEGIN


class FormSwep : public Filter {
public:

	FormSwep();
	~FormSwep();

	void IgnoreSampleRateChange( bool ignore = true ) {
		IgnoreSampleRateChange_ = ignore;
	};

	void SetResonance( double frequency, double radius );
	void SetStates( double frequency, double radius, double gain = 1.0 );
	void SetTargets( double frequency, double radius, double gain = 1.0 );
	void SetSweepRate( double rate );
	void SetSweepTime( double time );

	double GetLastOut() const {
		return last_frame_[0];
	};

	double Tick( double input );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

	virtual void SampleRateChanged( double new_rate, double old_rate );

	bool dirty_;
	double frequency_;
	double radius_;
	double StartFrequency_;
	double StartRadius_;
	double StartGain_;
	double targetFrequency_;
	double targetRadius_;
	double targetGain_;
	double deltaFrequency_;
	double deltaRadius_;
	double deltaGain_;
	double sweepState_;
	double sweepRate_;

};

inline double FormSwep::Tick( double input ) {
	if ( dirty_ )  {
		sweepState_ += sweepRate_;

		if ( sweepState_ >= 1.0 )   {
			sweepState_ = 1.0;
			dirty_ = false;
			radius_ = targetRadius_;
			frequency_ = targetFrequency_;
			gain_ = targetGain_;
		}
		else {
			radius_ = StartRadius_ + (deltaRadius_ * sweepState_);
			frequency_ = StartFrequency_ + (deltaFrequency_ * sweepState_);
			gain_ = StartGain_ + (deltaGain_ * sweepState_);
		}

		this->SetResonance( frequency_, radius_ );
	}

	inputs_[0] = gain_ * input;
	last_frame_[0] = b_[0] * inputs_[0] + b_[1] * inputs_[1] + b_[2] * inputs_[2];
	last_frame_[0] -= a_[2] * outputs_[2] + a_[1] * outputs_[1];
	inputs_[2] = inputs_[1];
	inputs_[1] = inputs_[0];
	outputs_[2] = outputs_[1];
	outputs_[1] = last_frame_[0];
	return last_frame_[0];
}

inline AudioFrames& FormSwep::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("FormSwep::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Tick( *samples );

	return frames;
}

inline AudioFrames& FormSwep::Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel, unsigned int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("FormSwep::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* in_samples = &in_frames[in_channel];
	double* out_samples = &out_frames[out_channel];
	unsigned int in_step = in_frames.GetChannelCount(), out_step = out_frames.GetChannelCount();

	for ( unsigned int i = 0; i < in_frames.GetFrameCount(); i++, in_samples += in_step, out_samples += out_step )
		* out_samples = Tick( *in_samples );

	return in_frames;
}

NAMESPACE_AUDIO_END

#endif
