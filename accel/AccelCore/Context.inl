#define TMPL(x)	template <class Ctx> x ContextAccelT<Ctx>::


NAMESPACE_TOPSIDE_BEGIN


TMPL(typename Ctx::Format) PipeComponent::GetFormat(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Value&) PipeComponent::GetValue(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Stream&) PipeComponent::GetStream(Ctx*) {TODO}
TMPL(void) PipeComponent::BeginStream(Ctx*) {TODO}
TMPL(void) PipeComponent::EndStream(Ctx*) {TODO}
TMPL(void) PipeComponent::Update(double dt) {TODO}
TMPL(bool) PipeComponent::LoadResources() {TODO}
TMPL(void) PipeComponent::Reset() {TODO}
TMPL(bool) PipeComponent::LoadAsInput(const AcceleratorHeader& in) {TODO}

TMPL(typename Ctx::Format) ConvertInputComponent::GetFormat(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Value&) ConvertInputComponent::GetValue(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Stream&) ConvertInputComponent::GetStream(Ctx*) {TODO}
TMPL(void) ConvertInputComponent::BeginStream(Ctx*) {TODO}
TMPL(void) ConvertInputComponent::EndStream(Ctx*) {TODO}
TMPL(void) ConvertInputComponent::Update(double dt) {TODO}
TMPL(bool) ConvertInputComponent::LoadResources() {TODO}
TMPL(void) ConvertInputComponent::Reset() {TODO}
TMPL(bool) ConvertInputComponent::LoadAsInput(const AcceleratorHeader& in) {
	const auto& conns = AccelSink::GetConnections();
	
	using InputComponent = typename ContextLibT<Ctx>::InputComponent;
	using Stream = typename ContextT<Ctx>::Stream;
	
	RefT_Entity<InputComponent> comp;
	
	if (!conns.IsEmpty()) {
		for (auto& conn : conns)
			if ((comp = CastRef<InterfaceBase>(conn).AsComponentBase()->template AsRef<InputComponent>()))
				break;
	}
	
	if (!comp) {
		ComponentBaseRef this_comp_base = AsRef<ComponentBase>();
		
		EntityRef e = this_comp_base->GetEntity();
		comp = e->Add<InputComponent>();
		
		ComponentBaseRef that_comp_base = comp->template AsRef<ComponentBase>();
		ASSERT(this_comp_base && that_comp_base);
		
		if (!that_comp_base->template LinkManually<AccelSource>(*this))
			return false;
	}
	
	String p = in.GetPath();
	if (p.GetCount()) {
		Stream& stream = comp->GetStream((C*)0);
		return stream.LoadFileAny(p);
	}
	else {
		LOG("ConvertInputComponent::LoadAsInput: internal error: unhandled header");
		return false;
	}
}

TMPL(typename Ctx::Format) ConvertOutputComponent::GetFormat(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Value&) ConvertOutputComponent::GetValue(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Stream&) ConvertOutputComponent::GetStream(Ctx*) {TODO}
TMPL(void) ConvertOutputComponent::BeginStream(Ctx*) {TODO}
TMPL(void) ConvertOutputComponent::EndStream(Ctx*) {TODO}
TMPL(void) ConvertOutputComponent::Update(double dt) {TODO}
TMPL(bool) ConvertOutputComponent::LoadResources() {TODO}
TMPL(void) ConvertOutputComponent::Reset() {TODO}
TMPL(bool) ConvertOutputComponent::LoadAsInput(const AcceleratorHeader& in) {TODO}


NAMESPACE_TOPSIDE_END

#undef TMPL
