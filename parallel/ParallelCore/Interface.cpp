#include "ParallelCore.h"


NAMESPACE_PARALLEL_BEGIN


bool DefaultExchangePoint::IsPacketStuck() {
	return false;
}

void DefaultExchangePoint::ForwardExchange(FwdScope& fwd) {
	Ref<DefaultInterfaceSink> sink = this->sink;
	TODO //fwd.AddNext(sink->AsAtomBase()->GetPacketForwarder());
}

void DefaultExchangePoint::ForwardSetup(FwdScope& fwd) {
	DefaultInterfaceSinkRef sink = this->Sink();
	ASSERT(sink);
	
	int ch_i = 0;
	
	Value& to_val = sink->GetValue(ch_i);
	Format to_fmt = to_val.GetFormat();
	if (!to_fmt.IsValid()) {
		ValDevTuple vd = sink->GetSinkCls();
		ASSERT(vd.IsValid());
		to_fmt = GetDefaultFormat(vd());
		ASSERT(to_fmt.IsValid());
		RTLOG("DefaultExchangePoint::ForwardSetup: fixing sink fmt to: " << to_fmt.ToString());
		to_val.SetFormat(to_fmt);
	}
}

void DefaultExchangePoint::ForwardAtom(FwdScope& fwd) {
	const int src_ch_i = 0;
	const int sink_ch_i = 0;
	
	WhenEnterValExPtForward(*this);
	
	RTLOG("DefaultExchangePoint::Forward: " << GetDynamicName() << "(" << HexStr(this) << ") begin");
	Ref<DefaultInterfaceSource>	src			= this->src;
	Ref<DefaultInterfaceSink>	sink		= this->sink;
	
	
	Ex ex(this);
	Value& src_value = src->GetSourceValue(src_ch_i);
	int src_sz = src_value.GetQueueSize();
	
	if (src_sz) {
		Value& sink_value = sink->GetValue(sink_ch_i);
		bool sink_full = sink_value.IsQueueFull();
		
		if (!sink_full) {RTLOG("ExchangePoint::Forward: exchanging");}
		else {RTLOG("ExchangePoint::Forward: sink full");}
		
		int iter = 0;
		while (src_sz && !sink_full) {
			
			ex.Set(src_value, fwd.Cfg());
			sink_value.Exchange(ex);
			
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
	
	TODO //fwd.AddNext(sink->AsAtomBase());
	
	WhenLeaveValExPtForward();
}

void DefaultExchangePoint::Init(MetaSpaceBase* mexpt) {
	ASSERT(mexpt);
	
	#if HAVE_VALSYSTEM
	USING_VALDEVCORE(ValSystem)
	this->conn = conn;
	if (conn) {
		SpaceRef loop = GetConnectorBaseSpace(conn);
		Machine& mach = GetSpaceMachine(loop);
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
		SpaceRef loop = GetConnectorBaseSpace(conn);
		Machine& mach = GetSpaceMachine(loop);
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
	
	SetContainerCount(type.iface.sink.count);
	for(int i = 0; i < type.iface.sink.count; i++)
		InitializeContainer(i, type.iface.sink.vd[i]);
	
	return true;
}

bool DefaultInterfaceSource::Initialize() {
	AtomBase* ab = AsAtomBase();
	AtomTypeCls type = ab->GetType();
	ASSERT(type.IsValid());
	
	SetContainerCount(type.iface.src.count);
	for(int i = 0; i < type.iface.src.count; i++)
		InitializeContainer(i, type.iface.src.vd[i]);
	
	return true;
}



NAMESPACE_PARALLEL_END
