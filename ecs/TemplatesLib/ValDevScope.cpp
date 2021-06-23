#include "TemplatesLib.h"

NAMESPACE_ECS_BEGIN

void ValExchangePoint::ForwardExchange(FwdScope& fwd) {
	Ref<ValSink> sink = this->sink;
	fwd.AddNext(sink->AsComponentBase()->GetPacketForwarder());
}



ValExchangePointBase* ValExchangePointBase::Create(TypeCls t) {
	TODO
	/*#define IFACE_CTX_CLS(dev, val, prefix) \
		if (t == AsTypeCls<VD<dev##Spec, val##Spec>>()) \
			return new ScopeValDevMachT<VD<dev##Spec, val##Spec>>::ValExchangePoint();
	#define IFACE(x) DEV_IFACE(x)
	IFACE_LIST
	#undef IFACE
	#undef IFACE_CTX_CLS*/
	ASSERT_(false, "Invalid TypeCls arg in ValExchangePointBase::Create");
	return 0;
}




void ValExchangePoint::ForwardSetup(FwdScope& fwd) {
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
	using SourceRef				= typename Core::ValSourceRef;
	using SinkRef				= typename Core::ValSinkRef;*/
	//using DevContextConnectorBaseRef	= typename DevMach::DevContextConnectorBaseRef;
	//using DevContextConnectorRef		= typename DevLib::DevContextConnectorRef;
	
	//ASSERT(!dbg_offset_is_set);
	
	
	
	TODO
	/*SinkRef sink = this->sink;
	StageComponent* sink_comp = CastPtr<StageComponent>(sink->AsComponentBase());
	Value& to_val = sink->GetValue((ValSpec*)0);
	Format to_fmt = to_val.GetFormat();
	if (!to_fmt.IsValid()) {
		to_fmt = DevCore::template GetDefaultFormat<ValSpec>();
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
	}*/
}


void InputComponent::Forward(FwdScope& fwd) {
	TODO
	#if 0
	using FromValSpec				= OrderSpec;
	using ToValSpec					= typename ValDevSpec::Val;
	using DevSpec					= typename ValDevSpec::Dev;
	
	using DevMach					= ScopeDevMachT<DevSpec>;
	using InternalPacketData		= typename DevMach::InternalPacketData;
	
	using FromValDevSpec			= VD<DevSpec, FromValSpec>;
	using FromValMach				= ScopeValMachT<FromValSpec>;
	using FromValDevMach			= ScopeValDevMachT<FromValDevSpec>;
	using FromValDevCore			= ScopeValDevCoreT<FromValDevSpec>;
	using FromPacket				= typename FromValMach::Packet;
	using FromValue					= typename FromValDevMach::Value;
	using FromPacketBuffer			= typename FromValDevMach::PacketBuffer;
	using FromSimpleValue			= typename FromValDevMach::SimpleValue;
	using FromSimpleBufferedValue	= typename FromValDevMach::SimpleBufferedValue;
	using FromSink					= typename FromValDevCore::ValSink;
	#define FROMCTX (FromValSpec*)0
	
	using ToValDevSpec				= VD<DevSpec, ToValSpec>;
	using ToValMach					= ScopeValMachT<ToValSpec>;
	using ToValDevMach				= ScopeValDevMachT<ToValDevSpec>;
	using ToValDevCore				= ScopeValDevCoreT<ToValDevSpec>;
	using ToValLib					= ScopeValLibT<ToValSpec>;
	using ToValCore					= ScopeValCoreT<ToValSpec>;
	using ToPacket					= typename ToValMach::Packet;
	using ToFormat					= typename ToValMach::Format;
	using ToValue					= typename ToValDevMach::Value;
	using ToSimpleBufferedValue		= typename ToValDevMach::SimpleBufferedValue;
	using ToSimpleValue				= typename ToValDevMach::SimpleValue;
	using ToPacketBuffer			= typename ToValDevMach::PacketBuffer;
	using ToSource					= typename ToValDevCore::ValSource;
	using ToSink					= typename ToValDevCore::ValSink;
	using ToSinkRef					= typename ToValDevCore::ValSinkRef;
	using ToPacketTracker			= typename ToValCore::PacketTracker;
	#define TOCTX (ToValSpec*)0
	
	if (this->ext)
		this->ext->Forward(fwd);
	
	ToSource& iface_src = *this;
	FromSink& iface_sink = *this;
	FromValue& sink_val = iface_sink.GetValue(FROMCTX);
	
	
	FromSimpleBufferedValue* sink_buf_val;
	FromSimpleValue* sink_sval;
	FromPacketBuffer* sink_buf;
	if ((sink_buf_val = CastPtr<FromSimpleBufferedValue>(&sink_val))) {
		sink_buf = &sink_buf_val->GetBuffer();
	}
	else if ((sink_sval = CastPtr<FromSimpleValue>(&sink_val))) {
		sink_buf = &sink_sval->GetBuffer();
	}
	else TODO
	
	
	ToValue& val = iface_src.GetStream(TOCTX).Get();
	ToSimpleValue* sval;
	ToSimpleBufferedValue* sbcal;
	ToPacketBuffer* pbuf;
	if ((sval = CastPtr<ToSimpleValue>(&val))) {
		pbuf = &sval->GetBuffer();
	}
	else if ((sbcal = CastPtr<ToSimpleBufferedValue>(&val))) {
		pbuf = &sbcal->GetBuffer();
	}
	else TODO
		
	
	while (sink_buf->GetCount() && !val.IsQueueFull()) {
		FromPacket in = sink_buf->First();
		sink_buf->RemoveFirst();
		
		int c = sink_buf->IsEmpty() ? 100 : 1;
		
		for(int i = 0; i < c && !val.IsQueueFull(); i++) {
			off32 off = in->GetOffset();
			RTLOG("InputComponent::Forward: play packet " << off.ToString());
			
			ToPacket to = ToValMach::CreatePacket(off);
			
			ToFormat fmt = ScopeDevCoreT<DevSpec>::template GetDefaultFormat<ToValSpec>();
			RTLOG("InputComponent::Forward: sending packet in format: " << fmt.ToString());
			to->SetFormat(fmt);
			
			InternalPacketData& data = to->template SetData<InternalPacketData>();
			data.pos = 0;
			data.count = 1;
			
			sval->StorePacket(to);
			
			ToPacketTracker::Track(TrackerInfo("InputComponent::Forward", __FILE__, __LINE__), *to);
			pbuf->Add(to);
		}
	}
	
	#undef FROMCTX
	#undef TOCTX
	#endif
}

void InputComponent::ForwardExchange(FwdScope& fwd) {
	ValSource& src = *this;
	ExchangePointRef expt = src.GetExPt();
	ASSERT(expt);
	if (expt) {
		fwd.AddNext(*expt);
	}
}


/*TMPL_VALDEVLIB(CLS::CtxStream&) InputComponent::GetStream(V*) {
	return stream;
}

void InputComponent::BeginStream(V*) {
	stream.FillBuffer();
}

void InputComponent::EndStream(V*) {
	stream.DropBuffer();
}

bool InputComponent::ReadFrame() {
	TODO
}

bool InputComponent::ProcessDeviceFrame() {
	TODO
}

bool InputComponent::LocalStream::IsOpen() const {
	TODO
}

bool InputComponent::LocalStream::Open(int fmt_idx) {
	TODO
}

bool InputComponent::LocalStream::LoadFileAny(String path) {
	TODO
}*/

void OutputComponent::Initialize() {
	TODO
	#if 0
	auto fmt = DevCore::template GetDefaultFormat<ValSpec>();
	sink_value.SetFormat(fmt);
	sink_value.SetMinBufSamples(fmt.GetSampleRate() * 2);
	
	
	cust_sys = ComponentBase::GetEntity()->GetMachine().template TryGet<CustomerSystem>();
	#endif
}

void OutputComponent::Uninitialize() {
	ASSERT(this->ext.IsEmpty());
}

void OutputComponent::Forward(FwdScope& fwd) {
	TODO
	#if 0
	using FromValSpec				= typename ValDevSpec::Val;
	using ToValSpec					= ReceiptSpec;
	using DevSpec					= typename ValDevSpec::Dev;
	
	using DevMach					= ScopeDevMachT<DevSpec>;
	using InternalPacketData		= typename DevMach::InternalPacketData;
	
	using FromValDevSpec			= VD<DevSpec, FromValSpec>;
	using FromValMach				= ScopeValMachT<FromValSpec>;
	using FromValDevMach			= ScopeValDevMachT<FromValDevSpec>;
	using FromValDevCore			= ScopeValDevCoreT<FromValDevSpec>;
	using FromPacket				= typename FromValMach::Packet;
	using FromValue					= typename FromValDevMach::Value;
	
	using ToValDevSpec				= VD<DevSpec, ToValSpec>;
	using ToValMach					= ScopeValMachT<ToValSpec>;
	using ToValDevMach				= ScopeValDevMachT<ToValDevSpec>;
	using ToValDevCore				= ScopeValDevCoreT<ToValDevSpec>;
	using ToValLib					= ScopeValLibT<ToValSpec>;
	using ToValCore					= ScopeValCoreT<ToValSpec>;
	using ToPacket					= typename ToValMach::Packet;
	using ToFormat					= typename ToValMach::Format;
	using ToPacketTracker			= typename ToValCore::PacketTracker;
	
	if (this->ext)
		this->ext->Forward(fwd);
	
	#define FROMCTX (FromValSpec*)0
	
	FromValue& sink_value = GetValue(FROMCTX);
	//Receipt& src_value = GetStream(RCPCTX).Get();
	auto& sink_buf = sink_value.GetBuffer();
	auto& src_buf = src_value.GetBuffer();
	
	cfg = &fwd.Cfg();
	
	lock.Enter();
	
	Index<dword> offs;
	for (auto& in : consumed_packets) {
		off32 o = in->GetOffset();
		if (offs.Find(o.value) >= 0)
			continue;
		offs.Add(o.value);
		
		ToPacket to = ToValMach::CreatePacket(o);
	
		ToFormat fmt = ScopeDevCoreT<DevSpec>::template GetDefaultFormat<ToValSpec>();
		RTLOG("OutputComponent::Forward: sending packet in format: " << fmt.ToString());
		to->SetFormat(fmt);
		
		InternalPacketData& data = to->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = 1;
		
		src_value.StorePacket(to);
		
		ToPacketTracker::Track(TrackerInfo("DebugSoundGeneratorComponent::Forward", __FILE__, __LINE__), *to);
		src_buf.Add(to);
	}
	
	lock.Leave();
	
	#undef FROMCTX
	#endif
}

void OutputComponent::ForwardExchange(FwdScope& fwd) {
	auto& src_buf = src_value.GetBuffer();
	if (!src_buf.IsEmpty()) {
		ValSource& src = *this;
		ExchangePointRef expt = src.GetExPt();
		ASSERT(expt);
		if (expt) {
			fwd.AddNext(*expt);
		}
	}
}

bool OutputComponent::ForwardMem(void* mem, size_t mem_size) {
	if (consumer.IsEmptySource())
		consumer.SetSource(sink_value.GetBuffer());
	
	if (mem) {
		Format fmt = sink_value.GetFormat();
		
		int size = fmt.GetFrameSize();
		if (size != mem_size) {
			RTLOG("OutputComponent::ForwardMem: error: memsize mismatch (" << size << " != " << mem_size << ")");
			return false;
		}
		
		int qsize = sink_value.GetQueueSize();
		if (qsize > 0 || consumer.HasLeftover()) {
			
			/*off32 begin_offset = buf.GetOffset();
			if (0) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: trying to consume " << begin_offset.ToString());
				RTLOG("BufferedAudioDeviceStream::SinkCallback: dumping");
				buf.Dump();
			}*/
			
			consumer.SetDestination(fmt, mem, size);
			consumer.ConsumeAll(false);
			consumer.ClearDestination();
			int csize = consumer.GetLastMemoryBytes();
			int consumed_count = consumer.GetCount();
			if (csize != size) {
				RTLOG("OutputComponent::ForwardMem: error: consumed " << csize << " (expected " << size << "), packets=" << consumed_count);
			}
			else {
				RTLOG("OutputComponent::ForwardMem:  consumed " << csize << ", packets=" << consumed_count);
			}
			
			lock.Enter();
			consumed_packets.Append(consumer.consumed_packets);
			lock.Leave();
			
			
			if (cust_sys && cfg)
				cust_sys->AddOnce(*this, *cfg);
			
			/*off32 end_offset = consumer.GetOffset();
			off32 diff = off32::GetDifference(begin_offset, end_offset);
			if (diff) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: device consumed count=" << diff.ToString());
				buf.RemoveFirst(diff.value);
			}
			else if (consumer.HasLeftover()) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: device consumed packet partially");
			}
			else if (!consumer.HasLeftover()) {
				RTLOG("error: BufferedAudioDeviceStream::SinkCallback: device error");
			}*/
			return true;
		}
		else {
			#if DEBUG_RT_PIPE
			RTLOG("error: OutputComponent::ForwardMem: got empty data");
			#endif
			
			memset(mem, 0, size);
		}
	}
	return false;
}




void PipeComponent::Initialize() {
	StageComponent::Initialize();
	auto fmt = GetDefaultFormat(vd);
	sink_value	.SetFormat(fmt);
	src_value	.SetFormat(fmt);
}

void PipeComponent::Uninitialize() {
	StageComponent::Uninitialize();
}

Value& PipeComponent::GetValue() {return sink_value;}
Stream& PipeComponent::GetStream() {return src_stream;}
bool PipeComponent::LoadAsInput(const StageComponentConf& in) {TODO}

void PipeComponent::Forward(FwdScope& fwd) {
	TODO
	#if 0
	using DevSpec				= typename ValDevSpec::Dev;
	using DevMach				= ScopeDevMachT<DevSpec>;
	using InternalPacketData	= typename DevMach::InternalPacketData;
	using StageComponentBase		= typename DevSpec::ComponentBase;
	
	auto& buf = sink_value.GetBuffer();
	if (buf.IsEmpty())
		return;
	
	if (this->ext)
		this->ext->Forward(fwd);
	
	Packet p = buf.First();
	buf.RemoveFirst();
	
	auto p_fmt = p->GetFormat();
	auto src_fmt = src_value.GetFormat();
	if (p_fmt != src_fmt) {DLOG("PipeComponent::Forward: error: packet format differs\nPacket format: " << p_fmt.ToString() << "\nSource format: " << src_fmt.ToString());}
	ASSERT(p_fmt == src_fmt);
	
	StageComponentBase::Process();
	
	InternalPacketData& data = p->template GetData<InternalPacketData>();
	data.pos++;
	data.ClearLinks();
	data.dev_comp = CastPtr<StageComponent>(this);
	ASSERT(data.dev_comp);
	
	
	StageComponent::template ForwardPacket<ValSpec>(fwd, p);
	#endif
}

void PipeComponent::ForwardExchange(FwdScope& fwd) {
	/*using ValSpec				= typename ValDevSpec::Val;
	using DevSpec				= typename ValDevSpec::Dev;
	using DevMach				= ScopeDevMachT<DevSpec>;
	using ValMach				= ScopeValMachT<ValSpec>;
	//using Mach					= ScopeValDevMachT<ValDevSpec>;
	using Core					= ScopeValDevCoreT<ValDevSpec>;
	using Format				= typename ValMach::Format;
	using ValStreamState		= typename ValMach::ValStreamState;
	using DevStreamState		= typename DevMach::DevStreamState;
	using ValSource				= typename Core::ValSource;
	using ValExchangePointRef	= typename Core::ValExchangePointRef;
	//using Ex					= typename Mach::Ex;
	*/
	ValSource& src = *this;
	ValExchangePointRef expt = src.GetExPt();
	ASSERT(expt);
	if (expt) {
		fwd.AddNext(*expt);
	}
}















void SideOutputComponent::Initialize() {
	TODO
}

void SideOutputComponent::Uninitialize() {
	TODO
}

void SideOutputComponent::Forward(FwdScope& fwd) {
	TODO
}

void SideOutputComponent::ForwardExchange(FwdScope& fwd) {
	TODO
}

Value& SideOutputComponent::GetValue() {
	TODO
}

Stream& SideOutputComponent::GetStream() {
	TODO
}








void SideInputComponent::Initialize() {
	TODO
}

void SideInputComponent::Uninitialize() {
	TODO
}

void SideInputComponent::Forward(FwdScope& fwd) {
	TODO
}

void SideInputComponent::ForwardExchange(FwdScope& fwd) {
	TODO
}

Value& SideInputComponent::GetValue() {
	TODO
}

Stream& SideInputComponent::GetStream() {
	TODO
}




#if 0
void DevCustomerComponent::Initialize() {
	
}

void DevCustomerComponent::Uninitialize() {
	
}

template <class ValDevSpec>
	typename ScopeValDevMachT<VD<typename ValDevSpec::Dev,ReceiptSpec>>::Format
		ScopeValDevLibT<ValDevSpec>::
		DevCustomerComponent::GetFormat(R*) {
	TODO
}

template <class ValDevSpec>
	typename ScopeValDevMachT<VD<typename ValDevSpec::Dev,ReceiptSpec>>::Value&
		ScopeValDevLibT<ValDevSpec>::
		DevCustomerComponent::GetValue(R*) {
	TODO
}

template <class ValDevSpec>
	typename ScopeValDevMachT<VD<typename ValDevSpec::Dev,OrderSpec>>::Stream&
		ScopeValDevLibT<ValDevSpec>::
		DevCustomerComponent::GetStream(O*) {
	TODO
}

#endif



NAMESPACE_ECS_END
