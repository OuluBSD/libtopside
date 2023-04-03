#ifndef _AudioCore_WVIN_H
#define _AudioCore_WVIN_H


NAMESPACE_AUDIO_BEGIN

class WaveIn : public Audio {
public:

	int GetChannelsOut() const {
		return data_.GetChannelCount();
	};

	const AudioFrames& GetLastFrame() const {
		return last_frame_;
	};

	virtual float Tick( int channel = 0 ) = 0;
	virtual AudioFrames& Tick( AudioFrames& frames, int channel = 0 ) = 0;

protected:

	AudioFrames data_;
	AudioFrames last_frame_;

};

NAMESPACE_AUDIO_END

#endif
