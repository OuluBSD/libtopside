#ifndef _IMedia_Media_h_
#define _IMedia_Media_h_

NAMESPACE_PARALLEL_BEGIN


template <class Backend>
class MediaStreamThreadT : Moveable<MediaStreamThreadT<Backend>> {
	using AudioInputFrame = typename Backend::AudioInputFrame;
	using VideoInputFrame = typename Backend::VideoInputFrame;
	using AudioInputFrameRef = typename Backend::AudioInputFrameRef;
	using VideoInputFrameRef = typename Backend::VideoInputFrameRef;
	
	AudioInputFrameRef acap;
	VideoInputFrameRef vcap;
	
	RunningFlagSingle flag;
	String last_error;
	bool loop_file = false;
	bool separate_thrd = false;
	
	
	void Process();
public:
	
	typedef MediaStreamThreadT CLASSNAME;
	MediaStreamThreadT() {}
	~MediaStreamThreadT() {Stop(); Clear();}
	
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
	bool IsSeparateThread() const {return separate_thrd;}
	
	
	Callback WhenError;
	
};


NAMESPACE_PARALLEL_END

#endif
