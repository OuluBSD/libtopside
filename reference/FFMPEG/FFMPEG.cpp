#include <Multimedia/Multimedia.h>


void TestFfmpeg() {
	using namespace TS;
	
	AudioFrame aframe;
	MediaVideoFrame vframe;
	MediaFileInput fin;
	String file = "file://" + GetHomeDirectory() + DIR_SEPS + "test.mp4";
	LOG("Trying to open: " << file);
	if (!fin.Open(file, aframe, vframe)) {
		LOG("Opening file failed: " + fin.GetLastError());
		return;
	}
	
	TODO
}

CONSOLE_APP_MAIN {
	TestFfmpeg();
}
