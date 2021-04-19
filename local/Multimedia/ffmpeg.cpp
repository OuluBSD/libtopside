#if FFMPEG
#include "Multimedia.h"

NAMESPACE_UPP

INITBLOCK {
	avdevice_register_all();
	avcodec_register_all();
	av_register_all();
}

EXITBLOCK {
	
}

END_UPP_NAMESPACE


NAMESPACE_OULU_BEGIN



void TestFfmpeg() {
	
	{
		AudioFrame aframe;
		MediaVideoFrame vframe;
		MediaFileInput fin;
		String file = "file://" + GetHomeDirectory() + DIR_SEPS + "test.mp4";
		LOG("Trying to open: " << file);
		if (!fin.Open(file, aframe, vframe)) {
			LOG("Opening file failed: " + fin.GetLastError());
			return;
		}
	}
	
}


NAMESPACE_OULU_END

#endif
