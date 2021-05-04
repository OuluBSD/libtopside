#ifndef _Oulu_Video_h_
#define _Oulu_Video_h_

NAMESPACE_OULU_BEGIN


struct VideoFormat {
	Size res = {0,0};
	double fps = 0;
	int var_size = 0;
	int channels = 0;
	int pitch = 0;
	
	void Clear();
	bool IsValid() const {return res.cx > 0 && res.cy > 0 && fps > 0 && var_size > 0 && channels > 0 && pitch >= GetMinPitch();}
	int GetMinPitch() const {return res.cx * channels * var_size;}
	void SetLinePadding(int bytes) {ASSERT(bytes >= 0); pitch = GetMinPitch() + bytes;}
	void SetPitch(int bytes) {pitch = bytes; ASSERT(bytes >= GetMinPitch());}
	Size GetSize() const {return res;}
	int GetFrameBytes() const {return res.cy * pitch;}
	bool operator!=(const VideoFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const VideoFormat& fmt) const {
		return	res == fmt.res &&
				fps == fmt.fps &&
				var_size == fmt.var_size &&
				channels == fmt.channels &&
				pitch == fmt.pitch
				;
	}
	
};

VideoFormat MakeVideoFormat(Size res, double fps, int var_size, int channels, int pitch);



struct VideoCodecFormat {
	
	
};

class Video {
	
public:
	Video() = default;
	virtual ~Video() = default;
	
	virtual void Exchange(VideoEx& e) = 0;
	virtual int GetQueueSize() const = 0;
	virtual VideoFormat GetVideoFormat() const = 0;
	virtual bool IsQueueFull() const = 0;
	
#ifdef flagOPENGL
	virtual bool PaintOpenGLTexture(int texture) {return false;}
#endif
	
};


class VideoSourceFormatResolution {
	
protected:
	VideoFormat		fmt;
	
public:
	
	VideoFormat		GetFormat() const {return fmt;}
	
	void			SetFormat(VideoFormat fmt) {this->fmt = fmt;}
	
};


class VideoSourceFormat {
	
protected:
	String								desc;
	VideoCodecFormat					codec;
	Array<VideoSourceFormatResolution>	res;
	
	VideoSourceFormatResolution&		GetResolution(int i) {return res[i];}
	
	
public:
	
	VideoSourceFormatResolution&		Add() {return res.Add();}
	void								SetDescription(String s) {desc = s;}
	
	String								GetDescription() const {return desc;}
	int									GetResolutionCount() const {return res.GetCount();}
	const VideoSourceFormatResolution&	GetResolution(int i) const {return res[i];}
	VideoCodecFormat					GetCodecFormat() const {return codec;}
	
	VideoSourceFormatResolution&		operator[](int i) {return res[i];}
	const VideoSourceFormatResolution&	operator[](int i) const {return res[i];}
	
	// IsMJPEG(): is src v4l2 and pix_fmt V4L2_PIX_FMT_MJPEG
	
};


class VideoProxy : public Video {
	Video* vid = 0;
	
public:
	VideoProxy() = default;
	VideoProxy(Video* vid) : vid(vid) {}
	
	void Set(Video* vid) {this->vid = vid;}
	
	operator bool() const {return vid != 0;}
	void Exchange(VideoEx& e) override {if (vid) vid->Exchange(e);}
	int GetQueueSize() const override {if (vid) return vid->GetQueueSize(); return 0;}
	VideoFormat GetVideoFormat() const override {if (vid) return vid->GetVideoFormat(); return VideoFormat();}
	bool IsQueueFull() const override {if (vid) return vid->IsQueueFull(); return 0;}
};


class VolatileVideoBuffer : public Video {
	// Settings
	VideoFormat vid_fmt;
	SpinLock lock;
	int frames = 0;
	int frame_size = 0;
	
	// Runtime values
	Vector<byte> data[2];
	int data_i = 0, read_pos = 0, write_pos = 0, queue_size = 0;
	
	#ifdef flagDEBUG
	int size_limit = 10*1024*1024;
	#endif
	
	bool CheckSize(int size);
	
public:
	
	VolatileVideoBuffer() = default;
	
	void SetSize(VideoFormat vid_fmt, int frames);
	void Clear();
	void Zero();
	
	byte* GetActiveMem() {return data[data_i].Begin();}
	const byte* GetActiveMem() const {return data[data_i].Begin();}
	int GetMemSize() const {return data[0].GetCount();}
	bool IsEmpty() const {return data[0].IsEmpty();}
	
	void Exchange(VideoEx& e) override;
	int GetQueueSize() const override {TODO return queue_size;}
	VideoFormat GetVideoFormat() const override {return vid_fmt;}
	bool IsQueueFull() const override {TODO return queue_size >= frames;}
#ifdef flagOPENGL
	bool PaintOpenGLTexture(int texture) override;
#endif
	
	#ifdef flagDEBUG
	void SetSizeLimit(int l) {size_limit = l;}
	#else
	void SetSizeLimit(int l) {}
	#endif
	
};



class VideoStream : public virtual RealtimeStream {
	
	
public:
	virtual ~VideoStream() {}
	
	virtual void						FillVideoBuffer() = 0;
	virtual void						DropVideoFrames(int frames) = 0;
	virtual int							GetVideoBufferSize() const = 0;
	virtual Video&						GetVideo() = 0;
	virtual int							GetActiveVideoFormat() const = 0;
	virtual int							GetFormatCount() const = 0;
	virtual const VideoSourceFormat&	GetFormat(int i) const = 0;
	virtual bool						FindClosestFormat(Size cap_sz, double fps, double bw_min, double bw_max, int& fmt, int& res) = 0;
	
	//virtual Size		GetVideoSize() const {return Size(0,0);}
	//virtual int		GetVideoDepth() const {return 0;}
	
};


NAMESPACE_OULU_END

#endif
