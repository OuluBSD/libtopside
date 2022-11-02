#ifndef _AudioCore_WVIN_H
#define _AudioCore_WVIN_H


NAMESPACE_AUDIO_BEGIN

class WaveIn : public Audio {
public:

	unsigned int GetChannelsOut() const {
		return data_.GetChannelCount();
	};

	const AudioFrames& GetLastFrame() const {
		return last_frame_;
	};

	virtual double Tick( unsigned int channel = 0 ) = 0;
	virtual AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 ) = 0;

protected:

	AudioFrames data_;
	AudioFrames last_frame_;

};

NAMESPACE_AUDIO_END

#endif
