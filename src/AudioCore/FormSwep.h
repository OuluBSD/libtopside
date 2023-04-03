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

	void SetResonance( float frequency, float radius );
	void SetStates( float frequency, float radius, float gain = 1.0f );
	void SetTargets( float frequency, float radius, float gain = 1.0f );
	void SetSweepRate( float rate );
	void SetSweepTime( float time );

	float GetLastOut() const {
		return last_frame_[0];
	};

	float Tick( float input );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

	virtual void SampleRateChanged( float new_rate, float old_rate );

	bool dirty_;
	float frequency_;
	float radius_;
	float StartFrequency_;
	float StartRadius_;
	float StartGain_;
	float targetFrequency_;
	float targetRadius_;
	float targetGain_;
	float deltaFrequency_;
	float deltaRadius_;
	float deltaGain_;
	float sweepState_;
	float sweepRate_;

};

inline float FormSwep::Tick( float input ) {
	if ( dirty_ )  {
		sweepState_ += sweepRate_;

		if ( sweepState_ >= 1.0f )   {
			sweepState_ = 1.0f;
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

inline AudioFrames& FormSwep::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("FormSwep::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Tick( *samples );

	return frames;
}

inline AudioFrames& FormSwep::Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel, int out_channel ) {
	#if defined(flagDEBUG)

	if ( in_channel >= in_frames.GetChannelCount() || out_channel >= out_frames.GetChannelCount() ) {
		LOG("FormSwep::Tick(): channel and AudioFrames arguments are incompatible!");
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
