#ifndef _Multimedia_Audio_h_
#define _Multimedia_Audio_h_

NAMESPACE_TOPSIDE_BEGIN


class AudioFrame : public Audio {
	
	
public:
	virtual ~AudioFrame() {}
	
};


class AudioInputFrame : public AudioFrame {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	
};


NAMESPACE_TOPSIDE_END

#endif
