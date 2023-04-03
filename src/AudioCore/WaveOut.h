#ifndef _AudioCore_WVOUT_H
#define _AudioCore_WVOUT_H


NAMESPACE_AUDIO_BEGIN


class WaveOut : public Audio {
public:

	WaveOut() : frame_counter_(0), clipping_(false) {};

	int GetFrameCount() const {
		return frame_counter_;
	};

	float GetTime() const {
		return (float) frame_counter_ / Audio::GetSampleRate();
	};

	bool ClipStatus() {
		return clipping_;
	};

	void ResetClipStatus() {
		clipping_ = false;
	};

	virtual void Tick( const float sample ) = 0;
	virtual void Tick( const AudioFrames& frames ) = 0;

protected:

	float& ClipTest( float& sample );

	AudioFrames data_;
	int frame_counter_;
	bool clipping_;

};

inline float& WaveOut::ClipTest( float& sample ) {
	bool clip = false;

	if ( sample > 1.0f ) {
		sample = 1.0f;
		clip = true;
	}
	else if ( sample < -1.0f ) {
		sample = -1.0f;
		clip = true;
	}

	if ( clip == true && clipping_ == false ) {
		clipping_ = true;
		LOG("WaveOut: data value(s) outside +-1.0f detected ... clamping at outer bound!");
		HandleError( AudioError::WARNING );
	}

	return sample;
}

NAMESPACE_AUDIO_END

#endif
