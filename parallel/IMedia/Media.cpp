#include "IMedia.h"

NAMESPACE_PARALLEL_BEGIN


template <class Backend>
void MediaStreamThreadT<Backend>::Start(bool separate_thrd) {
	Stop();
	this->separate_thrd = separate_thrd;
	if (separate_thrd) {
		flag.Start();
		Thread::Start(THISBACK(Process));
	}
}

template <class Backend>
void MediaStreamThreadT<Backend>::Stop() {
	flag.Stop();
}

template <class Backend>
void MediaStreamThreadT<Backend>::Process() {
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

template <class Backend>
void MediaStreamThreadT<Backend>::FillVideoBuffer() {
	if (vcap)
		vcap->FillBuffer();
}

template <class Backend>
void MediaStreamThreadT<Backend>::FillAudioBuffer() {
	if (acap)
		acap->FillBuffer();
}

template <class Backend>
void MediaStreamThreadT<Backend>::Clear() {
	if (acap) {
		acap->Close();
		acap.Clear();
	}
	if (vcap) {
		vcap->Close();
		vcap.Clear();
	}
}


#if HAVE_OPENGL
#if 0
template <class Backend>
void MediaStreamThreadT<Backend>::PaintOpenGL(GLuint active_tex) {
	if (cap)
		cap->GetVideo().PaintOpenGLTexture(active_tex);
}
#endif
#endif


MEDIA_EXCPLICIT_INITIALIZE_CLASS(MediaStreamThreadT)


NAMESPACE_PARALLEL_END
