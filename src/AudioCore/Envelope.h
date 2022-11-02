#ifndef _AudioCore_ENVELOPE_H
#define _AudioCore_ENVELOPE_H


NAMESPACE_AUDIO_BEGIN


class Envelope : public Generator {
public:

	Envelope();
	~Envelope();
	Envelope& operator= ( const Envelope& e );
	
	void KeyOn() {
		this->SetTarget( 1.0 );
	};

	void KeyOff() {
		this->SetTarget( 0.0 );
	};

	void SetRate( double rate );
	void SetTime( double time );
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
	double rate_;
	int state_;
};

inline double Envelope::Tick() {
	if ( state_ ) {
		if ( target_ > value_ ) {
			value_ += rate_;

			if ( value_ >= target_ ) {
				value_ = target_;
				state_ = 0;
			}
		}
		else {
			value_ -= rate_;

			if ( value_ <= target_ ) {
				value_ = target_;
				state_ = 0;
			}
		}

		last_frame_[0] = value_;
	}

	return value_;
}

inline AudioFrames& Envelope::Tick( AudioFrames& frames, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Envelope::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int step = frames.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
