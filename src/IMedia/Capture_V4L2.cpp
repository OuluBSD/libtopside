#include "IMedia.h"

#if 0
#if HAVE_V4L2_CAP

NAMESPACE_PARALLEL_BEGIN


bool CaptureDevice_V4L2::OpenDevice0(int fmt_i, int res_i) {
	Close();
	
	cur_time.Reset();
	
	if (fmt_i < 0 || fmt_i >= fmts.GetCount()) return false;
	const VideoSourceFormat& fmt = fmts[fmt_i];
	
	if (res_i < 0 || res_i >= fmt.GetResolutionCount()) return false;
	const VideoSourceFormatResolution& res = fmt.GetResolution(res_i);
	
	uint32 pix_fmt = fmt.GetPixelFormat();
	VideoFormat vid_fmt = res.GetFormat(VidCtx);
	Size sz = vid_fmt.size;
	const double fps = vid_fmt.fps;
	
	
	V4L2DeviceParameters param(path, pix_fmt, sz.cx, sz.cy, fps, 0);
	vid_cap = V4l2Capture::create(param, V4l2Access::IOTYPE_MMAP);
	if (vid_cap) {
		open_pix_fmt = pix_fmt;
		open_frame_sz = sz;
		return true;
	}
	
	return false;
}

void CaptureDevice_V4L2::Close() {
	if (vid_cap) {
		vid_cap->stop();
		delete vid_cap;
		vid_cap = 0;
	}
}

int CaptureDevice_V4L2::FillVideoBuffer() {
	
	if (vid_cap) {
		timeval timeout;
		bool is_readable = (vid_cap->isReadable(&timeout) == 1);
		
		if (is_readable) {
			TODO
			
		}
	}
	
	return 0;
}


NAMESPACE_PARALLEL_END

#endif
#endif
