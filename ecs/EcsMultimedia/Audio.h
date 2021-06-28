#ifndef _Multimedia_Audio_h_
#define _Multimedia_Audio_h_

NAMESPACE_ECS_BEGIN


class AudioFrame : public SimpleBufferedValue {
	
	
public:
	RTTI_DECL1(AudioFrame, SimpleBufferedValue)
	virtual ~AudioFrame() {}
	
};


class AudioInputFrame : public AudioFrame {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	RTTI_DECL1(AudioInputFrame, AudioFrame)
	
};


NAMESPACE_ECS_END

#endif
