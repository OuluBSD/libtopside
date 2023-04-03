#ifndef _AudioCore_PERCFLUT_H
#define _AudioCore_PERCFLUT_H


NAMESPACE_AUDIO_BEGIN


class PercFlut : public FM {
public:

	PercFlut();
	~PercFlut();
	void SetFrequency( float frequency );
	void NoteOn( float frequency, float amplitude );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

};

inline float PercFlut::Tick( int ) {
	float temp;
	temp = vibrato_.Tick() * mod_depth_ * 0.2f;
	waves_[0]->SetFrequency(base_frequency_ * (1.0f + temp) * ratios_[0]);
	waves_[1]->SetFrequency(base_frequency_ * (1.0f + temp) * ratios_[1]);
	waves_[2]->SetFrequency(base_frequency_ * (1.0f + temp) * ratios_[2]);
	waves_[3]->SetFrequency(base_frequency_ * (1.0f + temp) * ratios_[3]);
	waves_[3]->AddPhaseOffset( twozero_.GetLastOut() );
	temp = gains_[3] * adsr_[3]->Tick() * waves_[3]->Tick();
	twozero_.Tick(temp);
	waves_[2]->AddPhaseOffset( temp );
	temp = (1.0f - (control2_ * 0.5f)) * gains_[2] * adsr_[2]->Tick() * waves_[2]->Tick();
	temp += control2_ * 0.5f * gains_[1] * adsr_[1]->Tick() * waves_[1]->Tick();
	temp = temp * control1_;
	waves_[0]->AddPhaseOffset(temp);
	temp = gains_[0] * adsr_[0]->Tick() * waves_[0]->Tick();
	last_frame_[0] = temp * 0.5f;
	return last_frame_[0];
}

inline AudioFrames& PercFlut::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("PercFlut::Tick(): channel and AudioFrames arguments are incompatible!");
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
