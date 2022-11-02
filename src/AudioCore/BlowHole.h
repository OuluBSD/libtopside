#ifndef _AudioCore_BLOWHOLE_H
#define _AudioCore_BLOWHOLE_H


NAMESPACE_AUDIO_BEGIN





class BlowHole : public Instrument {
public:

	BlowHole( double lowest_freq = DEFAULT_LOWEST_FREQ);
	~BlowHole();
	void Clear();
	void SetFrequency( double frequency );
	void SetTonehole( double newValue );
	void SetVent( double newValue );
	void StartBlowing( double amplitude, double rate );
	void StopBlowing( double rate );
	void NoteOn( double frequency, double amplitude );
	void NoteOff( double amplitude );
	void ControlChange( int number, double value );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	DelayL    delays_[3];
	ReedTable reed_table_;
	OneZero   filter_;
	PoleZero  tonehole_;
	PoleZero  vent_;
	Envelope  envelope_;
	Noise     noise_;
	SineWave  vibrato_;

	double scatter_;
	double th_coeff_;
	double rh_gain_;
	double output_gain_;
	double noise_gain_;
	double vibrato_gain_;
};

inline double BlowHole::Tick( unsigned int ) {
	double pressure_diff;
	double breath_pressure;
	double temp;
	breath_pressure = envelope_.Tick();
	breath_pressure += breath_pressure * noise_gain_ * noise_.Tick();
	breath_pressure += breath_pressure * vibrato_gain_ * vibrato_.Tick();
	pressure_diff = delays_[0].GetLastOut() - breath_pressure;
	double pa = breath_pressure + pressure_diff * reed_table_.Tick( pressure_diff );
	double pb = delays_[1].GetLastOut();
	vent_.Tick( pa + pb );
	last_frame_[0] = delays_[0].Tick( vent_.GetLastOut() + pb );
	last_frame_[0] *= output_gain_;
	pa += vent_.GetLastOut();
	pb = delays_[2].GetLastOut();
	double pth = tonehole_.GetLastOut();
	temp = scatter_ * (pa + pb - 2 * pth);
	delays_[2].Tick( filter_.Tick(pa + temp) * -0.95 );
	delays_[1].Tick( pb + temp );
	tonehole_.Tick( pa + pb - pth + temp );
	return last_frame_[0];
}

inline AudioFrames& BlowHole::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("BlowHole::Tick(): channel and AudioFrames arguments are incompatible!");
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
