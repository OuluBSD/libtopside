#ifndef _Local_Media_h_
#define _Local_Media_h_


NAMESPACE_TOPSIDE_BEGIN


struct MediaFormat {
	AudioFormat snd;
	VideoFormat vid;
	
	bool IsValid() const {return snd.IsValid() || vid.IsValid();}
	
	bool operator!=(const MediaFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const MediaFormat& fmt) const {
		return	snd		== fmt.snd &&
				vid		== fmt.vid;
	}
};

struct AVBase {
	virtual Audio& GetAudio() = 0;
	virtual Video& GetVideo() = 0;
};

struct AVStreamBase {
	//virtual void FillVideoBuffer() = 0;
	//virtual void FillAudioBuffer() = 0;
	//virtual void Close() = 0;
	//virtual Audio& GetAudio() = 0;
	//virtual Video& GetVideo() = 0;
	virtual AudioStream& GetAudioStream() = 0;
	virtual VideoStream& GetVideoStream() = 0;
};

LOCAL_CTX(Media, AVBase, AVStreamBase)
#define MEDCTX MediaContext::Static()
#define MedCtx MediaContext&


class AVMediaProxy : public Media {
public:
	Audio* aud = 0;
	Video* vid = 0;

public:

	AVMediaProxy() = default;

	void Set(Audio& a, Video& v) {aud = &a; vid = &v;}
	Audio& GetAudio() override {return *aud;}
	Video& GetVideo() override {return *vid;}

	void			Exchange(MediaEx& e) override;
	int				GetQueueSize() const override;
	MediaFormat		GetFormat() const override;
	bool			IsQueueFull() const override;
	
};


NAMESPACE_TOPSIDE_END

#endif
