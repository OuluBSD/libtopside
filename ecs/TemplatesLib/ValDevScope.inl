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
	using StageComponent		= typename DevLib::StageComponent;
	using Value					= typename Mach::Value;
	using SourceRef				= typename Core::ValSourceRef;
	using SinkRef				= typename Core::ValSinkRef;
	using DevContextConnectorBaseRef	= typename DevMach::DevContextConnectorBaseRef;
	using DevContextConnectorRef		= typename DevLib::DevContextConnectorRef;
	
	//ASSERT(!dbg_offset_is_set);
	if (!dbg_offset_is_set) {
		SourceRef src = this->src;
		ASSERT(src);
		DevComponent* dev_comp;
		StageComponent* stage_comp;
		DevStreamState* state;
		if ((dev_comp = CastPtr<DevComponent>(src->AsComponentBase()))) {
			DevContextConnectorBaseRef cb = dev_comp->GetContext();
			DevContextConnectorRef c = cb;
			state = &c->GetStreamState();
		}
		else if ((stage_comp = CastPtr<StageComponent>(src->AsComponentBase()))) {
			state = &stage_comp->GetStreamState();
		}
		else {TODO}
		
		ValStreamState& vstate = state->template Get<ValSpec>();
		off32 exp_offset = vstate.offset;
		SetOffset(exp_offset);
	}
	
	SinkRef sink = this->sink;
	StageComponent* sink_comp = CastPtr<StageComponent>(sink->AsComponentBase());
	Value& to_val = sink->GetValue((ValSpec*)0);
	Format to_fmt = to_val.GetFormat();
	if (!to_fmt.IsValid()) {
		to_fmt = StageComponent::template GetDefaultFormat<ValSpec>();
		SimpleBufferedValue* sbuf;
		VolatileBuffer* vbuf;
		if ((sbuf = CastPtr<SimpleBufferedValue>(&to_val))) {
			sbuf->SetFormat(to_fmt);
		}
		else if ((vbuf = CastPtr<VolatileBuffer>(&to_val))) {
			vbuf->SetFormat(to_fmt);
		}
		else {
			LOG("Unexpected value type: " << to_val.GetDynamicName());
			TODO
		}
		ASSERT(to_val.GetFormat().IsValid());
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
	StageComponent::Initialize();
	auto fmt = StageComponent::template GetDefaultFormat<ValSpec>();
	sink_value	.SetFormat(fmt);
	src_value	.SetFormat(fmt);
}
TMPL_VALDEVLIB(void) PipeComponent::Uninitialize() {
	StageComponent::Uninitialize();
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
	using StageComponentBase		= typename DevSpec::ComponentBase;
	
	auto& buf = sink_value.GetBuffer();
	if (buf.IsEmpty())
		return;
	
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
	DevStreamState& state = StageComponent::GetStreamState();
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
