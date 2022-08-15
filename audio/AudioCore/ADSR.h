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
	void SetAttackRate( double rate );
	void SetAttackTarget( double target );
	void SetDecayRate( double rate );
	void SetSustainLevel( double level );
	void SetReleaseRate( double rate );
	void SetAttackTime( double time );
	void SetDecayTime( double time );
	void SetReleaseTime( double time );
	void SetAllTimes( double aTime, double dTime, double sLevel, double rTime );
	void SetTarget( double target );
	
	int GetState() const {
		return state_;
	};

	void SetValue( double value );

	double GetLastOut() const {
		return last_frame_[0];
	};

	double Tick();
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	void SampleRateChanged( double new_rate, double old_rate );

	int state_;
	double value_;
	double target_;
	double attack_rate_;
	double decay_rate_;
	double release_rate_;
	double release_time_;
	double sustain_level_;
};

inline double ADSR::Tick() {
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

		if ( value_ <= 0.0 ) {
			value_ = 0.0;
			state_ = IDLE;
		}

		last_frame_[0] = value_;
	}

	return value_;
}

inline AudioFrames& ADSR::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("ADSR::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = ADSR::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
