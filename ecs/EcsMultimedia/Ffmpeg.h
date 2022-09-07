#ifndef _Multimedia_Ffmpeg_ECS_h_
#define _Multimedia_Ffmpeg_ECS_h_

#if HAVE_FFMPEG

NAMESPACE_TOPSIDE_BEGIN


class FfmpegComponent :
	public Component<FfmpegComponent>,
	public AudioSource,
	public VideoSource
{
	FfmpegFileInput file_in;
	
	String last_error;
	MediaStreamThread vi;
	VideoProxy video_buf;
	Size def_cap_sz;
	int def_cap_fps;
	
public:
	RTTI_COMP2(FfmpegComponent, AudioSource, VideoSource)
	COPY_PANIC(FfmpegComponent);
	IFACE_CB(AudioSource);
	IFACE_CB(VideoSource);
	IFACE_GENERIC;
	VIS_COMP_2_0(Audio, Video)
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.source.decoder")
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.video.source.decoder")
	COMP_MAKE_ACTION_END
	
	FfmpegComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {COMP_DEF_VISIT_; vis % file_in;}
	
	// Audio
	AudioStream&	GetStream(AudCtx) override;
	void			BeginStream(AudCtx) override;
	void			EndStream(AudCtx) override;
	
	// Video
	VideoStream&	GetStream(VidCtx) override;
	void			BeginStream(VidCtx) override;
	void			EndStream(VidCtx) override;
	
	bool			LoadFileAny(String path);
	
	
	String GetLastError() const {return last_error;}
	
	MediaStreamThread& GetInput() {return vi;}
	
	
	Callback WhenStopped;
	
	static bool AllowDuplicates() {return true;}
	
};


NAMESPACE_TOPSIDE_END


#endif
#endif
