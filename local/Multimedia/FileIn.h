#ifndef _Multimedia_FileIn_h_
#define _Multimedia_FileIn_h_

#if HAVE_MEDIAFILE

NAMESPACE_OULU_BEGIN

int GetOglDataType(int sample_size, int is_var_float);

class MediaAudioFrame : public AudioInputFrame {
	SoundFormat fmt;
	Vector<byte> data;
	double time_pos = 0;
	int unread = 0;
	
protected:
	friend class MediaFileInput;
	friend class MediaFileChannel;
	
	bool Attach(SoundFormat fmt, AVCodecContext& ctx);
	
	void Get(void* v, int size) override;
	void Put(void* v, int size, bool realtime) override;
	int GetQueueSize() const override;
	SoundFormat GetFormat() const override {return fmt;}
	bool IsQueueFull() const override;
	dword GetWriteFrame() const override {throw Exc("MediaAudioFrame is not for writing");}
#ifdef flagOPENGL
	bool PaintOpenGLTexture(int texture) override;
#endif
	
	void Clear();
	void Process(double time_pos, AVFrame* frame);
	double GetTime() const {return time_pos;}
	
};

class MediaVideoFrame : public VideoInputFrame {
	
protected:
	friend class MediaFileInput;
	friend class MediaFileChannel;
	
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
	MediaVideoFrame();
	~MediaVideoFrame() {Clear();}
	
	void Clear();
	
	void Process(double time_pos, AVFrame* frame, bool vflip=true);
	
	double GetTime() const {return time_pos;}
	Size GetSize() const {return fmt.res;}
	VideoFormat GetFormat() const override {return fmt;}
	int GetLinesize() const {return video_dst_linesize[0];}
	
	static const int ALIGN = 8;
	
};

class MediaFileChannel {
	
protected:
	friend class MediaFileInput;
	
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
	bool OpenAudio(AVFormatContext* file_fmt_ctx, SoundFormat& fmt);
	bool OpenDevice();
	
	int AddStep(double seconds);
	void NextFrame() {read_frame_i = (read_frame_i + 1) % 2;}
	int GetWriteFrame() {return (read_frame_i + 1) % 2;}
	bool ReadFrame(AVPacket& pkt);
	
	Callback1<bool&> WhenRead;
};

class MediaFileInput : public MediaInputStream {
	Array<VideoInputFormat> fmts;
	
	AVFormatContext* file_fmt_ctx = NULL;
	
	MediaFileChannel v;
	MediaFileChannel a;
	MediaVideoFrame vframe[2];
	MediaAudioFrame aframe[2];
	
	AVPacket pkt;
	AVPacket orig_pkt;
	bool is_orig_pkt_ref = false;
	
	void AttachVideo(VideoFormat fmt) {for(int i = 0; i < 2; i++) vframe[i].Attach(fmt, *v.codec_ctx);}
	void AttachAudio(SoundFormat fmt) {for(int i = 0; i < 2; i++) aframe[i].Attach(fmt, *a.codec_ctx);}
	
	
	SoundFormat snd_fmt;
	String errstr;
	bool is_file_open = false;
	bool is_dev_open = false;
	
	
	String path;
	
	
	
	bool ReadFrame();
	
public:
	typedef MediaFileInput CLASSNAME;
	MediaFileInput() {}
	MediaFileInput(String path) {Open(path);}
	~MediaFileInput() {Clear();}
	
	void Clear();
	void ClearDevice();
	
	bool Open0(String path) override;
	bool OpenDevice0(int fmt, int res) override;
	bool IsDeviceOpen() const override {return is_dev_open;}
	bool Step(double seconds) override;
	bool Read() override;
	void Close() override {Clear();}
	int GetFormatCount() const override {return fmts.GetCount();}
	const VideoInputFormat& GetFormat(int i) const override {return fmts[i];}
	String GetPath() const override {return path;}
	bool FindClosestFormat(Size cap_sz, double fps, double bw_min, double bw_max, int& fmt, int& res) override {TODO}
	Sound& GetSound() override;
	Video& GetVideo() override;
	
	String GetLastError() const override {return errstr;}
	
	double GetSeconds() const override {return v.IsOpen() ? v.read_pos_time : a.read_pos_time;}
	Size GetVideoSize() const override {return vframe[v.read_frame_i].GetSize();}
	
	SoundFormat GetSoundFormat() const {return snd_fmt;}
	
};


NAMESPACE_OULU_END

#endif
#endif
