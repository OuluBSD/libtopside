#define TMPL(x)	template <class DevCtx> x ContextDevLibT<DevCtx>::


NAMESPACE_TOPSIDE_BEGIN


TMPL() ContextComponent::ContextComponent() {
	
}

TMPL(void) ContextComponent::PostLoadFileAny(String s) {
	TODO
}


NAMESPACE_TOPSIDE_END

#undef TMPL
