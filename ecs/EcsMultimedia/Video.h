#ifndef _Multimedia_Video_h_
#define _Multimedia_Video_h_

NAMESPACE_ECS_BEGIN



class VideoInputFrame : public Value {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	RTTI_DECL1(VideoInputFrame, Value)
	
};


class VideoOutputFrame : public Value {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	RTTI_DECL1(VideoOutputFrame, Value)
	
};

struct DataPtrVideoBuffer : public Value {
	RTTI_DECL1(DataPtrVideoBuffer, Value)
	
	
	void* data = 0;
	Format fmt;
	int type = 0;
	
	enum {
		UNKNOWN,
		OPENCV
	};
	
	void SetOpenCVFormat(Format fmt) {this->fmt = fmt; type = OPENCV;}
	
	void Exchange(Ex& e) override {}
	int GetQueueSize() const override {return 1;}
	Format GetFormat() const override {return fmt;}
	bool IsQueueFull() const override {return false;}
	
};


NAMESPACE_ECS_END

#endif
