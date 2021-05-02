#if 0
#ifndef _Multimedia_FileIn_h_
#define _Multimedia_FileIn_h_

#if HAVE_FFMPEG

NAMESPACE_OULU_BEGIN


int GetOglDataType(int sample_size, int is_var_float);

class FfmpegAudioFrame : public AudioInputFrame {
	AudioFormat fmt;
	Vector<byte> data;
	double time_pos = 0;
	int unread = 0;
	
protected:
	friend class FfmpegFileInput;
	friend class FfmpegFileChannel;
	
	bool Attach(AudioFormat fmt, AVCodecContext& ctx);
	
	void Get(void* v, int size) override;
	void Put(void* v, int size, bool realtime) override;
	int GetQueueSize() const override;
	AudioFormat GetAudioFormat() const override {return fmt;}
	bool IsQueueFull() const override;
	dword GetWriteFrame() const override {throw Exc("FfmpegAudioFrame is not for writing");}
	bool GetFrameFrom(Sound& snd, bool realtime) override;
#ifdef flagOPENGL
	bool PaintOpenGLTexture(int texture) override;
#endif
	
	void Clear();
	void Process(double time_pos, AVFrame* frame);
	double GetTime() const {return time_pos;}
	
};

class FfmpegVideoFrame : public VideoInputFrame {
	
protected:
	friend class FfmpegFileInput;
	friend class FfmpegFileChannel;
	
	struct SwsContext* img_convert_ctx = 0;
	AVFrame* rgba_frame = 0;
	
	uint8_t *video_dst_data[4] = {0,0,0,0};
	uint8_t *video_dst_data_vflip[4] = {0,0,0,0};
	int      video_dst_linesize[4];
	int      video_dst_linesize_vflip[4];
	int      video_dst_bufsize = 0;
	
	double time_pos = 0;
	VideoFormat fmt;
	
	bool Attach(VideoFormat fmt, AVCodecContext& ctx);
	
	void Get(void* v, int size) override;
	void Put(void* v, int size, bool realtime) override;
	int GetQueueSize() const override;
	bool IsQueueFull() const override;
#ifdef flagOPENGL
	bool PaintOpenGLTexture(int texture) override;
#endif
	
public:
	FfmpegVideoFrame();
	~FfmpegVideoFrame() {Clear();}
	
	void Clear();
	
	void Process(double time_pos, AVFrame* frame, bool vflip=true);
	
	double GetTime() const {return time_pos;}
	Size GetSize() const {return fmt.res;}
	VideoFormat GetVideoFormat() const override {return fmt;}
	int GetLinesize() const {return video_dst_linesize[0];}
	
	static const int ALIGN = 8;
	
};

class FfmpegFileChannel {
	
protected:
	friend class FfmpegFileInput;
	
	AVFormatContext* file_fmt_ctx = NULL;
	AVCodecContext* codec_ctx = NULL;
	AVCodecParserContext *parser = NULL;
	AVFrame *frame = NULL;
	AVCodec* codec = NULL;
	double read_pos_time = 0;
	double frame_pos_time = 0;
	int read_frame_i = 0;
	int stream_i = -1;
	bool is_open = false;
	
	String errstr;
	
	
	int DecodePacket(AVPacket& pkt, int *got_frame);
public:
	
	bool IsOpen() const {return is_open;}
	
	void Clear();
	void ClearDevice();
	
	bool OpenVideo(AVFormatContext* file_fmt_ctx, VideoFormat& fmt);
	bool OpenAudio(AVFormatContext* file_fmt_ctx, AudioFormat& fmt);
	bool OpenDevice();
	
	int AddStep(double seconds);
	void NextFrame() {read_frame_i = (read_frame_i + 1) % 2;}
	int GetWriteFrame() {return (read_frame_i + 1) % 2;}
	bool ReadFrame(AVPacket& pkt);
	
	Callback1<bool&> WhenRead;
};

class FfmpegFileInput : public MediaInputStream {
	Array<VideoInputFormat> fmts;
	
	AVFormatContext* file_fmt_ctx = NULL;
	
	FfmpegFileChannel v;
	FfmpegFileChannel a;
	FfmpegVideoFrame vframe[2];
	FfmpegAudioFrame aframe[2];
	
	AVPacket pkt;
	AVPacket orig_pkt;
	bool is_orig_pkt_ref = false;
	
	void AttachVideo(VideoFormat fmt) {for(int i = 0; i < 2; i++) vframe[i].Attach(fmt, *v.codec_ctx);}
	void AttachAudio(AudioFormat fmt) {for(int i = 0; i < 2; i++) aframe[i].Attach(fmt, *a.codec_ctx);}
	
	
	AudioFormat aud_fmt;
	String errstr;
	bool is_file_open = false;
	bool is_dev_open = false;
	
	
	String path;
	
	
	
	bool ReadAudioFrame();
	bool ReadVideoFrame();
	bool Read(bool audio);
	
public:
	typedef FfmpegFileInput CLASSNAME;
	FfmpegFileInput() {}
	FfmpegFileInput(String path) {Open(path);}
	~FfmpegFileInput() {Clear();}
	
	void Clear();
	void ClearDevice();
	
	bool Open0(String path) override;
	bool OpenDevice0(int fmt, int res) override;
	bool IsDeviceOpen() const override {return is_dev_open;}
	bool Step(double seconds) override;
	bool ReadVideo() override {return Read(false);}
	bool ReadAudio() override {return Read(true);}
	void Close() override {Clear();}
	String GetPath() const override {return path;}
	Sound& GetSound() override;
	Video& GetVideo() override;
	
	String GetLastError() const override {return errstr;}
	
	double GetSeconds() const override {return v.IsOpen() ? v.read_pos_time : a.read_pos_time;}
	Size GetVideoSize() const override {return vframe[v.read_frame_i].GetSize();}
	
	AudioFormat GetAudioFormat() const {return aud_fmt;}
	
};


NAMESPACE_OULU_END

#endif
#endif
#endif
