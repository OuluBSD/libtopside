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
	int def_cap_fps;
	bool stops_machine = false;
	String file_path;
	
	
public:
	typedef FfmpegAtomBase CLASSNAME;
	FfmpegAtomBase();
	
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
	void AltForward(FwdScope& fwd) override;
	void AltStorePacket(int sink_ch,  int src_ch, Packet& p) override;
	bool AltIsReady(ValDevCls vd) override;
	
	void Visit(RuntimeVisitor& vis) override {vis % file_in;}
	bool LoadFileAny(String path);
	void OnError();
	void OnStop();
	
	
	void SetError(String s);
	String GetLastError() const {return last_error;}
	
	MediaStreamThread& GetInput() {return vi;}
	
	
	Callback WhenStopped;
	
	static bool AllowDuplicates() {return true;}
	
};


NAMESPACE_SERIAL_END

#endif
#endif
