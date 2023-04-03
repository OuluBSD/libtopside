#ifndef _AudioCore_FMVOICES_H
#define _AudioCore_FMVOICES_H


NAMESPACE_AUDIO_BEGIN


class FMVoices : public FM {
public:
	FMVoices();
	~FMVoices();
	void SetFrequency( float frequency );
	void NoteOn( float frequency, float amplitude );
	void ControlChange( int number, float value );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	int currentVowel_;
	float tilt_[3];
	float mods_[3];
};

inline float FMVoices::Tick( int ) {
	float temp, temp2;
	temp = gains_[3] * adsr_[3]->Tick() * waves_[3]->Tick();
	temp2 = vibrato_.Tick() * mod_depth_ * 0.1f;
	waves_[0]->SetFrequency(base_frequency_ * (1.0f + temp2) * ratios_[0]);
	waves_[1]->SetFrequency(base_frequency_ * (1.0f + temp2) * ratios_[1]);
	waves_[2]->SetFrequency(base_frequency_ * (1.0f + temp2) * ratios_[2]);
	waves_[3]->SetFrequency(base_frequency_ * (1.0f + temp2) * ratios_[3]);
	waves_[0]->AddPhaseOffset(temp * mods_[0]);
	waves_[1]->AddPhaseOffset(temp * mods_[1]);
	waves_[2]->AddPhaseOffset(temp * mods_[2]);
	waves_[3]->AddPhaseOffset( twozero_.GetLastOut() );
	twozero_.Tick( temp );
	temp =  gains_[0] * tilt_[0] * adsr_[0]->Tick() * waves_[0]->Tick();
	temp += gains_[1] * tilt_[1] * adsr_[1]->Tick() * waves_[1]->Tick();
	temp += gains_[2] * tilt_[2] * adsr_[2]->Tick() * waves_[2]->Tick();
	last_frame_[0] = temp * 0.33f;
	return last_frame_[0];
}

inline AudioFrames& FMVoices::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("FMVoices::Tick(): channel and AudioFrames arguments are incompatible!");
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
