#ifndef _Multimedia_ECS_OpenCV_h_
#define _Multimedia_ECS_OpenCV_h_

#if HAVE_OPENCV

NAMESPACE_TOPSIDE_BEGIN


class OpenCVComponent :
	public Component<OpenCVComponent>,
	public AudioSource,
	public VideoSource
{
	VIS_COMP_2_0(Audio, Video)
	
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
	IFACE_CB(AudioSource);
	IFACE_CB(VideoSource);
	IFACE_GENERIC;
	
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


NAMESPACE_TOPSIDE_END

#endif
#endif
