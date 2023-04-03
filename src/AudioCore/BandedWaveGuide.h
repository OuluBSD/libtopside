#ifndef _AudioCore_BANDEDWG_H
#define _AudioCore_BANDEDWG_H


NAMESPACE_AUDIO_BEGIN


const int MAX_BANDED_MODES = 20;

class BandedWaveGuide : public Instrument {
public:

	BandedWaveGuide();
	~BandedWaveGuide();
	void Clear();
	void SetStrikePosition( float position );
	void SetPreset( int preset );
	void SetFrequency( float frequency );
	void StartBowing( float amplitude, float rate );
	void StopBowing( float rate );
	void Pluck( float amp );
	void NoteOn( float frequency, float amplitude );
	void NoteOff( float amplitude );
	void ControlChange( int number, float value );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	bool do_pluck_;
	bool track_velocity_;
	int mode_count_;
	int preset_modes_;
	BowTable bowTable_;
	ADSR     adsr_;
	BiQuad   bandpass_[MAX_BANDED_MODES];
	DelayL   delay_[MAX_BANDED_MODES];
	float max_velocity_;
	float modes_[MAX_BANDED_MODES];
	float frequency_;
	float base_gain_;
	float gains_[MAX_BANDED_MODES];
	float basegains_[MAX_BANDED_MODES];
	float excitation_[MAX_BANDED_MODES];
	float integration_constant_;
	float velocity_input_;
	float bow_velocity_;
	float bow_target_;
	float bow_position_;
	float strikeAmp_;
	int strike_position_;

};

inline AudioFrames& BandedWaveGuide::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("BandedWaveGuide::Tick(): channel and AudioFrames arguments are incompatible!");
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
