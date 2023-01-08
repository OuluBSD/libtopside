#include "IMedia.h"

NAMESPACE_PARALLEL_BEGIN



template <class Backend>
void AudioFrameQueueT<Backend>::Close() {
	this->GetParent()->template AsRef<FileInput>()->Close();
}

template <class Backend>
void AudioFrameQueueT<Backend>::FillBuffer() {
	this->GetParent()->template AsRef<FileInput>()->FillAudioBuffer();
}






template <class Backend>
void VideoFrameQueueT<Backend>::Close() {
	this->GetParent()->template AsRef<FileInput>()->Close();
}

template <class Backend>
void VideoFrameQueueT<Backend>::FillBuffer() {
	this->GetParent()->template AsRef<FileInput>()->FillVideoBuffer();
}






template <class Backend>
FileInputT<Backend>::FileInputT()
{
	aframe.SetParent(this);
	vframe.SetParent(this);
	
}

template <class Backend>
void FileInputT<Backend>::Clear() {
	ClearDevice();
	
	if (file_fmt_ctx)
		avformat_close_input(&file_fmt_ctx);
	file_fmt_ctx = NULL;
	
	has_audio = false;
	has_video = false;
	is_dev_open = false;
	path.Clear();
	errstr.Clear();
	
	a.Clear();
	v.Clear();
}

template <class Backend>
void FileInputT<Backend>::ClearDevice() {
	is_eof = true;
	is_dev_open = 0;
	aframe.Clear();
	vframe.Clear();
	
	ClearPacket();
}

template <class Backend>
void FileInputT<Backend>::InitPacket() {
	ClearPacket();
	pkt = Backend::NewPacket();
    pkt->data = NULL;
    pkt->size = 0;
}

template <class Backend>
void FileInputT<Backend>::ClearPacketData() {
	if (pkt_ref) {
		Backend::UnrefPacket(pkt);
		pkt_ref = false;
	}
    pkt->data = NULL;
    pkt->size = 0;
}

template <class Backend>
void FileInputT<Backend>::ClearPacket() {
	if (pkt) {
		ClearPacketData();
		Backend::DeletePacket(pkt);
		pkt = 0;
	}
	else {
		ASSERT(!pkt_ref);
	}
}

#if 0
template <class Backend>
void FileInputT<Backend>::SetFormat(Format fmt) {
	ASSERT(fmt.IsValid());
	if (fmt.IsAudio()) {
		aframe.fmt = fmt;
	}
	else if (fmt.IsVideo()) {
		vframe.fmt = fmt;
	}
	else TODO;
}
#endif

template <class Backend>
bool FileInputT<Backend>::IsOpen() const {
	return is_dev_open;
}

template <class Backend>
bool FileInputT<Backend>::OpenFile(String path) {
	LOG("FileInputT::OpenFile: opening file '" << path << "'");
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
	ASSERT(!aframe.fmt.IsValid() && !vframe.fmt.IsValid());
	has_audio = a.OpenAudio(file_fmt_ctx, aframe.fmt);
	has_video = v.OpenVideo(file_fmt_ctx, vframe.fmt);
	
	if (has_audio) {
		aframe.Clear();
	}
	if (has_video) {
		vframe.Clear();
	}
	
	return HasMediaOpen();
}

template <class Backend>
bool FileInputT<Backend>::Open() {
	ClearDevice();
	
	if (!HasMediaOpen())
		return false;
	
	bool audio_open = false;
	if (has_audio) {
		audio_open = a.OpenDevice();
	}
	
	bool video_open = false;
	if (has_video) {
		video_open = v.OpenDevice();
		if (video_open)
			vframe.Init(v.codec_ctx);
	}
	
	InitPacket();
    
	is_dev_open = audio_open || video_open;
	is_eof = !is_dev_open;
	return is_dev_open;
}

template <class Backend>
void FileInputT<Backend>::Close() {
	Clear();
}

template <class Backend>
void FileInputT<Backend>::FillVideoBuffer() {
	while (!vframe.IsQueueFull() && !IsEof()) {
		if (ReadFrame()) {
			if (ProcessVideoFrame())
				continue;
			if (ProcessAudioFrame())
				continue;
		}
		else break;
	}
}

template <class Backend>
void FileInputT<Backend>::FillAudioBuffer() {
	while (!aframe.IsQueueFull() && !IsEof()) {
		if (ReadFrame()) {
			if (ProcessVideoFrame())
				continue;
			if (ProcessAudioFrame())
				continue;
			
			ClearPacketData();
		}
		else break;
	}
	
	//if (IsEof())
	//	FillBuffersNull();
	
	ClearPacketData();
}

template <class Backend>
bool FileInputT<Backend>::ReadFrame() {
	ClearPacketData();
	
	ASSERT(!pkt->data && !pkt->size);
	if (av_read_frame(file_fmt_ctx, pkt) >= 0) {
		pkt_ref = true;
		is_eof = false;
		return true;
	}
	
	if (!is_eof) {
		RTLOG("FileInputT::ReadFrame: end of file");
		is_eof = true;
		WhenStopped();
	}
	
	return false;
}

template <class Backend>
bool FileInputT<Backend>::ProcessVideoFrame() {
	ASSERT(pkt && pkt_ref);
	if (v.ReadFrame(*pkt)) {
		vframe.Process(v.frame_pos_time, v.frame);
		av_frame_free(&v.frame);
		ClearPacketData();
		return true;
	}
	
	return false;
}

template <class Backend>
bool FileInputT<Backend>::ProcessAudioFrame() {
	ASSERT(pkt && pkt_ref);
	if (a.ReadFrame(*pkt)) {
		aframe.FillAudioBuffer(a.frame_pos_time, a.frame);
		av_frame_free(&a.frame);
		ClearPacketData();
		return true;
	}
	
	return false;
}


template <class Backend>
void FileInputT<Backend>::DropVideoFrames(int frames) {
	TODO
}



template <class Backend>
String FileInputT<Backend>::GetLastError() const {
	return errstr;
}

template <class Backend>
String FileInputT<Backend>::GetPath() const {
	return path;
}

template <class Backend>
double FileInputT<Backend>::GetSeconds() const {
	if (a.IsOpen())
		return a.GetSeconds();
	if (v.IsOpen())
		return v.GetSeconds();
	return 0;
}

template <class Backend>
bool FileInputT<Backend>::IsEof() const {
	return is_eof;
}




template <class Backend>
bool FileInputT<Backend>::IsAudioOpen() const {
	return is_dev_open && has_audio;
}














template <class Backend>
int FileChannelT<Backend>::DecodePacket(AVPacket& pkt, int *got_frame) {
    int ret = 0;
    int decoded = pkt.size;
    *got_frame = 0;
        
    // Decode frame
    ret = Backend::SendPacket(codec_ctx, pkt);
    if (ret < 0) {
        is_open = false;
        errstr = "Eof in packet decoding";
        return -1;
    }
    else if (ret > 0) {
        errstr = "Failed to decode packet";
        return -1;
    }
    
    // Receive frame
    if (!frame)
		frame = Backend::NewFrame();
    ret = Backend::ReceiveFrame(codec_ctx, *frame);
    if (ret < 0) {
        is_open = false;
        errstr = "Eof in frame decoding";
        return -1;
    }
    else if (ret > 0) {
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

template <class Backend>
void FileChannelT<Backend>::Clear() {
	if (frame)
		Backend::DeletePacket(frame);
	frame = 0;
	
	Backend::CloseCodecParserContext(parser);
	Backend::CloseCodecContext(codec_ctx);
	
	file_fmt_ctx = NULL;
	
	stream_i = -1;
	codec = NULL;
	
	is_open = false;
}

template <class Backend>
void FileChannelT<Backend>::ClearDevice() {
	codec = NULL;
	frame_pos_time = 0;
}

template <class Backend>
bool FileChannelT<Backend>::OpenVideo(AVFormatContext* file_fmt_ctx, Format& fmt) {
	Clear();
	fmt.Clear();
	fmt.vd = VD(CENTER,VIDEO);
	VideoFormat& vfmt = fmt;
	
	this->file_fmt_ctx = file_fmt_ctx;
	
	stream_i = Backend::FindVideoStream(*file_fmt_ctx);
	if (stream_i == -1) {
		errstr = "did not find video stream";
		return false;
	}
	
	AVStream& vstream = Backend::GetStream(*file_fmt_ctx, stream_i);
	AVCodecParameters& vcodec = Backend::GetParams(vstream);
	
	double fps = Backend::GetVideoFPS(vstream);
	Size frame_sz = Backend::GetFrameSize(vcodec);
	LightSampleFD::Type sample = Backend::GetVideoSampleType(vcodec);
	
	vfmt.SetSize(frame_sz);
	vfmt.SetFPS(fps);
	vfmt.SetType(sample);
	vfmt.SetLinePadding(0); // unknown at this point. Only AVFrame can tell
	
	is_open = true;
	return true;
}

template <class Backend>
bool FileChannelT<Backend>::OpenAudio(AVFormatContext* file_fmt_ctx, Format& fmt) {
	Clear();
	fmt.Clear();
	fmt.vd = VD(CENTER,AUDIO);
	AudioFormat& afmt = fmt;
	
	this->file_fmt_ctx = file_fmt_ctx;
	
	stream_i = Backend::FindAudioStream(*file_fmt_ctx);
	if (stream_i == -1) {
		errstr = "did not find video stream";
		return false;
	}
	
	AVStream& s = Backend::GetStream(*file_fmt_ctx, stream_i);
	AVCodecParameters& c = Backend::GetParams(s);
	SoundSample::Type sample = Backend::GetAudioSampleType(c);
	
	afmt.res[0] = Backend::GetChannels(c);
	afmt.freq = Backend::GetFrequency(c);
	afmt.sample_rate = Backend::GetSampleRate(c);
	afmt.SetType(sample);
	
	is_open = true;
	return true;
}

template <class Backend>
bool FileChannelT<Backend>::OpenDevice() {
	if (!is_open)
		return false;
	
	// Find the decoder for the stream
	if (!Backend::FindDecoder(*file_fmt_ctx, codec, stream_i)) {
		errstr = "unsupported codec";
		is_open = false;
		return false;
	}
	
	if (!Backend::InitParser(codec, parser)) {
		errstr = "parser not found";
		is_open = false;
		return false;
	}

    frame = Backend::NewFrame();
    
	codec_ctx = Backend::CreateCodecContext(codec);
	
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

template <class Backend>
bool FileChannelT<Backend>::ReadFrame(AVPacket& pkt) {
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













template <class Backend>
void AudioFrameQueueT<Backend>::FillAudioBuffer(double time_pos, AVFrame* frame) {
	Format& fmt = this->fmt;
	auto& buf = this->buf;
	
	// Sometimes you get the sample rate at this point
	AudioFormat& afmt = fmt;
	if (!afmt.sample_rate)
		afmt.sample_rate = frame->nb_samples;
	
	//breaks in the end of file: ASSERT(fmt.sample_rate == frame->nb_samples);
	ASSERT(fmt.IsValid());
	int var_size = av_get_bytes_per_sample((AVSampleFormat)frame->format);
	
	#ifdef flagDEBUG
	/*bool is_var_float =
		frame->format == AV_SAMPLE_FMT_FLT ||
		frame->format == AV_SAMPLE_FMT_DBL ||
		frame->format == AV_SAMPLE_FMT_FLTP ||
		frame->format == AV_SAMPLE_FMT_DBLP;*/
	ASSERT(fmt.IsValid());
	ASSERT(frame->sample_rate == afmt.freq);
	ASSERT(frame->channels == afmt.res[0]);
	ASSERT(var_size == afmt.GetSampleSize());
	#endif
	
	int frame_sz = frame->nb_samples * frame->channels * var_size;
	
	buf.EnterWrite();
	auto& p = buf.Add();
	off32 offset = gen.Create();
	p = CreatePacket(offset);
	RTLOG("AudioFrameQueueT::FillAudioBuffer: rendering packet " << offset.ToString() << ", " << time_pos);
	p->Set(fmt, time_pos);
	buf.LeaveWrite();
	
	Backend::CopyFramePixels(fmt, *frame, p->Data());
}







template <class Backend>
void VideoFrameQueueT<Backend>::Init(AVCodecContextRef& ctx) {
	Clear();
	
	Format& fmt = this->fmt;
	ASSERT(fmt.IsValid());
	
	VideoFormat& vfmt = fmt;
	Size sz = vfmt.GetSize();
	
	img_convert_ctx = Backend::GetImgConvContextRef(ctx, sz);
}

template <class Backend>
void VideoFrameQueueT<Backend>::Clear() {
	Base::Clear();
	frames.Clear();
}

template <class Backend>
void VideoFrameQueueT<Backend>::DropFrames(int i) {
	frames.RemoveFirst(i);
}

template <class Backend>
void VideoFrameQueueT<Backend>::Process(double time_pos, AVFrame* frame, bool vflip) {
	Format& fmt = this->fmt;
	auto& buf = this->buf;
	
	ASSERT(fmt.IsValid());
	auto& f = frames.Add();
	f.Create(pool);
	f->Init(fmt);
	f->time_pos = time_pos;
	f->Process(time_pos, frame, vflip, fmt, img_convert_ctx);
	
	Packet p = CreatePacket(gen.Create());
	p->SetFormat(fmt);
	f->MakePacket(p);
	buf.Add(p);
}




MEDIA_EXCPLICIT_INITIALIZE_CLASS(AudioFrameQueueT)
MEDIA_EXCPLICIT_INITIALIZE_CLASS(VideoFrameQueueT)
MEDIA_EXCPLICIT_INITIALIZE_CLASS(FileChannelT)
MEDIA_EXCPLICIT_INITIALIZE_CLASS(FileInputT)

NAMESPACE_PARALLEL_END
