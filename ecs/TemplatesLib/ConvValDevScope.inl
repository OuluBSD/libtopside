#if 0
#define CLS typename ScopeConvValDevLibT<ValSpec,FromDevSpec,ToDevSpec>

NAMESPACE_ECS_BEGIN

TMPL_CONVVALDEVLIB(void) ConvertComponent::Initialize() {
	using DevLib				= ScopeDevLibT<ToDevSpec>;
	using StageComponent			= typename DevLib::StageComponent;
	//using StageContextConnector		= typename DevLib::StageContextConnector;
	//using StageContextConnectorRef	= typename DevLib::StageContextConnectorRef;
	
	auto sink_fmt = FDevCore::template GetDefaultFormat<ValSpec>();
	sink_value.SetFormat(sink_fmt);
	
	auto src_fmt = TDevCore::template GetDefaultFormat<ValSpec>();
	src_value.SetFormat(src_fmt);
	
	ToComponent::Initialize();
	
	TODO
	/*ComponentBase* cb = CastPtr<ComponentBase>(this);
	ASSERT(cb);
	StageContextConnectorRef ctx = cb->GetEntity()->template FindNearestPoolWith<StageContextConnector>();
	ASSERT(ctx);
	if (ctx)
		ctx->FindAdd(this->template AsRef<StageComponent>());*/
}

TMPL_CONVVALDEVLIB(void) ConvertComponent::Uninitialize() {
	//FromComponent::Uninitialize();
	ToComponent::Uninitialize();
}

TMPL_CONVVALDEVLIB(CLS::FromValue&) ConvertComponent::GetValue(V*) {return sink_value;}
TMPL_CONVVALDEVLIB(CLS::ToStream&) ConvertComponent::GetStream(V*) {return stream;}
TMPL_CONVVALDEVLIB(bool) ConvertComponent::LoadAsInput(const StageComponentConf& in) {TODO}
TMPL_CONVVALDEVLIB(void) ConvertComponent::PreProcess() {TODO}
TMPL_CONVVALDEVLIB(bool) ConvertComponent::LocalStream::IsOpen() const {TODO}
TMPL_CONVVALDEVLIB(bool) ConvertComponent::LocalStream::Open(int fmt_idx) {TODO}
TMPL_CONVVALDEVLIB(void) ConvertComponent::LocalStream::Close() {TODO}
TMPL_CONVVALDEVLIB(bool) ConvertComponent::LocalStream::IsEof() {TODO}
TMPL_CONVVALDEVLIB(bool) ConvertComponent::LocalStream::ReadFrame() {TODO}
TMPL_CONVVALDEVLIB(bool) ConvertComponent::LocalStream::ProcessFrame() {TODO}
TMPL_CONVVALDEVLIB(bool) ConvertComponent::LocalStream::ProcessOtherFrame() {TODO}
TMPL_CONVVALDEVLIB(void) ConvertComponent::LocalStream::ClearPacketData() {TODO}

TMPL_CONVVALDEVLIB(void) ConvertComponent::Forward(FwdScope& fwd) {
	auto& buf = sink_value.GetBuffer();
	if (buf.IsEmpty())
		return;
	
	if (this->ext)
		this->ext->Forward(fwd);
	
	Packet p = buf.First();
	buf.RemoveFirst();
	
	Format p_fmt = p->GetFormat();
	ASSERT(p_fmt.IsValid());
	
	TypeCls from_spec = AsTypeCls<FromDevSpec>();
	TypeCls to_spec = AsTypeCls<ToDevSpec>();
	TypeCls dev_spec = p_fmt.GetDevSpec();
	ASSERT(dev_spec == from_spec && dev_spec != to_spec);
	
	ToComponent::template ConvertPacket<FromDevSpec, ValSpec>(p);
	
	TODO
	#if 0
	p_fmt = p->GetFormat();
	auto src_fmt = src_value.GetFormat();
	if (p_fmt != src_fmt) {
		//DLOG("ConvertComponent::Forward: error: packet format differs\nPacket format: " << p_fmt.ToString() << "\nSource format: " << src_fmt.ToString());
		Packet new_p = Data::CreatePacket();
		new_p->SetFormat(src_fmt);
		TMach::Convert(p, new_p);
		ASSERT(new_p->GetFormat() == src_fmt);
		ToComponent::template ForwardPacket<ValSpec>(fwd, new_p);
	}
	else {
		ToComponent::template ForwardPacket<ValSpec>(fwd, p);
	}
	#endif
}

TMPL_CONVVALDEVLIB(void) ConvertComponent::ForwardExchange(FwdScope& fwd) {
	using Core					= ScopeValDevCoreT<To>;
	using ValSource				= typename Core::ValSource;
	using ValExchangePointRef	= typename Core::ValExchangePointRef;
	
	ValSource& src = *this;
	ValExchangePointRef expt = src.GetExPt();
	ASSERT(expt);
	if (expt) {
		fwd.AddNext(*expt);
	}
}

NAMESPACE_ECS_END
#endif
