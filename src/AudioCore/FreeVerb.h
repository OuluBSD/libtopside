#ifndef _AudioCore_FREEVERB_H
#define _AudioCore_FREEVERB_H


NAMESPACE_AUDIO_BEGIN


class FreeVerb : public Effect {
public:

	FreeVerb();
	~FreeVerb();
	
	void SetEffectMix( float mix ) override;
	void SetRoomSize( float value );
	float GetRoomSize();
	void SetDamping( float value );
	float GetDamping();
	void SetWidth( float value );
	float GetWidth();
	void SetMode( bool isFrozen );
	float GetMode();
	void Clear() override;
	float GetLastOut( int channel = 0 );
	float Tick( float inputL, int channel ) override {return Tick(inputL, 0.0f, channel);}
	float Tick( float inputL, float inputR = 0.0f, int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );
	AudioFrames& Tick( AudioFrames& in_frames, AudioFrames& out_frames, int in_channel = 0, int out_channel = 0 );
	void LoadState(const ArrayMap<String, Object>& state) override;
	
protected:

	void Refresh();

	static const int nCombs = 8;
	static const int nAllpasses = 4;
	static const int stereoSpread = 23;
	static const float fixedGain;
	static const float scaleWet;
	static const float scaleDry;
	static const float scaleDamp;
	static const float scaleRoom;
	static const float offsetRoom;

	static int cDelayLengths[nCombs];
	static int aDelayLengths[nAllpasses];

	float g_;
	float gain_;
	float roomSizeMem_, roomSize_;
	float dampMem_, damp_;
	float wet1_, wet2_;
	float dry_;
	float width_;
	bool frozenMode_;

	Delay combDelayL_[nCombs];
	Delay combDelayR_[nCombs];
	OnePole combLPL_[nCombs];
	OnePole combLPR_[nCombs];

	Delay allPassDelayL_[nAllpasses];
	Delay allPassDelayR_[nAllpasses];
};

inline float FreeVerb::GetLastOut( int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("FreeVerb::GetLastOut(): channel argument must be less than 2!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	return last_frame_[channel];
}

inline float FreeVerb::Tick( float inputL, float inputR, int channel ) {
	#if defined(flagDEBUG)

	if ( channel > 1 ) {
		LOG("FreeVerb::Tick(): channel argument must be less than 2!");
		HandleError(AudioError::FUNCTION_ARGUMENT);
	}

	#endif
	float fInput = (inputL + inputR) * gain_;
	float outL = 0.0f;
	float outR = 0.0f;

	for ( int i = 0; i < nCombs; i++ ) {
		float yn = fInput + (roomSize_ * combLPL_[i].Tick( combDelayL_[i].GetNextOut() ) );
		combDelayL_[i].Tick(yn);
		outL += yn;
		yn = fInput + (roomSize_ * combLPR_[i].Tick( combDelayR_[i].GetNextOut() ) );
		combDelayR_[i].Tick(yn);
		outR += yn;
	}

	for ( int i = 0; i < nAllpasses; i++ ) {
		float vn_m = allPassDelayL_[i].GetNextOut();
		float vn = outL + (g_ * vn_m);
		allPassDelayL_[i].Tick(vn);
		outL = -vn + (1.0f + g_) * vn_m;
		vn_m = allPassDelayR_[i].GetNextOut();
		vn = outR + (g_ * vn_m);
		allPassDelayR_[i].Tick(vn);
		outR = -vn + (1.0f + g_) * vn_m;
	}

	last_frame_[0] = outL * wet1_ + outR * wet2_ + inputL * dry_;
	last_frame_[1] = outR * wet1_ + outL * wet2_ + inputR * dry_;
	return last_frame_[channel];
}

NAMESPACE_AUDIO_END

#endif
