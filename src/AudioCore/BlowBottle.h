#ifndef _AudioCore_BLOWBOTL_H
#define _AudioCore_BLOWBOTL_H


NAMESPACE_AUDIO_BEGIN


class BlowBottle : public Instrument {
public:

	BlowBottle();
	~BlowBottle();
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

	JetTable jet_table_;
	BiQuad resonator_;
	PoleZero dc_block_;
	Noise noise_;
	ADSR adsr_;
	SineWave vibrato_;
	float max_pressure_;
	float noise_gain_;
	float vibrato_gain_;
	float output_gain_;

};

inline float BlowBottle::Tick( int ) {
	float breath_pressure;
	float randPressure;
	float pressure_diff;
	breath_pressure = max_pressure_ * adsr_.Tick();
	breath_pressure += vibrato_gain_ * vibrato_.Tick();
	pressure_diff = breath_pressure - resonator_.GetLastOut();
	randPressure = noise_gain_ * noise_.Tick();
	randPressure *= breath_pressure;
	randPressure *= (1.0f + pressure_diff);
	resonator_.Tick( breath_pressure + randPressure - ( jet_table_.Tick( pressure_diff ) * pressure_diff ) );
	last_frame_[0] = 0.2f * output_gain_ * dc_block_.Tick( pressure_diff );
	return last_frame_[0];
}

inline AudioFrames& BlowBottle::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("BlowBottle::Tick(): channel and AudioFrames arguments are incompatible!");
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
