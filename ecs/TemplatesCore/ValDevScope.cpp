#include "TemplatesCore.h"


NAMESPACE_ECS_BEGIN

//PoolRef GetConnectorBasePool(ConnectorBase* conn);

Machine& GetPoolMachine(PoolRef pool);



void ValExchangePoint::Init(MetaExchangePoint* mexpt) {
	ASSERT(mexpt);
	/*ConnectorBase* conn = CastPtr<ConnectorBase>(mexpt);
	ASSERT(conn);*/
	
	#if HAVE_VALSYSTEM
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
	#endif
}

void ValExchangePoint::Deinit() {
	#if HAVE_VALSYSTEM
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
	#endif
}

void ValExchangePoint::Forward(FwdScope& fwd) {
	TODO
	#if 0
	USING_VALDEVCORE(ValSource)
	USING_VALDEVCORE(ValSink)
	USING_VALDEVCORE(CtxStream)
	USING_VALDEVMACH(Value)
	RTLOG("ValExchangePoint::Forward: " << GetDynamicName() << "(" << HexStr(this) << ") begin");
	Ref<ValSource>	src			= this->src;
	Ref<ValSink>	sink		= this->sink;
	
	
	CtxStream& src_stream = src->GetStream(CTX);
	//src->BeginStream(CTX);
	
	Ex ex(this);
	
	Value& src_value = src_stream.Get();
	int src_sz = src_value.GetQueueSize();
	
	if (src_sz) {
		Value& sink_value = sink->GetValue(CTX);
		bool sink_full = sink_value.IsQueueFull();
		
		if (!sink_full) {RTLOG("ExchangePoint::Forward: exchanging");}
		else {RTLOG("ExchangePoint::Forward: sink full");}
		
		int iter = 0;
		while (src_sz && !sink_full) {
			
			// Consumer model (works with single connection only)
			if (use_consumer) {
				ex.SetLoading(src_value, fwd.Cfg());
				sink_value.Exchange(ex);
			}
			// Producer model
			else {
				ex.SetStoring(sink_value, fwd.Cfg());
				src_value.Exchange(ex);
			}
			
			if (ex.IsFail()) {
				RTLOG("error: ExchangePoint::Forward: exchange failed");
				fwd.SetFailed();
				break;
			}
			
			src_sz = src_value.GetQueueSize();
			sink_full = sink_value.IsQueueFull();
			++iter;
			if (src_sz && !sink_full) {
				RTLOG("ExchangePoint::Forward: going to iter " << iter << ", sz=" << src_sz << ", sink_full=" << (int)sink_full);
			}
		}
	}
	else {
		RTLOG("ExchangePoint::Forward: empty source");
	}
	
	//src->EndStream(CTX);
	
	fwd.AddNext(sink->AsComponentBase());
	#endif
}









#if HAVE_VALSYSTEM

bool ValSystem::Initialize() {
	
	
	return true;
}

void ValSystem::Start() {
	
}

void ValSystem::Update(double dt) {
	USING_VALDEVCORE(ValExchangePointRef)
	USING_VALDEVCORE(V)
	
}

#if 0
void ValSystem::Iterate(double dt) {
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
		for(FwdScope scope(*expt); scope; scope++)
			scope.Forward();
		
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
#endif

void ValSystem::Stop() {
	
	
}

void ValSystem::Uninitialize() {
	srcs.Clear();
	sinks.Clear();
	expts.Clear();
	
	WhenUninit()();
}

void ValSystem::Add(ValSourceRef src) {
	ASSERT(src);
	srcs.FindAdd(src);
}

void ValSystem::Remove(ValSourceRef src) {
	srcs.RemoveKey(src);
}

void ValSystem::Add(ValSinkRef sink) {
	ASSERT(sink);
	sinks.FindAdd(sink);
}

void ValSystem::Remove(ValSinkRef sink) {
	sinks.RemoveKey(sink);
}

void ValSystem::Add(ValExchangePointRef expt) {
	ASSERT(expt);
	expts.FindAdd(expt);
}

void ValSystem::Remove(ValExchangePointRef expt) {
	expts.RemoveKey(expt);
}
#endif


NAMESPACE_ECS_END


//#undef USING
//#undef CTX
