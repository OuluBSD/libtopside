#ifndef _AtomLocal_Ffmpeg_h_
#define _AtomLocal_Ffmpeg_h_

#if HAVE_FFMPEG

NAMESPACE_SERIAL_BEGIN


class FfmpegAtomBase :
	virtual public AtomBase
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
	Size def_cap_sz;
	double time = 0;
	int audio_ch = -1, video_ch = -1;
	int def_cap_fps = 25;
	bool stops_machine = false;
	bool vflip = false;
	bool video_packet_ready = false, audio_packet_ready = false;
	String filepath;
	
	
public:
	typedef FfmpegAtomBase CLASSNAME;
	FfmpegAtomBase();
	
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Forward(FwdScope& fwd) override;
	bool ProcessPackets(PacketIO& io) override;
	bool IsReady(PacketIO& io) override;
	bool PostInitialize() override;
	void Update(double dt) override;
	
	void Visit(RuntimeVisitor& vis) override {vis % file_in;}
	bool LoadFileAny(String path);
	void OnError();
	void OnStop();
	
	
	void SetError(String s);
	String GetLastError() const {return last_error;}
	
	MediaStreamThread& GetInput() {return vi;}
	
	
	Callback WhenStopped;
	
	
};


NAMESPACE_SERIAL_END

#endif
#endif
