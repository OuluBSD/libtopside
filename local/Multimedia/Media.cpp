#include "Multimedia.h"


NAMESPACE_OULU_BEGIN


void MediaInputThread::Start() {
	Stop();
	flag.Start();
	Thread::Start(THISBACK(Process));
}

void MediaInputThread::Stop() {
	flag.Stop();
}

void MediaInputThread::Process() {
	ASSERT(cap);
	step_time.Reset();
	if (cap) {
		while (cap && cap->IsDeviceOpen() && flag.IsRunning()) {
			if (!cap->Step(ResetSeconds(step_time))) {
				Sleep(1);
				continue;
			}
			
			if (cap->ReadAudio()) {
				new_audio_frame = true;
			}
			else if (cap->ReadVideo()) {
				new_video_frame = true;
			}
			else {
				if (!cap->IsDeviceOpen())
					cap->ReopenDevice();
				else {
					last_error = "MediaInputThread::Process", "reading video input frame failed: " + cap->GetLastError();
					WhenError();
					Sleep(100);
				}
			}
		}
	}
	flag.SetStopped();
}


void MediaInputThread::Clear() {
	if (cap) {
		cap->Close();
		cap = 0;
	}
	path.Clear();
}


#ifdef flagOPENGL
void MediaInputThread::PaintOpenGL(GLuint active_tex) {
	if (cap) {
		cap->GetVideo().PaintOpenGLTexture(active_tex);
	}
}
#endif


NAMESPACE_OULU_END
