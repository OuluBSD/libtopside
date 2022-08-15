#ifndef _AudioCore_WHISTLE_H
#define _AudioCore_WHISTLE_H


NAMESPACE_AUDIO_BEGIN


class Whistle : public Instrument {
public:

	Whistle();
	~Whistle();
	void Clear();
	void SetFrequency( double frequency );
	void StartBlowing( double amplitude, double rate );
	void StopBlowing( double rate );
	void NoteOn( double frequency, double amplitude );
	void NoteOff( double amplitude );
	void ControlChange( int number, double value );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	vec3* temp_vector_p_;
	vec3 temp_vector_;
	OnePole onepole_;
	Noise noise_;
	Envelope envelope_;
	Sphere can_;
	Sphere pea_, bumper_;

	SineWave sine_;

	double base_frequency_;
	double noise_gain_;
	double fipple_freq_mod_;
	double fipple_gain_mod_;
	double blow_freq_mod_;
	double tick_size_;
	double can_loss_;
	int sub_sample_, sub_samp_count_;
};

inline AudioFrames& Whistle::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Whistle::Tick(): channel and AudioFrames arguments are incompatible!");
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
