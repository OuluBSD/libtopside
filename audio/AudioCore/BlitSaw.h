#ifndef _AudioCore_BLITSAW_H
#define _AudioCore_BLITSAW_H


NAMESPACE_AUDIO_BEGIN





class BlitSaw: public Generator {
public:

	BlitSaw( double frequency = 220.0 );
	~BlitSaw();
	void Reset();
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
	double C2_;
	double a_;
	double state_;

};

inline double BlitSaw::Tick() {
	double tmp, denominator = sin( phase_ );

	if ( fabs(denominator) <= std::numeric_limits<double>::epsilon() )
		tmp = a_;
	else {
		tmp =  sin( m_ * phase_ );
		tmp /= p_ * denominator;
	}

	tmp += state_ - C2_;
	state_ = tmp * 0.995;
	phase_ += rate_;

	if ( phase_ >= PI ) phase_ -= PI;

	last_frame_[0] = tmp;
	return last_frame_[0];
}

inline AudioFrames& BlitSaw::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("BlitSaw::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = BlitSaw::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
