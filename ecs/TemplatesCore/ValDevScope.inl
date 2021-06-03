#define USING(x)		using x = typename ScopeValDevCoreT<Dev>::x;
#define CTX				((V*)0)

NAMESPACE_TOPSIDE_BEGIN

PoolRef GetConnectorBasePool(ConnectorBase* conn);
Machine& GetPoolMachine(PoolRef pool);



TMPL_VALDEVMACH(void) ValExchangePoint::Init(ConnectorBase* conn) {
	USING_VALDEVCORE(ValSystem)
	this->conn = conn;
	if (conn) {
		PoolRef pool = GetConnectorBasePool(conn);
		Machine& mach = GetPoolMachine(pool);
		Ref<ValSystem> sys = mach.Get<ValSystem>();
		ASSERT(sys);
		if (sys)
			sys->Add(AsRef<ExchangePoint>());
	}
}

TMPL_VALDEVMACH(void) ValExchangePoint::Deinit() {
	USING_VALDEVCORE(ValSystem)
	if (conn) {
		PoolRef pool = GetConnectorBasePool(conn);
		Machine& mach = GetPoolMachine(pool);
		Ref<ValSystem> sys = mach.Get<ValSystem>();
		ASSERT(sys);
		if (sys)
			sys->Remove(AsRef<ExchangePoint>());
		conn = 0;
	}
}

TMPL_VALDEVMACH(void) ValExchangePoint::Update(double dt) {
	USING_VALDEVCORE(ValSource)
	USING_VALDEVCORE(ValSink)
	USING_VALDEVCORE(CtxStream)
	USING_VALDEVMACH(Value)
	ASSERT(dbg_offset_is_set);
	Ref<ValSource>	src			= this->src;
	Ref<ValSink>	sink		= this->sink;
	
	Ex ex(this);
	ex.SetOffset(offset);
	
	CtxStream& src_stream = src->GetStream(CTX);
	Value& src_value = src_stream.Get();
	int src_sz = src_value.GetQueueSize();
	
	if (src_sz) {
		Value& sink_value = sink->GetValue(CTX);
		bool sink_full = sink_value.IsQueueFull();
		
		if (!sink_full) {RTLOG("ExchangePoint::Update: exchanging");}
		else {RTLOG("ExchangePoint::Update: sink full");}
		
		#if 1
		int iter = 0;
		int total_exchanged = 0;
		int max_exchange = src_sz;
		while (src_sz && !sink_full) {
			off32 begin = ex.GetOffset();
			
			// Consumer works with single connection only
			if (use_consumer) {
				ex.SetLoading(src_value, src->Cfg());
				sink_value.Exchange(ex);
			}
			else {
				ex.SetStoring(sink_value, src->Cfg());
				src_value.Exchange(ex);
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
			
			src_sz = src_value.GetQueueSize();
			sink_full = sink_value.IsQueueFull();
			++iter;
			if (src_sz && !sink_full) {
				RTLOG("ExchangePoint::Update: going to iter " << iter << ", sz=" << src_sz << ", sink_full=" << (int)sink_full);
			}
		}
		#else
		if (src_sz && !sink_full) {
			off32 begin = ex.GetOffset();
				
			// Consumer works with single connection only
			if (use_consumer) {
				ex.SetLoading(src_value, src->Cfg());
				sink_value.Exchange(ex);
			}
			else {
				ex.SetStoring(sink_value, src->Cfg());
				src_value.Exchange(ex);
			}
			
			if (ex.IsFail()) {
				RTLOG("error: ExchangePoint::Update: exchange failed");
			}
		}
		#endif
	}
	else {
		RTLOG("ExchangePoint::Update: offset " << offset.ToString() << " empty source");
	}
	
	SetOffset(ex.GetOffset());
	dbg_offset_is_set = false;
}








TMPL_VALDEVCORE(bool) ValSystem::Initialize() {
	
	
	return true;
}

TMPL_VALDEVCORE(void) ValSystem::Start() {
	
}

TMPL_VALDEVCORE(void) ValSystem::Update(double dt) {
	USING_VALDEVCORE(ValExchangePointRef)
	USING_VALDEVCORE(V)
	
	
	for (ValSourceRef src : srcs) {
		CtxStream& stream = src->GetStream(CTX);
		int buf_sz = stream.Get().GetQueueSize();
		bool buffer_full = buf_sz >= 2;
		
		#if 0 && DEBUG_RT_PIPE
		RTLOG("update source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
		#endif
		
		src->Update(dt, buffer_full);
		if (src->Cfg().render) {
			#if DEBUG_RT_PIPE
			RTLOG("begin source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
			#endif
			
			src->BeginStream(CTX);
		}
	}
	
	int dbg_i = 0;
	for (ValExchangePointRef expt : expts) {
		off32 begin_offset = expt->GetOffset();
		#if 1 && DEBUG_RT_PIPE
		const RTTI& expt_rtti = expt->GetRTTI();
		RTLOG("expt " << dbg_i << " update " << HexStr((size_t)&expt_rtti.GetRTTI()) << "<" << expt_rtti.GetDynamicName() << "> offset " << IntStr(begin_offset.value));
		#endif
		
		ValSinkRef sink = expt->Sink();
		ValSourceRef src = expt->Source();
		#if 0 && DEBUG_RT_PIPE
		RTLOG("expt updpate src " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << "> offset " << IntStr(begin_offset.value));
		#endif
		
		expt->SetOffset(begin_offset);
		expt->Update(dt);
		
		off32 end_offset = expt->GetOffset();
		src->SetOffset(begin_offset, end_offset);
		
		#if DEBUG_RT_PIPE
		off32 diff = off32::GetDifference(begin_offset, end_offset);
		if (diff) {
			RTLOG("sink " << HexStr((size_t)&*sink) << "<" << sink->GetConfigString() << "> consumed " << diff.ToString());
		}
		#endif
		++dbg_i;
	}
	
	for (ValSourceRef src :srcs) {
		const auto& cfg = src->Cfg();
		if (cfg.begin_offset != cfg.end_offset) {
			#if DEBUG_RT_PIPE
			RTLOG("end source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
			#endif
			
			src->EndStream(CTX);
		}
	}
	
}

TMPL_VALDEVCORE(void) ValSystem::Stop() {
	
	
}

TMPL_VALDEVCORE(void) ValSystem::Uninitialize() {
	srcs.Clear();
	sinks.Clear();
	expts.Clear();
	
	WhenUninit();
}

TMPL_VALDEVCORE(void) ValSystem::Add(ValSourceRef src) {
	ASSERT(src);
	srcs.FindAdd(src);
}

TMPL_VALDEVCORE(void) ValSystem::Remove(ValSourceRef src) {
	srcs.RemoveKey(src);
}

TMPL_VALDEVCORE(void) ValSystem::Add(ValSinkRef sink) {
	ASSERT(sink);
	sinks.FindAdd(sink);
}

TMPL_VALDEVCORE(void) ValSystem::Remove(ValSinkRef sink) {
	sinks.RemoveKey(sink);
}

TMPL_VALDEVCORE(void) ValSystem::Add(ValExchangePointRef expt) {
	ASSERT(expt);
	expts.FindAdd(expt);
}

TMPL_VALDEVCORE(void) ValSystem::Remove(ValExchangePointRef expt) {
	expts.RemoveKey(expt);
}



NAMESPACE_TOPSIDE_END


#undef USING
#undef CTX
