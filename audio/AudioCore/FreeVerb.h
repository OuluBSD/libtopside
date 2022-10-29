#ifndef _AudioCore_FREEVERB_H
#define _AudioCore_FREEVERB_H


NAMESPACE_AUDIO_BEGIN


class FreeVerb : public Effect {
public:

	FreeVerb();
	~FreeVerb();
	
	void SetEffectMix( double mix ) override;
	void SetRoomSize( double value );
	double GetRoomSize();
	void SetDamping( double value );
	double GetDamping();
	void SetWidth( double value );
	double GetWidth();
	void SetMode( bool isFrozen );
	double GetMode();
	void Clear() override;
	double GetLastOut( unsigned int channel = 0 );
	double Tick( double inputL, unsigned int channel ) override {return Tick(inputL, 0.0, channel);}
	double Tick( double inputL, double inputR = 0.0, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, unsigned int in_channel = 0, unsigned int out_channel = 0 );
	void LoadState(const ArrayMap<String, Object>& state) override;
	
protected:

	void Refresh();

	static const int nCombs = 8;
	static const int nAllpasses = 4;
	static const int stereoSpread = 23;
	static const double fixedGain;
	static const double scaleWet;
	static const double scaleDry;
	static const double scaleDamp;
	static const double scaleRoom;
	static const double offsetRoom;

	static int cDelayLengths[nCombs];
	static int aDelayLengths[nAllpasses];

	double g_;
	double gain_;
	double roomSizeMem_, roomSize_;
	double dampMem_, damp_;
	double wet1_, wet2_;
	double dry_;
	double width_;
	bool frozenMode_;

	Delay combDelayL_[nCombs];
	Delay combDelayR_[nCombs];
	OnePole combLPL_[nCombs];
	OnePole combLPR_[nCombs];

	Delay allPassDelayL_[nAllpasses];
	Delay allPassDelayR_[nAllpasses];
};

inline double FreeVerb::GetLastOut( unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("FreeVerb::GetLastOut(): channel argument must be less than 2!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[channel];
}

inline double FreeVerb::Tick( double inputL, double inputR, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("FreeVerb::Tick(): channel argument must be less than 2!");
		HandleError(AudioError::FUNCTION_ARGUMENT);
	}

	#endif
	double fInput = (inputL + inputR) * gain_;
	double outL = 0.0;
	double outR = 0.0;

	for ( int i = 0; i < nCombs; i++ ) {
		double yn = fInput + (roomSize_ * combLPL_[i].Tick( combDelayL_[i].GetNextOut() ) );
		combDelayL_[i].Tick(yn);
		outL += yn;
		yn = fInput + (roomSize_ * combLPR_[i].Tick( combDelayR_[i].GetNextOut() ) );
		combDelayR_[i].Tick(yn);
		outR += yn;
	}

	for ( int i = 0; i < nAllpasses; i++ ) {
		double vn_m = allPassDelayL_[i].GetNextOut();
		double vn = outL + (g_ * vn_m);
		allPassDelayL_[i].Tick(vn);
		outL = -vn + (1.0 + g_) * vn_m;
		vn_m = allPassDelayR_[i].GetNextOut();
		vn = outR + (g_ * vn_m);
		allPassDelayR_[i].Tick(vn);
		outR = -vn + (1.0 + g_) * vn_m;
	}

	last_frame_[0] = outL * wet1_ + outR * wet2_ + inputL * dry_;
	last_frame_[1] = outR * wet1_ + outL * wet2_ + inputR * dry_;
	return last_frame_[channel];
}

NAMESPACE_AUDIO_END

#endif
