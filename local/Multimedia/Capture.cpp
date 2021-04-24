#include "Multimedia.h"


#undef CPU_SSE2
#if flagV4L2_OPENCV
	#include <opencv2/core.hpp>
	#include <opencv2/imgproc.hpp>
	#include <opencv2/highgui.hpp>
	#include <opencv2/videoio.hpp>

NAMESPACE_OULU_BEGIN

class MediaCaptureDevice::OpenCV {
public:
	MediaCaptureDevice& dev;
	
	cv::Mat frame, frame_flipped;
	cv::VideoCapture camera;
	
	OpenCV(MediaCaptureDevice* dev) : dev(*dev) {}
	
	bool OpenDevice0(Size sz, double fps, VideoFormat vid_fmt) {
		camera.set(cv::CAP_PROP_FRAME_WIDTH, sz.cx);
		camera.set(cv::CAP_PROP_FRAME_HEIGHT, sz.cy);
		camera.set(cv::CAP_PROP_FPS, fps);
		camera.open(dev.path.Begin());
		if (camera.isOpened()) {
			camera.set(cv::CAP_PROP_FRAME_WIDTH, sz.cx);
			camera.set(cv::CAP_PROP_FRAME_HEIGHT, sz.cy);
			camera.set(cv::CAP_PROP_FPS, fps);
			
			dev.vbuffer.SetOpenCVFormat(vid_fmt);
			dev.abuffer.Clear();
			return true;
		}
		return false;
	}
	#ifdef flagOPENGL
	bool PaintOpenGLTexture(int texture) {
		if (type == OPENCV && data != NULL) {
			glBindTexture (GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fmt.res.cx, fmt.res.cy, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
			return true;
		}
		return false;
	}
	#endif
	
	bool Read() {
		if (camera.isOpened()) {
			camera >> frame;
			if (frame.data == NULL)
				return false;
			cv::flip(frame, frame_flipped, 0);
			int sz = frame.cols * frame.rows * frame.channels();
			dev.vbuffer.data = frame_flipped.data;
			return true;
		}
		return false;
	}
	
	bool IsDeviceOpen() const {
		return camera.isOpened();
	}
};

NAMESPACE_OULU_END
#else
NAMESPACE_OULU_BEGIN

class MediaCaptureDevice::OpenCV {
public:
	MediaCaptureDevice& dev;
	OpenCV(MediaCaptureDevice* dev) : dev(*dev) {}
	bool OpenDevice0(Size sz, double fps, VideoFormat vid_fmt) {return false;}
	bool PaintOpenGLTexture(int texture) {return false;}
	bool Read() {return false;}
	bool IsDeviceOpen() const {return false;}
};

NAMESPACE_OULU_END
#endif




NAMESPACE_OULU_BEGIN

MediaCaptureDevice::MediaCaptureDevice() {
	ocv = new OpenCV(this);
}

MediaCaptureDevice::~MediaCaptureDevice() {
	Close();
}

bool MediaCaptureDevice::Open0(String path) {
	return path.IsEmpty() || path == this->path;
}

bool MediaCaptureDevice::OpenDevice0(int fmt_i, int res_i) {
	Close();
	
	cur_time.Reset();
	
	if (fmt_i < 0 || fmt_i >= fmts.GetCount()) return false;
	const VideoInputFormat& fmt = fmts[fmt_i];
	
	if (res_i < 0 || res_i >= fmt.GetResolutionCount()) return false;
	const VideoInputFormatResolution& res = fmt.GetResolution(res_i);
	
	uint32 pix_fmt = fmt.GetPixelFormat();
	VideoFormat vid_fmt = res.GetFormat();
	Size sz = vid_fmt.res;
	const double fps = vid_fmt.fps;
	
	if (ocv && ocv->OpenDevice0(sz, fps, vid_fmt))
		return true;
	
#if flagV4L2
	V4L2DeviceParameters param(path, pix_fmt, sz.cx, sz.cy, fps, 0);
	vid_cap = V4l2Capture::create(param, V4l2Access::IOTYPE_MMAP);
	if (vid_cap) {
		open_pix_fmt = pix_fmt;
		open_frame_sz = sz;
		return true;
	}
#endif
	
	
	return false;
}

#ifdef flagOPENGL
bool DataPtrVideoBuffer::PaintOpenGLTexture(int texture) {
	if (ocv && ocv->PaintOpenGLTexture(texture))
		return true;
	
	return false;
}
#endif

bool MediaCaptureDevice::Read() {
	if (ocv && ocv->Read())
		return true;
	
#if flagV4L2
	if (vid_cap) {
		timeval timeout;
		bool is_readable = (vid_cap->isReadable(&timeout) == 1);
		
		if (is_readable) {
			TODO
			/*vbuffer.SetSize Count(buf_size);
			size_t nb = vid_cap->read(buffer.Begin(), buf_size);
			if (nb > 0 && nb < buf_size) {
				if (open_pix_fmt == V4L2_PIX_FMT_MJPEG) {
					#if flagV4L2_SLOW
					MemStream mem(buffer, nb);
					sw_frame = jpg_raster.Load(mem);
					Size sz = sw_frame.GetSize();
					COUT("Got frame size " << sz.ToString());
					return true;
					#endif
				}
			}*/
		}
	}
#endif
	
	return false;
}

void MediaCaptureDevice::Close() {
#if flagV4L2
	if (vid_cap) {
		vid_cap->stop();
		delete vid_cap;
		vid_cap = 0;
	}
#endif
}

bool MediaCaptureDevice::IsDeviceOpen() const {
	if (ocv && ocv->IsDeviceOpen())
		return true;
	
	return false;
}

bool MediaCaptureDevice::FindClosestFormat(Size cap_sz, double fps, double bw_min, double bw_max, int& ret_fmt, int& ret_res) {
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
		const VideoInputFormat& fmt = fmts[i];
		for(int j = 0; j < fmt.GetResolutionCount(); j++) {
			const VideoInputFormatResolution& fmt_res = fmt.GetResolution(j);
			VideoFormat vid_fmt = fmt_res.GetFormat();
			Size fmt_sz = vid_fmt.res;
			double fmt_fps = vid_fmt.fps;
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


NAMESPACE_OULU_END
