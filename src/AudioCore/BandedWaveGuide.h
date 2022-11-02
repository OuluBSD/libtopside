#ifndef _AudioCore_BANDEDWG_H
#define _AudioCore_BANDEDWG_H


NAMESPACE_AUDIO_BEGIN


const int MAX_BANDED_MODES = 20;

class BandedWaveGuide : public Instrument {
public:

	BandedWaveGuide();
	~BandedWaveGuide();
	void Clear();
	void SetStrikePosition( double position );
	void SetPreset( int preset );
	void SetFrequency( double frequency );
	void StartBowing( double amplitude, double rate );
	void StopBowing( double rate );
	void Pluck( double amp );
	void NoteOn( double frequency, double amplitude );
	void NoteOff( double amplitude );
	void ControlChange( int number, double value );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	bool do_pluck_;
	bool track_velocity_;
	int mode_count_;
	int preset_modes_;
	BowTable bowTable_;
	ADSR     adsr_;
	BiQuad   bandpass_[MAX_BANDED_MODES];
	DelayL   delay_[MAX_BANDED_MODES];
	double max_velocity_;
	double modes_[MAX_BANDED_MODES];
	double frequency_;
	double base_gain_;
	double gains_[MAX_BANDED_MODES];
	double basegains_[MAX_BANDED_MODES];
	double excitation_[MAX_BANDED_MODES];
	double integration_constant_;
	double velocity_input_;
	double bow_velocity_;
	double bow_target_;
	double bow_position_;
	double strikeAmp_;
	int strike_position_;

};

inline AudioFrames& BandedWaveGuide::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("BandedWaveGuide::Tick(): channel and AudioFrames arguments are incompatible!");
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
