#ifndef _AudioCore_BLITSAW_H
#define _AudioCore_BLITSAW_H


NAMESPACE_AUDIO_BEGIN





class BlitSaw: public Generator {
public:

	BlitSaw( float frequency = 220.0f );
	~BlitSaw();
	void Reset();
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
	float C2_;
	float a_;
	float state_;

};

inline float BlitSaw::Tick() {
	float tmp, denominator = sin( phase_ );

	if ( fabs(denominator) <= std::numeric_limits<float>::epsilon() )
		tmp = a_;
	else {
		tmp =  sin( m_ * phase_ );
		tmp /= p_ * denominator;
	}

	tmp += state_ - C2_;
	state_ = tmp * 0.995f;
	phase_ += rate_;

	if ( phase_ >= PI ) phase_ -= PI;

	last_frame_[0] = tmp;
	return last_frame_[0];
}

inline AudioFrames& BlitSaw::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("BlitSaw::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = BlitSaw::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
