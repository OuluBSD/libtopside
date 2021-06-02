#define CTX				((D*)0)

NAMESPACE_TOPSIDE_BEGIN





TMPL_DEVLIB(String) Component::GetStringFromType(TypeCls i) {
	#define IFACE(x) \
		if (i == AsTypeCls<typename ScopeValDevCoreT<VD<DevSpec, x##Spec>>::ValSource>()) \
			return DevSpec::GetPrefix() + #x "Source"; \
		if (i == AsTypeCls<typename ScopeValDevCoreT<VD<DevSpec, x##Spec>>::ValSink>()) \
			return DevSpec::GetPrefix() + #x "Sink"; \
		if (i == AsTypeCls<typename ScopeValDevLibT<VD<DevSpec, x##Spec>>::PipeComponent>()) \
			return DevSpec::GetPrefix() + #x "PipeComponent";
		//if (i == AsTypeCls<ConvertCenterAccel##x##Component>()) return "ConvertCenterAccel" #x "Component";
	IFACE_LIST
	#undef IFACE
	return "invalid";
}

TMPL_DEVLIB(void) Component::OnError(String fn, String msg) {
	if (ctx && ctx->GetParent()) {
		ctx->GetParent()->OnError(RTTI::GetRTTI().GetTypeId(), fn, msg);
	}
	else {
		LOG(DevSpec::GetName() + "Component::" << fn << ": error: " << msg);
	}
}






TMPL_DEVLIB() ContextComponent::ContextComponent() {
	
}

TMPL_DEVLIB(void) ContextComponent::Initialize() {
	DLOG(DevSpec::GetName() + "ContextComponent::Initialize");
	Ref<System> sys = TS::ComponentBase::GetEntity()->GetMachine().template Get<System>();
	if (sys)
		sys	-> AddCtx(TS::ComponentBase::AsRef<ContextComponent>());
	
}

TMPL_DEVLIB(void) ContextComponent::Uninitialize() {
	DLOG(DevSpec::GetName() + "ContextComponent::Uninitialize");
	Ref<System> sys = TS::ComponentBase::GetEntity()->GetMachine().template Get<System>();
	if (sys)
		sys	-> RemoveCtx(TS::ComponentBase::AsRef<ContextComponent>());
}

TMPL_DEVLIB(void) ContextComponent::PostLoadFileAny(String path) {
	Object content;
	if (LoadFileAny(path, content)) {
		post_load = content;
	}
}

TMPL_DEVLIB(bool) ContextComponent::LoadFileAny(String path, Object& dst) {
	
	// If path is a directory instead of a file, then add default filename and extension
	if (DirectoryExists(path)) {
		for (String ext : GetDefaultExt<DevSpec>()) {
			if (path.Right(1) == DIR_SEPS)
				path = path.Left(path.GetCount()-1);
			String title = GetFileName(path);
			path = AppendFileName(path, title + ext);
			if (LoadFileAny(path, dst))
				return true;
		}
	}
	// Load file
	else {
		String ext = GetFileExt(path);
		
		// Iterate through all file extension loaders
		auto& ext_loaders = GetExtLoaders<DevSpec>();
		auto iter = ext_loaders.begin();
		for (; iter; ++iter)
			if (ext == *iter.key && iter.value()(path, dst, this))
				return true;
	}
	
	return false;
}

TMPL_DEVLIB(void) ContextComponent::Update() {
	TODO
}

TMPL_DEVLIB(void) ContextComponent::CreatePackets() {
	TODO
}














//Callback System::WhenUninit;

TMPL_DEVLIB(bool) System::Initialize() {
	
	
	return true;
}

TMPL_DEVLIB(void) System::Start() {
	
}

TMPL_DEVLIB(void) System::Update(double dt) {
	if (ctxs.IsEmpty() && srcs.IsEmpty() && expts.IsEmpty() && sinks.IsEmpty())
		return;
	
	RTLOG(DevSpec::GetName() + "System: begin");
	USING_DEVLIB(ExchangePointRef)
	USING_DEVLIB(D)
	
	
	for (ContextComponentRef& ctx : ctxs)
		ctx->Update();
	
	for (ContextComponentRef& ctx : ctxs)
		ctx->CreatePackets();
	
	
	
	for (SourceRef src : srcs) {
		CtxStream& stream = src->GetStream(CTX);
		int buf_sz = stream.Get().GetQueueSize();
		bool buffer_full = buf_sz >= 2;
		
		#if 1 && DEBUG_RT_PIPE
		RTLOG("update source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
		#endif
		
		src->Update(dt, buffer_full);
		if (src->Cfg().render) {
			#if DEBUG_RT_PIPE
			RTLOG("begin source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
			#endif
			
			src->BeginStream(CTX);
		}
	}
	
	int dbg_i = 0;
	for (ExchangePointRef expt : expts) {
		off32 begin_offset = expt->GetOffset();
		#if 1 && DEBUG_RT_PIPE
		const RTTI& expt_rtti = expt->GetRTTI();
		RTLOG("expt " << dbg_i << " update " << HexStr((size_t)&expt_rtti.GetRTTI()) << "<" << expt_rtti.GetDynamicName() << "> offset " << IntStr(begin_offset.value));
		#endif
		
		SinkRef sink = expt->Sink();
		SourceRef src = expt->Source();
		#if 0 && DEBUG_RT_PIPE
		RTLOG("expt updpate src " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << "> offset " << IntStr(begin_offset.value));
		#endif
		
		expt->SetOffset(begin_offset);
		expt->Update(dt);
		
		off32 end_offset = expt->GetOffset();
		src->SetOffset(begin_offset, end_offset);
		
		#if DEBUG_RT_PIPE
		off32 diff = off32::GetDifference(begin_offset, end_offset);
		if (diff) {
			RTLOG("sink " << HexStr((size_t)&*sink) << "<" << sink->GetConfigString() << "> consumed " << diff.ToString());
		}
		#endif
		++dbg_i;
	}
	
	for (SourceRef src :srcs) {
		const auto& cfg = src->Cfg();
		if (cfg.begin_offset != cfg.end_offset) {
			#if DEBUG_RT_PIPE
			RTLOG("end source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
			#endif
			
			src->EndStream(CTX);
		}
	}
	
	RTLOG(DevSpec::GetName() + "System: end");
}

TMPL_DEVLIB(void) System::Stop() {
	
	
}

TMPL_DEVLIB(void) System::Uninitialize() {
	srcs.Clear();
	sinks.Clear();
	expts.Clear();
	
	WhenUninit();
}

TMPL_DEVLIB(void) System::Add(SourceRef src) {
	ASSERT(src);
	srcs.FindAdd(src);
}

TMPL_DEVLIB(void) System::Remove(SourceRef src) {
	srcs.RemoveKey(src);
}

TMPL_DEVLIB(void) System::Add(SinkRef sink) {
	ASSERT(sink);
	sinks.FindAdd(sink);
}

TMPL_DEVLIB(void) System::Remove(SinkRef sink) {
	sinks.RemoveKey(sink);
}

TMPL_DEVLIB(void) System::Add(ExchangePointRef expt) {
	ASSERT(expt);
	expts.FindAdd(expt);
}

TMPL_DEVLIB(void) System::Remove(ExchangePointRef expt) {
	expts.RemoveKey(expt);
}

TMPL_DEVLIB(void) System::AddCtx(ContextComponentRef ctx) {
	ASSERT(ctx);
	ctxs.FindAdd(ctx);
}

TMPL_DEVLIB(void) System::RemoveCtx(ContextComponentRef ctx) {
	ctxs.RemoveKey(ctx);
}

NAMESPACE_TOPSIDE_END

#undef CTX
