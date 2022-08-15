#ifndef _AudioCore_PRCREV_H
#define _AudioCore_PRCREV_H


NAMESPACE_AUDIO_BEGIN


class PRCRev : public Effect {
public:

	PRCRev( double T60 = 1.0 );

	void Clear();
	void SetT60( double T60 );
	double GetLastOut( unsigned int channel = 0 );
	double Tick( double input, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );

protected:

	Delay    allpass_delays_[2];
	Delay    comb_delays_[2];
	double allpass_coeff_;
	double comb_coeff_[2];

};

inline double PRCRev::GetLastOut( unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("PRCRev::GetLastOut(): channel argument must be less than 2!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[channel];
}

inline double PRCRev::Tick( double input, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("PRCRev::Tick(): channel argument must be less than 2!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double temp, temp0, temp1, temp2, temp3;
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
	temp = (1.0 - effect_mix_) * input;
	last_frame_[0] += temp;
	last_frame_[1] += temp;
	return last_frame_[channel];
}

NAMESPACE_AUDIO_END

#endif
