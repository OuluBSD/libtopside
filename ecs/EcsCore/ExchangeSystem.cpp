#include "EcsCore.h"


NAMESPACE_OULU_BEGIN











bool ExchangeSystem::Initialize() {
	return true;
}

void ExchangeSystem::Start() {
	
}

void ExchangeSystem::Update(double dt) {
	
}

void ExchangeSystem::Stop() {
	
}

void ExchangeSystem::Uninitialize() {
	
}





AudioExchangePoint::AudioExchangePoint() {
	
}

void AudioExchangePoint::Init(ConnectorBase* conn) {
	this->conn = conn;
	if (conn) {
		Pool& pool = conn->GetPool();
		Machine& mach = pool.GetMachine();
		Ref<AudioSystem> sys = mach.Get<AudioSystem>();
		ASSERT(sys);
		if (sys)
			sys->Add(this);
	}
}

void AudioExchangePoint::Deinit() {
	if (conn) {
		Pool& pool = conn->GetPool();
		Machine& mach = pool.GetMachine();
		Ref<AudioSystem> sys = mach.Get<AudioSystem>();
		ASSERT(sys);
		if (sys)
			sys->Remove(this);
		conn = 0;
	}
}

void AudioExchangePoint::Update(double dt) {
	ASSERT(dbg_offset_is_set);
	Ref<AudioSource>	src			= this->src;
	Ref<AudioSink>		sink		= this->sink;
	
	AudioEx ex(this);
	ex.SetOffset(offset);
	
	AudioStream& src_stream = src->GetAudioSource();
	Audio& src_audio = src_stream.GetAudio();
	int src_sz = src_audio.GetQueueSize();
	
	if (src_sz) {
		Audio& sink_audio = sink->GetAudioSink();
		bool sink_full = sink_audio.IsQueueFull();
		
		while (src_sz && !sink_full) {
			
			// Consumer works with single connection
			if (use_consumer) {
				ex.SetLoading(src_audio, src->Cfg());
				sink_audio.Exchange(ex);
			}
			else {
				ex.SetStoring(sink_audio, src->Cfg());
				src_audio.Exchange(ex);
			}
		}
	}
	
	SetOffset(ex.GetOffset());
	dbg_offset_is_set = false;
}





VideoExchangePoint::VideoExchangePoint() {
	
}

void VideoExchangePoint::Update(double dt) {
	Ref<VideoSource>	src			= this->src;
	Ref<VideoSink>		sink		= this->sink;
	any_sink_consumed = false;
	
	VideoEx ex(this);
	VideoStream& src_stream = src->GetVideoSource();
	if (src_stream.GetVideoBufferSize()) {
		
		Video& src_video = src_stream.GetVideo();
		Video& sink_video = sink->GetVideoSink();

		if (!sink_video.IsQueueFull()) {
			any_sink_consumed = true;
			
			if (0) {
				ex.SetLoading(src_video, src->Cfg());
				sink_video.Exchange(ex);
			}
			else {
				ex.SetStoring(sink_video, src->Cfg());
				src_video.Exchange(ex);
			}
		}
	}
}

void VideoExchangePoint::Init(ConnectorBase* conn) {
	this->conn = conn;
	if (conn) {
		Pool& pool = conn->GetPool();
		Machine& mach = pool.GetMachine();
		Ref<VideoSystem> sys = mach.Get<VideoSystem>();
		ASSERT(sys);
		if (sys)
			sys->Add(this);
	}
}

void VideoExchangePoint::Deinit() {
	if (conn) {
		Pool& pool = conn->GetPool();
		Machine& mach = pool.GetMachine();
		Ref<VideoSystem> sys = mach.Get<VideoSystem>();
		ASSERT(sys);
		if (sys)
			sys->Remove(this);
		conn = 0;
	}
}


NAMESPACE_OULU_END
