#ifndef _Multimedia_Media_h_
#define _Multimedia_Media_h_


NAMESPACE_OULU_BEGIN


class MediaStream : public VolatileStream, public LockedScopeEnabler<MediaStream> {
	
	
protected:
	String last_path;
	int last_fmt = 0, last_res = 0;
	
	virtual bool OpenDevice0(int fmt, int res) = 0;
	virtual bool Open0(String path) = 0;
public:
	virtual ~MediaStream() {}
	
	bool Open(String path) {last_path = path; return Open0(path);}
	bool OpenDevice(int fmt, int res) {last_fmt = fmt; last_res = res; return OpenDevice0(fmt, res);}
	bool ReopenDevice() {return Open0(last_path) && OpenDevice0(last_fmt, last_res);}
	
	virtual int		FillVideoBuffer() = 0;
	virtual int		FillAudioBuffer() = 0;
	virtual void	DropFrames(int audio_frames, int video_frames) = 0;
	
	virtual bool	IsDeviceOpen() const = 0;
	virtual void	Close() = 0;
	virtual Sound&	GetSound() = 0;
	virtual Video&	GetVideo() = 0;
	virtual String	GetPath() const = 0;
	
	virtual int							GetFormatCount() const = 0;
	virtual const VideoInputFormat&		GetFormat(int i) const = 0;
	virtual bool						FindClosestFormat(Size cap_sz, double fps, double bw_min, double bw_max, int& fmt, int& res) = 0;
	
	virtual String GetLastError() const {return "unknown";}
	
	//virtual bool Step(double seconds) = 0;
	//virtual bool IsAnyQueueEmpty() = 0;
	
};

typedef Ref<MediaStream> MediaStreamRef;



class MediaInputStream : public MediaStream {
	
protected:
	friend class V4L2_DeviceManager;
	Array<VideoInputFormat> fmts;
	
	
public:
	
	int		GetFormatCount() const override;
	bool	FindClosestFormat(Size cap_sz, double fps, double bw_min, double bw_max, int& fmt, int& res) override;
	const VideoInputFormat& GetFormat(int i) const override;
	
};

class MediaOutputStream : public MediaStream {
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	
};






class MediaStreamThread : Moveable<MediaStreamThread> {
	MediaStreamRef cap;
	
	RunningFlagSingle flag;
	String last_error;
	bool loop_file = false;
	bool separate_thrd = false;
	
	
	void Process();
public:
	
	typedef MediaStreamThread CLASSNAME;
	MediaStreamThread() {}
	~MediaStreamThread() {Stop(); Clear();}
	
	void Clear();
	void Start(bool separate_thrd);
	void Stop();
	int FillVideoBuffer();
	int FillAudioBuffer();
	
	MediaStream& Cap() {ASSERT(cap); return *cap;}
	bool IsCap() const {return cap;}
	void SetCap(MediaStreamRef cap) {this->cap = cap;}
	bool IsRunning() const {return flag.IsRunning();}
	
	String GetLastError() const {return last_error;}
	
#ifdef flagOPENGL
	void PaintOpenGL(GLuint active_tex);
#endif
	
	
	Callback WhenError;
	
};



NAMESPACE_OULU_END


#endif
