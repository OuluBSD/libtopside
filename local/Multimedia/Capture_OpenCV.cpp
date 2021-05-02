// problematic hal/interface.h usage fix
// clang and gcc behaves in a different way
#if defined flagGCC && defined flagFREEBSD
	#include "Internal.h"
	
	#undef CPU_SSE2
	#include <opencv2/core.hpp>
	#include <opencv2/imgproc.hpp>
	#include <opencv2/highgui.hpp>
	#include <opencv2/videoio.hpp>
	
	#include "Multimedia.h"
#else
	#include "Multimedia.h"
	
	#undef CPU_SSE2
	#include <opencv2/core.hpp>
	#include <opencv2/imgproc.hpp>
	#include <opencv2/highgui.hpp>
	#include <opencv2/videoio.hpp>
#endif

#if HAVE_OPENCV

NAMESPACE_OULU_BEGIN


class OpenCVCaptureDevice::Data {
public:
	OpenCVCaptureDevice& dev;
	
	cv::Mat frame, frame_flipped;
	cv::VideoCapture camera;
	
	Data(OpenCVCaptureDevice* dev) : dev(*dev) {}
	
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
	
	void Close() {camera.release();}
	
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









OpenCVCaptureDevice::OpenCVCaptureDevice() {
	ocv = new Data(this);
}

OpenCVCaptureDevice::~OpenCVCaptureDevice() {
	Close();
}

bool OpenCVCaptureDevice::Open0(String path) {
	return path.IsEmpty() || path == this->path;
}

bool OpenCVCaptureDevice::OpenDevice0(int fmt_i, int res_i) {
	Close();
	
	cur_time.Reset();
	
	if (fmt_i < 0 || fmt_i >= fmts.GetCount()) return false;
	const VideoInputFormat& fmt = fmts[fmt_i];
	
	if (res_i < 0 || res_i >= fmt.GetResolutionCount()) return false;
	const VideoInputFormatResolution& res = fmt.GetResolution(res_i);
	
	uint32 pix_fmt = fmt.GetPixelFormat();
	VideoFormat vid_fmt = res.GetVideoFormat();
	Size sz = vid_fmt.res;
	const double fps = vid_fmt.fps;
	
	if (ocv && ocv->OpenDevice0(sz, fps, vid_fmt))
		return true;
	
	return false;
}

int OpenCVCaptureDevice::FillVideoBuffer() {
	if (ocv && ocv->Read())
		return 1;
	
	return 0;
}

void OpenCVCaptureDevice::Close() {
	if (ocv)
		ocv->Close();
}

bool OpenCVCaptureDevice::IsDeviceOpen() const {
	if (ocv && ocv->IsDeviceOpen())
		return true;
	
	return false;
}



NAMESPACE_OULU_END

#endif
