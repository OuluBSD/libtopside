#ifndef _Multimedia_FileIn_Ffmpeg_h_
#define _Multimedia_FileIn_Ffmpeg_h_

#if HAVE_FFMPEG

NAMESPACE_OULU_BEGIN


class FfmpegAudioFrame :
	public AudioInputFrame,
	public LockedScopeEnabler<FfmpegAudioFrame>
{
	AVFrame* frame = 0;
	
public:
	
	void		Exchange(AudioEx& e) override;
	int			GetQueueSize() const override;
	AudioFormat	GetAudioFormat() const override;
	bool		IsQueueFull() const override;
	dword		GetWriteFrame() const override {throw Exc("FfmpegAudioFrame is not for writing");}
	bool		GetFrameFrom(Sound& snd, bool realtime) override;
#ifdef flagOPENGL
	bool		PaintOpenGLTexture(int texture) override;
#endif
	
	void		Process(double time_pos, AVFrame* frame);
	
};

typedef Ref<FfmpegAudioFrame> FfmpegAudioFrameRef;



#define FFMPEG_VIDEOFRAME_RGBA_CONVERSION 1
class FfmpegVideoFrame :
	public VideoInputFrame,
	public LockedScopeEnabler<FfmpegVideoFrame>
{
	
	
public:
	
	void		Exchange(VideoEx& e) override;
	int			GetQueueSize() const override;
	bool		IsQueueFull() const override;
#ifdef flagOPENGL
	bool		PaintOpenGLTexture(int texture) override;
#endif
	VideoFormat	GetVideoFormat() const override;
	
	void		Process(double time_pos, AVFrame* frame, bool vflip=true);
	
};

typedef Ref<FfmpegVideoFrame> FfmpegVideoFrameRef;



class FfmpegFileChannel {
	
protected:
	friend class FfmpegFileInput;
	
	AVFormatContext* file_fmt_ctx = NULL;
	AVCodecContext* codec_ctx = NULL;
	AVCodecParserContext *parser = NULL;
	AVFrame *frame = NULL;
	AVCodec* codec = NULL;
	double frame_pos_time = 0;
	int stream_i = -1;
	bool is_open = false;
	String errstr;
	
	//int read_frame_i = 0;
	
	int DecodePacket(AVPacket& pkt, int *got_frame);
	
public:
	
	bool IsOpen() const {return is_open;}
	
	void Clear();
	void ClearDevice();
	
	bool OpenVideo(AVFormatContext* file_fmt_ctx, VideoFormat& fmt);
	bool OpenAudio(AVFormatContext* file_fmt_ctx, AudioFormat& fmt);
	bool OpenDevice();
	
	bool ReadFrame(AVPacket& pkt);
	double GetSeconds() const {return frame_pos_time;}
	
};



class FfmpegFileInput : public MediaInputStream {
	bool has_audio;
	bool has_video;
	bool is_dev_open;
	AudioFormat aud_fmt;
	VideoFormat vid_fmt;
	String path;
	String errstr;
	RefLinkedList<FfmpegVideoFrame> vframes;
	RefLinkedList<FfmpegAudioFrame> aframes;
	Ref<FfmpegVideoFrame> cur_vframe;
	Ref<FfmpegAudioFrame> cur_aframe;
	FfmpegFileChannel v;
	FfmpegFileChannel a;
	AVFormatContext* file_fmt_ctx = NULL;
	AVPacket pkt;
	bool pkt_ref = false;
	int min_buf_size = 2;
	
	bool HasMediaOpen() const {return has_video || has_audio;}
	void Clear();
	void ClearDevice();
	void ClearFrame();
	bool IsFrameLoaded() const {return pkt_ref;}
	bool ReadFrame();
	bool ProcessVideoFrame();
	bool ProcessAudioFrame();
	
public:
	
	bool	Open0(String path) override;
	bool	OpenDevice0(int fmt, int res) override;
	bool	IsDeviceOpen() const override;
	int		FillVideoBuffer() override;
	int		FillAudioBuffer() override;
	void	DropFrames(int audio_frames, int video_frames) override;
	void	Close() override;
	String	GetPath() const override;
	Sound&	GetSound() override;
	Video&	GetVideo() override;
	String	GetLastError() const override;
	double	GetSeconds() const override;
	Size	GetVideoSize() const override;
	bool	IsEof() const;
	
	
};

NAMESPACE_OULU_END

#endif
#endif
