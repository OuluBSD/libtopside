#define TMPL(x)	template <class DevSpec> x ScopeDevLibT<DevSpec>::


NAMESPACE_TOPSIDE_BEGIN


TMPL() ContextComponent::ContextComponent() {
	
}

TMPL(void) ContextComponent::PostLoadFileAny(String s) {
	TODO
}


NAMESPACE_TOPSIDE_END

#undef TMPL
