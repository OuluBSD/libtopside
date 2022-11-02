#include "IMedia.h"


NAMESPACE_PARALLEL_BEGIN


#ifdef flagFFMPEG
FfmpegMedia::AVPacket* FfmpegMedia::NewPacket() {
	return av_packet_alloc();
}

void FfmpegMedia::UnrefPacket(AVPacket* p) {
	av_packet_unref(p);
}

void FfmpegMedia::DeletePacket(AVPacket* p) {
	av_packet_free(&p);
}

AVFrame* FfmpegMedia::NewFrame() {
	return av_frame_alloc();
}

void FfmpegMedia::DeletePacket(AVFrame* f) {
	av_frame_free(&f);
}

void FfmpegMedia::CloseCodecParserContext(AVCodecParserContextRef& parser) {
	if (parser) {
		av_parser_close(parser);
		parser = NULL;
	}
}

void FfmpegMedia::CloseCodecContext(AVCodecContextRef& ctx) {
	if (ctx) {
		avcodec_free_context(&ctx);
		ctx = 0;
	}
}

int FfmpegMedia::SendPacket(AVCodecContextRef& ctx, const AVPacket& p) {
	int ret = avcodec_send_packet(ctx, &p);
	if (ret == AVERROR_EOF)
		return -1;
	else if (ret != 0)
		return 1;
	else
		return 0;
}

int FfmpegMedia::ReceiveFrame(AVCodecContextRef& ctx, AVFrame& frame) {
	int ret = avcodec_receive_frame(ctx, &frame);
	if (ret == AVERROR_EOF)
		return -1;
	else if (ret != 0)
		return 1;
	else
		return 0;
}

int FfmpegMedia::FindVideoStream(AVFormatContext& ctx) {
	int stream_i = -1;
	for (int i = 0; i < (int)ctx.nb_streams; i++) {
		if (ctx.streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO ) {
			stream_i = i;
			break;
		}
	}
	return stream_i;
}

int FfmpegMedia::FindAudioStream(AVFormatContext& ctx) {
	int stream_i = -1;
	for (int i = 0; i < (int)ctx.nb_streams; i++) {
		if (ctx.streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO ) {
			stream_i = i;
			break;
		}
	}
	return stream_i;
}

AVStream& FfmpegMedia::GetStream(AVFormatContext& ctx, int i) {
	return *ctx.streams[i];
}

AVCodecParameters& FfmpegMedia::GetParams(AVStream& s) {
	return *s.codecpar;
}

double FfmpegMedia::GetVideoFPS(const AVStream& s) {
	double fps;
	if (s.avg_frame_rate.den > 0)
		fps = (double)s.avg_frame_rate.num / (double)s.avg_frame_rate.den;
	else if (s.r_frame_rate.den > 0)
		fps = (double)s.r_frame_rate.num / (double)s.r_frame_rate.den;
	else
		fps = 25;
	return fps;
}

Size FfmpegMedia::GetFrameSize(const AVCodecParameters& c) {
	return Size(c.width, c.height);
}

LightSampleFD::Type FfmpegMedia::GetVideoSampleType(const AVCodecParameters& c) {
	#if FFMPEG_VIDEOFRAME_RGBA_CONVERSION
	return LightSampleFD::RGBA_U8_LE;
	#else
	switch (vcodec->format) {
	case AV_PIX_FMT_RGB24:
		return LightSampleFD::RGB_U8_LE;
		break;
	case AV_PIX_FMT_RGBA:
		return LightSampleFD::RGBA_U8_LE;
		break;
	default:
		return BinarySample::INVALID;
	}
	#endif
}

int FfmpegMedia::GetChannels(const AVCodecParameters& c) {
	return c.channels;
}

int FfmpegMedia::GetSampleRate(const AVCodecParameters& c) {
	return c.frame_size;
}

int FfmpegMedia::GetFrequency(const AVCodecParameters& c) {
	return c.sample_rate;
}

SoundSample::Type FfmpegMedia::GetAudioSampleType(const AVCodecParameters& c) {
	switch (c.format) {
		#define SET_FMT(f, t) \
		case f: \
			return SoundSample::t; \
			break;
			
		#if CPU_LITTLE_ENDIAN
		SET_FMT(AV_SAMPLE_FMT_U8,		U8_LE);
		SET_FMT(AV_SAMPLE_FMT_S16,		S16_LE);
		SET_FMT(AV_SAMPLE_FMT_S32,		S32_LE);
		SET_FMT(AV_SAMPLE_FMT_FLT,		FLT_LE);
		SET_FMT(AV_SAMPLE_FMT_DBL,		DBL_LE);
		
		SET_FMT(AV_SAMPLE_FMT_U8P,		U8_LE);
		SET_FMT(AV_SAMPLE_FMT_S16P,		S16_LE);
		SET_FMT(AV_SAMPLE_FMT_S32P,		S32_LE);
	    SET_FMT(AV_SAMPLE_FMT_FLTP,		FLT_LE);
	    SET_FMT(AV_SAMPLE_FMT_DBLP,		DBL_LE);
	    #else
	    #error TODO
	    #endif
	    
		//SET_FMT(AV_SAMPLE_FMT_S64, 8, 0, 1, 0);
		//SET_FMT(AV_SAMPLE_FMT_S64P, 8, 0, 1, 0);
		
		default:
		break;
	}
	return SoundSample::INVALID;
}

bool FfmpegMedia::InitParser(AVCodec& c, AVCodecParserContextRef& parser) {
	parser = av_parser_init(c->id);
	if (!parser) {
		// codecs like AV_CODEC_ID_PCM_F32LE doesn't require parser...
		if (c->id >= AV_CODEC_ID_PCM_S16LE &&
			c->id <  AV_CODEC_ID_ADPCM_IMA_QT) {
			// pass
		}
		else {
			return false;
		}
	}
	return true;
}

bool FfmpegMedia::FindDecoder(AVFormatContext& ctx, AVCodec& codec, int stream_i) {
	codec = avcodec_find_decoder(ctx.streams[stream_i]->codecpar->codec_id);
	return codec != NULL;
}

FfmpegMedia::AVCodecContextRef FfmpegMedia::CreateCodecContext(AVCodec& c) {
	return avcodec_alloc_context3(c);
}

void FfmpegMedia::CopyFramePixels(const Format& fmt, const AVFrame& frame, Vector<byte>& data) {
	
	// Non-planar data
	if (frame.data[1] == 0) {
		if (frame.data[0]) {
			ASSERT(fmt.GetFrameSize() >= frame.linesize[0]);
			data.SetCount(frame.linesize[0], 0);
			memcpy(data.begin(), frame.data[0], frame.linesize[0]);
		}
	}
	// Planar data
	else {
		byte* srcn[AV_NUM_DATA_POINTERS];
		memset(srcn, 0, sizeof(srcn));
		
		int var_size =
			fmt.IsVideo() ?
				fmt.vid.GetPackedSingleSize() :
				fmt.aud.GetPackedSingleSize();
		int frame_sz = fmt.GetFrameSize();
		
		if (0) {
			//LOG("time_pos:     " << time_pos);
			LOG("frame-sz:     " << frame_sz);
			LOG("fmt:          " << fmt.ToString());
			LOG("f-nb-samples: " << frame.nb_samples);
			LOG("f-channels:   " << frame.channels);
			if (0) __BREAK__
		}
		
		data.SetCount(frame_sz, 0);
		byte* dst = data.Begin();
		
		for(int i = 0; i < frame.channels; i++)
			srcn[i] = frame.data[i];
		
		for (int i = 0; i < frame.nb_samples; i++) {
			for(int j = 0; j < frame.channels; j++) {
				byte*& src = srcn[j];
				for(int k = 0; k < var_size; k++)
					*dst++ = *src++;
			}
		}
		ASSERT(dst == data.End());
	}
	
}

FfmpegMedia::ImgConvContextRef FfmpegMedia::GetImgConvContextRef(AVCodecContextRef& ctx, Size sz) {
	return sws_getContext(
		sz.cx, sz.cy, ctx->pix_fmt,
		sz.cx, sz.cy, AV_PIX_FMT_RGBA,
		SWS_FAST_BILINEAR, NULL, NULL, NULL);
}

int FfmpegMedia::CreateImage(uint8_t *video_dst_data[4], int video_dst_linesize[4], Size sz) {
	return av_image_alloc(	video_dst_data, video_dst_linesize,
					sz.cx, sz.cy, AV_PIX_FMT_RGBA, 1);
}

void FfmpegMedia::DeleteImgConvContextRef(ImgConvContextRef ctx) {
	if (ctx) {
		sws_freeContext(ctx);
		ctx = 0;
	}
}

void FfmpegMedia::FreeData(uint8_t*& data, int& len) {
	if (len) {
		av_free(data);
		data = 0;
		len = 0;
	}
}

void FfmpegMedia::Frame::Init(const VideoFormat& vid_fmt) {
	if (!video_dst_bufsize) {
		Size sz = vid_fmt.GetSize();
		video_dst_bufsize = FfmpegMedia::CreateImage(video_dst_data, video_dst_linesize, sz);
	}
}

void FfmpegMedia::Frame::Clear() {
	FfmpegMedia::FreeData(video_dst_data[0], video_dst_bufsize);
}

void FfmpegMedia::Frame::Process(double time_pos, AVFrame* frame, bool vflip, const VideoFormat& vid_fmt, ImgConvContextRef img_convert_ctx) {
	Size size = vid_fmt.GetSize();
	
	this->time_pos = time_pos;
	
	#if FFMPEG_VIDEOFRAME_RGBA_CONVERSION
	if (vflip) {
		for(int i = 0; i < 4; i++) {
			video_dst_linesize_vflip[i] = -video_dst_linesize[i];
			video_dst_data_vflip[i] = video_dst_data[i] + (size.cy - 1) * video_dst_linesize[i];
		}
	    sws_scale(
			img_convert_ctx,
			frame->data, frame->linesize,
			0, size.cy,
			video_dst_data_vflip, video_dst_linesize_vflip);
	}
	else {
	    sws_scale(
			img_convert_ctx,
			frame->data, frame->linesize,
			0, size.cy,
			video_dst_data, video_dst_linesize);
	}
	#else
	#error Unimplemented
	#endif
}

bool FfmpegMedia::Frame::PaintOpenGLTexture(int texture, const VideoFormat& vid_fmt) {
	if (!video_dst_bufsize)
		return false;
	
	TODO
	#if 0
	glBindTexture (GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F,
		vid_fmt.size.cx,
		vid_fmt.size.cy,
		0, GL_RGBA, GL_UNSIGNED_BYTE,
		video_dst_data[0]);
	#endif
	
	return true;
}

void FfmpegMedia::Frame::MakePacket(Packet& p) {
	PacketValue& v = *p;
	v.SetTime(time_pos);
	Vector<byte>& data = v.Data();
	data.SetCount(video_dst_bufsize);
	memcpy(data.Begin(), video_dst_data[0], video_dst_bufsize); // TODO optimize memcpy away
}


#endif


NAMESPACE_PARALLEL_END
