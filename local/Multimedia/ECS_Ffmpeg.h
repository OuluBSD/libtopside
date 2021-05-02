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
	V4L2_DeviceManager devmgr;
	MediaStreamThread vi;
	VideoProxy video_buf;
	SoundProxy sound_buf;
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
	
	bool LoadFileAny(String path) override;
	void EmitVideoSource(double dt) override;
	void EmitAudioSource(double dt) override;
	void Play(const AudioSinkConfig& config, Sound& snd) override;
	
	bool LoadInput(int id);
	
	String GetLastError() const {return last_error;}
	
	MediaStreamThread& GetInput() {return vi;}
	
	
	static bool AllowDuplicates() {return true;}
	
};


NAMESPACE_OULU_END


#endif
#endif
