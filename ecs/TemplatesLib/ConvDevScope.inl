#define CLS typename ScopeConvDevLibT<ValSpec,FromDevSpec,ToDevSpec>

NAMESPACE_TOPSIDE_BEGIN

TMPL_CONVDEVLIB(void) ConvertComponent::Initialize() {
	using DevLib				= ScopeDevLibT<ToDevSpec>;
	using DevComponent			= typename DevLib::DevComponent;
	using ContextComponent		= typename DevLib::ContextComponent;
	using ContextComponentRef	= typename DevLib::ContextComponentRef;
	
	ToComponent::Initialize();
	
	ComponentBase* cb = CastPtr<ComponentBase>(this);
	ASSERT(cb);
	ContextComponentRef ctx = cb->GetEntity()->template FindNearestWith<ContextComponent>();
	ASSERT(ctx);
	if (ctx)
		ctx->FindAdd(this->template AsRef<DevComponent>());
}

TMPL_CONVDEVLIB(void) ConvertComponent::Uninitialize() {
	//FromComponent::Uninitialize();
	ToComponent::Uninitialize();
}

TMPL_CONVDEVLIB(CLS::Format) ConvertComponent::GetFormat(V*) {TODO}
TMPL_CONVDEVLIB(CLS::FromValue&) ConvertComponent::GetValue(V*) {return sink_value;}
TMPL_CONVDEVLIB(CLS::ToStream&) ConvertComponent::GetStream(V*) {return stream;}
TMPL_CONVDEVLIB(void) ConvertComponent::BeginStream(V*) {TODO}
TMPL_CONVDEVLIB(void) ConvertComponent::EndStream(V*) {TODO}
TMPL_CONVDEVLIB(bool) ConvertComponent::LoadAsInput(const ToComponentConf& in) {TODO}
TMPL_CONVDEVLIB(void) ConvertComponent::PreProcess() {TODO}
TMPL_CONVDEVLIB(bool) ConvertComponent::LocalStream::IsOpen() const {TODO}
TMPL_CONVDEVLIB(bool) ConvertComponent::LocalStream::Open(int fmt_idx) {TODO}
TMPL_CONVDEVLIB(void) ConvertComponent::LocalStream::Close() {TODO}
TMPL_CONVDEVLIB(bool) ConvertComponent::LocalStream::IsEof() {TODO}
TMPL_CONVDEVLIB(bool) ConvertComponent::LocalStream::ReadFrame() {TODO}
TMPL_CONVDEVLIB(bool) ConvertComponent::LocalStream::ProcessFrame() {TODO}
TMPL_CONVDEVLIB(bool) ConvertComponent::LocalStream::ProcessOtherFrame() {TODO}
TMPL_CONVDEVLIB(void) ConvertComponent::LocalStream::ClearPacketData() {TODO}

TMPL_CONVDEVLIB(void) ConvertComponent::Forward(FwdScope& fwd) {
	auto& buf = sink_value.GetBuffer();
	if (buf.IsEmpty())
		return;
	
	Packet p = buf.First();
	buf.RemoveFirst();
	
	Format fmt = p->GetFormat();
	if (fmt.IsDeviceInternal()) {
		TypeCls from_spec = AsTypeCls<FromDevSpec>();
		TypeCls to_spec = AsTypeCls<ToDevSpec>();
		TypeCls dev_spec = fmt.GetDevSpec();
		ASSERT(dev_spec == from_spec && dev_spec != to_spec);
		
		ToComponent::template ConvertPacket<FromDevSpec, ValSpec>(p);
	}
	
	ToComponent::template ForwardPacket<ValSpec>(fwd, p);
}

TMPL_CONVDEVLIB(void) ConvertComponent::ForwardExchange(FwdScope& fwd) {
	using Core					= ScopeValDevCoreT<To>;
	using ValSource				= typename Core::ValSource;
	using ValExchangePointRef	= typename Core::ValExchangePointRef;
	
	ValSource& src = *this;
	auto& conns = src.GetConnections();
	for(auto& link : conns) {
		ValExchangePointRef expt = link.expt;
		ASSERT(expt);
		if (expt) {
			fwd.AddNext(*expt);
		}
	}
}

NAMESPACE_TOPSIDE_END
