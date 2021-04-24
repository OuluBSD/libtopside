#ifndef _Multimedia_Audio_h_
#define _Multimedia_Audio_h_

NAMESPACE_OULU_BEGIN


class AudioFrame : public Sound {
	
	
public:
	virtual ~AudioFrame() {}
	
};


class AudioInputFrame : public AudioFrame {
	
protected:
	friend class MediaDeviceManager;
	
	
public:
	
};


NAMESPACE_OULU_END

#endif
