#ifndef _Multimedia_Ffmpeg_ECS_h_
#define _Multimedia_Ffmpeg_ECS_h_

#if HAVE_FFMPEG

NAMESPACE_OULU_BEGIN


class FfmpegComponent :
	public Component<FfmpegComponent>,
	public AudioSource,
	public VideoSource
{
	String last_error;
	FfmpegFileInput file_in;
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
	
	
	static bool AllowDuplicates() {return true;}
	
};


NAMESPACE_OULU_END


#endif
#endif
