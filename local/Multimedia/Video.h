#ifndef _Multimedia_Video_h_
#define _Multimedia_Video_h_

NAMESPACE_OULU_BEGIN


class VideoFrame : public Video {
	
	
public:
	virtual ~VideoFrame() {}
	
};

class VideoInputFormatResolution {
	
protected:
	friend class MediaDeviceManager;
	friend class MediaFileInput;
	
	VideoFormat fmt;
	
public:
	
	VideoFormat GetFormat() const {return fmt;}
	
	int GetPitch() const {return fmt.pitch;}
	void SetPitch(int i) {fmt.SetPitch(i);}
};


class VideoInputFormat {
	
protected:
	friend class MediaDeviceManager;
	friend class MediaFileInput;
	
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
	friend class MediaDeviceManager;
	
	
public:
	
};


class VideoOutputFrame : public VideoFrame {
	
protected:
	friend class MediaDeviceManager;
	
	
public:
	
};


NAMESPACE_OULU_END

#endif
