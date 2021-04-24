#ifndef _Multimedia_Capture_h_
#define _Multimedia_Capture_h_

NAMESPACE_OULU_BEGIN


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
	VideoFormat GetFormat() const override {return fmt;}
	bool IsQueueFull() const override {return false;}
#ifdef flagOPENGL
	bool PaintOpenGLTexture(int texture) override;
#endif
	
};


class MediaCaptureDevice : public MediaInputStream {
	
protected:
	friend class MediaDeviceManager;
	
	String path;
	Array<VideoInputFormat> fmts;
	
	//Vector<char> buffer;
	DataPtrVideoBuffer vbuffer;
	VolatileSoundBuffer abuffer;
	Image sw_frame;
	uint32 open_pix_fmt = 0;
	Size open_frame_sz;
	TimeStop cur_time;
	
	
	class OpenCV;
	
	#if flagV4L2_SLOW
	JPGRaster jpg_raster;
	#endif
	
	One<OpenCV> ocv;

	#if flagV4L2
	static const int buf_size = 5000000;
	V4l2Capture* vid_cap = 0;
	#endif
	
	
public:
	MediaCaptureDevice();
	~MediaCaptureDevice();
	
	bool Open0(String path) override;
	bool OpenDevice0(int fmt, int res) override;
	bool IsDeviceOpen() const override;
	bool Step(double seconds) override {return true;}
	bool Read() override;
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
