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

TMPL_DEVLIB(void) DevComponent::Close() {
	DevComponentBase::Close();
	is_open = false;
}

TMPL_DEVLIB(bool) DevComponent::Open() {
	DLOG(DevSpec::GetName() + "Component(" << GetTypeString() << ")::Open: begin");
	const char* fn_name = "Open";
	
	if (is_open)
		Close();
	
	if (DevComponentBase::Open())
		is_open = true;
	
	DLOG(DevSpec::GetName() + "Component(" << GetTypeString() << ")::Open: end");
	return is_open;
}

TMPL_DEVLIB(void) DevComponent::PostProcess() {
	GetStreamState().Step(group->GetValSpec());
}

template <class DevSpec>
template <class ValSpec>
void ScopeDevLibT<DevSpec>::DevComponent::ForwardPacket(FwdScope& fwd, typename ScopeValMachT<ValSpec>::Packet p) {
	using VD					= TS::VD<DevSpec,ValSpec>;
	using DevMach				= ScopeDevMachT<DevSpec>;
	using ValMach				= ScopeValMachT<ValSpec>;
	using Mach					= ScopeValDevMachT<VD>;
	using Core					= ScopeValDevCoreT<VD>;
	using InternalPacketData	= typename DevMach::InternalPacketData;
	using TrackerInfo			= typename ValMach::TrackerInfo;
	using ValStream				= typename Mach::Stream;
	using SimpleStream			= typename Mach::SimpleStream;
	using PacketBuffer			= typename Mach::PacketBuffer;
	using Value					= typename Mach::Value;
	using SimpleBufferedValue	= typename Mach::SimpleBufferedValue;
	using SimpleBufferedStream	= typename Mach::SimpleBufferedStream;
	using ValSource				= typename Core::ValSource;
	using ValSourceRef			= typename Core::ValSourceRef;
	
	DLOG("DevComponent::ForwardPacket: begin");
	
	InternalPacketData& data = p->template GetData<InternalPacketData>();
	
	p->CheckTracking(TrackerInfo(this, __FILE__, __LINE__));
	
	DevComponentBase::Process();
	
	if (data.pos >= data.count-1)
		PostProcess();
	else {
		data.pos++;
	}
	
	ValSource* src = CastPtr<ValSource>(this);
	if (src) {
		ValStream& stream = src->GetStream((ValSpec*)0);
		SimpleBufferedStream* sbstream = CastPtr<SimpleBufferedStream>(&stream);
		if (sbstream) {
			Value& value = sbstream->Get();
			SimpleBufferedValue* bval = CastPtr<SimpleBufferedValue>(&value);
			if (bval) {
				PacketBuffer& buf = bval->GetBuffer();
				buf.Add(p);
			}
			else {
				TODO
			}
		}
		else {
			SimpleStream* sstream = CastPtr<SimpleStream>(&stream);
			if (sstream) {
				Value& value = sstream->Get();
				
				TODO
			}
			else {
				TODO
			}
		}
	}
	
	fwd.AddNext(this);
	
	DLOG("ComponentBase::ForwardPacket: end");
}












TMPL_DEVLIB(bool) DevComponentGroup::Open() {
	int dbg_i = 0;
	for(DevComponentRef& comp : comps) {
		if (!comp->IsOpen() && !comp->Open()) {
			DLOG(DevSpec::GetName() + "ComponentGroup::Open: error: a component did not open properly (comp #" + IntStr(dbg_i) + ")");
			return false;
		}
		++dbg_i;
	}
	return true;
}

TMPL_DEVLIB(void) DevComponentGroup::Close() {
	for(DevComponentRef& comp : comps) {
		comp->Close();
		comp->template AsRef<ComponentBase>()->Destroy();
	}
}

TMPL_DEVLIB(void) DevComponentGroup::CloseTemporary() {TODO}
TMPL_DEVLIB(void) DevComponentGroup::Clear() {TODO}
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

TMPL_DEVLIB(void) DevComponentGroup::FindAdd(DevComponentRef r) {
	DevComponentGroupRef g = this->template AsRef<DevComponentGroup>();
	ASSERT(!r->group || r->group == g);
	r->group = g;
	comps.FindAdd(r);
	UpdateCompFlags();
}

TMPL_DEVLIB(void) DevComponentGroup::Remove(DevComponentRef r) {
	DevComponentGroupRef g = this->template AsRef<DevComponentGroup>();
	ASSERT(r->group == g);
	r->group.Clear();
	comps.RemoveKey(r);
	UpdateCompFlags();
}

TMPL_DEVLIB(void) DevComponentGroup::UpdateCompFlags() {
	int comp_i = 0;
	int comp_count = comps.GetCount();
	for (DevComponentRef& comp : comps) {
		comp->pos = comp_i;
		comp->UpdateCompFlags(val_spec, comp_i, comp_count);
		++comp_i;
	}
}

TMPL_DEVLIB(void) DevComponentGroup::UpdateDevBuffers() {
	for(DevComponentRef& comp : comps)
		comp->UpdateDevBuffers();
}

TMPL_DEVLIB(bool) DevComponentGroup::CreatePackets() {
	if (comps.IsEmpty())
		return false;
	
	ASSERT(GetParent()->IsOpen());
	
	for(auto& comp : comps)
		comp->PreProcess();
	
	// Device cannot possibly store buffered packets (e.g. GPU):
	// - 'cost' of storing packets is infinity
	//   --> processing of packets must happen in edge-in (when sink gets packet)
	for(DevComponentRef& comp : comps)
		{ASSERT(comp->IsEmptyStream());}
	for(DevComponentRef& comp : comps)
		comp->ClearStream();
	
	
	DevComponentRef& comp = comps.First();
	InterfaceSinkBaseRef sink = comp->template AsRef<InterfaceSinkBase>();
	if (!sink)
		return false;
	
	
	return DevComponentGroupBase::CreateForwardPacket(*sink);
}

TMPL_DEVLIB(void) DevComponentGroup::DumpComponents() {
	LOG(DevSpec::GetName() + "ComponentGroup::DumpComponents");
	int i = 0;
	for(DevComponentRef& comp : comps) {
		LOG(i++ << ": " << comp->ToString());
	}
}

TMPL_DEVLIB(CLS::DevComponentRef) DevComponentGroup::GetComponentById(int id) const {
	ASSERT(id >= 0);
	for (const auto& s : comps)
		if (s->id == id)
			return s;
	THROW(Exc(DevSpec::GetName() + "Component not found"));
}

TMPL_DEVLIB(bool) DevComponentGroup::CheckDevice() {
	for(DevComponentRef& comp : comps)
		if (!comp->CheckDevice())
			return false;
	return true;
}








TMPL_DEVLIB() ContextComponent::ContextComponent() {
	
}

TMPL_DEVLIB(void) ContextComponent::Initialize() {
	DLOG(DevSpec::GetName() + "ContextComponent::Initialize");
	Ref<DevSystem> sys = TS::ComponentBase::GetEntity()->GetMachine().template Get<DevSystem>();
	if (sys)
		sys	-> AddCtx(TS::ComponentBase::AsRef<ContextComponent>());
	
	FindComponents();
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
	ComponentBase* b = CastPtr<ComponentBase>(this);
	ASSERT(b);
	EntityRef e = TS::ComponentBase::GetEntity();
	for(ComponentBaseRef& c : e->GetComponents()) {
		DevComponentRef d = c->AsRef<DevComponent>();
		if (d) {
			TypeCls val_spec = d->GetValSpecType();
			DevComponentGroup& g = GetAddGroupContext(val_spec);
			g.FindAdd(d);
		}
	}
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

TMPL_DEVLIB(bool) ContextComponent::CheckDevice() {
	for(auto& gr : groups)
		if (!gr.CheckDevice())
			return false;
	return true;
}

TMPL_DEVLIB(void) ContextComponent::Close() {
	for(auto& gr : groups)
		gr.Close();
}

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
	
	if (!CheckDevice()) {
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
	
	using FromDevSpec		= DevSpec;
	using FromVD			= TS::VD<DevSpec,ValSpec>;
	using FromVDCore		= ScopeValDevCoreT<FromVD>;
	using FromSource		= typename FromVDCore::ValSource;
	using FromSourceRef		= typename FromVDCore::ValSourceRef;
	using FromSink			= typename FromVDCore::ValSink;
	using FromSinkRef		= typename FromVDCore::ValSinkRef;
	
	using ToDevSpec			= CenterSpec;
	using ToVD				= TS::VD<ToDevSpec,ValSpec>;
	using ToVDCore			= ScopeValDevCoreT<ToVD>;
	using ToSource			= typename ToVDCore::ValSource;
	using ToSourceRef		= typename ToVDCore::ValSourceRef;
	using ToDevComp			= typename ScopeConvDevLibT<ValSpec,DevSpec,ToDevSpec>::ConvertComponent;
	using ToDevCompRef		= Ref<ToDevComp, RefParent1<Entity>>;
	
	FromSourceRef valdev_src = comp->As<FromSource>();
	if (!valdev_src) {
		OnError(fn_name, "last " + FromDevSpec::GetName() + "-group component does not have " + FromVD::GetPrefix() + "Source interface");
		gr.DumpComponents();
		return false;
	}
	
	ToDevCompRef val_out = e->Find<ToDevComp>();
	if (!val_out) {
		val_out = ComponentBase::GetEntity()->template Add<ToDevComp>();
		
		ToSourceRef val_src = val_out->template As<ToSource>();
		if (!val_src) {
			OnError(fn_name, "could not find " + ToVD::GetPrefix() + "Source interface");
			return false;
		}
		
		auto val_src_conn	= e->FindConnector<ConnectAllInterfaces<ToVD>>();
		auto dev_conn		= e->FindConnector<ConnectAllDevInterfaces<ToDevSpec>>();
		if (!val_src_conn && !dev_conn) {
			OnError(fn_name, "could not find " + ToVD::GetPrefix() + "Source nor " + ToDevSpec::GetName() + "Spec connector");
			return false;
		}
		
		// Connect ValSource to any existing ValSink
		bool linked = false;
		if (			val_src_conn	&& val_src_conn	->template LinkAny<ToVD>(val_src))
			linked = true;
		if (!linked &&	dev_conn		&& dev_conn		->template LinkAny<ToVD>(val_src))
			linked = true;
		
		if (!linked) {
			OnError(fn_name, "could not link " + ToVD::GetPrefix() + "Source automatically");
			return false;
		}
	}
	
	FromSinkRef valdev_sink = val_out->template As<FromSink>();
	if (!valdev_sink) {
		OnError(fn_name, "component does not have " + FromVD::GetPrefix() + "Sink interface");
		return false;
	}
	
	auto valdev_src_conn	= e->FindConnector<ConnectAllInterfaces<FromVD>>();
	auto dev_conn			= e->FindConnector<ConnectAllDevInterfaces<FromDevSpec>>();
	if (!valdev_src_conn && !dev_conn) {
		OnError(fn_name, "could not find " + FromVD::GetPrefix() + "Source connector");
		return false;
	}
	
	bool linked = false;
	if (			valdev_src_conn	&& valdev_src_conn	->template LinkManually<FromVD>(valdev_src, valdev_sink))
		linked = true;
	if (!linked &&	dev_conn		&& dev_conn			->template LinkManually<FromVD>(valdev_src, valdev_sink))
		linked = true;
	if (!linked) {
		OnError(fn_name, "could not link " + FromVD::GetPrefix() + "Source to DevValSink manually");
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

TMPL_DEVLIB(void) ContextComponent::FindAdd(DevComponentRef c) {
	TypeCls val_spec = c->GetValSpecType();
	DevComponentGroup& gr = GetAddGroupContext(val_spec);
	gr.FindAdd(c);
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
