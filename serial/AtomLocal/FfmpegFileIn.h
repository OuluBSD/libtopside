#ifndef _AtomLocal_FfmpegFileIn_h_
#define _AtomLocal_FfmpegFileIn_h_

#if HAVE_FFMPEG

NAMESPACE_SERIAL_BEGIN



class FfmpegFileInput;

class FfmpegAudioFrameQueue :
	public AudioInputFrame
{
	off32_gen	gen;
	off32		offset;
	
protected:
	friend class FfmpegFileInput;
	
	
	
public:
	using Parent = FfmpegFileInput;
	RTTI_DECL1(FfmpegAudioFrameQueue, AudioInputFrame)
	
	FfmpegAudioFrameQueue() : offset(gen) {}
	
	void				FillAudioBuffer(double time_pos, AVFrame* frame);
	void				Visit(RuntimeVisitor& vis) {}
	
	void				Close() override;
	void				FillBuffer() override;
	
	int64				GetCurrentOffset() const {return offset.value;}
	
};

typedef Ref<FfmpegAudioFrameQueue> FfmpegAudioFrameQueueRef;



#define FFMPEG_VIDEOFRAME_RGBA_CONVERSION 1
class FfmpegVideoFrameQueue :
	public VideoInputFrame
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
	
	Format fmt;
	
public:
	RTTI_DECL1(FfmpegVideoFrameQueue, VideoInputFrame)
	using Parent = FfmpegFileInput;
	~FfmpegVideoFrameQueue() {Clear();}
	
	void				Visit(RuntimeVisitor& vis) {}
	void				Init(AVCodecContext& ctx);
	//void				FillBuffersNull();
	
	void				Close() override;
	void				Clear() override;
	void				FillBuffer() override;
	
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
	~FfmpegFileChannel() {Clear();}
	bool IsOpen() const {return is_open;}
	
	void Clear();
	void ClearDevice();
	
	bool OpenVideo(AVFormatContext* file_fmt_ctx, Format& fmt);
	bool OpenAudio(AVFormatContext* file_fmt_ctx, Format& fmt);
	bool OpenDevice();
	
	bool ReadFrame(AVPacket& pkt);
	double GetSeconds() const {return frame_pos_time;}
	
};



class FfmpegFileInput :
	public PacketBufferParent
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
	//void FillBuffersNull();
	
	
public:
	RTTI_DECL_R0(FfmpegFileInput)
	FfmpegFileInput();
	~FfmpegFileInput() {Clear();}
	
	bool						IsEof() const;
	void						Visit(RuntimeVisitor& vis) {vis % aframe % vframe;}
	void						Clear();
	double						GetSeconds() const;
	bool						IsAudioOpen() const;
	
	void						FillVideoBuffer();
	void						FillAudioBuffer();
	FfmpegAudioFrameQueue&		GetAudio() {return aframe;}
	FfmpegVideoFrameQueue&		GetVideo() {return vframe;}
	
	bool						IsOpenAudio() const {return has_audio;}
	bool						IsOpenVideo() const {return has_video;}
	bool						IsOpen() const;
	bool						Open();
	void						Close();
	bool						OpenFile(String path);
	void						SetFormat(Format fmt);
	
	String	GetLastError() const;
	
	void	DropVideoFrames(int frames);
	String						GetPath() const;
	
	
	Callback WhenStopped;
	
};



NAMESPACE_SERIAL_END

#endif
#endif
