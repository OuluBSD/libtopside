#define TMPL(x)	template <class ValDevSpec> x ScopeValDevLibT<ValDevSpec>::


NAMESPACE_TOPSIDE_BEGIN

#define CLS ScopeValDevLibT<ValDevSpec>

TMPL(typename CLS::CtxStream&) InputComponent::GetStream(C*) {
	return stream;
}

TMPL(void) InputComponent::BeginStream(C*) {
	stream.FillBuffer();
}

TMPL(void) InputComponent::EndStream(C*) {
	stream.DropBuffer();
}

TMPL(bool) InputComponent::ReadFrame() {
	TODO
}

TMPL(bool) InputComponent::ProcessDeviceFrame() {
	TODO
}

TMPL(bool) InputComponent::LocalStream::IsOpen() const {
	TODO
}

TMPL(bool) InputComponent::LocalStream::Open(int fmt_idx) {
	TODO
}

TMPL(bool) InputComponent::LocalStream::LoadFileAny(String path) {
	TODO
}

#undef CLS

NAMESPACE_TOPSIDE_END

#undef TMPL
