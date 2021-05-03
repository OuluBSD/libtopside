#ifndef _Multimedia_Media_h_
#define _Multimedia_Media_h_


NAMESPACE_OULU_BEGIN







class MediaStreamThread : Moveable<MediaStreamThread> {
	MediaSourceStreamRef cap;
	
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
	void SetCap(MediaSourceStreamRef cap) {this->cap = cap;}
	bool IsRunning() const {return flag.IsRunning();}
	
	String GetLastError() const {return last_error;}
	
#ifdef flagOPENGL
	void PaintOpenGL(GLuint active_tex);
#endif
	
	
	Callback WhenError;
	
};



NAMESPACE_OULU_END


#endif
