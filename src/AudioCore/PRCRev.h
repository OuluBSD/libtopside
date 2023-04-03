#ifndef _AudioCore_PRCREV_H
#define _AudioCore_PRCREV_H


NAMESPACE_AUDIO_BEGIN


class PRCRev : public Effect {
public:

	PRCRev( float T60 = 1.0f );

	void Clear() override;
	void SetT60( float T60 );
	float GetLastOut( int channel = 0 );
	float Tick( float input, int channel = 0 ) override;
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

	Delay    allpass_delays_[2];
	Delay    comb_delays_[2];
	float allpass_coeff_;
	float comb_coeff_[2];

};

inline float PRCRev::GetLastOut( int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("PRCRev::GetLastOut(): channel argument must be less than 2!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[channel];
}

inline float PRCRev::Tick( float input, int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("PRCRev::Tick(): channel argument must be less than 2!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float temp, temp0, temp1, temp2, temp3;
	temp = allpass_delays_[0].GetLastOut();
	temp0 = allpass_coeff_ * temp;
	temp0 += input;
	allpass_delays_[0].Tick(temp0);
	temp0 = -(allpass_coeff_ * temp0) + temp;
	temp = allpass_delays_[1].GetLastOut();
	temp1 = allpass_coeff_ * temp;
	temp1 += temp0;
	allpass_delays_[1].Tick(temp1);
	temp1 = -(allpass_coeff_ * temp1) + temp;
	temp2 = temp1 + ( comb_coeff_[0] * comb_delays_[0].GetLastOut() );
	temp3 = temp1 + ( comb_coeff_[1] * comb_delays_[1].GetLastOut() );
	last_frame_[0] = effect_mix_ * (comb_delays_[0].Tick(temp2));
	last_frame_[1] = effect_mix_ * (comb_delays_[1].Tick(temp3));
	temp = (1.0f - effect_mix_) * input;
	last_frame_[0] += temp;
	last_frame_[1] += temp;
	return last_frame_[channel];
}

NAMESPACE_AUDIO_END

#endif
