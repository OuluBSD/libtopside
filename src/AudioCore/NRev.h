#ifndef _AudioCore_NREV_H
#define _AudioCore_NREV_H


NAMESPACE_AUDIO_BEGIN


class NRev : public Effect {
public:

	NRev( float T60 = 1.0f );
	void Clear() override;
	void SetT60( float T60 );
	float GetLastOut( int channel = 0 );
	float Tick( float input, int channel = 0 ) override;
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );

protected:

	Delay allpass_delays_[8];
	Delay comb_delays_[6];
	float allpass_coeff_;
	float comb_coeff_[6];
	float lowpass_state_;

};

inline float NRev::GetLastOut( int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("NRev::GetLastOut(): channel argument must be less than 2!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[channel];
}

inline float NRev::Tick( float input, int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("NRev::Tick(): channel argument must be less than 2!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float temp, temp0, temp1, temp2, temp3;
	int i;
	temp0 = 0.0f;

	for ( i = 0; i < 6; i++ ) {
		temp = input + (comb_coeff_[i] * comb_delays_[i].GetLastOut());
		temp0 += comb_delays_[i].Tick(temp);
	}

	for ( i = 0; i < 3; i++ )	{
		temp = allpass_delays_[i].GetLastOut();
		temp1 = allpass_coeff_ * temp;
		temp1 += temp0;
		allpass_delays_[i].Tick(temp1);
		temp0 = -(allpass_coeff_ * temp1) + temp;
	}

	lowpass_state_ = 0.7f * lowpass_state_ + 0.3f * temp0;
	temp = allpass_delays_[3].GetLastOut();
	temp1 = allpass_coeff_ * temp;
	temp1 += lowpass_state_;
	allpass_delays_[3].Tick( temp1 );
	temp1 = -( allpass_coeff_ * temp1 ) + temp;
	temp = allpass_delays_[4].GetLastOut();
	temp2 = allpass_coeff_ * temp;
	temp2 += temp1;
	allpass_delays_[4].Tick( temp2 );
	last_frame_[0] = effect_mix_ * ( -( allpass_coeff_ * temp2 ) + temp );
	temp = allpass_delays_[5].GetLastOut();
	temp3 = allpass_coeff_ * temp;
	temp3 += temp1;
	allpass_delays_[5].Tick( temp3 );
	last_frame_[1] = effect_mix_ * ( - ( allpass_coeff_ * temp3 ) + temp );
	temp = ( 1.0f - effect_mix_ ) * input;
	last_frame_[0] += temp;
	last_frame_[1] += temp;
	return last_frame_[channel];
}

NAMESPACE_AUDIO_END

#endif

