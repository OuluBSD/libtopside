#include "Multimedia.h"


#if HAVE_FFMPEG

NAMESPACE_OULU_BEGIN


void FfmpegFileInput::Clear() {
	ClearDevice();
	
	has_audio = false;
	has_video = false;
	is_dev_open = false;
	aud_fmt.Clear();
	vid_fmt.Clear();
	path.Clear();
	errstr.Clear();
	
}

void FfmpegFileInput::ClearDevice() {
	is_dev_open = 0;
	cur_aframe.Clear();
	cur_vframe.Clear();
	aframes.Clear();
	vframes.Clear();
	
	ClearFrame();
}

void FfmpegFileInput::ClearFrame() {
	if (pkt_ref) {
		av_packet_unref(&pkt);
		pkt_ref = false;
	}
}

bool FfmpegFileInput::Open0(String path) {
	Clear();
	
	this->path = path;
	
	// Open video file
	if(avformat_open_input(&file_fmt_ctx, path.Begin(), NULL, NULL) != 0) {
		errstr = "couldn't open file: " + path;
		return false;
	}
	
	// Retrieve stream information
	if(avformat_find_stream_info(file_fmt_ctx, NULL)<0) {
		errstr = "couldn't find stream information";
		return false;
	}
	
	// Dump information about file onto standard error
	av_dump_format(file_fmt_ctx, 0, path.Begin(), 0);
	
	// Find the first video stream
	has_audio = a.OpenAudio(file_fmt_ctx, aud_fmt);
	has_video = v.OpenVideo(file_fmt_ctx, vid_fmt);
	
	if (has_video) {
		VideoInputFormat& vf = fmts.Add();
		VideoInputFormatResolution& res = vf.res.Add();
		res.fmt = vid_fmt;
	}
	
	return HasMediaOpen();
}

bool FfmpegFileInput::OpenDevice0(int fmt, int res) {
	ClearDevice();
	
	if (!HasMediaOpen())
		return false;
	
	if (fmt != 0 || res != 0)
		return false;
	
	bool audio_open = has_audio ? a.OpenDevice() : false;
	bool video_open = has_video ? v.OpenDevice() : false;
	
	av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;
    
	is_dev_open = audio_open || video_open;
	return is_dev_open;
}

bool FfmpegFileInput::IsDeviceOpen() const {
	return is_dev_open;
}

int FfmpegFileInput::FillVideoBuffer() {
	while (vframes.GetCount() < min_buf_size && !IsEof()) {
		if (ReadFrame()) {
			if (ProcessVideoFrame())
				continue;
			if (ProcessAudioFrame())
				continue;
		}
		else break;
	}
	return vframes.GetCount();
}

int FfmpegFileInput::FillAudioBuffer() {
	while (aframes.GetCount() < min_buf_size && !IsEof()) {
		if (ReadFrame()) {
			if (ProcessVideoFrame())
				continue;
			if (ProcessAudioFrame())
				continue;
		}
		else break;
	}
	return aframes.GetCount();
}

bool FfmpegFileInput::ReadFrame() {
	ClearFrame();
	
	if (av_read_frame(file_fmt_ctx, &pkt) >= 0) {
		pkt_ref = true;
		return true;
	}
	
	return false;
}

bool FfmpegFileInput::ProcessVideoFrame() {
	ASSERT(pkt_ref);
	if (v.ReadFrame(pkt)) {
		FfmpegVideoFrameRef f = vframes.Add();
		f->Process(v.frame_pos_time, v.frame);
		ClearFrame();
		return true;
	}
	
	return false;
}

bool FfmpegFileInput::ProcessAudioFrame() {
	ASSERT(pkt_ref);
	if (a.ReadFrame(pkt)) {
		FfmpegAudioFrameRef f = aframes.Add();
		f->Process(a.frame_pos_time, a.frame);
		ClearFrame();
		return true;
	}
	
	return false;
}

void FfmpegFileInput::DropFrames(int audio_frames, int video_frames) {
	audio_frames = std::min(audio_frames, aframes.GetCount());
	video_frames = std::min(video_frames, vframes.GetCount());
	
	if (audio_frames) {
		cur_aframe.Clear();
		aframes.RemoveFirst(audio_frames);
	}
	
	if (video_frames) {
		cur_vframe.Clear();
		vframes.RemoveFirst(video_frames);
	}
}

void FfmpegFileInput::Close() {
	Clear();
}

String FfmpegFileInput::GetPath() const {
	return path;
}

Sound& FfmpegFileInput::GetSound() {
	cur_aframe = *aframes.begin();
	return *cur_aframe;
}

Video& FfmpegFileInput::GetVideo() {
	cur_vframe = *vframes.begin();
	return *cur_vframe;
}

String FfmpegFileInput::GetLastError() const {
	return errstr;
}

double FfmpegFileInput::GetSeconds() const {
	if (a.IsOpen())
		return a.GetSeconds();
	if (v.IsOpen())
		return v.GetSeconds();
	return 0;
}

Size FfmpegFileInput::GetVideoSize() const {
	RefLinkedList<FfmpegVideoFrame>& vframes = const_cast<RefLinkedList<FfmpegVideoFrame>&>(this->vframes);
	if (vframes.GetCount())
		return vframes.begin()->GetVideoFormat().GetSize();
	return Size(0,0);
}

bool FfmpegFileInput::IsEof() const {
	TODO
}













int FfmpegFileChannel::DecodePacket(AVPacket& pkt, int *got_frame) {
    int ret = 0;
    int decoded = pkt.size;
    *got_frame = 0;
        
    // Decode frame
    ret = avcodec_send_packet(codec_ctx, &pkt);
    if (ret == AVERROR_EOF) {
        is_open = false;
        errstr = "Eof in packet decoding";
        return -1;
    }
    else if (ret != 0) {
        errstr = "Failed to decode packet";
        return -1;
    }
    
    // Receive frame
    ret = avcodec_receive_frame(codec_ctx, frame);
    if (ret == AVERROR_EOF) {
        is_open = false;
        errstr = "Eof in frame decoding";
        return -1;
    }
    else if (ret != 0) {
        errstr = "Error decoding frame";
        return -1;
    }
    else {
        *got_frame = 1;
        
		double frame_time = (double)codec_ctx->time_base.num / (double)codec_ctx->time_base.den;
		if (codec_ctx->time_base.num == 0)
			frame_time = 1.0 / 1000.0;
		frame_pos_time = frame->pts * frame_time;
    }
    
    return decoded;
}

void FfmpegFileChannel::Clear() {
	if (frame)
		av_frame_free(&frame);
	frame = 0;
	
	if (parser)
		av_parser_close(parser);
	parser = NULL;
	
	if (codec_ctx)
		avcodec_free_context(&codec_ctx);
	codec_ctx = NULL;
	
	stream_i = -1;
	codec = NULL;
	
	is_open = false;
}

void FfmpegFileChannel::ClearDevice() {
	codec = NULL;
	frame_pos_time = 0;
}

bool FfmpegFileChannel::OpenVideo(AVFormatContext* file_fmt_ctx, VideoFormat& fmt) {
	Clear();
	fmt.Clear();
	
	this->file_fmt_ctx = file_fmt_ctx;
	
	stream_i = -1;
	for (int i = 0; i < file_fmt_ctx->nb_streams; i++) {
		if (file_fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && stream_i < 0) {
			stream_i = i;
		}
	}
	if (stream_i == -1) {
		errstr = "did not find video stream";
		return false;
	}
	
	AVStream* vstream = file_fmt_ctx->streams[stream_i];
	AVCodecParameters* vcodec = vstream->codecpar;
	
	double fps = (double)vstream->avg_frame_rate.num / (double)vstream->avg_frame_rate.den;
	Size frame_sz(vcodec->width, vcodec->height);
	
	fmt.res = frame_sz;
	fmt.fps = fps;
	
	#if FFMPEG_VIDEOFRAME_RGBA_CONVERSION
	fmt.var_size = 1;
	fmt.channels = 4;
	#else
	switch (vcodec->format) {
	case AV_PIX_FMT_RGB24:
		fmt.var_size = 1;
		fmt.channels = 3;
		break;
	case AV_PIX_FMT_RGBA:
		fmt.var_size = 1;
		fmt.channels = 4;
		break;
	case AV_PIX_FMT_VAAPI:
		errstr = "VAAPI support unimplemented";
		return false;
	default:
		errstr = "unsupported video pixel format";
		return false;
	}
	#endif
	
	fmt.SetLinePadding(0); // unknown at this point. Only AVFrame can tell
	
	is_open = true;
	return true;
}

bool FfmpegFileChannel::OpenAudio(AVFormatContext* file_fmt_ctx, AudioFormat& fmt) {
	Clear();
	fmt.Clear();
	
	this->file_fmt_ctx = file_fmt_ctx;
	
	stream_i = -1;
	for (int i = 0; i < file_fmt_ctx->nb_streams; i++) {
		if (file_fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && stream_i < 0) {
			stream_i = i;
		}
	}
	if (stream_i == -1) {
		errstr = "did not find audio stream";
		return false;
	}
	
	AVStream* astream = file_fmt_ctx->streams[stream_i];
	AVCodecParameters* acodec = astream->codecpar;
	
	fmt.channels = acodec->channels;
	fmt.freq = acodec->sample_rate;
	fmt.sample_rate = acodec->frame_size;
	fmt.var_size = 0;
	fmt.is_var_float = 0;
	if (!fmt.sample_rate)
		fmt.sample_rate = 1024;
	switch (acodec->format) {
		#define SET_FMT(f, var_sz, var_flt, var_sign, var_be) \
		case f: \
			fmt.var_size = var_sz; \
			fmt.is_var_float = var_flt; \
			fmt.is_var_signed = var_sign; \
			fmt.is_var_bigendian = var_be; \
			break;
		SET_FMT(AV_SAMPLE_FMT_U8, 1, 0, 0, 0);
		SET_FMT(AV_SAMPLE_FMT_S16, 2, 0, 1, 0);
		SET_FMT(AV_SAMPLE_FMT_S32, 4, 0, 1, 0);
		SET_FMT(AV_SAMPLE_FMT_FLT, 4, 1, 1, 0);
		SET_FMT(AV_SAMPLE_FMT_DBL, 8, 1, 1, 0);
		
		SET_FMT(AV_SAMPLE_FMT_U8P, 1, 0, 0, 0);
		SET_FMT(AV_SAMPLE_FMT_S16P, 2, 0, 1, 0);
		SET_FMT(AV_SAMPLE_FMT_S32P, 4, 0, 1, 0);
	    SET_FMT(AV_SAMPLE_FMT_FLTP, 4, 1, 1, 0);
	    SET_FMT(AV_SAMPLE_FMT_DBLP, 8, 1, 1, 0);
	    
		//SET_FMT(AV_SAMPLE_FMT_S64, 8, 0, 1, 0);
		//SET_FMT(AV_SAMPLE_FMT_S64P, 8, 0, 1, 0);
		
		default:
		errstr = "unexpected audio format";
		return false;
	}
	
	is_open = true;
	return true;
}

bool FfmpegFileChannel::OpenDevice() {
	if (!is_open)
		return false;
	
	// Find the decoder for the stream
	codec = avcodec_find_decoder(file_fmt_ctx->streams[stream_i]->codecpar->codec_id);
	if (codec == NULL) {
		errstr = "unsupported codec";
		is_open = false;
		return false;
	}
	
	parser = av_parser_init(codec->id);
	if (!parser) {
		// codecs like AV_CODEC_ID_PCM_F32LE doesn't require parser...
		if (codec->id >= AV_CODEC_ID_PCM_S16LE &&
			codec->id <  AV_CODEC_ID_ADPCM_IMA_QT) {
			// pass
		}
		else {
			errstr = "parser not found";
			is_open = false;
			return false;
		}
	}

    frame = av_frame_alloc();
    
	codec_ctx = avcodec_alloc_context3(codec);
	
	// Copy context
	avcodec_parameters_to_context(codec_ctx, file_fmt_ctx->streams[stream_i]->codecpar);
	
	// Open codec
	AVDictionary* opts = NULL;
	if (avcodec_open2(codec_ctx, codec, &opts) < 0) {
		errstr = "could not open codec";
		is_open = false;
		return false; // Could not open codec
	}
	
	return true;
}

bool FfmpegFileChannel::ReadFrame(AVPacket& pkt) {
    if (pkt.stream_index != stream_i)
        return false;
    
	int got_frame = 0;
	do {
		int ret = DecodePacket(pkt, &got_frame);
		if (ret < 0)
			break;
		pkt.data += ret;
		pkt.size -= ret;
		if (got_frame)
			return true;
	}
	while (pkt.size > 0);
	
	return false;
}















void FfmpegAudioFrame::Exchange(AudioEx& e) {
	TODO
}

int FfmpegAudioFrame::GetQueueSize() const {
	TODO
}

AudioFormat FfmpegAudioFrame::GetAudioFormat() const {
	TODO
}

bool FfmpegAudioFrame::IsQueueFull() const {
	TODO
}

bool FfmpegAudioFrame::GetFrameFrom(Sound& snd, bool realtime) {
	TODO
}

#ifdef flagOPENGL
bool FfmpegAudioFrame::PaintOpenGLTexture(int texture) {
	TODO
}

#endif

void FfmpegAudioFrame::Process(double time_pos, AVFrame* frame) {
	TODO
}

















void FfmpegVideoFrame::Exchange(VideoEx& e) {
	TODO
}

int FfmpegVideoFrame::GetQueueSize() const {
	TODO
}

bool FfmpegVideoFrame::IsQueueFull() const {
	TODO
}

#ifdef flagOPENGL
bool FfmpegVideoFrame::PaintOpenGLTexture(int texture) {
	TODO
}

#endif
VideoFormat FfmpegVideoFrame::GetVideoFormat() const {
	TODO
}

void FfmpegVideoFrame::Process(double time_pos, AVFrame* frame, bool vflip) {
	TODO
	#if FFMPEG_VIDEOFRAME_RGBA_CONVERSION
	
	#else
	#error Unimplemented
	#endif
}



NAMESPACE_OULU_END

#endif