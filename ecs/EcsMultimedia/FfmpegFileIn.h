#ifndef _Multimedia_FileIn_Ffmpeg_h_
#define _Multimedia_FileIn_Ffmpeg_h_

#if HAVE_FFMPEG

NAMESPACE_TOPSIDE_BEGIN

class FfmpegFileInput;

class FfmpegAudioFrameQueue :
	public AudioInputFrame,
	public RefScopeEnabler<FfmpegAudioFrameQueue,FfmpegFileInput>
{
	
protected:
	friend class FfmpegFileInput;
	
	
	
public:
	using Parent = FfmpegFileInput;
	RTTI_DECL_R1(FfmpegAudioFrameQueue, AudioInputFrame)
	~FfmpegAudioFrameQueue() {ClearBuffer();}
	
	void		FillAudioBuffer(double time_pos, AVFrame* frame);
	
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
	using Recycler = TS::Recycler<Frame,true>;
	using Pool = RecyclerPool<Frame,true>;
	
	struct SwsContext* img_convert_ctx = 0;
	Pool pool;
	LinkedList<Recycler> frames;
	int min_buf_samples = MIN_AUDIO_BUFFER_SAMPLES;
	
	
protected:
	friend class FfmpegFileInput;
	
	VideoFormat vid_fmt;
	
public:
	RTTI_DECL_R1(FfmpegVideoFrameQueue, VideoInputFrame)
	using Parent = FfmpegFileInput;
	~FfmpegVideoFrameQueue() {Clear();}
	
	void			Visit(RuntimeVisitor& vis) {}
	void			Init(AVCodecContext& ctx);
	void			Clear();
	void			FillBuffersNull();
	
	void				Exchange(VideoEx& e) override;
	int					GetQueueSize() const override;
	bool				IsQueueFull() const override;
	VideoFormat			GetFormat() const override;
	VideoPacketBuffer&	GetBuffer() override {TODO}
	
	void				Process(double time_pos, AVFrame* frame, bool vflip=true);
	void				DropFrames(int i);
	
};

typedef Ref<FfmpegVideoFrameQueue> FfmpegVideoFrameQueueRef;



class FfmpegFileChannel
{
	
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



class FfmpegFileInput :
	public RefScopeEnabler<FfmpegFileInput,ComponentBase>
{
	FfmpegAudioFrameQueue aframe;
	FfmpegVideoFrameQueue vframe;
	
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
	
	struct LocalAudioStream : public SimpleBufferedAudioStream {
		RTTI_DECL1(LocalAudioStream, AudioStream)
		FfmpegFileInput& par;
		LocalAudioStream(FfmpegFileInput* par) :
			par(*par),
			SimpleBufferedAudioStream(par->aframe) {}
		bool			IsOpen() const override;
		bool			Open(int fmt_idx) override;
		void			Close() override {par.Close();}
		bool			IsEof() override {return par.IsEof();}
		bool			ReadFrame() override {return par.ReadFrame();}
		bool			ProcessFrame() override {return par.ProcessAudioFrame();}
		bool			ProcessOtherFrame() override {return par.ProcessVideoFrame();}
		void			ClearPacketData() override {par.ClearPacketData();}
	};
	LocalAudioStream astream;
	
public:
	RTTI_DECL_R0(FfmpegFileInput)
	FfmpegFileInput();
	
	void SetParent(RefParent1<ComponentBase> p) override {
		RefScopeParent::SetParent(p);
		astream.SetParent(p);
	}
	
	bool	IsEof() const;
	void	Visit(RuntimeVisitor& vis) {vis % aframe % vframe;}
	void	Clear();
	double	GetSeconds() const;
	
	
	void	FillVideoBuffer();
	void	FillAudioBuffer();
	
	bool						IsOpenAudio() const {return has_audio;}
	bool						IsOpenVideo() const {return has_video;}
	bool						IsOpen() const;
	bool						Open();
	void						Close();
	Audio&						GetAudio();
	Video&						GetVideo();
	AudioStream&				GetAudioStream();
	VideoStream&				GetVideoStream();
	bool						OpenFile(String path);
	
	String	GetLastError() const;
	
	void	DropVideoFrames(int frames);
	String						GetPath() const;
	
	
	Callback WhenStopped;
	
};

NAMESPACE_TOPSIDE_END

#endif
#endif
