#ifndef _AudioCore_MOOG_H
#define _AudioCore_MOOG_H


NAMESPACE_AUDIO_BEGIN


class Moog : public Sampler {
public:


	Moog();
	~Moog();
	void SetFrequency( double frequency );
	void NoteOn( double frequency, double amplitude );
	
	void SetModulationSpeed( double mod_speed ) {
		loops_[1]->SetFrequency( mod_speed );
	};
	
	void SetModulationDepth( double mod_depth ) {
		mod_depth_ = mod_depth * 0.5;
	};

	void ControlChange( int number, double value );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	FormSwep filters_[2];
	double mod_depth_;
	double filter_q_;
	double filter_rate_;

};

inline double Moog::Tick( unsigned int ) {
	double temp;

	if ( mod_depth_ != 0.0 ) {
		temp = loops_[1]->Tick() * mod_depth_;
		loops_[0]->SetFrequency( base_frequency_ * (1.0 + temp) );
	}

	temp = attackGain_ * attacks_[0]->Tick();
	temp += loop_gain_ * loops_[0]->Tick();
	temp = filter_.Tick( temp );
	temp *= adsr_.Tick();
	temp = filters_[0].Tick( temp );
	last_frame_[0] = filters_[1].Tick( temp );
	return last_frame_[0] * 6.0;
}

inline AudioFrames& Moog::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Moog::Tick(): channel and AudioFrames arguments are incompatible!");
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