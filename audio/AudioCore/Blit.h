#ifndef _AudioCore_BLIT_H
#define _AudioCore_BLIT_H


NAMESPACE_AUDIO_BEGIN


class Blit: public Generator {
public:

	Blit( double frequency = 220.0 );
	~Blit();
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

};

inline double Blit::Tick() {
	double tmp, denominator = sin( phase_ );

	if ( denominator <= std::numeric_limits<double>::epsilon() )
		tmp = 1.0;
	else {
		tmp =  sin( m_ * phase_ );
		tmp /= m_ * denominator;
	}

	phase_ += rate_;

	if ( phase_ >= PI ) phase_ -= PI;

	last_frame_[0] = tmp;
	return last_frame_[0];
}

inline AudioFrames& Blit::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Blit::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Blit::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
