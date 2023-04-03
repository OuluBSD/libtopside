#ifndef _AudioCore_RESONATE_H
#define _AudioCore_RESONATE_H


NAMESPACE_AUDIO_BEGIN


class Resonate : public Instrument {
public:

	Resonate();
	~Resonate();

	void SetResonance( float frequency, float radius );
	void SetNotch( float frequency, float radius );

	void SetEqualGainZeroes() {
		filter_.SetEqualGainZeroes();
	};

	void KeyOn() {
		adsr_.KeyOn();
	};

	void KeyOff() {
		adsr_.KeyOff();
	};

	void NoteOn( float frequency, float amplitude );
	void NoteOff( float amplitude );
	void ControlChange( int number, float value );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	ADSR     adsr_;
	BiQuad   filter_;
	Noise    noise_;
	float pole_frequency_;
	float pole_radius_;
	float zero_frequency_;
	float zero_radius_;

};

inline float Resonate::Tick( int ) {
	last_frame_[0] = filter_.Tick( noise_.Tick() );
	last_frame_[0] *= adsr_.Tick();
	return last_frame_[0];
}

inline AudioFrames& Resonate::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Resonate::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int j, step = frames.GetChannelCount() - channel_count;

	if ( channel_count == 1 ) {
		for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
			* samples++ = Tick();
	}
	else {
		for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
			*samples++ = Tick();

			for ( j = 1; j < channel_count; j++ )
				*samples++ = last_frame_[j];
		}
	}

	return frames;
}

NAMESPACE_AUDIO_END

#endif
