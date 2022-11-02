#ifndef _AudioCore_RESONATE_H
#define _AudioCore_RESONATE_H


NAMESPACE_AUDIO_BEGIN


class Resonate : public Instrument {
public:

	Resonate();
	~Resonate();

	void SetResonance( double frequency, double radius );
	void SetNotch( double frequency, double radius );

	void SetEqualGainZeroes() {
		filter_.SetEqualGainZeroes();
	};

	void KeyOn() {
		adsr_.KeyOn();
	};

	void KeyOff() {
		adsr_.KeyOff();
	};

	void NoteOn( double frequency, double amplitude );
	void NoteOff( double amplitude );
	void ControlChange( int number, double value );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	ADSR     adsr_;
	BiQuad   filter_;
	Noise    noise_;
	double pole_frequency_;
	double pole_radius_;
	double zero_frequency_;
	double zero_radius_;

};

inline double Resonate::Tick( unsigned int ) {
	last_frame_[0] = filter_.Tick( noise_.Tick() );
	last_frame_[0] *= adsr_.Tick();
	return last_frame_[0];
}

inline AudioFrames& Resonate::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Resonate::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int j, step = frames.GetChannelCount() - channel_count;

	if ( channel_count == 1 ) {
		for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
			* samples++ = Tick();
	}
	else {
		for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
			*samples++ = Tick();

			for ( j = 1; j < channel_count; j++ )
				*samples++ = last_frame_[j];
		}
	}

	return frames;
}

NAMESPACE_AUDIO_END

#endif
