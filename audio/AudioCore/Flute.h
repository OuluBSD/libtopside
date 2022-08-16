#ifndef _AudioCore_FLUTE_H
#define _AudioCore_FLUTE_H


NAMESPACE_AUDIO_BEGIN


class Flute : public Instrument {
public:

	Flute( double lowest_freq = DEFAULT_LOWEST_FREQ);
	~Flute();
	void Clear();
	void SetFrequency( double frequency );
	
	void SetJetReflection( double coefficient ) {
		jetReflection_ = coefficient;
	};

	void SetEndReflection( double coefficient ) {
		end_reflection = coefficient;
	};

	void SetJetDelay( double aRatio );
	void StartBlowing( double amplitude, double rate );
	void StopBlowing( double rate );
	void NoteOn( double frequency, double amplitude );
	void NoteOff( double amplitude );
	void ControlChange( int number, double value );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	DelayL   jet_delay_;
	DelayL   bore_delay_;
	JetTable jet_table_;
	OnePole  filter_;
	PoleZero dc_block_;
	Noise    noise_;
	ADSR     adsr_;
	SineWave vibrato_;

	double last_frequency_;
	double max_pressure_;
	double jetReflection_;
	double end_reflection;
	double noise_gain_;
	double vibrato_gain_;
	double output_gain_;
	double jetRatio_;

};

inline double Flute::Tick( unsigned int ) {
	double pressure_diff;
	double breath_pressure;
	breath_pressure = max_pressure_ * adsr_.Tick();
	breath_pressure += breath_pressure * ( noise_gain_ * noise_.Tick() + vibrato_gain_ * vibrato_.Tick() );
	double temp = -filter_.Tick( bore_delay_.GetLastOut() );
	temp = dc_block_.Tick( temp );
	pressure_diff = breath_pressure - (jetReflection_ * temp);
	pressure_diff = jet_delay_.Tick( pressure_diff );
	pressure_diff = jet_table_.Tick( pressure_diff ) + (end_reflection * temp);
	last_frame_[0] = (double) 0.3 * bore_delay_.Tick( pressure_diff );
	last_frame_[0] *= output_gain_;
	return last_frame_[0];
}

inline AudioFrames& Flute::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Flute::Tick(): channel and AudioFrames arguments are incompatible!");
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
