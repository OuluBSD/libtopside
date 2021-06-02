#define CTX				((D*)0)

NAMESPACE_TOPSIDE_BEGIN





TMPL_DEVLIB(String) DevComponent::GetStringFromType(TypeCls i) {
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

TMPL_DEVLIB(void) DevComponent::OnError(String fn, String msg) {
	if (ctx && ctx->GetParent()) {
		ctx->GetParent()->OnError(RTTI::GetRTTI().GetTypeId(), fn, msg);
	}
	else {
		LOG(DevSpec::GetName() + "Component::" << fn << ": error: " << msg);
	}
}





TMPL_DEVLIB(bool) DevComponentGroup::Open() {TODO}
TMPL_DEVLIB(void) DevComponentGroup::CloseTemporary() {TODO}
TMPL_DEVLIB(void) DevComponentGroup::Clear() {TODO}
TMPL_DEVLIB(void) DevComponentGroup::FindComponents() {TODO}
		
		
		
TMPL_DEVLIB() ContextComponent::ContextComponent() {
	
}

TMPL_DEVLIB(void) ContextComponent::Initialize() {
	DLOG(DevSpec::GetName() + "ContextComponent::Initialize");
	Ref<DevSystem> sys = TS::ComponentBase::GetEntity()->GetMachine().template Get<DevSystem>();
	if (sys)
		sys	-> AddCtx(TS::ComponentBase::AsRef<ContextComponent>());
	
}

TMPL_DEVLIB(void) ContextComponent::Uninitialize() {
	DLOG(DevSpec::GetName() + "ContextComponent::Uninitialize");
	Ref<DevSystem> sys = TS::ComponentBase::GetEntity()->GetMachine().template Get<DevSystem>();
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
	DLOG("ContextComponent::Update: begin");
	
	//lock.Enter();
	
	if (!post_load.IsVoid()) {
		DLOG("ContextComponent::Update: load new program");
		
		Object to_load;
		Swap(post_load, to_load);
		
		for(DevComponentGroup& g : groups)
			g.CloseTemporary();
		
		Clear();
		FindComponents();
		DumpEntityComponents();
		
		if (!Load(to_load))
			return;
		Reset();
		
		//  Reload stage pointers
		if (!RefreshStageQueue())
			return;
		DumpEntityComponents();
		
		#if HAVE_OPENGL
		ASSERT_(IsOpenGLContextOpen(), "OpenGL is not started. Probably SDL2 (or similar) system is not added to the ECS.");
		#endif
		
		is_open = true;
		for(DevComponentGroup& g : groups)
			if (!g.Open())
				{is_open = false; break;}
		
		if (!is_open) {
			DLOG("ContextComponent::Update: error: did not open properly");
			return;
		}
		
		stream.vid.fmt.Set(LightSampleFD::FLT_LE_ABCD, Size(640,480));
		stream.vid.fmt.SetFPS(60);
		stream.aud.fmt.Set(SoundSample::S16_LE, 2, 44100, 1024);
		RefreshStreamValuesAll();
		
		RefreshPipeline();
	}
	
	//lock.Leave();
	
	DLOG("ContextComponent::Update: end");
}

TMPL_DEVLIB(void) ContextComponent::CreatePackets() {
	TODO
}

TMPL_DEVLIB(void) ContextComponent::Clear() {
	for(auto& gr : groups)
		gr.Clear();
	
	stream.Clear();
	common_source.Clear();
	groups.Clear();
	last_error.Clear();
	post_load = Null;
	is_open = false;
	
}

TMPL_DEVLIB(void) ContextComponent::Reset() {
	stream.Reset();
}

TMPL_DEVLIB(void) ContextComponent::FindComponents() {
	for(DevComponentGroup& g : groups)
		g.FindComponents();
}

TMPL_DEVLIB(void) ContextComponent::DumpEntityComponents() {
	LOG(DevSpec::GetName() + "ContextComponent:");
	EntityRef e = TS::ComponentBase::GetEntity();
	int i = 0;
	for (ComponentRef& comp : e->GetComponents().GetValues()) {
		if (comp) {
			auto& base = *comp;
			DevComponent* fcomp = CastPtr<DevComponent>(&base);
			if (fcomp) {
				LOG("\t" << i++ << ": " << DevSpec::GetName() << "Component: " << fcomp->ToString());
			}
			else {
				LOG("\t" << i++ << ": " << base.GetDynamicName());
			}
		}
	}
}
TMPL_DEVLIB(bool) ContextComponent::Load(Object& o) {TODO}
TMPL_DEVLIB(bool) ContextComponent::RefreshStageQueue() {TODO}
TMPL_DEVLIB(void) ContextComponent::RefreshStreamValuesAll() {TODO}
TMPL_DEVLIB(void) ContextComponent::RefreshPipeline() {TODO}












//Callback DevSystem::WhenUninit;

TMPL_DEVLIB(bool) DevSystem::Initialize() {
	
	
	return true;
}

TMPL_DEVLIB(void) DevSystem::Start() {
	
}

TMPL_DEVLIB(void) DevSystem::Update(double dt) {
	if (ctxs.IsEmpty())
		return;
	
	RTLOG(DevSpec::GetName() + "DevSystem::Update: begin");
	
	
	for (ContextComponentRef& ctx : ctxs)
		ctx->Update();
	
	for (ContextComponentRef& ctx : ctxs)
		ctx->CreatePackets();
	
	
	RTLOG(DevSpec::GetName() + "DevSystem::Update: end");
}

TMPL_DEVLIB(void) DevSystem::Stop() {
	
	
}

TMPL_DEVLIB(void) DevSystem::Uninitialize() {
	ctxs.Clear();
	
	WhenUninit();
}

TMPL_DEVLIB(void) DevSystem::AddCtx(ContextComponentRef ctx) {
	ASSERT(ctx);
	ctxs.FindAdd(ctx);
}

TMPL_DEVLIB(void) DevSystem::RemoveCtx(ContextComponentRef ctx) {
	ctxs.RemoveKey(ctx);
}

NAMESPACE_TOPSIDE_END

#undef CTX
