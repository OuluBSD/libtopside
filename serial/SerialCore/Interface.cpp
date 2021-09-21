#include "Internal.h"


NAMESPACE_SERIAL_BEGIN


void DefaultExchangePoint::ForwardExchange(FwdScope& fwd) {
	Ref<DefaultInterfaceSink> sink = this->sink;
	fwd.AddNext(sink->AsAtomBase()->GetPacketForwarder());
}



DefaultExchangePoint* DefaultExchangePoint::Create(TypeCls t) {
	TODO
	/*#define IFACE_CTX_CLS(dev, val, prefix) \
		if (t == AsTypeCls<VD<dev##Spec, val##Spec>>()) \
			return new ScopeValDevMachT<VD<dev##Spec, val##Spec>>::DefaultExchangePoint();
	#define IFACE(x) DEV_IFACE(x)
	IFACE_LIST
	#undef IFACE
	#undef IFACE_CTX_CLS*/
	ASSERT_(false, "Invalid TypeCls arg in DefaultExchangePoint::Create");
	return 0;
}




void DefaultExchangePoint::ForwardSetup(FwdScope& fwd) {
	/*USING_VALDEVMACH(ValSpec)
	using ValSpec				= typename ValDevSpec::Val;
	using DevSpec				= typename ValDevSpec::Dev;
	using ValMach				= ScopeValMachT<ValSpec>;
	using Mach					= ScopeValDevMachT<ValDevSpec>;
	using DevMach				= ScopeDevMachT<DevSpec>;
	using DevCore				= ScopeDevCoreT<DevSpec>;
	using DevLib				= ScopeDevLibT<DevSpec>;
	using Core					= ScopeValDevCoreT<ValDevSpec>;
	using ValStreamState		= typename ValMach::ValStreamState;
	using DevStreamState		= typename DevMach::DevStreamState;
	using DevComponent			= typename DevLib::DevComponent;
	using StageComponent		= typename DevLib::StageComponent;
	using Value					= typename Mach::Value;
	using SourceRef				= typename Core::DefaultInterfaceSourceRef;
	using SinkRef				= typename Core::DefaultInterfaceSinkRef;*/
	//using DevContextConnectorBaseRef	= typename DevMach::DevContextConnectorBaseRef;
	//using DevContextConnectorRef		= typename DevLib::DevContextConnectorRef;
	
	//ASSERT(!dbg_offset_is_set);
	
	
	
	DefaultInterfaceSinkRef sink = this->Sink();
	ASSERT(sink);
	
	Value& to_val = sink->GetValue();
	Format to_fmt = to_val.GetFormat();
	if (!to_fmt.IsValid()) {
		ValDevTuple vd = sink->GetSinkCls();
		ASSERT(vd.IsValid());
		to_fmt = GetDefaultFormat(vd());
		SimpleBufferedValue* sbbuf;
		SimpleValue* sbuf;
		if ((sbbuf = CastPtr<SimpleBufferedValue>(&to_val))) {
			sbbuf->SetFormat(to_fmt);
		}
		else if ((sbuf = CastPtr<SimpleValue>(&to_val))) {
			sbuf->SetFormat(to_fmt);
		}
		else {
			LOG("Unexpected value type: " << to_val.GetDynamicName());
			TODO
		}
		auto fmt = to_val.GetFormat();
		ASSERT(fmt.IsValid());
	}
}

void DefaultExchangePoint::ForwardAtom(FwdScope& fwd) {
	WhenEnterValExPtForward(*this);
	
	RTLOG("DefaultExchangePoint::Forward: " << GetDynamicName() << "(" << HexStr(this) << ") begin");
	Ref<DefaultInterfaceSource>	src			= this->src;
	Ref<DefaultInterfaceSink>	sink		= this->sink;
	
	
	Stream& src_stream = src->GetStream();
	//src->BeginStream();
	
	Ex ex(this);
	
	Value& src_value = src_stream.Get();
	int src_sz = src_value.GetQueueSize();
	
	if (src_sz) {
		Value& sink_value = sink->GetValue();
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
	
	fwd.AddNext(sink->AsAtomBase());
	
	WhenLeaveValExPtForward();
}

void DefaultExchangePoint::Init(MetaExchangePoint* mexpt) {
	ASSERT(mexpt);
	/*ConnectorBase* conn = CastPtr<ConnectorBase>(mexpt);
	ASSERT(conn);*/
	
	#if HAVE_VALSYSTEM
	USING_VALDEVCORE(ValSystem)
	this->conn = conn;
	if (conn) {
		LoopRef loop = GetConnectorBaseLoop(conn);
		Machine& mach = GetLoopMachine(loop);
		Ref<ValSystem> sys = mach.Get<ValSystem>();
		ASSERT(sys);
		if (sys)
			sys->Add(AsRef<ExchangePoint>());
	}
	#endif
}

void DefaultExchangePoint::Deinit() {
	#if HAVE_VALSYSTEM
	USING_VALDEVCORE(ValSystem)
	if (conn) {
		LoopRef loop = GetConnectorBaseLoop(conn);
		Machine& mach = GetLoopMachine(loop);
		Ref<ValSystem> sys = mach.Get<ValSystem>();
		ASSERT(sys);
		if (sys)
			sys->Remove(AsRef<ExchangePoint>());
		conn = 0;
	}
	#endif
}



bool DefaultInterfaceSink::Initialize() {
	AtomBase* ab = AsAtomBase();
	AtomTypeCls type = ab->GetType();
	ASSERT(type.IsValid());
	
	InitializeContainer(this, type.iface.sink);
	
	return true;
}

bool DefaultInterfaceSource::Initialize() {
	AtomBase* ab = AsAtomBase();
	AtomTypeCls type = ab->GetType();
	ASSERT(type.IsValid());
	
	InitializeContainer(this, type.iface.src);
	
	return true;
}



NAMESPACE_SERIAL_END
