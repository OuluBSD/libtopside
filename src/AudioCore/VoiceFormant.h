#ifndef _AudioCore_VOICFORM_H
#define _AudioCore_VOICFORM_H


NAMESPACE_AUDIO_BEGIN


class VoiceFormant : public Instrument {
public:

	VoiceFormant();
	~VoiceFormant();
	void Clear();
	void SetFrequency( float frequency );
	bool SetPhoneme( const char* phoneme );

	void SetVoiced( float vGain ) {
		voiced_->SetGainTarget(vGain);
	};

	void SetUnVoiced( float nGain ) {
		noise_env_.SetTarget(nGain);
	};

	void SetFilterSweepRate( int whichOne, float rate );

	void SetPitchSweepRate( float rate ) {
		voiced_->SetSweepRate(rate);
	};

	void Speak() {
		voiced_->NoteOn();
	};

	void Quiet();
	void NoteOn( float frequency, float amplitude );

	void NoteOff( float amplitude ) {
		this->Quiet();
	};

	void ControlChange( int number, float value );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	SingWave* voiced_;
	Noise    noise_;
	Envelope noise_env_;
	FormSwep filters_[4];
	OnePole  onepole_;
	OneZero  onezero_;

};

inline float VoiceFormant::Tick( int ) {
	float temp;
	temp = onepole_.Tick( onezero_.Tick( voiced_->Tick() ) );
	temp += noise_env_.Tick() * noise_.Tick();
	last_frame_[0] = filters_[0].Tick(temp);
	last_frame_[0] += filters_[1].Tick(temp);
	last_frame_[0] += filters_[2].Tick(temp);
	last_frame_[0] += filters_[3].Tick(temp);
	return last_frame_[0];
}

inline AudioFrames& VoiceFormant::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("VoiceFormant::Tick(): channel and AudioFrames arguments are incompatible!");
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
