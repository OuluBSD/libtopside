#ifndef _AudioCore_BLITSQUARE_H
#define _AudioCore_BLITSQUARE_H


NAMESPACE_AUDIO_BEGIN


class BlitSquare: public Generator {
public:

	BlitSquare( double frequency = 220.0 );
	~BlitSquare();
	void Reset();
	
	void SetPhase( double phase ) {
		phase_ = PI * phase;
	};

	double GetPhase() const {
		return phase_ / PI;
	};

	void SetFrequency( double frequency );
	void SetHarmonics( unsigned int nHarmonics = 0 );

	double GetLastOut() const {
		return last_frame_[0];
	};

	double Tick();
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	void UpdateHarmonics();

	unsigned int harmonic_count_;
	unsigned int m_;
	double rate_;
	double phase_;
	double p_;
	double a_;
	double last_blit_output_;
	double dcb_state_;
};

inline double BlitSquare::Tick() {
	double temp = last_blit_output_;
	double denominator = sin( phase_ );

	if ( fabs( denominator )  < std::numeric_limits<double>::epsilon() ) {
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
	last_frame_[0] = last_blit_output_ - dcb_state_ + 0.999 * last_frame_[0];
	dcb_state_ = last_blit_output_;
	phase_ += rate_;

	if ( phase_ >= TWO_PI ) phase_ -= TWO_PI;

	return last_frame_[0];
}

inline AudioFrames& BlitSquare::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("BlitSquare::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = BlitSquare::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
