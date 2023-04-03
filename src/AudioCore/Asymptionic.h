#ifndef _AudioCore_ASYMP_H
#define _AudioCore_ASYMP_H


NAMESPACE_AUDIO_BEGIN


const float TARGET_THRESHOLD = 0.000001f;

class Asymptionic : public Generator {
public:

	Asymptionic();
	~Asymptionic();
	void KeyOn();
	void KeyOff();
	void SetTau( float tau );
	void SetTime( float time );
	void SetT60( float t60 );
	void SetTarget( float target );
	void SetValue( float value );
	
	int GetState() const {
		return state_;
	};

	float GetLastOut() const {
		return last_frame_[0];
	};

	float Tick();
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	void SampleRateChanged( float new_rate, float old_rate );

	float value_;
	float target_;
	float factor_;
	float constant_;
	int state_;
};

inline float Asymptionic::Tick() {
	if ( state_ ) {
		value_ = factor_ * value_ + constant_;

		if ( target_ > value_ ) {
			if ( target_ - value_ <= TARGET_THRESHOLD ) {
				value_ = target_;
				state_ = 0;
			}
		}
		else {
			if ( value_ - target_ <= TARGET_THRESHOLD ) {
				value_ = target_;
				state_ = 0;
			}
		}

		last_frame_[0] = value_;
	}

	return value_;
}

inline AudioFrames& Asymptionic::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Asymptionic::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Asymptionic::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
