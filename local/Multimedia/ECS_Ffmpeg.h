#ifndef _Multimedia_Ffmpeg_ECS_h_
#define _Multimedia_Ffmpeg_ECS_h_

#if HAVE_FFMPEG

NAMESPACE_TOPSIDE_BEGIN


class FfmpegComponent :
	public Component<FfmpegComponent>,
	public AudioSource,
	public VideoSource
{
	VIS_COMP_2_0(Audio, Video)
	
	FfmpegFileInput file_in;
	
	String last_error;
	MediaStreamThread vi;
	VideoProxy video_buf;
	Size def_cap_sz;
	int def_cap_fps;
	
public:
	COPY_PANIC(FfmpegComponent);
	IFACE_CB(AudioSource);
	IFACE_CB(VideoSource);
	IFACE_GENERIC;
	
	FfmpegComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis % file_in;}
	
	// Audio
	AudioStream&	GetAudioSource() override;
	void			BeginAudioSource() override;
	void			EndAudioSource() override;
	
	// Video
	VideoStream&	GetVideoSource() override;
	void			BeginVideoSource() override;
	void			EndVideoSource(bool any_sink_consumed) override;
	bool			LoadFileAny(String path) override;
	
	
	String GetLastError() const {return last_error;}
	
	MediaStreamThread& GetInput() {return vi;}
	
	
	Callback WhenStopped;
	
	static bool AllowDuplicates() {return true;}
	
};


NAMESPACE_TOPSIDE_END


#endif
#endif
