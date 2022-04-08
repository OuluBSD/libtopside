#ifndef _IMedia_FileIn_h_
#define _IMedia_FileIn_h_

NAMESPACE_PARALLEL_BEGIN



template <class Backend> class FileInputT;



template <class Backend>
class AudioFrameQueueT :
	public AudioInputFrameT<Backend>
{
	off32_gen	gen;
	
public:
	using FileInput = typename Backend::FileInput;
	using Base = AudioInputFrameT<Backend>;
	RTTI_DECL1(AudioFrameQueueT, Base)
	
	AudioFrameQueueT() {}
	
	void				FillAudioBuffer(double time_pos, AVFrame* frame);
	void				Visit(RuntimeVisitor& vis) {}
	
	void				Close() override;
	void				FillBuffer() override;
	
	int64				GetCurrentOffset() const {return gen.GetCurrent();}
	
};




template <class Backend>
class VideoFrameQueueT :
	public VideoInputFrameT<Backend>
{
	struct Frame : Moveable<Frame> {
		uint8_t *video_dst_data[4] = {0,0,0,0};
		uint8_t *video_dst_data_vflip[4] = {0,0,0,0};
		int      video_dst_linesize[4];
		int      video_dst_linesize_vflip[4];
		int      video_dst_bufsize = 0;
		double	time_pos = 0;
		
		~Frame() {Clear();}
		void	Init(const VideoFormat& vid_fmt);
		void	Clear();
		void	Process(double time_pos, AVFrame* frame, bool vflip, const VideoFormat& vid_fmt, SwsContext* img_convert_ctx);
		bool	PaintOpenGLTexture(int texture, const VideoFormat& vid_fmt);
		void	MakePacket(Packet& p);
	};
	using Recycler = TS::Recycler<Frame,true>;
	using Pool = RecyclerPool<Frame,true>;
	
	struct SwsContext*		img_convert_ctx = 0;
	LinkedList<Recycler>	frames;
	Pool					pool;
	int						min_buf_samples = MIN_AUDIO_BUFFER_SAMPLES;
	off32_gen				gen;
	
	
public:
	using FileInput = typename Backend::FileInput;
	using Base = VideoInputFrameT<Backend>;
	RTTI_DECL1(VideoFrameQueueT, Base)
	//using Parent = FileInputT;
	~VideoFrameQueueT() {Clear();}
	
	void				Visit(RuntimeVisitor& vis) {}
	void				Init(AVCodecContext& ctx);
	//void				FillBuffersNull();
	
	void				Close() override;
	void				Clear() override;
	void				FillBuffer() override;
	
	void				Process(double time_pos, AVFrame* frame, bool vflip=true);
	void				DropFrames(int i);
	
};



template <class Backend>
class FileChannelT
{
	
protected:
	using FileInput = class FileInputT<Backend>;
	friend FileInput;
	
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
	~FileChannelT() {Clear();}
	bool IsOpen() const {return is_open;}
	
	void Clear();
	void ClearDevice();
	
	bool OpenVideo(AVFormatContext* file_fmt_ctx, Format& fmt);
	bool OpenAudio(AVFormatContext* file_fmt_ctx, Format& fmt);
	bool OpenDevice();
	
	bool ReadFrame(AVPacket& pkt);
	double GetSeconds() const {return frame_pos_time;}
	
};



template <class Backend>
class FileInputT :
	public PacketBufferParent
{
	using AudioFrameQueue = typename Backend::AudioFrameQueue;
	using VideoFrameQueue = typename Backend::VideoFrameQueue;
	using FileChannel = typename Backend::FileChannel;
	
	AudioFrameQueue aframe;
	VideoFrameQueue vframe;
	
	bool has_audio;
	bool has_video;
	bool is_dev_open;
	String path;
	String errstr;
	FileChannel v;
	FileChannel a;
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
	RTTI_DECL_R0(FileInputT)
	FileInputT();
	~FileInputT() {Clear();}
	
	bool						IsEof() const;
	void						Visit(RuntimeVisitor& vis) {vis % aframe % vframe;}
	void						Clear();
	double						GetSeconds() const;
	bool						IsAudioOpen() const;
	
	void						FillVideoBuffer();
	void						FillAudioBuffer();
	AudioFrameQueue&			GetAudio() {return aframe;}
	VideoFrameQueue&			GetVideo() {return vframe;}
	
	bool						IsOpenAudio() const {return has_audio;}
	bool						IsOpenVideo() const {return has_video;}
	bool						IsOpen() const;
	bool						Open();
	void						Close();
	bool						OpenFile(String path);
	//void						SetFormat(Format fmt);
	
	String	GetLastError() const;
	
	void	DropVideoFrames(int frames);
	String						GetPath() const;
	
	
	Callback WhenStopped;
	
};



NAMESPACE_PARALLEL_END

#endif
