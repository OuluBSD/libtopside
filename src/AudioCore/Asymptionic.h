#ifndef _AudioCore_ASYMP_H
#define _AudioCore_ASYMP_H


NAMESPACE_AUDIO_BEGIN


const double TARGET_THRESHOLD = 0.000001;

class Asymptionic : public Generator {
public:

	Asymptionic();
	~Asymptionic();
	void KeyOn();
	void KeyOff();
	void SetTau( double tau );
	void SetTime( double time );
	void SetT60( double t60 );
	void SetTarget( double target );
	void SetValue( double value );
	
	int GetState() const {
		return state_;
	};

	double GetLastOut() const {
		return last_frame_[0];
	};

	double Tick();
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	void SampleRateChanged( double new_rate, double old_rate );

	double value_;
	double target_;
	double factor_;
	double constant_;
	int state_;
};

inline double Asymptionic::Tick() {
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

inline AudioFrames& Asymptionic::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Asymptionic::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Asymptionic::Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
