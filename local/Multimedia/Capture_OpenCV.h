#ifndef _Multimedia_OpenCV_Capture_h_
#define _Multimedia_OpenCV_Capture_h_

#if HAVE_OPENCV

NAMESPACE_OULU_BEGIN



class OpenCVCaptureDevice : public MediaInputStream {
	
protected:
	friend class V4L2_DeviceManager;
	
	String path;
	
	//Vector<char> buffer;
	DataPtrVideoBuffer vbuffer;
	VolatileSoundBuffer abuffer;
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
	
	bool Open0(String path) override;
	bool OpenDevice0(int fmt, int res) override;
	bool IsDeviceOpen() const override;
	int FillVideoBuffer() override;
	int FillAudioBuffer() override {return 0;}
	void DropFrames(int audio_frames, int video_frames) override {}
	void Close() override;
	Sound& GetSound() override {return abuffer;}
	Video& GetVideo() override {return vbuffer;}
	
	String GetPath() const override {return path;}
	
	// bw_max - maximum bandwidth range maximum (multiplier for desired bandwidth as upper limit)
	// bw_min - maximum bandwidth range minimum (multiplier for desired bandwidth as lower limit)
	
	double GetSeconds() const override {return cur_time.Seconds();}
	Size GetVideoSize() const override {return open_frame_sz;}
	
	
};


NAMESPACE_OULU_END

#endif
#endif
