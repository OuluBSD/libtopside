#ifndef _AudioCore_FLUTE_H
#define _AudioCore_FLUTE_H


NAMESPACE_AUDIO_BEGIN


class Flute : public Instrument {
public:

	Flute( float lowest_freq = DEFAULT_LOWEST_FREQ);
	~Flute();
	void Clear();
	void SetFrequency( float frequency );
	
	void SetJetReflection( float coefficient ) {
		jetReflection_ = coefficient;
	};

	void SetEndReflection( float coefficient ) {
		end_reflection = coefficient;
	};

	void SetJetDelay( float aRatio );
	void StartBlowing( float amplitude, float rate );
	void StopBlowing( float rate );
	void NoteOn( float frequency, float amplitude );
	void NoteOff( float amplitude );
	void ControlChange( int number, float value );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	DelayL   jet_delay_;
	DelayL   bore_delay_;
	JetTable jet_table_;
	OnePole  filter_;
	PoleZero dc_block_;
	Noise    noise_;
	ADSR     adsr_;
	SineWave vibrato_;

	float last_frequency_;
	float max_pressure_;
	float jetReflection_;
	float end_reflection;
	float noise_gain_;
	float vibrato_gain_;
	float output_gain_;
	float jetRatio_;

};

inline float Flute::Tick( int ) {
	float pressure_diff;
	float breath_pressure;
	breath_pressure = max_pressure_ * adsr_.Tick();
	breath_pressure += breath_pressure * ( noise_gain_ * noise_.Tick() + vibrato_gain_ * vibrato_.Tick() );
	float temp = -filter_.Tick( bore_delay_.GetLastOut() );
	temp = dc_block_.Tick( temp );
	pressure_diff = breath_pressure - (jetReflection_ * temp);
	pressure_diff = jet_delay_.Tick( pressure_diff );
	pressure_diff = jet_table_.Tick( pressure_diff ) + (end_reflection * temp);
	last_frame_[0] = (float) 0.3 * bore_delay_.Tick( pressure_diff );
	last_frame_[0] *= output_gain_;
	return last_frame_[0];
}

inline AudioFrames& Flute::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Flute::Tick(): channel and AudioFrames arguments are incompatible!");
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
