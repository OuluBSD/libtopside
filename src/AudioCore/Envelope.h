#ifndef _AudioCore_ENVELOPE_H
#define _AudioCore_ENVELOPE_H


NAMESPACE_AUDIO_BEGIN


class Envelope : public Generator {
public:

	Envelope();
	~Envelope();
	Envelope& operator= ( const Envelope& e );
	
	void KeyOn() {
		this->SetTarget( 1.0f );
	};

	void KeyOff() {
		this->SetTarget( 0.0f );
	};

	void SetRate( float rate );
	void SetTime( float time );
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
	float rate_;
	int state_;
};

inline float Envelope::Tick() {
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

inline AudioFrames& Envelope::Tick( AudioFrames& frames, int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= frames.GetChannelCount() ) {
		LOG("Envelope::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int step = frames.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
		* samples = Tick();

	return frames;
}

NAMESPACE_AUDIO_END

#endif
