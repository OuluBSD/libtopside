#ifndef _AudioCore_WHISTLE_H
#define _AudioCore_WHISTLE_H


NAMESPACE_AUDIO_BEGIN


class Whistle : public Instrument {
public:

	Whistle();
	~Whistle();
	void Clear();
	void SetFrequency( float frequency );
	void StartBlowing( float amplitude, float rate );
	void StopBlowing( float rate );
	void NoteOn( float frequency, float amplitude );
	void NoteOff( float amplitude );
	void ControlChange( int number, float value );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	vec3* temp_vector_p_;
	vec3 temp_vector_;
	OnePole onepole_;
	Noise noise_;
	Envelope envelope_;
	Sphere can_;
	Sphere pea_, bumper_;

	SineWave sine_;

	float base_frequency_;
	float noise_gain_;
	float fipple_freq_mod_;
	float fipple_gain_mod_;
	float blow_freq_mod_;
	float tick_size_;
	float can_loss_;
	int sub_sample_, sub_samp_count_;
};

inline AudioFrames& Whistle::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Whistle::Tick(): channel and AudioFrames arguments are incompatible!");
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
