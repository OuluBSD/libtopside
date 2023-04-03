#ifndef _AudioCore_BLOWHOLE_H
#define _AudioCore_BLOWHOLE_H


NAMESPACE_AUDIO_BEGIN





class BlowHole : public Instrument {
public:

	BlowHole( float lowest_freq = DEFAULT_LOWEST_FREQ);
	~BlowHole();
	void Clear();
	void SetFrequency( float frequency );
	void SetTonehole( float newValue );
	void SetVent( float newValue );
	void StartBlowing( float amplitude, float rate );
	void StopBlowing( float rate );
	void NoteOn( float frequency, float amplitude );
	void NoteOff( float amplitude );
	void ControlChange( int number, float value );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	DelayL    delays_[3];
	ReedTable reed_table_;
	OneZero   filter_;
	PoleZero  tonehole_;
	PoleZero  vent_;
	Envelope  envelope_;
	Noise     noise_;
	SineWave  vibrato_;

	float scatter_;
	float th_coeff_;
	float rh_gain_;
	float output_gain_;
	float noise_gain_;
	float vibrato_gain_;
};

inline float BlowHole::Tick( int ) {
	float pressure_diff;
	float breath_pressure;
	float temp;
	breath_pressure = envelope_.Tick();
	breath_pressure += breath_pressure * noise_gain_ * noise_.Tick();
	breath_pressure += breath_pressure * vibrato_gain_ * vibrato_.Tick();
	pressure_diff = delays_[0].GetLastOut() - breath_pressure;
	float pa = breath_pressure + pressure_diff * reed_table_.Tick( pressure_diff );
	float pb = delays_[1].GetLastOut();
	vent_.Tick( pa + pb );
	last_frame_[0] = delays_[0].Tick( vent_.GetLastOut() + pb );
	last_frame_[0] *= output_gain_;
	pa += vent_.GetLastOut();
	pb = delays_[2].GetLastOut();
	float pth = tonehole_.GetLastOut();
	temp = scatter_ * (pa + pb - 2 * pth);
	delays_[2].Tick( filter_.Tick(pa + temp) * -0.95f );
	delays_[1].Tick( pb + temp );
	tonehole_.Tick( pa + pb - pth + temp );
	return last_frame_[0];
}

inline AudioFrames& BlowHole::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("BlowHole::Tick(): channel and AudioFrames arguments are incompatible!");
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
