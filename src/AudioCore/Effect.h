#ifndef _AudioCore_EFFECT_H
#define _AudioCore_EFFECT_H


NAMESPACE_AUDIO_BEGIN


class Effect : public Audio {
public:

	Effect() {
		last_frame_.SetCount( 1, 1, 0.0f );
	};

	int GetChannelsOut() const {
		return last_frame_.GetChannelCount();
	};

	const AudioFrames& GetLastFrame() const {
		return last_frame_;
	};

	virtual void Clear() = 0;
	virtual void SetEffectMix( float mix );
	
	virtual float Tick( float input, int channel ) = 0;
	virtual float Tick2( float input1, float input2, int channel ) {Panic("not implemented"); return 0;}
	virtual void LoadState(const ArrayMap<String, Object>& state) {}
	
protected:

	bool IsPrime( int number );

	AudioFrames last_frame_;
	float effect_mix_;

};

inline void Effect::SetEffectMix( float mix ) {
	if ( mix < 0.0f ) {
		LOG("Effect::SetEffectMix: mix parameter is less than zero ... Setting to zero!");
		HandleError( AudioError::WARNING );
		effect_mix_ = 0.0f;
	}
	else if ( mix > 1.0f ) {
		LOG("Effect::SetEffectMix: mix parameter is greater than 1.0f ... Setting to one!");
		HandleError( AudioError::WARNING );
		effect_mix_ = 1.0f;
	}
	else
		effect_mix_ = mix;
}

inline bool Effect::IsPrime( int number ) {
	if ( number == 2 ) return true;

	if ( number & 1 ) {
		for ( int i = 3; i < (int)sqrt((float)number) + 1; i += 2 )
			if ( (number % i) == 0 ) return false;

		return true;
	}
	else return false;
}

NAMESPACE_AUDIO_END

#endif

