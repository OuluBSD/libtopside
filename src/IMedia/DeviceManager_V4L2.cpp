#include "IMedia.h"

#if HAVE_V4L2_DEVMGR

#include <fcntl.h>
#ifdef flagLINUX
	#include <linux/videodev2.h>
#endif
#include <libv4l2.h>
#include <sys/ioctl.h>


NAMESPACE_PARALLEL_BEGIN




V4L2_DeviceManager::V4L2_DeviceManager() {

}

void V4L2_DeviceManager::Refresh() {
	devs.Clear();
	
	for (int i = 0; i < 10; i++) {
		String path = "/dev/video" + IntStr(i);
		int fd = v4l2_open(path, O_RDWR);
		if (fd != -1) {
			V4L2_Device& dev = devs.Add();
			
			dev.path = path;
			
			#ifdef flagFREEBSD
			TODO
			#endif
			
			#ifdef flagLINUX
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
				
				capfmt.codec.pix_fmt = fmtdesc.pixelformat;
				
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
							res.fmt.Set(
								LightSampleFD::U8_LE_ABC,
								frmsize.discrete.width, frmsize.discrete.height,
								fps, 1);
							//LOG("\t" << res.fmt.ToString());
						}
						else if (frmsize.type == V4L2_FRMSIZE_TYPE_STEPWISE) {
							VideoSourceFormatResolution& res = capfmt.res.Add();
							res.fmt.Set(
								LightSampleFD::U8_LE_ABC,
								frmsize.stepwise.max_width, frmsize.stepwise.max_height,
								fps, 1);
							//LOG("\t" << res.fmt.ToString());
						}
						ival.index++;
					}
					frmsize.index++;
				}
				
				fmtdesc.index++;
			}
			v4l2_close(fd);
			#endif
		}
	}
}

NAMESPACE_PARALLEL_END

#endif
