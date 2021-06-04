NAMESPACE_TOPSIDE_BEGIN

#define CLS typename ScopeValDevLibT<ValDevSpec>


TMPL_VALDEVMACH(void) ValExchangePoint::ForwardSetup(FwdScope& fwd) {
	USING_VALDEVMACH(ValSpec)
	using ValSpec				= typename ValDevSpec::Val;
	using DevSpec				= typename ValDevSpec::Dev;
	using ValMach				= ScopeValMachT<ValSpec>;
	using Mach					= ScopeValDevMachT<ValDevSpec>;
	using DevMach				= ScopeDevMachT<DevSpec>;
	using DevLib				= ScopeDevLibT<DevSpec>;
	using Core					= ScopeValDevCoreT<ValDevSpec>;
	using ValStreamState		= typename ValMach::ValStreamState;
	using DevStreamState		= typename DevMach::DevStreamState;
	using DevComponent			= typename DevLib::DevComponent;
	using Value					= typename Mach::Value;
	using SourceRef				= typename Core::ValSourceRef;
	using SinkRef				= typename Core::ValSinkRef;
	ASSERT(!dbg_offset_is_set);
	
	SourceRef src = this->src;
	ASSERT(src);
	DevComponent* src_comp = CastPtr<DevComponent>(src->AsComponentBase());
	ASSERT(src_comp);
	DevStreamState& state = src_comp->GetStreamState();
	ValStreamState& vstate = state.template Get<ValSpec>();
	off32 exp_offset = vstate.offset;
	SetOffset(exp_offset);
	
	SinkRef sink = this->sink;
	DevComponent* sink_comp = CastPtr<DevComponent>(sink->AsComponentBase());
	Value& to_val = sink->GetValue((ValSpec*)0);
	Format to_fmt = to_val.GetFormat();
	if (!to_fmt.IsValid()) {
		to_fmt = sink_comp->template GetDefaultFormat<ValSpec>();
		SimpleBufferedValue* sbuf;
		if ((sbuf = CastPtr<SimpleBufferedValue>(&to_val))) {
			sbuf->SetFormat(to_fmt);
			ASSERT(to_val.GetFormat().IsValid());
		}
		else {
			TODO
		}
	}
}




TMPL_VALDEVLIB(CLS::CtxStream&) InputComponent::GetStream(V*) {
	return stream;
}

TMPL_VALDEVLIB(void) InputComponent::BeginStream(V*) {
	stream.FillBuffer();
}

TMPL_VALDEVLIB(void) InputComponent::EndStream(V*) {
	stream.DropBuffer();
}

TMPL_VALDEVLIB(bool) InputComponent::ReadFrame() {
	TODO
}

TMPL_VALDEVLIB(bool) InputComponent::ProcessDeviceFrame() {
	TODO
}

TMPL_VALDEVLIB(bool) InputComponent::LocalStream::IsOpen() const {
	TODO
}

TMPL_VALDEVLIB(bool) InputComponent::LocalStream::Open(int fmt_idx) {
	TODO
}

TMPL_VALDEVLIB(bool) InputComponent::LocalStream::LoadFileAny(String path) {
	TODO
}


TMPL_VALDEVLIB(void) PipeComponent::Initialize() {
	DevComponent::Initialize();
	sink_value	.SetFormat(DevComponent::template GetDefaultFormat<ValSpec>());
	src_value	.SetFormat(DevComponent::template GetDefaultFormat<ValSpec>());
}
TMPL_VALDEVLIB(void) PipeComponent::Uninitialize() {
	DevComponent::Uninitialize();
}

TMPL_VALDEVLIB(CLS::Format) PipeComponent::GetFormat(V*) {TODO}
TMPL_VALDEVLIB(CLS::Value&) PipeComponent::GetValue(V*) {return sink_value;}
TMPL_VALDEVLIB(CLS::CtxStream&) PipeComponent::GetStream(V*) {return stream;}
TMPL_VALDEVLIB(void) PipeComponent::BeginStream(V*) {TODO}
TMPL_VALDEVLIB(void) PipeComponent::EndStream(V*) {TODO}
TMPL_VALDEVLIB(bool) PipeComponent::LoadAsInput(const DevCompConf& in) {TODO}

TMPL_VALDEVLIB(void) PipeComponent::Forward(FwdScope& fwd) {
	using DevSpec				= typename ValDevSpec::Dev;
	using DevMach				= ScopeDevMachT<DevSpec>;
	using InternalPacketData	= typename DevMach::InternalPacketData;
	using DevComponentBase		= typename DevSpec::ComponentBase;
	
	auto& buf = sink_value.GetBuffer();
	if (buf.IsEmpty())
		return;
	
	Packet p = buf.First();
	buf.RemoveFirst();
	
	auto p_fmt = p->GetFormat();
	auto src_fmt = src_value.GetFormat();
	ASSERT(p_fmt == src_fmt);
	
	DevComponentBase::Process();
	
	InternalPacketData& data = p->template GetData<InternalPacketData>();
	data.pos++;
	data.ClearLinks();
	data.dev_comp = CastPtr<DevComponent>(this);
	ASSERT(data.dev_comp);
	
	
	DevComponent::template ForwardPacket<ValSpec>(fwd, p);
}

TMPL_VALDEVLIB(void) PipeComponent::ForwardExchange(FwdScope& fwd) {
	using ValSpec				= typename ValDevSpec::Val;
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
	
	#if 1
	ValSource& src = *this;
	auto& conns = src.GetConnections();
	for(auto& link : conns) {
		ValExchangePointRef expt = link.expt;
		ASSERT(expt);
		if (expt) {
			fwd.AddNext(*expt);
		}
	}
	#else
	DevStreamState& state = DevComponent::GetStreamState();
	ValStreamState& vstate = state.template Get<ValSpec>();
	off32 exp_offset = vstate.offset;
	
	ValSource& src = *this;
	auto& conns = src.GetConnections();
	for(auto& link : conns) {
		ValExchangePointRef expt = link.expt;
		ASSERT(expt);
		if (expt) {
			expt->SetOffset(vstate.offset);
			fwd.AddNext(*expt);
		}
	}
	#endif
}

#undef CLS

NAMESPACE_TOPSIDE_END
