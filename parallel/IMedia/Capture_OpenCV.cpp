
// problematic hal/interface.h usage fix
// clang and gcc behaves in a different way
#if defined flagGCC && defined flagFREEBSD
	#if flagOPENCV
		#undef CPU_SSE2
		#include <opencv2/core.hpp>
		#include <opencv2/imgproc.hpp>
		#include <opencv2/highgui.hpp>
		#include <opencv2/videoio.hpp>
	#endif
	
	#include "IMedia.h"
#else
	#include "IMedia.h"
	
	#if flagOPENCV
		#undef CPU_SSE2
		// error here means that you didn't add opencv include dir to build method conf
		#include <opencv2/core.hpp>
		#include <opencv2/imgproc.hpp>
		#include <opencv2/highgui.hpp>
		#include <opencv2/videoio.hpp>
	#endif
#endif

#if flagOPENCV



#if defined flagGCC && flagFREEBSD
bool cv::VideoCapture::open(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const& a, int b) {
	return false;
}
#endif


NAMESPACE_PARALLEL_BEGIN


class OpenCVCaptureDevice::Data {
	off32_gen	gen;
	
	Size prev_sz;
	double prev_fps;
	Format prev_fmt;
	bool prev_vflip;
	
public:
	OpenCVCaptureDevice& dev;
	
	cv::Mat frame, frame_flipped;
	cv::VideoCapture camera;
	
	Data(OpenCVCaptureDevice* dev) : dev(*dev) {}
	
	bool OpenDevice0(Size sz, double fps, const Format& fmt, bool vflip) {
		prev_sz = sz;
		prev_fps = fps;
		prev_fmt = fmt;
		prev_vflip = vflip;
		
		camera.set(cv::CAP_PROP_FRAME_WIDTH, sz.cx);
		camera.set(cv::CAP_PROP_FRAME_HEIGHT, sz.cy);
		camera.set(cv::CAP_PROP_FPS, fps);
		camera.open(dev.path.Begin());
		if (camera.isOpened()) {
			camera.set(cv::CAP_PROP_FRAME_WIDTH, sz.cx);
			camera.set(cv::CAP_PROP_FRAME_HEIGHT, sz.cy);
			camera.set(cv::CAP_PROP_FPS, fps);
			
			return true;
		}
		return false;
	}
	
	void Close() {camera.release();}
	
	bool ReopenDevice() {Close(); return OpenDevice0(prev_sz, prev_fps, prev_fmt, prev_vflip);}
	
	bool Read() {
		if (camera.isOpened()) {
			camera >> frame;
			if (frame.data == NULL)
				return false;
			if (prev_vflip)
				cv::flip(frame, frame_flipped, 0);
			else
				frame_flipped = frame;
			
			cv::cvtColor(frame_flipped, frame, cv::COLOR_BGR2RGB);
			
			int sz = frame.cols * frame.rows * frame.channels();
			
			Packet p = CreatePacket(gen.Create());
			PacketValue& v = *p;
			v.SetFormat(prev_fmt);
			auto& data = v.Data();
			ASSERT(sz > 0);
			data.SetCount(sz);
			memcpy(data.Begin(), frame.data, sz);
			dev.last_p = p;
			
			return true;
		}
		return false;
	}
	
	bool IsDeviceOpen() const {
		return camera.isOpened();
	}
};









OpenCVCaptureDevice::OpenCVCaptureDevice() {
	ocv = new Data(this);
}

OpenCVCaptureDevice::~OpenCVCaptureDevice() {
	Close();
}

bool OpenCVCaptureDevice::Open(int fmt_i, int res_i, bool vflip, Format& f) {
	Close();
	
	cur_time.Reset();
	
	if (fmt_i < 0 || fmt_i >= fmts.GetCount()) return false;
	const VideoSourceFormat& fmt = fmts[fmt_i];
	
	if (res_i < 0 || res_i >= fmt.GetResolutionCount()) return false;
	const VideoSourceFormatResolution& res = fmt.GetResolution(res_i);
	
	VideoFormat vid_fmt = res.GetFormat();
	Size sz = vid_fmt.GetSize();
	const double fps = vid_fmt.GetFPS();
	if (fps <= 0.0) return false;
	time_step = 1.0 / fps;
	
	f.SetVideo(DevCls::CENTER, vid_fmt);
	if (ocv && ocv->OpenDevice0(sz, fps, f, vflip))
		return true;
	
	return false;
}

void OpenCVCaptureDevice::Close() {
	if (ocv)
		ocv->Close();
}

void OpenCVCaptureDevice::Start() {
	Stop();
	flag.Start(1);
	Thread::Start(THISBACK(Process));
}

void OpenCVCaptureDevice::Stop() {
	flag.Stop();
}

void OpenCVCaptureDevice::Process() {
	if (ocv) {
		TimeStop ts;
		while (ocv && ocv->IsDeviceOpen() && flag.IsRunning()) {
			if (ts.Seconds() >= time_step) {
				ts.Reset();
				
				if (ocv->Read()) {
					// got new video frame
					frame_counter++;
				}
				else
					Sleep(1);
			}
			
			if (!ocv->IsDeviceOpen())
				ocv->ReopenDevice();
			
		}
	}
	flag.DecreaseRunning();
}

bool OpenCVCaptureDevice::FindClosestFormat(Size cap_sz, double fps, double bw_min, double bw_max, int& ret_fmt, int& ret_res) {
	double tgt_bw = (double)cap_sz.cx * (double)cap_sz.cy * (double)fps;
	double bw_low = bw_min * tgt_bw;
	double bw_high = bw_max * tgt_bw;
	if (bw_low > bw_high)
		return false;
	
	struct Result : Moveable<Result> {
		double diff;
		int fmt, res;
		bool operator()(const Result& a, const Result& b) const {return a.diff < b.diff;}
	};
	Vector<Result> results;
	
	for(int i = 0; i < fmts.GetCount(); i++) {
		const VideoSourceFormat& fmt = fmts[i];
		for(int j = 0; j < fmt.GetResolutionCount(); j++) {
			const VideoSourceFormatResolution& fmt_res = fmt.GetResolution(j);
			VideoFormat vid_fmt = fmt_res.GetFormat();
			Size fmt_sz = vid_fmt.GetSize();
			double fmt_fps = vid_fmt.GetFPS();
			double fmt_bw = (double)fmt_sz.cx * (double)fmt_sz.cy * fmt_fps;
			if (fmt_bw >= bw_low && fmt_bw <= bw_high) {
				Result& r = results.Add();
				r.diff = fabs(tgt_bw - fmt_bw);
				r.fmt = i;
				r.res = j;
			}
		}
	}
	if (results.GetCount()) {
		Sort(results, Result());
		if (0) {
			for(int i = 0; i < results.GetCount(); i++) {
				const Result& r = results[i];
				LOG(i << ": " << r.diff << ": " << r.fmt << ", " << r.res);
			}
		}
		const Result& res = results[0];
		ret_fmt = res.fmt;
		ret_res = res.res;
		return true;
	}
	return false;
}

bool OpenCVCaptureDevice::IsOpen() const {
	if (ocv && ocv->IsDeviceOpen())
		return true;
	
	return false;
}


NAMESPACE_PARALLEL_END

#endif
