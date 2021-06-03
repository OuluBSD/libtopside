#define CLS typename ScopeConvDevLibT<ValSpec,FromDevSpec,ToDevSpec>

NAMESPACE_TOPSIDE_BEGIN


TMPL_CONVDEVLIB(CLS::Format) ConvertComponent::GetFormat(V*) {TODO}
TMPL_CONVDEVLIB(CLS::FromValue&) ConvertComponent::GetValue(V*) {TODO}
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

TMPL_CONVDEVLIB(void) ConvertComponent::Forward() {TODO}

NAMESPACE_TOPSIDE_END
