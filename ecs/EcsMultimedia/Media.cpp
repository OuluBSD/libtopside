#include "EcsMultimedia.h"


NAMESPACE_TOPSIDE_BEGIN


void MediaStreamThread::Start(bool separate_thrd) {
	Stop();
	this->separate_thrd = separate_thrd;
	if (separate_thrd) {
		flag.Start();
		Thread::Start(THISBACK(Process));
	}
}

void MediaStreamThread::Stop() {
	flag.Stop();
}

void MediaStreamThread::Process() {
	TODO
	#if 0
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
	#endif
}

void MediaStreamThread::FillVideoBuffer() {
	if (cap)
		cap->GetVideoStream().FillBuffer();
}

void MediaStreamThread::FillAudioBuffer() {
	if (cap)
		cap->GetAudioStream().FillBuffer();
}


void MediaStreamThread::Clear() {
	if (cap) {
		cap->Close();
		cap.Clear();
	}
}


#if HAVE_OPENGL
#if 0
void MediaStreamThread::PaintOpenGL(GLuint active_tex) {
	if (cap)
		cap->GetVideo().PaintOpenGLTexture(active_tex);
}
#endif
#endif


NAMESPACE_TOPSIDE_END
