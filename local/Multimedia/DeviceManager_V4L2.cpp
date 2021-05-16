#include "Multimedia.h"

#if HAVE_V4L2_DEVMGR

#include <fcntl.h>
#include <linux/videodev2.h>
#include <libv4l2.h>
#include <sys/ioctl.h>


NAMESPACE_TOPSIDE_BEGIN

MediaStream* V4L2_Device::FindOpenDevice() {
	for (OpenCVCaptureDevice& m : caps)
		if (m.IsDeviceOpen())
			return &m;
	
	/*for (FfmpegFileInput& m : inputs)
		if (m.IsDeviceOpen())
			return &m;*/
	
	return 0;
}







V4L2_DeviceManager::V4L2_DeviceManager() {

}

/*V4L2_Device& V4L2_DeviceManager::GetAddVirtual(String path) {
	for(V4L2_Device& v : virtuals)
		if (v.GetPath() == path)
			return v;
	V4L2_Device& v = virtuals.Add();
	v.path = path;
	return v;
}*/

void V4L2_DeviceManager::Refresh() {
	devs.Clear();
	
	for (int i = 0; i < 10; i++) {
		String path = "/dev/video" + IntStr(i);
		int fd = v4l2_open(path, O_RDWR);
		if (fd != -1) {
			V4L2_Device& dev = devs.Add();
			
			dev.path = path;
			
			OpenCVCaptureDevice* cap = 0;
			struct v4l2_fmtdesc fmtdesc;
			memset(&fmtdesc, 0, sizeof(fmtdesc));
			fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			while (ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc) == 0) {
				
				/*if (fmtdesc.pixelformat != V4L2_PIX_FMT_MJPEG &&
					fmtdesc.pixelformat != V4L2_PIX_FMT) {
					fmtdesc.index++;
					continue; // unsupported
				}*/
				
				if (!cap) {
					cap = &dev.caps.Add();
					cap->path = path;
				}
				VideoSourceFormat& capfmt = cap->fmts.Add();
				capfmt.SetDescription((const char*)fmtdesc.description);
				
				TODO
				#if 0
				capfmt.pix_fmt = fmtdesc.pixelformat;
				
				struct v4l2_frmsizeenum frmsize;
				memset(&frmsize, 0, sizeof(frmsize));
				frmsize.pixel_format = fmtdesc.pixelformat;
				frmsize.index = 0;
				while (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmsize) >= 0) {
					struct v4l2_frmivalenum ival;
					memset(&ival, 0, sizeof(ival));
					ival.index = 0;
					ival.pixel_format = frmsize.pixel_format;
					ival.width = frmsize.discrete.width;
					ival.height = frmsize.discrete.height;
					
					while (ioctl(fd, VIDIOC_ENUM_FRAMEINTERVALS, &ival) >= 0) {
						double frame_time = (double)ival.discrete.numerator / (double)ival.discrete.denominator;
						double fps = 1.0 / frame_time;
						if (frmsize.type == V4L2_FRMSIZE_TYPE_DISCRETE) {
							VideoSourceFormatResolution& res = capfmt.res.Add();
							res.fmt.res.cx = frmsize.discrete.width;
							res.fmt.res.cy = frmsize.discrete.height;
							res.fmt.fps = fps;
							res.fmt.var_size = 1;
							res.fmt.channels = 3;
							res.fmt.SetLinePadding(0);
							//LOG("\t" << res.sz.ToString() << ", " << res.fps << "fps");
						}
						else if (frmsize.type == V4L2_FRMSIZE_TYPE_STEPWISE) {
							VideoSourceFormatResolution& res = capfmt.res.Add();
							res.fmt.res.cx = frmsize.stepwise.max_width;
							res.fmt.res.cy = frmsize.stepwise.max_height;
							res.fmt.fps = fps;
							res.fmt.var_size = 1;
							res.fmt.channels = 3;
							res.fmt.SetLinePadding(0);
							//LOG("\t" << res.sz.ToString() << ", " << res.fps << "fps");
						}
						ival.index++;
					}
					frmsize.index++;
				}
				#endif
				
				fmtdesc.index++;
			}
			v4l2_close(fd);
		}
	}
}

NAMESPACE_TOPSIDE_END

#endif
