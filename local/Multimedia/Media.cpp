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
	if (cap) {
		while (cap && cap->IsDeviceOpen() && flag.IsRunning()) {
			if (cap->IsAnyQueueEmpty()) {
				if (!cap->Step(0.001)) {
					continue;
				}
				
				if (cap->ReadAudio()) {
					// got new audio frame
				}
				else if (cap->ReadVideo()) {
					// got new video frame
				}
				else
					Sleep(1);
			}
			
			if (loop_file && !cap->IsDeviceOpen())
				cap->ReopenDevice();
			
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
