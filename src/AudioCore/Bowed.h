#ifndef _AudioCore_BOWED_H
#define _AudioCore_BOWED_H


NAMESPACE_AUDIO_BEGIN


class Bowed : public Instrument {
public:

	Bowed( double lowest_freq = 8.0 );
	~Bowed();
	void Clear();
	void SetFrequency( double frequency );

	void SetVibrato( double gain ) {
		vibrato_gain_ = gain;
	};

	void StartBowing( double amplitude, double rate );
	void StopBowing( double rate );
	void NoteOn( double frequency, double amplitude );
	void NoteOff( double amplitude );
	void ControlChange( int number, double value );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	DelayL   neck_delay_;
	DelayL   bridge_delay_;
	BowTable bowTable_;
	OnePole  string_filter_;
	BiQuad   body_filters_[6];
	SineWave vibrato_;
	ADSR     adsr_;

	bool     bow_down_;
	double max_velocity_;
	double base_delay_;
	double vibrato_gain_;
	double betaRatio_;

};

inline double Bowed::Tick( unsigned int ) {
	double bow_velocity = max_velocity_ * adsr_.Tick();
	double bridge_reflection = -string_filter_.Tick( bridge_delay_.GetLastOut() );
	double nut_reflection = -neck_delay_.GetLastOut();
	double string_velocity = bridge_reflection + nut_reflection;
	double delta_v = bow_velocity - string_velocity;
	double new_velocity = 0.0;

	if ( bow_down_ )
		new_velocity = delta_v * bowTable_.Tick( delta_v );

	neck_delay_.Tick( bridge_reflection + new_velocity);
	bridge_delay_.Tick(nut_reflection + new_velocity);

	if ( vibrato_gain_ > 0.0 )  {
		neck_delay_.SetDelay( (base_delay_ * (1.0 - betaRatio_) ) +
							 (base_delay_ * vibrato_gain_ * vibrato_.Tick()) );
	}

	last_frame_[0] = 0.1248 * body_filters_[5].Tick( body_filters_[4].Tick( body_filters_[3].Tick( body_filters_[2].Tick( body_filters_[1].Tick( body_filters_[0].Tick( bridge_delay_.GetLastOut() ) ) ) ) ) );
	return last_frame_[0];
}

inline AudioFrames& Bowed::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Bowed::Tick(): channel and AudioFrames arguments are incompatible!");
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
