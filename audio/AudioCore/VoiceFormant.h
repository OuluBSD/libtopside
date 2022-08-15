#ifndef _AudioCore_VOICFORM_H
#define _AudioCore_VOICFORM_H


NAMESPACE_AUDIO_BEGIN


class VoiceFormant : public Instrument {
public:

	VoiceFormant();
	~VoiceFormant();
	void Clear();
	void SetFrequency( double frequency );
	bool SetPhoneme( const char* phoneme );

	void SetVoiced( double vGain ) {
		voiced_->SetGainTarget(vGain);
	};

	void SetUnVoiced( double nGain ) {
		noise_env_.SetTarget(nGain);
	};

	void SetFilterSweepRate( unsigned int whichOne, double rate );

	void SetPitchSweepRate( double rate ) {
		voiced_->SetSweepRate(rate);
	};

	void Speak() {
		voiced_->NoteOn();
	};

	void Quiet();
	void NoteOn( double frequency, double amplitude );

	void NoteOff( double amplitude ) {
		this->Quiet();
	};

	void ControlChange( int number, double value );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	SingWave* voiced_;
	Noise    noise_;
	Envelope noise_env_;
	FormSwep filters_[4];
	OnePole  onepole_;
	OneZero  onezero_;

};

inline double VoiceFormant::Tick( unsigned int ) {
	double temp;
	temp = onepole_.Tick( onezero_.Tick( voiced_->Tick() ) );
	temp += noise_env_.Tick() * noise_.Tick();
	last_frame_[0] = filters_[0].Tick(temp);
	last_frame_[0] += filters_[1].Tick(temp);
	last_frame_[0] += filters_[2].Tick(temp);
	last_frame_[0] += filters_[3].Tick(temp);
	return last_frame_[0];
}

inline AudioFrames& VoiceFormant::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("VoiceFormant::Tick(): channel and AudioFrames arguments are incompatible!");
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
