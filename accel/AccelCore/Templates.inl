#define TMPL(x)	template <class Ctx> x ContextAccelT<Ctx>::


NAMESPACE_TOPSIDE_BEGIN


TMPL(typename Ctx::Format) PipeComponent::GetFormat(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Value&) PipeComponent::GetValue(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Stream&) PipeComponent::GetStream(Ctx*) {TODO}
TMPL(void) PipeComponent::BeginStream(Ctx*) {TODO}
TMPL(void) PipeComponent::EndStream(Ctx*) {TODO}

TMPL(typename Ctx::Format) ConvertInputComponent::GetFormat(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Value&) ConvertInputComponent::GetValue(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Stream&) ConvertInputComponent::GetStream(Ctx*) {TODO}
TMPL(void) ConvertInputComponent::BeginStream(Ctx*) {TODO}
TMPL(void) ConvertInputComponent::EndStream(Ctx*) {TODO}

TMPL(typename Ctx::Format) ConvertOutputComponent::GetFormat(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Value&) ConvertOutputComponent::GetValue(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Stream&) ConvertOutputComponent::GetStream(Ctx*) {TODO}
TMPL(void) ConvertOutputComponent::BeginStream(Ctx*) {TODO}
TMPL(void) ConvertOutputComponent::EndStream(Ctx*) {TODO}


NAMESPACE_TOPSIDE_END
