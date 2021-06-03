#define CTX				((D*)0)
#define CLS				typename ScopeDevLibT<DevSpec>

NAMESPACE_TOPSIDE_BEGIN


TMPL_DEVLIB(int) DevComponentConfVector::Find(const DevComponentConf& a) const {
	int i = 0;
	for (DevComponentConf& b : in) {
		if (a.IsEqualHeader(b))
			return i;
		++i;
	}
	return -1;
}

TMPL_DEVLIB(void) DevComponentConfVector::Add(const DevComponentConf& a) {
	ASSERT(Find(a) < 0);
	in.Add(a);
}






TMPL_DEVLIB(void) DevComponent::Initialize() {
	DLOG(DevSpec::GetName() + "Component(" << GetTypeString() << ")::Initialize");
	Ref<DevComponent> ref = DevComponentBase::template AsRef<DevComponent>();
	
	Ref<DevSystem> sys = CastRef<ComponentBase>(this).GetEntity()->GetMachine().template Get<DevSystem>();
	if (sys)
		sys	-> Add(ref);
}
TMPL_DEVLIB(void) DevComponent::Uninitialize() {
	DLOG(DevSpec::GetName() + "Component(" << GetTypeString() << ")::Uninitialize");
	Ref<DevComponent> ref = DevComponentBase::template AsRef<DevComponent>();
	
	if (group) {
		group->Remove(ref);
		group.Clear();
	}
	
	Ref<DevSystem> sys = CastRef<ComponentBase>(this).GetEntity()->GetMachine().template Get<DevSystem>();
	if (sys)
		sys	-> Remove(ref);
	
	//Clear();
}

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
	if (group && group->GetParent()) {
		group->GetParent()->OnError(String(RTTI::GetRTTI().GetDynamicName()) + "::" + fn, msg);
	}
	else {
		LOG(DevSpec::GetName() + "Component::" << fn << ": error: " << msg);
	}
}

TMPL_DEVLIB(CLS::DevStreamState&) DevComponent::GetStreamState() {return group->GetStreamState();}

TMPL_DEVLIB(void) DevComponent::Clear() {
	id = -1;
	in.Clear();
	DevComponentBase::Clear();
}

TMPL_DEVLIB(bool) DevComponent::IsDevPipeComponent(TypeCls type) {
	#define IFACE(x) \
	if (type == AsTypeCls<typename ScopeValDevLibT<VD<DevSpec, x##Spec>>::PipeComponent>()) \
		return true;
	IFACE_LIST
	#undef IFACE
	return false;
}





TMPL_DEVLIB(bool) DevComponentGroup::Open() {TODO}
TMPL_DEVLIB(void) DevComponentGroup::CloseTemporary() {TODO}
TMPL_DEVLIB(void) DevComponentGroup::Clear() {TODO}
TMPL_DEVLIB(void) DevComponentGroup::FindComponents() {TODO}
TMPL_DEVLIB(void) DevComponentGroup::ConnectInputs(DevComponentConfVector& v) {TODO}

TMPL_DEVLIB(bool) DevComponentGroup::LoadExisting(TypeCls type, ObjectMap& st_map, int stage_i, String frag_code) {
	String fn_name = DevSpec::GetName() + "ComponentGroup::LoadExisting";
	for (auto& comp : comps) {
		if (comp->GetTypeId() == type) {
			if (!comp->Load(st_map, stage_i, frag_code)) {
				GetParent()->OnError(fn_name, "Loading stage " + IntStr(stage_i) + " failed");
				return false;
			}
			return true;
		}
	}
	return false;
}

TMPL_DEVLIB(void) DevComponentGroup::FindUniqueInputs(DevComponentConfVector& v) {
	for (auto& comp : comps)
		for(DevComponentConf& in : comp->in)
			if (/*in.IsTypeComponentSource() &&*/ v.Find(in) < 0)
				v.Add(in);
}

TMPL_DEVLIB(void) DevComponentGroup::UpdateCompFlags() {
	int comp_i = 0;
	int comp_count = comps.GetCount();
	for (DevComponentRef& comp : comps) {
		comp->UpdateCompFlags(val_spec, comp_i, comp_count);
		++comp_i;
	}
}

TMPL_DEVLIB(void) DevComponentGroup::UpdateDevBuffers() {
	for(DevComponentRef& comp : comps)
		comp->UpdateDevBuffers();
}

TMPL_DEVLIB(bool) DevComponentGroup::CreatePackets() {
	TODO
}






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

TMPL_DEVLIB(bool) ContextComponent::CreatePackets() {
	if (groups.IsFilled()) {
		stream.UpdateValuesBase();
		
		int dbg_i = 0;
		for (auto& gr : groups) {
			CreatePackets(gr);
			++dbg_i;
		}
			
		return true;
	}
	return false;
}

TMPL_DEVLIB(bool) ContextComponent::CreatePackets(DevComponentGroup& gr) {
	if (is_open /*&& lock.TryEnter()*/ ) {
		
		stream.UpdateValues(gr.GetValSpec());
		
		for (auto& gr : groups)
			gr.CreatePackets();
		
		//lock.Leave();
		return true;
	}
	return false;
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

TMPL_DEVLIB(bool) ContextComponent::Load(Object& json) {TODO}

TMPL_DEVLIB(bool) ContextComponent::RefreshStageQueue() {
	DLOG(DevSpec::GetName() << "ContextComponent::RefreshStageQueue: begin");
	
	// Solve dependencies
	
	Graph g;
	for(auto& gr : groups)
		for(auto& s : gr.comps)
			if (s->GetId() >= 0)
				g.AddKey(s->GetId());
	g.DumpKeys();
	for(auto& gr : groups) {
		for(const DevComponentRef& s : gr.comps) {
			int comp_id = s->GetId();
			if (comp_id >= 0) {
				for(const DevComponentConf& in : s->GetInputs()) {
					int in_id = in.GetId();
					LOG("id: " << in_id);
					if (in_id >= 0)
						g.AddEdgeKey(in_id, comp_id);
				}
			}
		}
	}
	g.TopologicalSort();
	if (g.IsError()) {
		OnError("RefreshStageQueue", g.GetError());
		return false;
	}
	
	
	DLOG("\ttopologically sorted stage list:");
	for(int i = 0; i < g.GetSortedCount(); i++) {
		DLOG("\t\t" << i << ": " << g.GetKey(i).ToString());
	}
	
	struct TopologicalStages : public ErrorReporter {
		Graph& g;
		TopologicalStages(Graph& g) : g(g) {}
		bool operator()(const RefT_Entity<DevComponent>& a, const RefT_Entity<DevComponent>& b) const {
			int a_pos = g.FindSorted(a->GetId());
			int b_pos = g.FindSorted(b->GetId());
			return a_pos < b_pos;
		}
	};
	TopologicalStages sorter(g);
	
	for(auto& gr : groups) {
		Sort(gr.comps, sorter);
		if (sorter.IsError()) {
			OnError("RefreshStageQueue", sorter.GetError());
			return false;
		}
	}
	
	#if 1
	DLOG("\ttopologically sorted stage list:");
	int i = 0;
	for(auto& gr : groups) {
		int j = 0;
		for(auto& comp : gr.comps) {
			DLOG("\t\t" << i << ": " << j++ << ": " << comp->ToString());
		}
		++i;
	}
	#endif
	
	
	DLOG(DevSpec::GetName() << "ContextComponent::RefreshStageQueue: end");
	return true;
}

TMPL_DEVLIB(bool) ContextComponent::CheckInputTextures() {TODO}
TMPL_DEVLIB(void) ContextComponent::Close() {TODO}

TMPL_DEVLIB(void) ContextComponent::RefreshStreamValuesAll() {
	stream.UpdateValuesBase();
	#define IFACE(x) stream.UpdateValues(AsTypeCls<x##Spec>());
	IFACE_LIST
	#undef IFACE
}

TMPL_DEVLIB(void) ContextComponent::RefreshPipeline() {
	DLOG(DevSpec::GetName() << "ContextComponent::RefreshPipeline begin");
	
	for(auto& gr : groups)
		gr.RefreshPipeline();
	
	for(auto& gr : groups)
		gr.UpdateDevBuffers();
	
	if (!CheckInputTextures()) {
		Close();
		return;
	}
	
	stream.Reset();
		
	
	DLOG(DevSpec::GetName() << "ContextComponent::RefreshPipeline end");
}

TMPL_DEVLIB(void) ContextComponent::OnError(String fn, String msg) {
	LOG(DevSpec::GetName() << "ContextComponent::" << fn << ": error: " << msg);
	last_error = msg;
	WhenError();
}

TMPL_DEVLIB(CLS::DevComponentGroup&) ContextComponent::GetAddGroupContext(TypeCls val_spec) {
	for(DevComponentGroup& gr : groups)
		if (gr.val_spec == val_spec)
			return gr;
	DevComponentGroup& gr = groups.Add();
	gr.SetParent(this);
	gr.val_spec = val_spec;
	return gr;
}

TMPL_DEVLIB(bool) ContextComponent::ConnectComponentInputs() {
	TODO
	#if 0
	const char* fn_name = "ConnectComponentInputs";
	bool succ = true;
	
	DumpEntityComponents();
	DLOG("Component vector:");
	int i = 0;
	for(auto& comp : comps) {
		DLOG("\t" << i << ": " << comp->ToString());
	}
	
	for (Ref<DevComponent>& comp_sink : comps) {
		ComponentBase& sink_base = comp_sink->GetECS();
		Ref<DeveratorSink> sink = sink_base.AsDeveratorSink();
		if (!sink)
			continue;
		ASSERT(sink->GetConnections().IsEmpty());
		
		for (const DeveratorHeader& in : comp_sink->in) {
			if (in.IsTypeEmpty())
				continue;
			
			bool found = false;
			for (Ref<DevComponent>& comp_src : comps) {
				ComponentBase& src_base = comp_src->GetECS();
				Ref<DeveratorSource> src = src_base.AsDeveratorSource();
				
				if (!src)
					continue;
				
				bool match = false;
				if (in.GetId() >= 0)
					match = comp_src->GetId() == in.GetId();
				else
					match = src->GetStream(ACCCTX).GetHeader().IsEqualHeader(in);
				
				if (match) {
					CookieRef src_cookie, sink_cookie;
					
					if (&src_base == &sink_base) {
						comp_sink->is_doublebuf = true;
						found = true;
						break;
					}
					else if (src->Accept(sink, src_cookie, sink_cookie)) {
						ExchangePointRef expt;
						src->Link(expt, sink, src_cookie, sink_cookie);
						found = true;
						break;
					}
					else {
						OnError(fn_name, "manual linking failed unexpectedly");
					}
				}
			}
			
			if (!found) {
				OnError(fn_name, "could not find DeveratorSource for input sink " + comp_sink->ToString() + ", " + in.ToString());
				succ = false;
				break;
			}
		}
		
		if (!succ) break;
	}
	
	return succ;
	#endif
}

TMPL_DEVLIB(bool) ContextComponent::ConnectComponentOutputs() {
	DLOG(DevSpec::GetName() + "ContextComponent::ConnectComponentOutputs begin");
	bool ret = true;
	
	for (DevComponentGroup& gr : groups) {
		if (gr.comps.IsEmpty())
			continue;
		
		#define IFACE(x) \
		if (gr.val_spec == AsTypeCls<x##Spec>()) {\
			if (!ConnectComponentOutputsT<x##Spec>(gr)) {ret = false; break;}\
		}
		IFACE_LIST
		#undef IFACE
	}
	
	DLOG(DevSpec::GetName() + "ContextComponent::ConnectComponentOutputs end");
	return ret;
}

template <class DevSpec>
template <class ValSpec>
bool ScopeDevLibT<DevSpec>::ContextComponent::ConnectComponentOutputsT(DevComponentGroup& gr) {
	String fn_name = DevSpec::GetName() + "ContextComponent::ConnectComponentOutputs";
	
	EntityRef e = ComponentBase::GetEntity();
	ComponentBaseRef comp = gr.comps.Top()->template AsRef<ComponentBase>();
	
	using VDCore = ScopeValDevCoreT<VD<DevSpec,ValSpec>>;
	using ValSource = typename VDCore::ValSource;
	using ValSourceRef = typename VDCore::ValSourceRef;
	using ValSink = typename VDCore::ValSink;
	using ValSinkRef = typename VDCore::ValSinkRef;
	using FromCenterComp = typename ScopeConvDevLibT<ValSpec,CenterSpec,DevSpec>::ConvertComponent;
	using FromCenterCompRef = Ref<FromCenterComp, RefParent1<Entity>>;
	
	ValSourceRef accel_aud_src = comp->As<ValSource>();
	if (!accel_aud_src) {
		OnError(fn_name, "last audio group component does not have ValSource interface");
		return false;
	}
	
	FromCenterCompRef aud_out = e->Find<FromCenterComp>();
	if (!aud_out) {
		aud_out = AddEntityComponent<FromCenterComp>(gr);
		
		ValSourceRef aud_src = aud_out->template As<ValSource>();
		if (!aud_src) {
			OnError(fn_name, "could not find ValSource interface");
			return false;
		}
		
		auto aud_src_conn = e->FindConnector<ConnectAllInterfaces<ValSource>>();
		if (!aud_src_conn) {
			OnError(fn_name, "could not find ValSource connector");
			return false;
		}
		
		// Connect ValSource to any existing ValSink
		if (!aud_src_conn->LinkAny(aud_src)) {
			OnError(fn_name, "could not link ValSource automatically");
			return false;
		}
	}
	
	ValSinkRef accel_aud_sink = comp->As<ValSink>();
	if (!accel_aud_sink) {
		OnError(fn_name, "component does not have DevValSink interface");
		return false;
	}
	
	auto accel_aud_src_conn = e->FindConnector<ConnectAllInterfaces<ValSource>>();
	if (!accel_aud_src_conn) {
		OnError(fn_name, "could not find ValSource connector");
		return false;
	}
	
	if (!accel_aud_src_conn->LinkManually(accel_aud_src, accel_aud_sink)) {
		OnError(fn_name, "could not link ValSource to DevValSink manually");
		return false;
	}
	
	return true;
}

TMPL_DEVLIB(bool) ContextComponent::CreateComponents(DevComponentConfVector& v) {
	TODO
	#if 0
	const char* fn_name = "CreateComponents";
	
	for(DeveratorHeader& in : v.in) {
		switch (in.GetType()) {
		case DeveratorHeader::TYPE_TEXTURE:
		case DeveratorHeader::TYPE_CUBEMAP:
		case DeveratorHeader::TYPE_VOLUME:
			if (!AddEntityDevComponent<PhotoContext, ConvertCenterDevPhotoComponent>(in))
				return false;
			break;
			
		case DeveratorHeader::TYPE_WEBCAM:
		case DeveratorHeader::TYPE_VIDEO:
		case DeveratorHeader::TYPE_MUSIC:
		case DeveratorHeader::TYPE_MUSICSTREAM:
			if (!AddEntityDevComponent<VideoContext, ConvertCenterDevVideoComponent>(in))
				return false;
			break;
			
		case DeveratorHeader::TYPE_KEYBOARD:
			if (!AddEntityDevComponent<EventContext, ConvertCenterDevEventComponent>(in))
				return false;
			break;
			
		case DeveratorHeader::TYPE_EMPTY:
		case DeveratorHeader::TYPE_BUFFER:
			break;
			
		case DeveratorHeader::TYPE_INVALID:
		default:
			OnError(fn_name, "Invalid type");
			return false;
		}
		
	}
	return true;
	#endif
}











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
#undef CLS
