#define TMPL(x)	template <class Ctx> x ContextT<Ctx>::
#define TMPL_ECS(x)	template <class Ctx> x ContextEcsT<Ctx>::
#define USING(x) using x = typename ContextEcsT<Ctx>::x;
#define CTX ((C*)0)

NAMESPACE_TOPSIDE_BEGIN

PoolRef GetConnectorBasePool(ConnectorBase* conn);
Machine& GetPoolMachine(PoolRef pool);



TMPL(void) ExchangePoint::Init(ConnectorBase* conn) {
	USING(System)
	this->conn = conn;
	if (conn) {
		PoolRef pool = GetConnectorBasePool(conn);
		Machine& mach = GetPoolMachine(pool);
		Ref<System> sys = mach.Get<System>();
		ASSERT(sys);
		if (sys)
			sys->Add(AsRef<ExchangePoint>());
	}
}

TMPL(void) ExchangePoint::Deinit() {
	USING(System)
	if (conn) {
		PoolRef pool = GetConnectorBasePool(conn);
		Machine& mach = GetPoolMachine(pool);
		Ref<System> sys = mach.Get<System>();
		ASSERT(sys);
		if (sys)
			sys->Remove(AsRef<ExchangePoint>());
		conn = 0;
	}
}

TMPL(void) ExchangePoint::Update(double dt) {
	USING(Source)
	USING(Sink)
	USING(Stream)
	USING(Value)
	ASSERT(dbg_offset_is_set);
	Ref<Source>	src			= this->src;
	Ref<Sink>	sink		= this->sink;
	
	Ex ex(this);
	ex.SetOffset(offset);
	
	Stream& src_stream = src->GetStream(CTX);
	Value& src_audio = src_stream.Get();
	int src_sz = src_audio.GetQueueSize();
	
	if (src_sz) {
		Value& sink_audio = sink->GetValue(CTX);
		bool sink_full = sink_audio.IsQueueFull();
		
		if (!sink_full) {RTLOG("ExchangePoint::Update: exchanging");}
		else {RTLOG("ExchangePoint::Update: sink full");}
		
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
				RTLOG("error: ExchangePoint::Update: exchange failed");
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
				RTLOG("ExchangePoint::Update: going to iter " << iter << ", sz=" << src_sz << ", sink_full=" << (int)sink_full);
			}
		}
	}
	else {
		RTLOG("ExchangePoint::Update: offset " << offset.ToString() << " empty source");
	}
	
	SetOffset(ex.GetOffset());
	dbg_offset_is_set = false;
}






//Callback System::WhenUninit;

TMPL_ECS(bool) System::Initialize() {
	
	
	return true;
}

TMPL_ECS(void) System::Start() {
	
}

TMPL_ECS(void) System::Update(double dt) {
	USING(ExchangePointRef)
	USING(C)
	
	
	for (SourceRef src : srcs) {
		Stream& stream = src->GetStream(CTX);
		int buf_sz = stream.Get().GetQueueSize();
		bool buffer_full = buf_sz >= 2;
		
		#if 0 && DEBUG_AUDIO_PIPE
		RTLOG("update source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
		#endif
		
		src->Update(dt, buffer_full);
		if (src->Cfg().render) {
			#if DEBUG_AUDIO_PIPE
			RTLOG("begin source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
			#endif
			
			src->BeginStream(CTX);
		}
	}
	
	for (ExchangePointRef expt : expts) {
		SourceRef src = expt->Source();
		off32 begin_offset = expt->GetOffset();
		
		#if 0 && DEBUG_AUDIO_PIPE
		RTLOG("expt updpate " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << "> offset " << IntStr(begin_offset.value));
		#endif
		
		expt->SetOffset(begin_offset);
		expt->Update(dt);
		
		off32 end_offset = expt->GetOffset();
		src->SetOffset(begin_offset, end_offset);
		
		#if DEBUG_AUDIO_PIPE
		off32 diff = off32::GetDifference(begin_offset, end_offset);
		if (diff) {
			auto sink = expt->Sink();
			RTLOG("sink " << HexStr((size_t)&*sink) << "<" << sink->GetConfigString() << "> consumed " << diff.ToString());
		}
		#endif
	}
	
	for (SourceRef src :srcs) {
		const auto& cfg = src->Cfg();
		if (cfg.begin_offset != cfg.end_offset) {
			#if DEBUG_AUDIO_PIPE
			RTLOG("end source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
			#endif
			
			src->EndStream(CTX);
		}
	}
	
}

TMPL_ECS(void) System::Stop() {
	
	
}

TMPL_ECS(void) System::Uninitialize() {
	srcs.Clear();
	sinks.Clear();
	expts.Clear();
	
	WhenUninit();
}

TMPL_ECS(void) System::Add(SourceRef src) {
	ASSERT(src);
	srcs.FindAdd(src);
}

TMPL_ECS(void) System::Remove(SourceRef src) {
	srcs.RemoveKey(src);
}

TMPL_ECS(void) System::Add(SinkRef sink) {
	ASSERT(sink);
	sinks.FindAdd(sink);
}

TMPL_ECS(void) System::Remove(SinkRef sink) {
	sinks.RemoveKey(sink);
}

TMPL_ECS(void) System::Add(ExchangePointRef expt) {
	ASSERT(expt);
	expts.FindAdd(expt);
}

TMPL_ECS(void) System::Remove(ExchangePointRef expt) {
	expts.RemoveKey(expt);
}



NAMESPACE_TOPSIDE_END


#undef TMPL
#undef TMPL_ECS
#undef USING
#undef CTX
