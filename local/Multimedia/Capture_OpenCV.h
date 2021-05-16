#ifndef _Multimedia_OpenCV_Capture_h_
#define _Multimedia_OpenCV_Capture_h_

#if HAVE_OPENCV

NAMESPACE_TOPSIDE_BEGIN



class OpenCVCaptureDevice : public MediaSourceStream {
	
protected:
	friend class V4L2_DeviceManager;
	
	String path;
	
	//Vector<char> buffer;
	DataPtrVideoBuffer vbuffer;
	VolatileAudioBuffer abuffer;
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
	OpenCVCaptureDevice();
	~OpenCVCaptureDevice();
	
	void						Visit(RuntimeVisitor& vis) {}
	
	// RealtimeStream
	double						GetSeconds() const override {return cur_time.Seconds();}
	
	// AudioStream
	Audio&						GetAudio() override {return abuffer;}
	void						FillAudioBuffer() override {}
	void						DropAudioBuffer() override {}
	
	// VideoStream
	void						FillVideoBuffer() override;
	void						DropVideoFrames(int frames) override;
	int							GetVideoBufferSize() const override {return 1;}
	Video&						GetVideo() override {return vbuffer;}
	int							GetActiveVideoFormatIdx() const override;
	int							GetFormatCount() const override;
	const VideoSourceFormat&	GetFormat(int i) const override;
	bool						FindClosestFormat(Size cap_sz, double fps, double bw_min, double bw_max, int& fmt, int& res) override;
	
	// MediaStream
	bool						Open0(String path) override;
	bool						OpenDevice0(int fmt, int res) override;
	bool						IsDeviceOpen() const override;
	void						Close() override;
	String						GetPath() const override {return path;}
	
	
	
};


NAMESPACE_TOPSIDE_END

#endif
#endif
