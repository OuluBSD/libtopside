#ifndef _Multimedia_Audio_h_
#define _Multimedia_Audio_h_

NAMESPACE_TOPSIDE_BEGIN


class AudioFrame : public SimpleBufferedAudio {
	
	
public:
	RTTI_DECL1(AudioFrame, Audio)
	virtual ~AudioFrame() {}
	
};


class AudioInputFrame : public AudioFrame {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	RTTI_DECL1(AudioInputFrame, AudioFrame)
	
};


NAMESPACE_TOPSIDE_END

#endif
