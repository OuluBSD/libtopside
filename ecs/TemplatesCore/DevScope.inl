#define TMPL(x)			template <class DevCtx> x ContextDevMachT<DevCtx>::
#define TMPL_ECS(x)		template <class DevCtx> x ScopeDevCoreT<DevCtx>::
#define USING(x)		using x = typename ScopeDevCoreT<DevCtx>::x;
#define CTX				((V*)0)

NAMESPACE_TOPSIDE_BEGIN



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
TMPL(void) ExchangePoint::Update(double dt) {TODO}





//Callback System::WhenUninit;

TMPL_ECS(bool) System::Initialize() {
	
	
	return true;
}

TMPL_ECS(void) System::Start() {
	
}

TMPL_ECS(void) System::Update(double dt) {
	USING(ExchangePointRef)
	USING(D)
	
	TODO
	#if 0
	for (SourceRef src : srcs) {
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
	for (ExchangePointRef expt : expts) {
		off32 begin_offset = expt->GetOffset();
		#if 1 && DEBUG_RT_PIPE
		const RTTI& expt_rtti = expt->GetRTTI();
		RTLOG("expt " << dbg_i << " update " << HexStr((size_t)&expt_rtti.GetRTTI()) << "<" << expt_rtti.GetDynamicName() << "> offset " << IntStr(begin_offset.value));
		#endif
		
		SinkRef sink = expt->Sink();
		SourceRef src = expt->Source();
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
	
	for (SourceRef src :srcs) {
		const auto& cfg = src->Cfg();
		if (cfg.begin_offset != cfg.end_offset) {
			#if DEBUG_RT_PIPE
			RTLOG("end source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
			#endif
			
			src->EndStream(CTX);
		}
	}
	
	#endif
	
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
