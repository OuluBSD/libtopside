#ifndef _AudioCore_EFFECT_H
#define _AudioCore_EFFECT_H


NAMESPACE_AUDIO_BEGIN


class Effect : public Audio {
public:

	Effect() {
		last_frame_.SetCount( 1, 1, 0.0 );
	};

	unsigned int GetChannelsOut() const {
		return last_frame_.GetChannelCount();
	};

	const AudioFrames& GetLastFrame() const {
		return last_frame_;
	};

	virtual void Clear() = 0;
	virtual void SetEffectMix( double mix );
	
	virtual double Tick( double input, unsigned int channel ) = 0;
	
protected:

	bool IsPrime( unsigned int number );

	AudioFrames last_frame_;
	double effect_mix_;

};

inline void Effect::SetEffectMix( double mix ) {
	if ( mix < 0.0 ) {
		LOG("Effect::SetEffectMix: mix parameter is less than zero ... Setting to zero!");
		HandleError( AudioError::WARNING );
		effect_mix_ = 0.0;
	}
	else if ( mix > 1.0 ) {
		LOG("Effect::SetEffectMix: mix parameter is greater than 1.0 ... Setting to one!");
		HandleError( AudioError::WARNING );
		effect_mix_ = 1.0;
	}
	else
		effect_mix_ = mix;
}

inline bool Effect::IsPrime( unsigned int number ) {
	if ( number == 2 ) return true;

	if ( number & 1 ) {
		for ( int i = 3; i < (int)sqrt((double)number) + 1; i += 2 )
			if ( (number % i) == 0 ) return false;

		return true;
	}
	else return false;
}

NAMESPACE_AUDIO_END

#endif

