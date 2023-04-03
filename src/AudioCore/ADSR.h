#ifndef _AudioCore_ADSR_H
#define _AudioCore_ADSR_H


NAMESPACE_AUDIO_BEGIN


class ADSR : public Generator {
public:


	enum {
		ATTACK,
		DECAY,
		SUSTAIN,
		RELEASE,
		IDLE
	};


	ADSR();
	~ADSR();
	void KeyOn();
	void KeyOff();
	void SetAttackRate( float rate );
	void SetAttackTarget( float target );
	void SetDecayRate( float rate );
	void SetSustainLevel( float level );
	void SetReleaseRate( float rate );
	void SetAttackTime( float time );
	void SetDecayTime( float time );
	void SetReleaseTime( float time );
	void SetAllTimes( float aTime, float dTime, float sLevel, float rTime );
	void SetTarget( float target );
	
	int GetState() const {
		return state_;
	};

	void SetValue( float value );

	float GetLastOut() const {
		return last_frame_[0];
	};

	float Tick();
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	void SampleRateChanged( float new_rate, float old_rate );

	int state_;
	float value_;
	float target_;
	float attack_rate_;
	float decay_rate_;
	float release_rate_;
	float release_time_;
	float sustain_level_;
};

inline float ADSR::Tick() {
	switch ( state_ ) {
	case ATTACK:
		value_ += attack_rate_;

		if ( value_ >= target_ ) {
			value_ = target_;
			target_ = sustain_level_;
			state_ = DECAY;
		}

		last_frame_[0] = value_;
		break;

	case DECAY:
		if ( value_ > sustain_level_ ) {
			value_ -= decay_rate_;

			if ( value_ <= sustain_level_ ) {
				value_ = sustain_level_;
				state_ = SUSTAIN;
			}
		}
		else {
			value_ += decay_rate_;

			if ( value_ >= sustain_level_ ) {
				value_ = sustain_level_;
				state_ = SUSTAIN;
			}
		}

		last_frame_[0] = value_;
		break;

	case RELEASE:
		value_ -= release_rate_;

		if ( value_ <= 0.0f ) {
			value_ = 0.0f;
			state_ = IDLE;
		}

		last_frame_[0] = value_;
	}

	return value_;
}

inline AudioFrames& ADSR::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("ADSR::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = ADSR::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
