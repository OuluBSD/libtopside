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

class Video {
	
public:
	Video() = default;
	virtual ~Video() = default;
	
	virtual void Get(void* v, int size) = 0;
	virtual void Put(void* v, int size, bool realtime) = 0;
	virtual int GetQueueSize() const = 0;
	virtual VideoFormat GetVideoFormat() const = 0;
	virtual bool IsQueueFull() const = 0;
	
#ifdef flagOPENGL
	virtual bool PaintOpenGLTexture(int texture) {return false;}
#endif
	
};


class VideoProxy : public Video {
	Video* vid = 0;
	
public:
	VideoProxy() = default;
	VideoProxy(Video* vid) : vid(vid) {}
	
	void Set(Video* vid) {this->vid = vid;}
	
	operator bool() const {return vid != 0;}
	void Get(void* v, int size) override {if (vid) vid->Get(v, size);}
	void Put(void* v, int size, bool realtime) override {if (vid) vid->Put(v, size, realtime);}
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
	
	void Get(void* v, int size) override;
	void Put(void* v, int size, bool realtime) override;
	int GetQueueSize() const override {return queue_size;}
	VideoFormat GetVideoFormat() const override {return vid_fmt;}
	bool IsQueueFull() const override {return queue_size >= frames;}
#ifdef flagOPENGL
	bool PaintOpenGLTexture(int texture) override;
#endif
	
	#ifdef flagDEBUG
	void SetSizeLimit(int l) {size_limit = l;}
	#else
	void SetSizeLimit(int l) {}
	#endif
	
};

NAMESPACE_OULU_END

#endif
