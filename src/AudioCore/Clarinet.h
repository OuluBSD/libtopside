#ifndef _AudioCore_CLARINET_H
#define _AudioCore_CLARINET_H


NAMESPACE_AUDIO_BEGIN


class Clarinet : public Instrument {
public:

	Clarinet( double lowest_freq = 8.0 );
	~Clarinet();
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

	DelayL delay_line_;
	ReedTable reed_table_;
	OneZero filter_;
	Envelope envelope_;
	Noise noise_;
	SineWave vibrato_;

	double output_gain_;
	double noise_gain_;
	double vibrato_gain_;
};

inline double Clarinet::Tick( unsigned int ) {
	double pressure_diff;
	double breath_pressure;
	breath_pressure = envelope_.Tick();
	breath_pressure += breath_pressure * noise_gain_ * noise_.Tick();
	breath_pressure += breath_pressure * vibrato_gain_ * vibrato_.Tick();
	pressure_diff = -0.95 * filter_.Tick( delay_line_.GetLastOut() );
	pressure_diff = pressure_diff - breath_pressure;
	last_frame_[0] = delay_line_.Tick(breath_pressure + pressure_diff * reed_table_.Tick(pressure_diff));
	last_frame_[0] *= output_gain_;
	return last_frame_[0];
}

inline AudioFrames& Clarinet::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Clarinet::Tick(): channel and AudioFrames arguments are incompatible!");
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
