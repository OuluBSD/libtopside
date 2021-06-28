#ifndef _Multimedia_OpenCV_Capture_h_
#define _Multimedia_OpenCV_Capture_h_

#if HAVE_OPENCV

NAMESPACE_ECS_BEGIN



class OpenCVCaptureDevice : public MediaStream {
	
protected:
	friend class V4L2_DeviceManager;
	
	String path;
	
	//Vector<char> buffer;
	DataPtrVideoBuffer vbuffer;
	AudioVolatileBuffer abuffer;
	SimpleAudioStream astream;
	SimpleVideoStream vstream;
	AVMediaProxy avproxy;
	Image sw_frame;
	uint32 open_pix_fmt = 0;
	Size open_frame_sz;
	TimeStop cur_time;
	
	
	class Data;
	
	#if V4L2_SLOW
	JPGRaster jpg_raster;
	#endif
	
	One<Data> ocv;

	
	
public:
	RTTI_DECL1(OpenCVCaptureDevice, MediaStream)
	OpenCVCaptureDevice();
	~OpenCVCaptureDevice();
	
	void						Visit(RuntimeVisitor& vis) {}
	
	
	Media&						Get() override {return avproxy;}
	void						FillBuffer() override {}
	void						DropBuffer() override {}
	int							GetActiveFormatIdx() const override;
	int							GetFormatCount() const override;
	MediaFormat					GetFormat(int i) const override;
	bool						FindClosestFormat(const MediaFormat&, int& idx) override;
	//void						FillAudioBuffer() override {}
	//void						FillVideoBuffer() override;
	bool						IsOpen() const override;
	//Audio&						GetAudio() override {return abuffer;}
	//Video&						GetVideo() override {return vbuffer;}
	AudioStream&				GetAudioStream() override {return astream;}
	VideoStream&				GetVideoStream() override {return vstream;}
	bool						Open(int fmt_idx) override;
	void						Close() override;
	
	String						GetPath() const {return path;}
	double						GetSeconds() const {return cur_time.Seconds();}
	
	
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
	bool						FindClosestFormat(Size cap_sz, double fps, double bw_min, double bw_max, int& fmt, int& res) override;
	
	// MediaStream
	bool						Open0(String path) override;
	bool						OpenDevice0(int fmt, int res) override;
	String						GetPath() const override {return path;}
	*/
	
	
};


NAMESPACE_ECS_END

#endif
#endif
