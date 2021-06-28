#ifndef _Multimedia_Audio_h_
#define _Multimedia_Audio_h_

NAMESPACE_ECS_BEGIN


class AudioFrame : public PacketBufferBase {
	
	
public:
	RTTI_DECL1(AudioFrame, PacketBufferBase)
	virtual ~AudioFrame() {}
	
	
	Format fmt;
	
};


class AudioInputFrame : public AudioFrame {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	RTTI_DECL1(AudioInputFrame, AudioFrame)
	
	
};

using AudioInputFrameRef = Ref<AudioInputFrame>;

NAMESPACE_ECS_END

#endif
