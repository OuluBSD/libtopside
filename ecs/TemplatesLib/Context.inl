#define TMPL(x)	template <class Ctx> x ContextLibT<Ctx>::
	
	
NAMESPACE_TOPSIDE_BEGIN




TMPL(typename ContextT<Ctx>::Stream&) InputComponent::GetStream(Ctx*) {TODO}
TMPL(void) InputComponent::BeginStream(Ctx*) {TODO}
TMPL(void) InputComponent::EndStream(Ctx*) {TODO}


NAMESPACE_TOPSIDE_END

#undef TMPL
