#ifndef _AudioCore_BLOWBOTL_H
#define _AudioCore_BLOWBOTL_H


NAMESPACE_AUDIO_BEGIN


class BlowBottle : public Instrument {
public:

	BlowBottle();
	~BlowBottle();
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

	JetTable jet_table_;
	BiQuad resonator_;
	PoleZero dc_block_;
	Noise noise_;
	ADSR adsr_;
	SineWave vibrato_;
	double max_pressure_;
	double noise_gain_;
	double vibrato_gain_;
	double output_gain_;

};

inline double BlowBottle::Tick( unsigned int ) {
	double breath_pressure;
	double randPressure;
	double pressure_diff;
	breath_pressure = max_pressure_ * adsr_.Tick();
	breath_pressure += vibrato_gain_ * vibrato_.Tick();
	pressure_diff = breath_pressure - resonator_.GetLastOut();
	randPressure = noise_gain_ * noise_.Tick();
	randPressure *= breath_pressure;
	randPressure *= (1.0 + pressure_diff);
	resonator_.Tick( breath_pressure + randPressure - ( jet_table_.Tick( pressure_diff ) * pressure_diff ) );
	last_frame_[0] = 0.2 * output_gain_ * dc_block_.Tick( pressure_diff );
	return last_frame_[0];
}

inline AudioFrames& BlowBottle::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("BlowBottle::Tick(): channel and AudioFrames arguments are incompatible!");
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
