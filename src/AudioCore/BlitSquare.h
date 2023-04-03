#ifndef _AudioCore_BLITSQUARE_H
#define _AudioCore_BLITSQUARE_H


NAMESPACE_AUDIO_BEGIN


class BlitSquare: public Generator {
public:

	BlitSquare( float frequency = 220.0f );
	~BlitSquare();
	void Reset();
	
	void SetPhase( float phase ) {
		phase_ = PI * phase;
	};

	float GetPhase() const {
		return phase_ / PI;
	};

	void SetFrequency( float frequency );
	void SetHarmonics( int nHarmonics = 0 );

	float GetLastOut() const {
		return last_frame_[0];
	};

	float Tick();
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	void UpdateHarmonics();

	int harmonic_count_;
	int m_;
	float rate_;
	float phase_;
	float p_;
	float a_;
	float last_blit_output_;
	float dcb_state_;
};

inline float BlitSquare::Tick() {
	float temp = last_blit_output_;
	float denominator = sin( phase_ );

	if ( fabs( denominator )  < std::numeric_limits<float>::epsilon() ) {
		if ( phase_ < 0.1f || phase_ > TWO_PI - 0.1f )
			last_blit_output_ = a_;
		else
			last_blit_output_ = -a_;
	}
	else {
		last_blit_output_ =  sin( m_ * phase_ );
		last_blit_output_ /= p_ * denominator;
	}

	last_blit_output_ += temp;
	last_frame_[0] = last_blit_output_ - dcb_state_ + 0.999f * last_frame_[0];
	dcb_state_ = last_blit_output_;
	phase_ += rate_;

	if ( phase_ >= TWO_PI ) phase_ -= TWO_PI;

	return last_frame_[0];
}

inline AudioFrames& BlitSquare::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("BlitSquare::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = BlitSquare::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
