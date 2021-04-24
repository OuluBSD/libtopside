#include "Multimedia.h"

#if HAVE_MEDIAFILE

NAMESPACE_OULU_BEGIN

#ifdef flagOPENGL
int GetOglDataType(int sample_size, int is_float) {
	if (!is_float) {
		switch (sample_size) {
			case 1: return GL_UNSIGNED_BYTE;
			case 2: return GL_UNSIGNED_SHORT;
			case 4: return GL_UNSIGNED_INT;
		}
	}
	else {
		switch (sample_size) {
			case 4: return GL_FLOAT;
			case 8: return GL_DOUBLE;
		}
	}
	return 0;
}
#endif


void MediaAudioFrame::Clear() {
	time_pos = 0;
	fmt.Clear();
}

void MediaAudioFrame::Get(void* v_, int size) {
	ASSERT(size == data.GetCount());
	if (size > 0 && size <= data.GetCount()) {
		memcpy(v_, data.Begin(), size);
	}
	unread = 0;
}

void MediaAudioFrame::Put(void* v, int size, bool realtime) {
	TODO
}

int MediaAudioFrame::GetQueueSize() const {
	return unread;
}

bool MediaAudioFrame::IsQueueFull() const {
	return unread >= 1;
}

/*bool MediaAudioFrame::IsQueueFullAttach(SoundFormat fmt, AVCodecContext& ctx) {
	TODO
}*/

void MediaAudioFrame::Process(double time_pos, AVFrame* frame) {
	this->time_pos = time_pos;
	
	ASSERT(data.GetCount());
	if (data.GetCount()) {
		#if 0
		memcpy(data.Begin(), frame->data, data.GetCount());
		#else
		// Transpose data
		byte* dst = data.Begin();
		int ss = fmt.var_size;
		int channels = fmt.channels;
		int sr = fmt.sample_rate;
		ASSERT(fmt.sample_rate);
		for(int ch = 0; ch < channels; ch++) {
			byte* src = (byte*)frame->data;
			src += ch * ss;
			for(int i = 0; i < sr; i++) {
				for(int j = 0; j < ss; j++)
					*dst++ = *src++;
				src += ss * (channels - 1);
			}
		}
		ASSERT(dst == data.End());
		#endif
		unread = 1;
	}
}

bool MediaAudioFrame::Attach(SoundFormat fmt, AVCodecContext& ctx) {
	Clear();
	
	this->fmt = fmt;
	if (!fmt.IsValid())
		return false;
	
	int frame_size = fmt.var_size * fmt.sample_rate * fmt.channels;
	data.SetCount(frame_size, 0);
	
	return true;
}

#ifdef flagOPENGL
bool MediaAudioFrame::PaintOpenGLTexture(int texture) {
	if (data.IsEmpty())
		return false;
	ASSERT(data.GetCount() == fmt.var_size * fmt.sample_rate * fmt.channels);
	
	glBindTexture (GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	Size res(fmt.sample_rate, fmt.channels);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F,
		res.cx,
		res.cy,
		0, GL_RED, GetOglDataType(fmt.var_size, fmt.is_var_float),
		data.Begin());
	
	return true;
}
#endif







MediaVideoFrame::MediaVideoFrame() {
	
}

void MediaVideoFrame::Clear() {
	time_pos = 0;
	
	if (rgba_frame) {
		av_frame_free(&rgba_frame);
		rgba_frame = 0;
	}
	
	if (img_convert_ctx) {
		sws_freeContext(img_convert_ctx);
		img_convert_ctx = 0;
	}
	
	if (video_dst_bufsize) {
		av_free(video_dst_data[0]);
		video_dst_data[0] = 0;
		video_dst_bufsize = 0;
	}
}

bool MediaVideoFrame::Attach(VideoFormat fmt, AVCodecContext& ctx) {
	Clear();
	
	this->fmt = fmt;
	Size sz = Size(ctx.width, ctx.height);
	
	if (sz != fmt.res)
		return false;
	
	img_convert_ctx =
		sws_getContext(
		sz.cx, sz.cy, ctx.pix_fmt,
		sz.cx, sz.cy, AV_PIX_FMT_RGBA,
		SWS_FAST_BILINEAR, NULL, NULL, NULL);
		
    int ret = av_image_alloc(video_dst_data, video_dst_linesize,
                     sz.cx, sz.cy, AV_PIX_FMT_RGBA, 1);
	if (ret < 0)
		return false;
	
	video_dst_bufsize = ret;
	return true;
}

void MediaVideoFrame::Process(double time_pos, AVFrame* frame, bool vflip) {
	this->time_pos = time_pos;
	
	if (vflip) {
		for(int i = 0; i < 4; i++) {
			video_dst_linesize_vflip[i] = -video_dst_linesize[i];
			video_dst_data_vflip[i] = video_dst_data[i] + (fmt.res.cy - 1) * video_dst_linesize[i];
		}
	    sws_scale(
			img_convert_ctx,
			frame->data, frame->linesize,
			0, fmt.res.cy,
			video_dst_data_vflip, video_dst_linesize_vflip);
	}
	else {
	    sws_scale(
			img_convert_ctx,
			frame->data, frame->linesize,
			0, fmt.res.cy,
			video_dst_data, video_dst_linesize);
	}
	
}

void MediaVideoFrame::Get(void* v_, int size) {
	TODO
}

void MediaVideoFrame::Put(void* v, int size, bool realtime) {
	TODO
}

int MediaVideoFrame::GetQueueSize() const {
	TODO
}

bool MediaVideoFrame::IsQueueFull() const {
	TODO
}

#ifdef flagOPENGL
bool MediaVideoFrame::PaintOpenGLTexture(int texture) {
	if (!video_dst_bufsize)
		return false;
	
	glBindTexture (GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F,
		fmt.res.cx,
		fmt.res.cy,
		0, GL_RGBA, GL_UNSIGNED_BYTE,
		video_dst_data[0]);
	return true;
}
#endif






void MediaFileChannel::Clear() {
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

void MediaFileChannel::ClearDevice() {
	
	read_frame_i = 0;
	codec = NULL;
	
	read_pos_time = 0;
}



void MediaFileInput::Clear() {
	ClearDevice();
	
	v.Clear();
	a.Clear();
	
	// File
	if (file_fmt_ctx)
		avformat_free_context(file_fmt_ctx);
	file_fmt_ctx = NULL;
	
	path.Clear();
	fmts.Clear();
	
	is_file_open = false;
}

void MediaFileInput::ClearDevice() {
	v.ClearDevice();
	a.ClearDevice();
	
	if (is_orig_pkt_ref) {
		av_packet_unref(&orig_pkt);
		is_orig_pkt_ref = false;
	}
	
	for(int i = 0; i < 2; i++) vframe[i].Clear();
	for(int i = 0; i < 2; i++) aframe[i].Clear();
	
	is_dev_open = false;
}


bool MediaFileChannel::OpenVideo(AVFormatContext* file_fmt_ctx, VideoFormat& fmt) {
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
	
	#if 1
	// MediaVideoFrame converts the frame to RGBA!!!
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

bool MediaFileChannel::OpenAudio(AVFormatContext* file_fmt_ctx, SoundFormat& fmt) {
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
		case AV_SAMPLE_FMT_U8:          ///< unsigned 8 bits
		fmt.var_size = 1;
		fmt.is_var_float = 0;
		break;
		
	    case AV_SAMPLE_FMT_S16:         ///< signed 16 bits
		fmt.var_size = 2;
		fmt.is_var_float = 0;
		break;
		
	    case AV_SAMPLE_FMT_S32:         ///< signed 32 bits
		fmt.var_size = 4;
		fmt.is_var_float = 0;
		break;
		
	    case AV_SAMPLE_FMT_FLT:         ///< float
		fmt.var_size = 4;
		fmt.is_var_float = 1;
		break;
		
	    case AV_SAMPLE_FMT_DBL:         ///< double
		fmt.var_size = 8;
		fmt.is_var_float = 1;
		break;
		
	
	    case AV_SAMPLE_FMT_U8P:         ///< unsigned 8 bits, planar
		fmt.var_size = 1;
		fmt.is_var_float = 0;
		break;
		
	    case AV_SAMPLE_FMT_S16P:        ///< signed 16 bits, planar
		fmt.var_size = 2;
		fmt.is_var_float = 0;
		break;
		
	    case AV_SAMPLE_FMT_S32P:        ///< signed 32 bits, planar
		fmt.var_size = 4;
		fmt.is_var_float = 0;
		break;
		
	    case AV_SAMPLE_FMT_FLTP:        ///< float, planar
		fmt.var_size = 4;
		fmt.is_var_float = 1;
		break;
		
	    case AV_SAMPLE_FMT_DBLP:        ///< double, planar
		fmt.var_size = 8;
		fmt.is_var_float = 1;
		break;
		
	    case AV_SAMPLE_FMT_S64:         ///< signed 64 bits
		fmt.var_size = 8;
		fmt.is_var_float = 0;
		break;
		
	    case AV_SAMPLE_FMT_S64P:
		fmt.var_size = 8;
		fmt.is_var_float = 0;
		break;
		
		default:
		errstr = "unexpected audio format";
		return false;
	}
	
	is_open = true;
	return true;
}

bool MediaFileInput::Open0(String path) {
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
	VideoFormat vid_fmt;
	bool has_audio = a.OpenAudio(file_fmt_ctx, snd_fmt);
	bool has_video = v.OpenVideo(file_fmt_ctx, vid_fmt);
	
	if (has_video) {
		VideoInputFormat& vf = fmts.Add();
		VideoInputFormatResolution& res = vf.res.Add();
		res.fmt = vid_fmt;
	}
	
	is_file_open = has_video || has_audio;
	return is_file_open;
}

bool MediaFileChannel::OpenDevice() {
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

bool MediaFileInput::OpenDevice0(int fmt, int res) {
	ClearDevice();
	
	if (!is_file_open)
		return false;
	
	if (fmt != 0 || res != 0)
		return false;
	
	bool audio_open = a.OpenDevice();
	if (audio_open) {
		AttachAudio(snd_fmt);
		//a.WhenRead = THISBACK(ReadAudioFrame);
	}
	
	bool video_open = v.OpenDevice();
	if (video_open) {
		AttachVideo(fmts[0][0].GetFormat());
		//v.WhenRead = THISBACK(ReadVideoFrame);
	}
	
	av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;
    
	is_dev_open = audio_open || video_open;
	return is_dev_open;
}

int MediaFileChannel::AddStep(double seconds) {
	read_pos_time += seconds;
	int next_frame_i = (read_frame_i + 1) % 2;
	return next_frame_i;
}

bool MediaFileInput::Step(double seconds) {
	bool succ = is_dev_open;
	if (v.IsOpen()) {
		int next_frame_i = v.AddStep(seconds);
		if (v.read_pos_time >= vframe[next_frame_i].GetTime())
			v.NextFrame();
		else
			succ = false;
	}
	if (a.IsOpen()) {
		int next_frame_i = a.AddStep(seconds);
		if (a.read_pos_time >= aframe[next_frame_i].GetTime())
			a.NextFrame();
		else
			succ = false;
	}
	return succ;
}

bool MediaFileInput::Read() {
	if (!is_dev_open)
		return false;
	
	bool succ = false;
	if (pkt.size > 0) {
		if (ReadFrame())
			return true;
	}
	if (is_orig_pkt_ref) {
		av_packet_unref(&orig_pkt);
		is_orig_pkt_ref = false;
	}
	
	while (av_read_frame(file_fmt_ctx, &pkt) >= 0) {
		ASSERT(!is_orig_pkt_ref);
		orig_pkt = pkt;
		is_orig_pkt_ref = true;
		
		if (ReadFrame())
			return true;
		
		ASSERT(is_orig_pkt_ref);
		is_orig_pkt_ref = false;
		av_packet_unref(&orig_pkt);
	}
	
	return false;
}

/*bool MediaFileInput::Read() {
	bool succ = is_open;
	if (v.IsOpen() && !v.Read())
		succ = false;
	if (a.IsOpen() && !a.Read())
		succ = false;
	if (!succ && pkt.pos < 0)
		is_dev_open = false;
	return succ;
}*/

bool MediaFileInput::ReadFrame() {
	if (a.ReadFrame(pkt)) {
		aframe[a.GetWriteFrame()].Process(a.frame_pos_time, a.frame);
		return true;
	}
	
	if (v.ReadFrame(pkt)) {
		vframe[v.GetWriteFrame()].Process(v.frame_pos_time, v.frame);
		return true;
	}
	
	return false;
}

bool MediaFileChannel::ReadFrame(AVPacket& pkt) {
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

int MediaFileChannel::DecodePacket(AVPacket& pkt, int *got_frame) {
    int ret = 0;
    int decoded = pkt.size;
    *got_frame = 0;
        
    // Decode video frame
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
    
    // Receive video frame
    ret = avcodec_receive_frame(codec_ctx, frame);
    if (ret == AVERROR_EOF) {
        is_open = false;
        errstr = "Eof in frame decoding";
        return -1;
    }
    else if (ret != 0) {
        errstr = "Error decoding video frame";
        return -1;
    }
    else {
        *got_frame = 1;
        
		double frame_time = (double)codec_ctx->time_base.num / (double)codec_ctx->time_base.den;
		if (codec_ctx->time_base.num == 0)
			frame_time = 1.0 / 1000.0;
		frame_pos_time = frame->pts * frame_time;
		
		
        #if 0
		MediaVideoFrame& vframe = this->vframe[read_vframe_i];
		read_vframe_i = (read_vframe_i + 1) % 2;
		
        vframe.Process(t, frame, true);
        
        VideoInputFormat& fmt = fmts[0];
        VideoInputFormatResolution& fres = fmt.GetResolution(0);
        if (fres.GetPitch() != vframe.GetLinesize())
            fres.SetPitch(vframe.GetLinesize());
       	#endif
    }
    
    #if 0
    else if (pkt.stream_index == audio_stream_idx) {
        // decode audio frame
        ret = avcodec_decode_audio4(audio_dec_ctx, frame, got_frame, &pkt);
        if (ret < 0) {
            fprintf(stderr, "Error decoding audio frame\n");
            return ret;
        }
        
        // Some audio decoders decode only part of the packet, and have to be
        // called again with the remainder of the packet data.
        // Sample: fate-suite/lossless-audio/luckynight-partial.shn
        // Also, some decoders might over-read the packet.
        decoded = FFMIN(ret, pkt.size);
        if (*got_frame) {
            size_t unpadded_linesize = frame->nb_samples * av_get_bytes_per_sample(frame->format);
            printf("audio_frame%s n:%d nb_samples:%d pts:%s\n",
                   cached ? "(cached)" : "",
                   audio_frame_count++, frame->nb_samples,
                   av_ts2timestr(frame->pts, &audio_dec_ctx->time_base));
            
            // Write the raw audio data samples of the first plane. This works
            // fine for packed formats (e.g. AV_SAMPLE_FMT_S16). However,
            // most audio decoders output planar audio, which uses a separate
            // plane of audio samples for each channel (e.g. AV_SAMPLE_FMT_S16P).
            // In other words, this code will write only the first audio channel
            // in these cases.
            // You should use libswresample or libavfilter to convert the frame
            // to packed data.
            fwrite(frame->extended_data[0], 1, unpadded_linesize, audio_dst_file);
        }
    }
    #endif
    
    return decoded;
}

Sound& MediaFileInput::GetSound() {
	return aframe[a.read_frame_i];
}

Video& MediaFileInput::GetVideo() {
	return vframe[v.read_frame_i];
}



NAMESPACE_OULU_END

#endif
