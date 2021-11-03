#ifndef _Multimedia_OpenCV_Capture_h_
#define _Multimedia_OpenCV_Capture_h_

#if HAVE_OPENCV

NAMESPACE_SERIAL_BEGIN



class OpenCVCaptureDevice :
	RTTIBase
{
	
protected:
	friend class V4L2_DeviceManager;
	
	Array<VideoSourceFormat>	fmts;
	
	String				path;
	Packet				last_p;
	Image				sw_frame;
	uint32				open_pix_fmt = 0;
	Size				open_frame_sz;
	TimeStop			cur_time;
	RunningFlag			flag;
	double				time_step = 0;
	int					frame_counter = 0;
	
	class Data;
	
	#if V4L2_SLOW
	JPGRaster			jpg_raster;
	#endif
	
	One<Data>			ocv;

	
	
public:
	typedef OpenCVCaptureDevice CLASSNAME;
	RTTI_DECL0(OpenCVCaptureDevice);
	OpenCVCaptureDevice();
	~OpenCVCaptureDevice();
	
	void						Visit(RuntimeVisitor& vis) {}
	
	bool						FindClosestFormat(Size cap_sz, double fps, double bw_min, double bw_max, int& ret_fmt, int& ret_res);
	bool						Open(int fmt_idx, int res_i, bool vflip);
	void						Close();
	void						Start();
	void						Stop();
	void						Process();
	
	String						GetPath() const {return path;}
	bool						IsOpen() const;
	int							GetFrameCount() const {return frame_counter;}
	Packet						GetPacket() {return last_p;}
	
	/*
	Media&						Get() override {return avproxy;}
	void						FillBuffer() override {}
	void						DropBuffer() override {}
	int							GetActiveFormatIdx() const override;
	int							GetFormatCount() const override;
	MediaFormat					GetFormat(int i) const override;
	
	//void						FillAudioBuffer() override {}
	//void						FillVideoBuffer() override;
	//Audio&						GetAudio() override {return abuffer;}
	//Video&						GetVideo() override {return vbuffer;}
	AudioStream&				GetAudioStream() override {return astream;}
	VideoStream&				GetVideoStream() override {return vstream;}
	
	double						GetSeconds() const {return cur_time.Seconds();}
	*/
	
	/*
	// RealtimeStream
	
	// AudioStream
	void						DropBuffer(AudCtx) override {}
	
	// VideoStream
	void						DropVideoFrames(int frames) override;
	int							GetVideoBufferSize() const override {return 1;}
	int							GetActiveVideoFormatIdx() const override;
	int							GetFormatCount() const override;
	const VideoSourceFormat&	GetFormat(int i) const override;
	
	// MediaStream
	bool						Open0(String path) override;
	bool						OpenDevice0(int fmt, int res) override;
	String						GetPath() const override {return path;}
	*/
	
	
};


NAMESPACE_SERIAL_END

#endif
#endif
