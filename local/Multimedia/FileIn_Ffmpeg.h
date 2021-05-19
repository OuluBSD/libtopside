#ifndef _Multimedia_FileIn_Ffmpeg_h_
#define _Multimedia_FileIn_Ffmpeg_h_

#if HAVE_FFMPEG

NAMESPACE_TOPSIDE_BEGIN

class FfmpegFileInput;

class FfmpegAudioFrameQueue :
	public AudioInputFrame,
	public RefScopeEnabler<FfmpegAudioFrameQueue,FfmpegFileInput>
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
	
	void		Visit(RuntimeVisitor& vis) {}
	void		Init();
	void		Clear();
	void		FillAudioBuffer(double time_pos, AVFrame* frame);
	void		FillBuffersNull();
	void		DropAudioBuffer();
	
	void		Exchange(AudioEx& e) override;
	int			GetQueueSize() const override;
	AudioFormat	GetFormat() const override;
	bool		IsQueueFull() const override;
	
};

typedef Ref<FfmpegAudioFrameQueue> FfmpegAudioFrameQueueRef;



#define FFMPEG_VIDEOFRAME_RGBA_CONVERSION 1
class FfmpegVideoFrameQueue :
	public VideoInputFrame,
	public RefScopeEnabler<FfmpegVideoFrameQueue,FfmpegFileInput>
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
	using Recycler = Topside::Recycler<Frame,true>;
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
	
	void		Visit(RuntimeVisitor& vis) {}
	void		Init(AVCodecContext& ctx);
	void		Clear();
	void		FillBuffersNull();
	
	void		Exchange(VideoEx& e) override;
	int			GetQueueSize() const override;
	bool		IsQueueFull() const override;
	VideoFormat	GetFormat() const override;
	
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



class FfmpegFileInput : public MediaStream {
	FfmpegAudioFrameQueue aframe;
	FfmpegVideoFrameQueue vframe;
	AVMediaProxy avproxy;
	
	bool has_audio;
	bool has_video;
	bool is_dev_open;
	String path;
	String errstr;
	FfmpegFileChannel v;
	FfmpegFileChannel a;
	AVFormatContext* file_fmt_ctx = NULL;
	AVPacket* pkt = 0;
	bool is_eof = false;
	bool pkt_ref = false;
	
	bool HasMediaOpen() const {return has_video || has_audio;}
	void ClearDevice();
	void ClearPacketData();
	void ClearPacket();
	void InitPacket();
	bool IsFrameLoaded() const {return pkt_ref;}
	bool ReadFrame();
	bool ProcessVideoFrame();
	bool ProcessAudioFrame();
	void FillBuffersNull();
	
public:
	FfmpegFileInput();
	
	bool	IsEof() const;
	void	Visit(RuntimeVisitor& vis) {vis % aframe % vframe;}
	void	Clear();
	double	GetSeconds() const;
	
	
	Media&						Get() override {return avproxy;}
	void						FillBuffer() override {}
	void						DropBuffer() override {}
	int							GetActiveFormatIdx() const override;
	int							GetFormatCount() const override;
	MediaFormat					GetFormat(int i) const override;
	bool						FindClosestFormat(const MediaFormat&, int& idx) override;;
	//void	FillVideoBuffer() override;
	//void	FillAudioBuffer() override;
	bool	IsOpen() const override;
	bool	Open(int fmt_idx) override;
	void	Close() override;
	//Audio&	GetAudio() override;
	//Video&	GetVideo() override;
	AudioStream&	GetAudioStream() override;
	VideoStream&	GetVideoStream() override;
	bool	OpenFile(String path);
	
	/*
	// Realtime
	String	GetLastError() const override;
	
	// Audio
	void	DropAudioBuffer() override;
	
	// Video
	void	DropVideoFrames(int frames) override;
	int		GetActiveVideoFormatIdx() const override;
	int		GetVideoBufferSize() const override {return vframe.GetQueueSize();}
	
	// Media
	bool	Open0(String path) override;
	bool	OpenDevice0(int fmt, int res) override;
	String	GetPath() const override;*/
	
	
	
	Callback WhenStopped;
	
};

NAMESPACE_TOPSIDE_END

#endif
#endif
