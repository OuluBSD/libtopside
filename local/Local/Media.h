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

class Media {
	
public:
	Media() = default;
	virtual ~Media() = default;
	
	virtual Audio& GetAudio() = 0;
	virtual Video& GetVideo() = 0;
	
	MediaFormat GetFormat() {return MediaFormat {GetAudio().GetAudioFormat(), GetVideo().GetVideoFormat()};}
	
};


class MediaProxy : public Media {
	Media* media = 0;
	
public:
	MediaProxy() = default;
	MediaProxy(Media* media) : media(media) {}
	
	void Set(Media* media) {this->media = media;}
	
	Audio& GetAudio() override {if (media) return media->GetAudio(); throw Exc("MediaProxy is empty");}
	Video& GetVideo() override {if (media) return media->GetVideo(); throw Exc("MediaProxy is empty");}
	
};


class VolatileMediaBuffer : public Media {
public:
	VolatileAudioBuffer aud;
	VolatileVideoBuffer vid;
	
public:
	
	VolatileMediaBuffer() = default;
	
	
	Audio& GetAudio() override {return aud;}
	Video& GetVideo() override {return vid;}
	
	void Set(VideoFormat vid_fmt, int vid_frames, AudioFormat aud_fmt, int aud_frames) {
		if (vid_fmt.IsValid())
			vid.SetSize(vid_fmt, vid_frames);
		else
			vid.Clear();
		
		if (aud_fmt.IsValid())
			aud.SetSize(aud_fmt, aud_frames);
		else
			aud.Clear();
	}
	
};

class AVMediaProxy : public Media {
public:
	Audio* aud = 0;
	Video* vid = 0;
	
public:
	
	AVMediaProxy() = default;
	
	Audio& GetAudio() override {return *aud;}
	Video& GetVideo() override {return *vid;}
	
};








class MediaStream :
	public AudioStream,
	public VideoStream
{
	
	
protected:
	String last_path;
	int last_fmt = 0, last_res = 0;
	
	virtual bool OpenDevice0(int fmt, int res) = 0;
	virtual bool Open0(String path) = 0;
public:
	virtual ~MediaStream() {}
	
	bool Open(String path) {last_path = path; return Open0(path);}
	bool OpenDevice(int fmt, int res) {last_fmt = fmt; last_res = res; return OpenDevice0(fmt, res);}
	bool ReopenDevice() {return Open0(last_path) && OpenDevice0(last_fmt, last_res);}
	
	
	virtual bool	IsDeviceOpen() const = 0;
	virtual void	Close() = 0;
	virtual String	GetPath() const = 0;
	
	
	
};




class MediaSourceStream :
	public MediaStream,
	public RefScopeEnabler<MediaSourceStream,ComponentBase>
{
	
protected:
	friend class V4L2_DeviceManager;
	Array<VideoSourceFormat> fmts;
	
	
public:
	
	int		GetFormatCount() const override;
	bool	FindClosestFormat(Size cap_sz, double fps, double bw_min, double bw_max, int& fmt, int& res) override;
	const VideoSourceFormat& GetFormat(int i) const override;
	
};




class MediaSinkStream :
	public MediaStream,
	public RefScopeEnabler<MediaSinkStream,ComponentBase>
{
	
protected:
	friend class V4L2_DeviceManager;
	
	
public:
	
};



using MediaSourceStreamRef	= Ref<MediaSourceStream,RefParent1<ComponentBase>>;
using MediaSinkStreamRef	= Ref<MediaSinkStream,RefParent1<ComponentBase>>;

NAMESPACE_TOPSIDE_END

#endif
