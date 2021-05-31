#define TMPL(x)			template <class Dev> x ContextAccelT<Dev>::
#define CONV_TMPL(x)	template <class From, class To> x ContextConvT<From,To>::


NAMESPACE_TOPSIDE_BEGIN

#define CLS ContextAccelT<Dev>

TMPL(typename CLS::Format) PipeComponent::GetFormat(Ctx*) {TODO}
TMPL(typename CLS::Value&) PipeComponent::GetValue(Ctx*) {TODO}
TMPL(typename CLS::CtxStream&) PipeComponent::GetStream(typename Dev::Value*) {return stream;}
TMPL(void) PipeComponent::BeginStream(typename Dev::Value*) {TODO}
TMPL(void) PipeComponent::EndStream(typename Dev::Value*) {TODO}
TMPL(bool) PipeComponent::LoadAsInput(const AcceleratorHeader& in) {TODO}
TMPL(void) PipeComponent::UpdateTexBuffers() {
	auto* stream = Stream();
	if (stream) {
		ASSERT(stream->vid.fmt.size.cx > 0 && stream->vid.fmt.size.cy > 0);
		ClearTex();
#if HAVE_OPENGL
		Ogl_CreateTex(
			stream->vid.fmt.size, 4,
			1, 1,
			AcceleratorHeader::FILTER_LINEAR,
			AcceleratorHeader::WRAP_CLAMP);
#endif
	}
}

TMPL(bool) PipeComponent::LocalStream::IsOpen() const {TODO}
TMPL(bool) PipeComponent::LocalStream::Open(int fmt_idx) {TODO}
TMPL(void) PipeComponent::LocalStream::Close() {TODO}
TMPL(bool) PipeComponent::LocalStream::IsEof() {TODO}
TMPL(bool) PipeComponent::LocalStream::ReadFrame() {TODO}
TMPL(bool) PipeComponent::LocalStream::ProcessFrame() {TODO}
TMPL(bool) PipeComponent::LocalStream::ProcessOtherFrame() {TODO}
TMPL(void) PipeComponent::LocalStream::ClearPacketData() {TODO}

/*TMPL(void) PipeComponent::LocalSourceValue::Exchange(Ex& e) {TODO}
TMPL(int) PipeComponent::LocalSourceValue::GetQueueSize() const {TODO}
TMPL(typename CLS::Format) PipeComponent::LocalSourceValue::GetFormat() const {TODO}
TMPL(bool) PipeComponent::LocalSourceValue::IsQueueFull() const {TODO}*/

#undef CLS



#define CLS ContextConvT<From,To>

CONV_TMPL(typename CLS::FromFormat) ConvertComponent::GetFormat(F*) {TODO}
CONV_TMPL(typename CLS::FromValue&) ConvertComponent::GetValue(F*) {TODO}
CONV_TMPL(typename CLS::ToStream&) ConvertComponent::GetStream(T*) {TODO}
CONV_TMPL(void) ConvertComponent::BeginStream(T*) {TODO}
CONV_TMPL(void) ConvertComponent::EndStream(T*) {TODO}
CONV_TMPL(bool) ConvertComponent::LoadAsInput(const AcceleratorHeader& in) {
	const auto& conns = FromSink::GetConnections();
	
	using InputComponent = typename ContextLibT<From>::InputComponent;
	using Stream = typename ContextMachT<From>::Stream;
	
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
		
		String err_msg;
		if (!that_comp_base->template LinkManually<FromSource>(*this, &err_msg)) {
			ctx->GetParent()->OnError("ConvertComponent::LoadAsInput", "Manual linking failed: " + err_msg);
			return false;
		}
	}
	
	String p = in.GetPath();
	if (p.GetCount()) {
		Stream& stream = comp->GetStream((F*)0);
		if (!stream.LoadFileAny(p)) {
			ctx->GetParent()->OnError("ConvertComponent::LoadAsInput", "Stream failed to load '" + p + "'");
			return false;
		}
		return true;
	}
	else {
		ctx->GetParent()->OnError("ConvertComponent::LoadAsInput", "Unhandled header configuration");
		return false;
	}
}
CONV_TMPL(void) ConvertComponent::PreProcess() {
	TODO
	#if 0
	if (changed && data.GetCount() && color_buf[0] > 0) {
		changed = false;
		ASSERT(data.GetCount() == data_res.cx * data_res.cy);
#if HAVE_OPENGL
		Ogl_UpdateTex(data_res, data.Begin());
#endif
	}
	#endif
}
CONV_TMPL(void) ConvertComponent::UpdateTexBuffers() {
	TODO
	#if 0
	if (AsTypeCls<ToCtx>() == AsTypeCls<AudioContext>()) {
		auto* stream = Stream();
		if (stream) {
			ClearTex();
	#if HAVE_OPENGL
			int sr = stream->aud_fmt.sample_rate;
			int ch = stream->aud_fmt.channels;
			ASSERT(sr > 0);
			ASSERT(ch > 0);
			ASSERT(stream->aud_fmt.template IsSampleType<float>());
			Ogl_CreateTex(
				Size(sr, 1), ch,
				0, 0,
				AcceleratorHeader::FILTER_LINEAR,
				AcceleratorHeader::WRAP_CLAMP);
	#endif
		}
	}
	else {
		auto* stream = Stream();
		if (stream) {
			ClearTex();
			if (stream->data_res.cx > 0 && stream->data_res.cy > 0) {
	#if HAVE_OPENGL
				Ogl_CreateTex(
					stream->data_res, 1,
					0, 0,
					AcceleratorHeader::FILTER_NEAREST,
					AcceleratorHeader::WRAP_CLAMP);
	#endif
			}
		}
	}
	#endif
}





#if 0

CONV_TMPL(typename CLS::ToFormat) ConvertOutputComponent::GetFormat(T*) {TODO}
CONV_TMPL(typename CLS::ToValue&) ConvertOutputComponent::GetValue(T*) {TODO}
CONV_TMPL(typename CLS::FromStream&) ConvertOutputComponent::GetStream(F*) {return stream;}
CONV_TMPL(void) ConvertOutputComponent::BeginStream(F*) {stream.FillBuffer();}
CONV_TMPL(void) ConvertOutputComponent::EndStream(F*) {stream.DropBuffer();}
CONV_TMPL(void) ConvertOutputComponent::UpdateTexBuffers() {
}

CONV_TMPL(bool) ConvertOutputComponent::ReadFrame() {
	TODO
}

CONV_TMPL(bool) ConvertOutputComponent::ProcessFrame() {
	TODO
}

CONV_TMPL(void) ConvertOutputComponent::ClearPacketData() {
	TODO
}

#endif

#undef CLS


NAMESPACE_TOPSIDE_END

#undef TMPL
