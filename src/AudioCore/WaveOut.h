#ifndef _AudioCore_WVOUT_H
#define _AudioCore_WVOUT_H


NAMESPACE_AUDIO_BEGIN


class WaveOut : public Audio {
public:

	WaveOut() : frame_counter_(0), clipping_(false) {};

	unsigned long GetFrameCount() const {
		return frame_counter_;
	};

	double GetTime() const {
		return (double) frame_counter_ / Audio::GetSampleRate();
	};

	bool ClipStatus() {
		return clipping_;
	};

	void ResetClipStatus() {
		clipping_ = false;
	};

	virtual void Tick( const double sample ) = 0;
	virtual void Tick( const AudioFrames& frames ) = 0;

protected:

	double& ClipTest( double& sample );

	AudioFrames data_;
	unsigned long frame_counter_;
	bool clipping_;

};

inline double& WaveOut::ClipTest( double& sample ) {
	bool clip = false;

	if ( sample > 1.0 ) {
		sample = 1.0;
		clip = true;
	}
	else if ( sample < -1.0 ) {
		sample = -1.0;
		clip = true;
	}

	if ( clip == true && clipping_ == false ) {
		clipping_ = true;
		LOG("WaveOut: data value(s) outside +-1.0 detected ... clamping at outer bound!");
		HandleError( AudioError::WARNING );
	}

	return sample;
}

NAMESPACE_AUDIO_END

#endif
