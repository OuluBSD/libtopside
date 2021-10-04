#ifndef _AtomLocal_OpenCV_h_
#define _AtomLocal_OpenCV_h_

NAMESPACE_SERIAL_BEGIN

#if 0

class OpenCVComponent :
	public Component<OpenCVComponent>,
	public AudioSource,
	public VideoSource
{
	OpenCVCaptureDevice cap;
	
	String last_error;
	V4L2_DeviceManager devmgr;
	MediaStreamThread vi;
	VideoProxy video_buf;
	AudioProxy audio_buf;
	Size def_cap_sz;
	int def_cap_fps;
	
	
public:
	RTTI_COMP2(OpenCVComponent, AudioSource, VideoSource)
	COPY_PANIC(OpenCVComponent);
	
	OpenCVComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {COMP_DEF_VISIT_; vis % cap;}
	
	//bool LoadFileAny(String path) override;
	
	bool LoadInput(int id);
	
	String GetLastError() const {return last_error;}
	
	MediaStreamThread& GetInput() {return vi;}
	
	
	static bool AllowDuplicates() {return true;}
	
	
	// Audio
	AudioStream&	GetStream(AudCtx) override {TODO}
	void			BeginStream(AudCtx) override {TODO}
	void			EndStream(AudCtx) override {TODO}
	
	// Video
	VideoStream&	GetStream(VidCtx) override {TODO}
	void			BeginStream(VidCtx) override {TODO}
	void			EndStream(VidCtx) override {TODO}
	
};

#endif

NAMESPACE_SERIAL_END

#endif
