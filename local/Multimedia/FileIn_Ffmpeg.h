#ifndef _Multimedia_FileIn_Ffmpeg_h_
#define _Multimedia_FileIn_Ffmpeg_h_

#if HAVE_FFMPEG

NAMESPACE_OULU_BEGIN


class FfmpegAudioFrameQueue :
	public AudioInputFrame,
	public LockedScopeEnabler<FfmpegAudioFrameQueue>
{
	AudioPacketProducer producer;
	AudioPacketBuffer buf;
	dword frame_counter = 0;
	int min_buf_size = MIN_AUDIO_BUFFER_FRAMES;
	off32 begin, begin_offset_min, begin_offset_max, end_offset_min, end_offset_max;
	dword exchange_count = 0;
	
protected:
	friend class FfmpegFileInput;
	
	AudioFormat aud_fmt;
	
public:
	~FfmpegAudioFrameQueue() {Clear();}
	
	void		Init();
	void		Clear();
	void		FillAudioBuffer(double time_pos, AVFrame* frame);
	void		DropAudioBuffer();
	
	void		Exchange(AudioEx& e) override;
	int			GetQueueSize() const override;
	AudioFormat	GetAudioFormat() const override;
	bool		IsQueueFull() const override;
#ifdef flagOPENGL
	bool		PaintOpenGLTexture(int texture) override;
#endif
	
};

typedef Ref<FfmpegAudioFrameQueue> FfmpegAudioFrameQueueRef;



#define FFMPEG_VIDEOFRAME_RGBA_CONVERSION 1
class FfmpegVideoFrameQueue :
	public VideoInputFrame,
	public LockedScopeEnabler<FfmpegVideoFrameQueue>
{
	struct Frame : Moveable<Frame> {
		uint8_t *video_dst_data[4] = {0,0,0,0};
		uint8_t *video_dst_data_vflip[4] = {0,0,0,0};
		int      video_dst_linesize[4];
		int      video_dst_linesize_vflip[4];
		int      video_dst_bufsize = 0;
		double	time_pos;
		
		~Frame() {Clear();}
		void Init(const VideoFormat& vid_fmt);
		void Clear();
		void Process(double time_pos, AVFrame* frame, bool vflip, const VideoFormat& vid_fmt, SwsContext* img_convert_ctx);
		bool PaintOpenGLTexture(int texture, const VideoFormat& vid_fmt);
	};
	using Recycler = Oulu::Recycler<Frame,true>;
	using Pool = RecyclerPool<Frame,true>;
	
	struct SwsContext* img_convert_ctx = 0;
	Pool pool;
	LinkedList<Recycler> frames;
	int min_buf_size = 2;
	
	
protected:
	friend class FfmpegFileInput;
	
	VideoFormat vid_fmt;
	
public:
	~FfmpegVideoFrameQueue() {Clear();}
	
	void		Init(AVCodecContext& ctx);
	void		Clear();
	
	void		Exchange(VideoEx& e) override;
	int			GetQueueSize() const override;
	bool		IsQueueFull() const override;
#ifdef flagOPENGFfmpegFileInputL
	bool		PaintOpenGLTexture(int texture) override;
#endif
	VideoFormat	GetVideoFormat() const override;
	
	void		Process(double time_pos, AVFrame* frame, bool vflip=true);
	void		DropFrames(int i);
	
};

typedef Ref<FfmpegVideoFrameQueue> FfmpegVideoFrameQueueRef;



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



class FfmpegFileInput : public MediaSourceStream {
	bool has_audio;
	bool has_video;
	bool is_dev_open;
	String path;
	String errstr;
	FfmpegVideoFrameQueue vframe;
	FfmpegAudioFrameQueue aframe;
	FfmpegFileChannel v;
	FfmpegFileChannel a;
	AVFormatContext* file_fmt_ctx = NULL;
	AVPacket* pkt = 0;
	bool is_eof = false;
	bool pkt_ref = false;
	
	bool HasMediaOpen() const {return has_video || has_audio;}
	void Clear();
	void ClearDevice();
	void ClearPacketData();
	void ClearPacket();
	void InitPacket();
	bool IsFrameLoaded() const {return pkt_ref;}
	bool ReadFrame();
	bool ProcessVideoFrame();
	bool ProcessAudioFrame();
	
public:
	
	bool	IsEof() const;
	
	
	// Realtime
	double	GetSeconds() const override;
	String	GetLastError() const override;
	
	// Audio
	Audio&	GetAudio() override;
	void	FillAudioBuffer() override;
	void	DropAudioBuffer() override;
	
	// Video
	void	FillVideoBuffer() override;
	void	DropVideoFrames(int frames) override;
	Video&	GetVideo() override;
	int		GetActiveVideoFormat() const override;
	int		GetVideoBufferSize() const override {return vframe.GetQueueSize();}
	
	// Media
	bool	Open0(String path) override;
	bool	OpenDevice0(int fmt, int res) override;
	bool	IsDeviceOpen() const override;
	void	Close() override;
	String	GetPath() const override;
	
	
	
	Callback WhenStopped;
	
};

NAMESPACE_OULU_END

#endif
#endif
