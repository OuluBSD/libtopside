#include "EcsMultimedia.h"

#if HAVE_OPENCV

NAMESPACE_TOPSIDE_BEGIN


bool OpenCVComponent::LoadInput(int id) {
	if (id < 0 || id >= devmgr.GetNativeCount()) {
		last_error = "invalid input id: " + IntStr(id);
		return false;
	}
	
	V4L2_Device& dev = devmgr.GetNative(id);
	for(int l = 0; l < dev.GetCaptureCount() && !vi.IsCap(); l++) {
		OpenCVCaptureDevice& cap = dev.GetCapture(l);
		int fmt_i = -1;
		MediaFormat desired_format;
		TODO
		if (cap.FindClosestFormat(desired_format, fmt_i)) {
			if (cap.Open(fmt_i)) {
				vi.SetCap(cap.AsRef<MediaStream>());
				vi.Start(true);
				
				return true;
			}
			else {
				last_error = "couldn't open webcam " + cap.GetPath();
			}
		}
		else {
			last_error =
				"couldn't find expected format " + def_cap_sz.ToString() +
				", " + IntStr(def_cap_fps) +
				"fps from webcam "+ cap.GetPath();
		}
	}
	
	return false;
}


NAMESPACE_TOPSIDE_END

#endif
