#ifndef _Multimedia_OpenCV_Capture_h_
#define _Multimedia_OpenCV_Capture_h_

#if HAVE_OPENCV

NAMESPACE_OULU_BEGIN



class OpenCVCaptureDevice : public MediaInputStream {
	
protected:
	friend class V4L2_DeviceManager;
	
	String path;
	Array<VideoInputFormat> fmts;
	
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

	#if HAVE_V4L2
	static const int buf_size = 5000000;
	V4l2Capture* vid_cap = 0;
	#endif
	
	
public:
	OpenCVCaptureDevice();
	~OpenCVCaptureDevice();
	
	bool Open0(String path) override;
	bool OpenDevice0(int fmt, int res) override;
	bool IsDeviceOpen() const override;
	bool Step(double seconds) override {return true;}
	bool ReadVideo() override;
	bool ReadAudio() override {return false;}
	void Close() override;
	Sound& GetSound() override {return abuffer;}
	Video& GetVideo() override {return vbuffer;}
	
	int GetFormatCount() const override {return fmts.GetCount();}
	const VideoInputFormat& GetFormat(int i) const override {return fmts[i];}
	String GetPath() const override {return path;}
	
	// bw_max - maximum bandwidth range maximum (multiplier for desired bandwidth as upper limit)
	// bw_min - maximum bandwidth range minimum (multiplier for desired bandwidth as lower limit)
	bool FindClosestFormat(Size cap_sz, double fps, double bw_min, double bw_max, int& fmt, int& res) override;
	
	double GetSeconds() const override {return cur_time.Seconds();}
	Size GetVideoSize() const override {return open_frame_sz;}
	
	
};


NAMESPACE_OULU_END

#endif
#endif
