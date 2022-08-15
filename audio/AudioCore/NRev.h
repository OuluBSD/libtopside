#ifndef _AudioCore_NREV_H
#define _AudioCore_NREV_H


NAMESPACE_AUDIO_BEGIN


class NRev : public Effect {
public:

	NRev( double T60 = 1.0 );
	void Clear();
	void SetT60( double T60 );
	double GetLastOut( unsigned int channel = 0 );
	double Tick( double input, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

	Delay allpass_delays_[8];
	Delay comb_delays_[6];
	double allpass_coeff_;
	double comb_coeff_[6];
	double lowpass_state_;

};

inline double NRev::GetLastOut( unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("NRev::GetLastOut(): channel argument must be less than 2!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[channel];
}

inline double NRev::Tick( double input, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("NRev::Tick(): channel argument must be less than 2!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double temp, temp0, temp1, temp2, temp3;
	int i;
	temp0 = 0.0;

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

	lowpass_state_ = 0.7 * lowpass_state_ + 0.3 * temp0;
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
	temp = ( 1.0 - effect_mix_ ) * input;
	last_frame_[0] += temp;
	last_frame_[1] += temp;
	return last_frame_[channel];
}

NAMESPACE_AUDIO_END

#endif

