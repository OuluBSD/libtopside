#ifndef _AtomLocal_Media_h_
#define _AtomLocal_Media_h_

NAMESPACE_SERIAL_BEGIN


class MediaStreamThread : Moveable<MediaStreamThread> {
	AudioInputFrameRef acap;
	VideoInputFrameRef vcap;
	
	RunningFlagSingle flag;
	String last_error;
	bool loop_file = false;
	bool separate_thrd = false;
	
	
	void Process();
public:
	
	typedef MediaStreamThread CLASSNAME;
	MediaStreamThread() {}
	~MediaStreamThread() {Stop(); Clear();}
	
	void Clear();
	void Start(bool separate_thrd);
	void Stop();
	void FillVideoBuffer();
	void FillAudioBuffer();
	
	AudioInputFrame& GetAudio() {ASSERT(acap); return *acap;}
	VideoInputFrame& GetVideo() {ASSERT(vcap); return *vcap;}
	bool IsCap() const {return acap && vcap;}
	void SetCap(AudioInputFrameRef acap, VideoInputFrameRef vcap) {this->acap = acap; this->vcap = vcap;}
	bool IsRunning() const {return flag.IsRunning();}
	
	String GetLastError() const {return last_error;}
	
/*#if HAVE_OPENGL
	void PaintOpenGL(GLuint active_tex);
#endif*/
	
	
	Callback WhenError;
	
};


NAMESPACE_SERIAL_END

#endif
