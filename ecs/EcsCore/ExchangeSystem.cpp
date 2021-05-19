#include "EcsCore.h"


NAMESPACE_TOPSIDE_BEGIN







AudioExchangePoint::AudioExchangePoint() {
	
}

void AudioExchangePoint::Init(ConnectorBase* conn) {
	this->conn = conn;
	if (conn) {
		PoolRef pool = conn->GetPool();
		Machine& mach = pool->GetMachine();
		Ref<AudioSystem> sys = mach.Get<AudioSystem>();
		ASSERT(sys);
		if (sys)
			sys->Add(AsRef<AudioExchangePoint>());
	}
}

void AudioExchangePoint::Deinit() {
	if (conn) {
		PoolRef pool = conn->GetPool();
		Machine& mach = pool->GetMachine();
		Ref<AudioSystem> sys = mach.Get<AudioSystem>();
		ASSERT(sys);
		if (sys)
			sys->Remove(AsRef<AudioExchangePoint>());
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
	Audio& src_audio = src_stream.Get();
	int src_sz = src_audio.GetQueueSize();
	
	if (src_sz) {
		Audio& sink_audio = sink->GetAudioSink();
		bool sink_full = sink_audio.IsQueueFull();
		
		if (!sink_full) {AUDIOLOG("AudioExchangePoint::Update: exchanging");}
		else {AUDIOLOG("AudioExchangePoint::Update: sink full");}
		
		int iter = 0;
		int total_exchanged = 0;
		int max_exchange = src_sz;
		while (src_sz && !sink_full) {
			off32 begin = ex.GetOffset();
			
			// Consumer works with single connection only
			if (use_consumer) {
				ex.SetLoading(src_audio, src->Cfg());
				sink_audio.Exchange(ex);
			}
			else {
				ex.SetStoring(sink_audio, src->Cfg());
				src_audio.Exchange(ex);
			}
			
			if (ex.IsFail()) {
				AUDIOLOG("error: AudioExchangePoint::Update: exchange failed");
				break;
			}
			
			off32 end = ex.GetOffset();
			off32 exchanged = off32::GetDifference(begin, end);
			total_exchanged += exchanged.value;
			if (total_exchanged >= max_exchange)
				break;
			
			src_sz = src_audio.GetQueueSize();
			sink_full = sink_audio.IsQueueFull();
			++iter;
			if (src_sz && !sink_full) {
				AUDIOLOG("AudioExchangePoint::Update: going to iter " << iter << ", sz=" << src_sz << ", sink_full=" << (int)sink_full);
			}
		}
	}
	else {
		AUDIOLOG("AudioExchangePoint::Update: offset " << offset.ToString() << " empty source");
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
	
	TODO // copy audio update
	
	VideoEx ex(this);
	VideoStream& src_stream = src->GetVideoSource();
	if (src_stream.GetBufferSize()) {
		
		Video& src_video = src_stream.Get();
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
		PoolRef pool = conn->GetPool();
		Machine& mach = pool->GetMachine();
		Ref<VideoSystem> sys = mach.Get<VideoSystem>();
		ASSERT(sys);
		if (sys)
			sys->Add(AsRef<VideoExchangePoint>());
	}
}

void VideoExchangePoint::Deinit() {
	if (conn) {
		PoolRef pool = conn->GetPool();
		Machine& mach = pool->GetMachine();
		Ref<VideoSystem> sys = mach.Get<VideoSystem>();
		ASSERT(sys);
		if (sys)
			sys->Remove(AsRef<VideoExchangePoint>());
		conn = 0;
	}
}













DisplayExchangePoint::DisplayExchangePoint() {
	
}

void DisplayExchangePoint::Update(double dt) {
	ASSERT(dbg_offset_is_set);
	Ref<DisplaySource>	src			= this->src;
	Ref<DisplaySink>		sink		= this->sink;
	
	DisplayEx ex(this);
	ex.SetOffset(offset);
	
	DisplayStream& src_stream = src->GetDisplaySource();
	Display& src_display = src_stream.Get();
	int src_sz = src_display.GetQueueSize();
	
	if (src_sz) {
		Display& sink_display = sink->GetDisplaySink();
		bool sink_full = sink_display.IsQueueFull();
		
		if (!sink_full) {DISPLAYLOG("DisplayExchangePoint::Update: exchanging");}
		else {DISPLAYLOG("DisplayExchangePoint::Update: sink full");}
		
		int iter = 0;
		int total_exchanged = 0;
		int max_exchange = src_sz;
		while (src_sz && !sink_full) {
			off32 begin = ex.GetOffset();
			
			// Consumer works with single connection only
			if (use_consumer) {
				ex.SetLoading(src_display, src->Cfg());
				sink_display.Exchange(ex);
			}
			else {
				ex.SetStoring(sink_display, src->Cfg());
				src_display.Exchange(ex);
			}
			
			if (ex.IsFail()) {
				DISPLAYLOG("error: DisplayExchangePoint::Update: exchange failed");
				break;
			}
			
			off32 end = ex.GetOffset();
			off32 exchanged = off32::GetDifference(begin, end);
			total_exchanged += exchanged.value;
			if (total_exchanged >= max_exchange)
				break;
			
			src_sz = src_display.GetQueueSize();
			sink_full = sink_display.IsQueueFull();
			++iter;
			if (src_sz && !sink_full) {
				DISPLAYLOG("DisplayExchangePoint::Update: going to iter " << iter << ", sz=" << src_sz << ", sink_full=" << (int)sink_full);
			}
		}
	}
	else {
		DISPLAYLOG("DisplayExchangePoint::Update: offset " << offset.ToString() << " empty source");
	}
	
	SetOffset(ex.GetOffset());
	dbg_offset_is_set = false;
}

void DisplayExchangePoint::Init(ConnectorBase* conn) {
	this->conn = conn;
	if (conn) {
		PoolRef pool = conn->GetPool();
		Machine& mach = pool->GetMachine();
		Ref<DisplaySystem> sys = mach.Get<DisplaySystem>();
		ASSERT(sys);
		if (sys)
			sys->Add(AsRef<DisplayExchangePoint>());
	}
}

void DisplayExchangePoint::Deinit() {
	if (conn) {
		PoolRef pool = conn->GetPool();
		Machine& mach = pool->GetMachine();
		Ref<DisplaySystem> sys = mach.Get<DisplaySystem>();
		ASSERT(sys);
		if (sys)
			sys->Remove(AsRef<DisplayExchangePoint>());
		conn = 0;
	}
}




NAMESPACE_TOPSIDE_END
