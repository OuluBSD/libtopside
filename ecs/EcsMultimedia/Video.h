#ifndef _Multimedia_Video_h_
#define _Multimedia_Video_h_

NAMESPACE_ECS_BEGIN



class VideoInputFrame : public PacketBufferBase {
	
protected:
	friend class V4L2_DeviceManager;
	
public:
	RTTI_DECL1(VideoInputFrame, PacketBufferBase)
	
	
	Format fmt;
	
};

using VideoInputFrameRef = Ref<VideoInputFrame>;


class VideoOutputFrame : public PacketBufferBase {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	RTTI_DECL1(VideoOutputFrame, PacketBufferBase)
	
};

struct DataPtrVideoBuffer : public PacketBufferBasePtr {
	RTTI_DECL1(DataPtrVideoBuffer, PacketBufferBasePtr)
	
	
	void* data = 0;
	Format fmt;
	int type = 0;
	
	enum {
		UNKNOWN,
		OPENCV
	};
	
	void SetOpenCVFormat(Format fmt) {this->fmt = fmt; type = OPENCV;}
	
};


NAMESPACE_ECS_END

#endif
