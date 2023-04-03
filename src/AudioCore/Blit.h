#ifndef _AudioCore_BLIT_H
#define _AudioCore_BLIT_H


NAMESPACE_AUDIO_BEGIN


class Blit: public Generator {
public:

	Blit( float frequency = 220.0f );
	~Blit();
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

};

inline float Blit::Tick() {
	float tmp, denominator = sin( phase_ );

	if ( denominator <= std::numeric_limits<float>::epsilon() )
		tmp = 1.0f;
	else {
		tmp =  sin( m_ * phase_ );
		tmp /= m_ * denominator;
	}

	phase_ += rate_;

	if ( phase_ >= PI ) phase_ -= PI;

	last_frame_[0] = tmp;
	return last_frame_[0];
}

inline AudioFrames& Blit::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Blit::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Blit::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
