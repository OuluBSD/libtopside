#include "EcsCore.h"


NAMESPACE_OULU_BEGIN


void RealtimeSourceConfig::Update(double dt, bool buffer_full) {
	sync_age += dt;
	
	this->dt += dt;
	++src_frame;
	
	if (sync_age >= sync_dt) {
		if (sync_age > 2 * sync_dt)
			sync_age = sync_dt;
		else
			sync_age = Modulus(sync_age, sync_dt);
		
		last_sync_src_frame = src_frame;
		
		frames_after_sync = 0;
		sync = true;
		
		render = true;
	}
	else if (!buffer_full) {
		sync = false;
		frames_after_sync = src_frame > last_sync_src_frame ? src_frame - last_sync_src_frame : 0;
		
		render = true;
	}
	else {
		render = false;
	}
}










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
	Ref<AudioSource>	src			= this->src;
	Ref<AudioSink>		sink		= this->sink;
	
	AudioEx ex(this);
	AudioStream& src_stream = src->GetAudioSource();
	if (src_stream.GetAudioBufferSize()) {
		Audio& src_audio = src_stream.GetAudio();
		Audio& sink_audio = sink->GetAudioSink();
		
		if (0) {
			ex.SetLoading(src_audio, src->Cfg());
			sink_audio.Exchange(ex);
		}
		else {
			ex.SetStoring(sink_audio, src->Cfg());
			src_audio.Exchange(ex);
		}
	}
}





VideoExchangePoint::VideoExchangePoint() {
	
}

void VideoExchangePoint::Update(double dt) {
	Ref<VideoSource>	src			= this->src;
	Ref<VideoSink>		sink		= this->sink;
	
	VideoEx ex(this);
	VideoStream& src_stream = src->GetVideoSource();
	if (src_stream.GetVideoBufferSize()) {
		Video& src_audio = src_stream.GetVideo();
		Video& sink_audio = sink->GetVideoSink();
		
		ex.SetLoading(src_audio);
		sink_audio.Exchange(ex);
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
