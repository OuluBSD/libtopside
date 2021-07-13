#ifndef _Multimedia_Ffmpeg_ECS_h_
#define _Multimedia_Ffmpeg_ECS_h_

#if HAVE_FFMPEG

NAMESPACE_ECS_BEGIN


class FfmpegExt :
	public ComponentExtBase
{
	typedef enum {
		INVALID_MODE,
		AUDIO_ONLY,
		VIDEO_ONLY,
		AUDIOVIDEO,
	} Mode;
	
	FfmpegFileInput		file_in;
	Mode				mode = INVALID_MODE;
	
	String last_error;
	MediaStreamThread vi;
	//VideoProxy video_buf;
	Size def_cap_sz;
	int def_cap_fps;
	bool stops_machine = false;
	String file_path;
	
public:
	typedef FfmpegExt CLASSNAME;
	FfmpegExt();
	
	bool Initialize(const Eon::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis % file_in;}
	void Forward(FwdScope& fwd) override;
	void StorePacket(Packet& p) override;
	bool IsReady(ValDevCls vd) override;
	
	bool LoadFileAny(String path);
	void OnError();
	void OnStop();
	
	EXT_MAKE_ACTION_BEGIN
	if (vd.val.type == ValCls::AUDIO) {
		EXT_MAKE_ACTION_UNDEF_TO_TRUE("perma.audio.source.decoder")
	}
	else if (vd.val.type == ValCls::VIDEO) {
		EXT_MAKE_ACTION_UNDEF_TO_TRUE("perma.video.source.decoder")
	}
	EXT_MAKE_ACTION_END
	
	
	void SetError(String s);
	String GetLastError() const {return last_error;}
	
	MediaStreamThread& GetInput() {return vi;}
	
	
	Callback WhenStopped;
	
	static bool AllowDuplicates() {return true;}
	
};


NAMESPACE_ECS_END


#endif
#endif
