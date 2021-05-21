#ifndef _Multimedia_Video_h_
#define _Multimedia_Video_h_

NAMESPACE_TOPSIDE_BEGIN



class VideoInputFrame : public Video {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	RTTI_DECL1(VideoInputFrame, Video)
	
};


class VideoOutputFrame : public Video {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	RTTI_DECL1(VideoOutputFrame, Video)
	
};

struct DataPtrVideoBuffer : public Video {
	RTTI_DECL1(DataPtrVideoBuffer, Video)
	
	
	void* data = 0;
	VideoFormat fmt;
	int type = 0;
	
	enum {
		UNKNOWN,
		OPENCV
	};
	
	void SetOpenCVFormat(VideoFormat fmt) {this->fmt = fmt; type = OPENCV;}
	
	void Exchange(VideoEx& e) override {}
	int GetQueueSize() const override {return fmt.GetFrameBytes();}
	VideoFormat GetFormat() const override {return fmt;}
	bool IsQueueFull() const override {return false;}
	
};


NAMESPACE_TOPSIDE_END

#endif
