#ifndef _Multimedia_OpenCV_Capture_h_
#define _Multimedia_OpenCV_Capture_h_

#if HAVE_OPENCV

NAMESPACE_TOPSIDE_BEGIN



class OpenCVCaptureDevice : public MediaStream {
	
protected:
	friend class V4L2_DeviceManager;
	
	String path;
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
	bool						IsOpen() const override;
	AudioStream&				GetAudioStream() override {return astream;}
	VideoStream&				GetVideoStream() override {return vstream;}
	bool						Open(int fmt_idx) override;
	void						Close() override;
	
	String						GetPath() const {return path;}
	double						GetSeconds() const {return cur_time.Seconds();}
	
	
	
	
};


NAMESPACE_TOPSIDE_END

#endif
#endif
