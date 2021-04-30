#ifndef _Multimedia_Video_h_
#define _Multimedia_Video_h_

NAMESPACE_OULU_BEGIN


class VideoFrame : public Video {
	
	
public:
	virtual ~VideoFrame() {}
	
};

class VideoInputFormatResolution {
	
protected:
	friend class V4L2_DeviceManager;
	friend class FfmpegFileInput;
	
	VideoFormat fmt;
	
public:
	
	VideoFormat GetVideoFormat() const {return fmt;}
	
	int GetPitch() const {return fmt.pitch;}
	void SetPitch(int i) {fmt.SetPitch(i);}
};


class VideoInputFormat {
	
protected:
	friend class V4L2_DeviceManager;
	friend class FfmpegFileInput;
	
	String desc;
	uint32 pix_fmt = 0;
	Array<VideoInputFormatResolution> res;
	
	VideoInputFormatResolution& GetResolution(int i) {return res[i];}
	
	
public:
	
	String GetDescription() const {return desc;}
	
	int GetResolutionCount() const {return res.GetCount();}
	const VideoInputFormatResolution& GetResolution(int i) const {return res[i];}
	uint32 GetPixelFormat() const {return pix_fmt;}
	
	const VideoInputFormatResolution& operator[](int i) const {return res[i];}
	
	// IsMJPEG(): is src v4l2 and pix_fmt V4L2_PIX_FMT_MJPEG
	
};


class VideoInputFrame : public VideoFrame {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	
};


class VideoOutputFrame : public VideoFrame {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	
};

struct DataPtrVideoBuffer : public Video {
	void* data = 0;
	VideoFormat fmt;
	int type = 0;
	
	enum {
		UNKNOWN,
		OPENCV
	};
	
	void SetOpenCVFormat(VideoFormat fmt) {this->fmt = fmt; type = OPENCV;}
	
	void Get(void* v, int size) override {}
	void Put(void* v, int size, bool realtime) override {}
	int GetQueueSize() const override {return 1;}
	VideoFormat GetVideoFormat() const override {return fmt;}
	bool IsQueueFull() const override {return false;}
#ifdef flagOPENGL
	bool PaintOpenGLTexture(int texture) override;
#endif
	
};


NAMESPACE_OULU_END

#endif
