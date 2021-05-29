#define TMPL(x)	template <class Ctx> x ContextAccelT<Ctx>::


NAMESPACE_TOPSIDE_BEGIN


TMPL(typename Ctx::Format) PipeComponent::GetFormat(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Value&) PipeComponent::GetValue(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Stream&) PipeComponent::GetStream(Ctx*) {TODO}
TMPL(void) PipeComponent::BeginStream(Ctx*) {TODO}
TMPL(void) PipeComponent::EndStream(Ctx*) {TODO}
TMPL(bool) PipeComponent::LoadAsInput(const AcceleratorHeader& in) {TODO}
TMPL(void) PipeComponent::UpdateTexBuffers() {
	auto* stream = Stream();
	if (stream) {
		ASSERT(stream->video_size.cx > 0 && stream->video_size.cy > 0);
		ClearTex();
#if HAVE_OPENGL
		Ogl_CreateTex(
			stream->video_size, 4,
			1, 1,
			AcceleratorHeader::FILTER_LINEAR,
			AcceleratorHeader::WRAP_CLAMP);
#endif
	}
}

TMPL(typename Ctx::Format) ConvertInputComponent::GetFormat(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Value&) ConvertInputComponent::GetValue(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Stream&) ConvertInputComponent::GetStream(Ctx*) {TODO}
TMPL(void) ConvertInputComponent::BeginStream(Ctx*) {TODO}
TMPL(void) ConvertInputComponent::EndStream(Ctx*) {TODO}
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
		
		String err_msg;
		if (!that_comp_base->template LinkManually<BaseSource>(*this, &err_msg)) {
			ctx->GetParent()->OnError("ConvertInputComponent::LoadAsInput", "Manual linking failed: " + err_msg);
			return false;
		}
	}
	
	String p = in.GetPath();
	if (p.GetCount()) {
		Stream& stream = comp->GetStream((C*)0);
		if (!stream.LoadFileAny(p)) {
			ctx->GetParent()->OnError("ConvertInputComponent::LoadAsInput", "Stream failed to load '" + p + "'");
			return false;
		}
		return true;
	}
	else {
		ctx->GetParent()->OnError("ConvertInputComponent::LoadAsInput", "Unhandled header configuration");
		return false;
	}
}
TMPL(void) ConvertInputComponent::PreProcess() {
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
TMPL(void) ConvertInputComponent::UpdateTexBuffers() {
	TODO
	#if 0
	auto* stream = Stream();
	if (stream) {
		ClearTex();
		if (data_res.cx > 0 && data_res.cy > 0) {
#if HAVE_OPENGL
			Ogl_CreateTex(
				data_res, 1,
				0, 0,
				AcceleratorHeader::FILTER_NEAREST,
				AcceleratorHeader::WRAP_CLAMP);
#endif
		}
	}
	#endif
}

TMPL(typename Ctx::Format) ConvertOutputComponent::GetFormat(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Value&) ConvertOutputComponent::GetValue(Ctx*) {TODO}
TMPL(typename ContextT<Ctx>::Stream&) ConvertOutputComponent::GetStream(Ctx*) {return stream;}
TMPL(void) ConvertOutputComponent::BeginStream(Ctx*) {stream.FillBuffer();}
TMPL(void) ConvertOutputComponent::EndStream(Ctx*) {stream.DropBuffer();}
TMPL(void) ConvertOutputComponent::UpdateTexBuffers() {
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

TMPL(bool) ConvertOutputComponent::ReadFrame() {
	TODO
}

TMPL(bool) ConvertOutputComponent::ProcessFrame() {
	TODO
}

TMPL(void) ConvertOutputComponent::ClearPacketData() {
	TODO
}


NAMESPACE_TOPSIDE_END

#undef TMPL
