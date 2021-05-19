#ifndef _Multimedia_Media_h_
#define _Multimedia_Media_h_


NAMESPACE_TOPSIDE_BEGIN







class MediaStreamThread : Moveable<MediaStreamThread> {
	MediaStreamRef cap;
	
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
	
	MediaStream& Cap() {ASSERT(cap); return *cap;}
	bool IsCap() const {return cap;}
	void SetCap(MediaStreamRef cap) {this->cap = cap;}
	bool IsRunning() const {return flag.IsRunning();}
	
	String GetLastError() const {return last_error;}
	
#if HAVE_OPENGL
	void PaintOpenGL(GLuint active_tex);
#endif
	
	
	Callback WhenError;
	
};



NAMESPACE_TOPSIDE_END


#endif
