#ifndef _AudioCore_GENERATOR_H
#define _AudioCore_GENERATOR_H


NAMESPACE_AUDIO_BEGIN


class Generator : public Audio {
public:

	Generator() {
		last_frame_.SetCount( 1, 1, 0.0f );
	};

	int GetChannelsOut() const {
		return last_frame_.GetChannelCount();
	};

	const AudioFrames& GetLastFrame() const {
		return last_frame_;
	};

	virtual AudioFrames& Tick( AudioFrames& frames, int channel = 0 ) = 0;

protected:

	AudioFrames last_frame_;
};


NAMESPACE_AUDIO_END

#endif
