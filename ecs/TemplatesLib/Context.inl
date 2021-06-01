#define TMPL(x)	template <class Dev> x ContextLibT<Dev>::


NAMESPACE_TOPSIDE_BEGIN

#define CLS ContextLibT<Dev>

TMPL(typename CLS::CtxStream&) InputComponent::GetStream(Ctx*) {
	return stream;
}

TMPL(void) InputComponent::BeginStream(Ctx*) {
	stream.FillBuffer();
}

TMPL(void) InputComponent::EndStream(Ctx*) {
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
