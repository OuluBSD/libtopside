#ifndef _Multimedia_OpenCV_Capture_h_
#define _Multimedia_OpenCV_Capture_h_

#if flagOPENCV

NAMESPACE_PARALLEL_BEGIN



class OpenCVCaptureDevice :
	RTTIBase
{
	
protected:
	friend class V4L2_DeviceManager;
	
	using VideoSourceFormat = VideoSourceFormatT<V4L2Media>;
	using VideoSourceFormatResolution = VideoSourceFormatResolutionT<V4L2Media>;
	
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
	bool						Open(int fmt_idx, int res_i, bool vflip, Format& fmt);
	void						Close();
	void						Start();
	void						Stop();
	void						Process();
	
	String						GetPath() const {return path;}
	bool						IsOpen() const;
	int							GetFrameCount() const {return frame_counter;}
	Packet						GetPacket() {return last_p;}
	
};


NAMESPACE_PARALLEL_END

#endif
#endif
