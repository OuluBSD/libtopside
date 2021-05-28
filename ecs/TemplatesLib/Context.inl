#define TMPL(x)	template <class Ctx> x ContextLibT<Ctx>::
	
	
NAMESPACE_TOPSIDE_BEGIN


TMPL(typename ContextT<Ctx>::Stream&) InputComponent::GetStream(Ctx*) {
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


NAMESPACE_TOPSIDE_END

#undef TMPL
