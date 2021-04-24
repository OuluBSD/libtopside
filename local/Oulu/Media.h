#ifndef _Oulu_Media_h_
#define _Oulu_Media_h_


NAMESPACE_OULU_BEGIN


struct MediaFormat {
	SoundFormat snd;
	VideoFormat vid;
	
	bool IsValid() const {return snd.IsValid() || vid.IsValid();}
	
	bool operator!=(const MediaFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const MediaFormat& fmt) const {
		return	snd		== fmt.snd &&
				vid		== fmt.vid;
	}
};

class Media {
	
public:
	Media() = default;
	virtual ~Media() = default;
	
	virtual Sound& GetSound() = 0;
	virtual Video& GetVideo() = 0;
	
	MediaFormat GetFormat() {return MediaFormat {GetSound().GetFormat(), GetVideo().GetFormat()};}
	
};


class MediaProxy : public Media {
	Media* media = 0;
	
public:
	MediaProxy() = default;
	MediaProxy(Media* media) : media(media) {}
	
	void Set(Media* media) {this->media = media;}
	
	Sound& GetSound() override {if (media) return media->GetSound(); throw Exc("MediaProxy is empty");}
	Video& GetVideo() override {if (media) return media->GetVideo(); throw Exc("MediaProxy is empty");}
	
};


class VolatileMediaBuffer : public Media {
public:
	VolatileSoundBuffer snd;
	VolatileVideoBuffer vid;
	
public:
	
	VolatileMediaBuffer() = default;
	
	
	Sound& GetSound() override {return snd;}
	Video& GetVideo() override {return vid;}
	
	void Set(VideoFormat vid_fmt, int vid_frames, SoundFormat snd_fmt, int snd_frames) {
		if (vid_fmt.IsValid())
			vid.SetSize(vid_fmt, vid_frames);
		else
			vid.Clear();
		
		if (snd_fmt.IsValid())
			snd.SetSize(snd_fmt, snd_frames);
		else
			snd.Clear();
	}
	
};

class MediaPtrBuffer : public Media {
public:
	Sound* snd = 0;
	Video* vid = 0;
	
public:
	
	MediaPtrBuffer() = default;
	
	Sound& GetSound() override {return *snd;}
	Video& GetVideo() override {return *vid;}
	
};

NAMESPACE_OULU_END

#endif
