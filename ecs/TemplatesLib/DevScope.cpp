#include "TemplatesLib.h"

//#define CTX				((D*)0)
//#define CLS				typename ScopeDevLibT<DevSpec>

NAMESPACE_ECS_BEGIN


/*template <class DevSpec, class R>
void ComponentBase::AddToContext(R ref) {
	ASSERT(ref);
	using DevContextConnector = typename ScopeDevLibT<DevSpec>::DevContextConnector;
	Ref<DevContextConnector> c = GetEntity()->FindConnector<DevContextConnector>();
	if (c)
		c->AddCtx(ref);
}

template <class DevSpec, class R>
void ComponentBase::RemoveFromContext(R ref) {
	ASSERT(ref);
	using DevContextConnector = typename ScopeDevLibT<DevSpec>::DevContextConnector;
	Ref<DevContextConnector> c = GetEntity()->FindConnector<DevContextConnector>();
	if (c)
		c->RemoveCtx(ref);
}*/








int StageComponentConfVector::Find(const StageComponentConf& a) const {
	int i = 0;
	for (StageComponentConf& b : in) {
		if (a.IsEqualHeader(b))
			return i;
		++i;
	}
	return -1;
}

void StageComponentConfVector::Add(const StageComponentConf& a) {
	ASSERT(Find(a) < 0);
	in.Add(a);
}






void StageComponent::Initialize() {
	DLOG("StageComponent(" << GetTypeString() << ")::Initialize");
	StageComponentRef ref = AsRef<StageComponent>();
	
	TODO
	/*Ref<DevSystem> sys = CastRef<ComponentBase>(this).GetEntity()->GetMachine().template Get<DevSystem>();
	if (sys)
		sys	-> AddComp(ref);
	*/
}

void StageComponent::Uninitialize() {
	DLOG("StageComponent(" << GetTypeString() << ")::Uninitialize");
	StageComponentRef ref = AsRef<StageComponent>();
	
	/*if (group) {
		group->Remove(ref);
		group.Clear();
	}*/
	
	TODO
	/*Ref<DevSystem> sys = CastRef<ComponentBase>(this).GetEntity()->GetMachine().template Get<DevSystem>();
	if (sys)
		sys	-> RemoveComp(ref);*/
	
	//Clear();
}

String StageComponent::GetStringFromType(TypeCls i) {
	TODO
	/*#define IFACE(x) \
		if (i == AsTypeCls<typename ScopeValDevCoreT<VD<DevSpec, x##Spec>>::ValSource>()) \
			return DevSpec::GetPrefix() + #x "Source"; \
		if (i == AsTypeCls<typename ScopeValDevCoreT<VD<DevSpec, x##Spec>>::ValSink>()) \
			return DevSpec::GetPrefix() + #x "Sink"; \
		if (i == AsTypeCls<typename ScopeValDevLibT<VD<DevSpec, x##Spec>>::PipeComponent>()) \
			return DevSpec::GetPrefix() + #x "PipeComponent";
		//if (i == AsTypeCls<ConvertCenterAccel##x##Component>()) return "ConvertCenterAccel" #x "Component";
	IFACE_LIST
	#undef IFACE*/
	return "invalid";
}

void StageComponent::OnError(String fn, String msg) {
	/*if (group && group->GetParent()) {
		group->GetParent()->OnError(String(RTTI::GetRTTI().GetDynamicName()) + "::" + fn, msg);
	}
	else {*/
	LOG("StageComponent::" << fn << ": error: " << msg);
}

//DevStreamState& StageComponent::GetStreamState() {return group->GetStreamState();}

void StageComponent::Clear() {
	id = -1;
	in.Clear();
	TODO
	//StageComponentBase::Clear();
}

bool StageComponent::IsDevPipeComponent(TypeCls type) {
	TODO
	/*#define IFACE(x) \
	if (type == AsTypeCls<typename ScopeValDevLibT<VD<DevSpec, x##Spec>>::PipeComponent>()) \
		return true;
	IFACE_LIST
	#undef IFACE*/
	return false;
}

void StageComponent::Close() {
	TODO
	//StageComponentBase::Close();
	is_open = false;
}

bool StageComponent::Open() {
	DLOG("StageComponent(" << GetTypeString() << ")::Open: begin");
	const char* fn_name = "Open";
	
	if (is_open)
		Close();
	
	TODO
	//if (StageComponentBase::Open())
	//	is_open = true;
	
	DLOG("StageComponent(" << GetTypeString() << ")::Open: end");
	return is_open;
}

void StageComponent::PostProcess() {
	TODO
	//GetStreamState().Step(group->GetValSpec());
}

void StageComponent::ForwardPacket(ValCls dst, FwdScope& fwd, Packet p) {
	/*using VD					= TS::VD<DevSpec,ValSpec>;
	using DevMach				= ScopeDevMachT<DevSpec>;
	using ValMach				= ScopeValMachT<ValSpec>;
	using Mach					= ScopeValDevMachT<VD>;
	using Core					= ScopeValDevCoreT<VD>;
	using InternalPacketData	= typename DevMach::InternalPacketData;
	using ValStream				= typename Mach::Stream;
	using SimpleStream			= typename Mach::SimpleStream;
	using PacketBuffer			= typename Mach::PacketBuffer;
	using Value					= typename Mach::Value;
	using SimpleBufferedValue	= typename Mach::SimpleBufferedValue;
	using SimpleBufferedStream	= typename Mach::SimpleBufferedStream;
	using ValSource				= typename Core::ValSource;
	using ValSourceRef			= typename Core::ValSourceRef;*/
	
	#if 0
	DLOG("StageComponent::ForwardPacket: begin");
	
	if (p->template IsData<InternalPacketData>()) {
		InternalPacketData& data = p->template GetData<InternalPacketData>();
		
		p->CheckTracking(TrackerInfo(this, __FILE__, __LINE__));
		
		StageComponentBase::Process();
		
		if (data.pos >= data.count-1)
			PostProcess();
		else {
			data.pos++;
		}
	}
	else {
		StageComponentBase::Process();
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
	
	#endif
}









#if 0

bool StageComponentGroup::Open() {
	int dbg_i = 0;
	for(StageComponentRef& comp : comps) {
		if (!comp->IsOpen() && !comp->Open()) {
			DLOG(DevSpec::GetName() + "ComponentGroup::Open: error: a component did not open properly (comp #" + IntStr(dbg_i) + ")");
			return false;
		}
		++dbg_i;
	}
	return true;
}

void StageComponentGroup::Close() {
	for(StageComponentRef& comp : comps) {
		comp->Close();
		comp->template AsRef<ComponentBase>()->Destroy();
	}
}

void StageComponentGroup::CloseTemporary() {TODO}
void StageComponentGroup::Clear() {TODO}
void StageComponentGroup::ConnectInputs(StageComponentConfVector& v) {TODO}

bool StageComponentGroup::LoadExisting(TypeCls type, ObjectMap& st_map, int stage_i, String frag_code) {
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

void StageComponentGroup::FindUniqueInputs(StageComponentConfVector& v) {
	for (auto& comp : comps)
		for(StageComponentConf& in : comp->in)
			if (/*in.IsTypeComponentSource() &&*/ v.Find(in) < 0)
				v.Add(in);
}

void StageComponentGroup::FindAdd(StageComponentRef r) {
	StageComponentGroupRef g = this->template AsRef<StageComponentGroup>();
	ASSERT(!r->group || r->group == g);
	r->group = g;
	comps.FindAdd(r);
	UpdateCompFlags();
}

void StageComponentGroup::Remove(StageComponentRef r) {
	StageComponentGroupRef g = this->template AsRef<StageComponentGroup>();
	ASSERT(r->group == g);
	r->group.Clear();
	comps.RemoveKey(r);
	UpdateCompFlags();
}

void StageComponentGroup::UpdateCompFlags() {
	int comp_i = 0;
	int comp_count = comps.GetCount();
	for (StageComponentRef& comp : comps) {
		comp->pos = comp_i;
		comp->UpdateCompFlags(val_spec, comp_i, comp_count);
		++comp_i;
	}
}

void StageComponentGroup::UpdateDevBuffers() {
	for(StageComponentRef& comp : comps)
		comp->UpdateDevBuffers();
}

bool StageComponentGroup::ForwardPackets() {
	if (comps.IsEmpty())
		return false;
	
	ASSERT(GetParent()->IsOpen());
	
	for(auto& comp : comps)
		comp->PreProcess();
	
	// Device cannot possibly store buffered packets (e.g. GPU):
	// - 'cost' of storing packets is infinity
	//   --> processing of packets must happen in edge-in (when sink gets packet)
	for(StageComponentRef& comp : comps)
		{ASSERT(comp->IsEmptyStream());}
	for(StageComponentRef& comp : comps)
		comp->ClearStream();
	
	
	StageComponentRef& comp = comps.First();
	InterfaceSinkBaseRef sink = comp->template AsRef<InterfaceSinkBase>();
	if (!sink)
		return false;
	
	
	return StageComponentGroupBase::CreateForwardPacket(*sink);
}

void StageComponentGroup::DumpComponents() {
	LOG(DevSpec::GetName() + "ComponentGroup::DumpComponents");
	int i = 0;
	for(StageComponentRef& comp : comps) {
		LOG(i++ << ": " << comp->ToString());
	}
}

TMPL_DEVLIB(CLS::StageComponentRef) StageComponentGroup::GetComponentById(int id) const {
	ASSERT(id >= 0);
	for (const auto& s : comps)
		if (s->id == id)
			return s;
	THROW(Exc(DevSpec::GetName() + "Component not found"));
}

bool StageComponentGroup::CheckDevice() {
	for(StageComponentRef& comp : comps)
		if (!comp->CheckDevice())
			return false;
	return true;
}










DevContextConnector::DevContextConnector() {
	
}

void DevContextConnector::Initialize() {
	DLOG(DevSpec::GetName() + "DevContextConnector::Initialize");
	Ref<DevSystem> sys = TS::ConnectorBase::GetPool()->GetMachine().template Get<DevSystem>();
	if (sys)
		sys	-> AddDev(TS::ConnectorBase::AsRef<DevContextConnector>());
}

void DevContextConnector::Uninitialize() {
	DLOG(DevSpec::GetName() + "DevContextConnector::Uninitialize");
	Ref<DevSystem> sys = TS::ConnectorBase::GetPool()->GetMachine().template Get<DevSystem>();
	if (sys)
		sys	-> RemoveDev(TS::ConnectorBase::AsRef<DevContextConnector>());
}

void DevContextConnector::Update(double dt) {
	
}

void DevContextConnector::ForwardPackets(double dt) {
	for (DevComponentRef& dev : devs) {
		dev->ForwardPackets(dt);
	}
}

void DevContextConnector::FindAdd(DevComponentRef r) {
	ASSERT(r);
	ASSERT_(!r->GetContext(), "Did you AddToContext but it was not needed?");
	r->SetContext(this->template AsRef<DevContextConnector>());
	devs.FindAdd(r);
}

void DevContextConnector::Remove(DevComponentRef r) {
	ASSERT(r);
	ASSERT(r->GetContext() == this->template AsRef<DevContextConnector>());
	r->ClearContext();
	devs.RemoveKey(r);
}

void DevContextConnector::AddCtx(DevSourceRef r) {
	ASSERT(r);
	srcs.FindAdd(r);
	FindAdd(r->template AsRef<DevComponent>());
}

void DevContextConnector::RemoveCtx(DevSourceRef r) {
	ASSERT(r);
	srcs.RemoveKey(r);
	Remove(r->template AsRef<DevComponent>());
}

void DevContextConnector::AddCtx(DevSinkRef r) {
	ASSERT(r);
	sinks.FindAdd(r);
	FindAdd(r->template AsRef<DevComponent>());
}

void DevContextConnector::RemoveCtx(DevSinkRef r) {
	ASSERT(r);
	sinks.RemoveKey(r);
	Remove(r->template AsRef<DevComponent>());
}

#endif




void DevComponentBase::Initialize() {
	//USING_DEVLIB(DevContextConnector);
	//USING_DEVLIB(DevContextConnectorRef)
	ASSERT(!ctx);
	ComponentBase* cb = CastPtr<ComponentBase>(this);
	ASSERT(cb);
	/*DevContextConnectorRef conn = cb->GetEntity()->FindConnector<DevContextConnector>();
	ASSERT(conn);
	conn->FindAdd(this->template AsRef<DevComponent>());
	ctx = conn;*/
}

void DevComponentBase::Uninitialize() {
	//USING_DEVLIB(DevContextConnector)
	//USING_DEVLIB(DevContextConnectorRef)
	
	/*ASSERT(ctx);
	DevContextConnectorRef conn = ctx;
	ASSERT(conn);
	conn->Remove(this->template AsRef<DevComponent>());
	ctx.Clear();*/
}











#if 0
TMPL_DEVLIB_CTOR StageContextConnector::StageContextConnector() {
	
}

void StageContextConnector::Initialize() {
	DLOG(DevSpec::GetName() + "StageContextConnector::Initialize");
	Ref<DevSystem> sys = TS::ConnectorBase::GetPool()->GetMachine().template Get<DevSystem>();
	if (sys)
		sys	-> AddStage(TS::ConnectorBase::AsRef<StageContextConnector>());
	
	FindComponents();
}

void StageContextConnector::Uninitialize() {
	DLOG(DevSpec::GetName() + "StageContextConnector::Uninitialize");
	Ref<DevSystem> sys = TS::ConnectorBase::GetPool()->GetMachine().template Get<DevSystem>();
	if (sys)
		sys	-> RemoveStage(TS::ConnectorBase::AsRef<StageContextConnector>());
}

void StageContextConnector::PostLoadFileAny(String path) {
	Object content;
	if (LoadFileAny(path, content)) {
		post_load = content;
	}
}

bool StageContextConnector::LoadFileAny(String path, Object& dst) {
	
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

void StageContextConnector::Update(double dt) {
	DLOG("StageContextConnector::Update: begin");
	
	//lock.Enter();
	
	if (!post_load.IsVoid()) {
		DLOG("StageContextConnector::Update: load new program");
		
		Object to_load;
		Swap(post_load, to_load);
		
		for(StageComponentGroup& g : groups)
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
		for(StageComponentGroup& g : groups)
			if (!g.Open())
				{is_open = false; break;}
		
		if (!is_open) {
			DLOG("StageContextConnector::Update: error: did not open properly");
			return;
		}
		
		#define IFACE(x) stream.template Get<x##Spec>().fmt = Core::template GetDefaultFormat<x##Spec>();
		IFACE_LIST
		#undef IFACE
		
		RefreshStreamValuesAll();
		
		RefreshPipeline();
	}
	
	//lock.Leave();
	
	DLOG("StageContextConnector::Update: end");
}

bool StageContextConnector::ForwardPackets() {
	if (groups.IsFilled()) {
		stream.UpdateValuesBase();
		
		int dbg_i = 0;
		for (auto& gr : groups) {
			ForwardPackets(gr);
			++dbg_i;
		}
			
		return true;
	}
	return false;
}

bool StageContextConnector::ForwardPackets(StageComponentGroup& gr) {
	if (is_open /*&& lock.TryEnter()*/ ) {
		
		stream.UpdateValues(gr.GetValSpec());
		
		for (auto& gr : groups)
			gr.ForwardPackets();
		
		//lock.Leave();
		return true;
	}
	return false;
}

void StageContextConnector::Clear() {
	for(auto& gr : groups)
		gr.Clear();
	
	stream.Clear();
	common_source.Clear();
	groups.Clear();
	last_error.Clear();
	post_load = Null;
	is_open = false;
	
}

void StageContextConnector::Reset() {
	stream.Reset();
}

void StageContextConnector::FindComponents() {
	ComponentBase* b = CastPtr<ComponentBase>(this);
	ASSERT(b);
	PoolRef p = TS::ConnectorBase::GetPool();
	TODO
	/*for(ComponentBaseRef& c : e->GetComponents()) {
		StageComponentRef d = c->AsRef<StageComponent>();
		if (d) {
			TypeCls val_spec = d->GetValSpec();
			StageComponentGroup& g = GetAddGroupContext(val_spec);
			g.FindAdd(d);
		}
	}*/
}

void StageContextConnector::DumpEntityComponents() {
	LOG(DevSpec::GetName() + "StageContextConnector:");
	PoolRef p = TS::ConnectorBase::GetPool();
	TODO
	/*EntityRef e = TS::ComponentBase::GetEntity();
	int i = 0;
	for (ComponentRef& comp : e->GetComponents().GetValues()) {
		if (comp) {
			auto& base = *comp;
			StageComponent* fcomp = CastPtr<StageComponent>(&base);
			if (fcomp) {
				LOG("\t" << i++ << ": " << DevSpec::GetName() << "Component: " << fcomp->ToString());
			}
			else {
				LOG("\t" << i++ << ": " << base.GetDynamicName());
			}
		}
	}*/
}

bool StageContextConnector::Load(Object& json) {TODO}

bool StageContextConnector::RefreshStageQueue() {
	DLOG(DevSpec::GetName() << "StageContextConnector::RefreshStageQueue: begin");
	
	// Solve dependencies
	
	Graph g;
	for(auto& gr : groups)
		for(auto& s : gr.comps)
			if (s->GetId() >= 0)
				g.AddKey(s->GetId());
	g.DumpKeys();
	for(auto& gr : groups) {
		for(const StageComponentRef& s : gr.comps) {
			int comp_id = s->GetId();
			if (comp_id >= 0) {
				for(const StageComponentConf& in : s->GetInputs()) {
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
		bool operator()(const RefT_Entity<StageComponent>& a, const RefT_Entity<StageComponent>& b) const {
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
	
	
	DLOG(DevSpec::GetName() << "StageContextConnector::RefreshStageQueue: end");
	return true;
}

bool StageContextConnector::CheckDevice() {
	for(auto& gr : groups)
		if (!gr.CheckDevice())
			return false;
	return true;
}

void StageContextConnector::Close() {
	for(auto& gr : groups)
		gr.Close();
}

void StageContextConnector::RefreshStreamValuesAll() {
	stream.UpdateValuesBase();
	#define IFACE(x) stream.UpdateValues(AsTypeCls<x##Spec>());
	IFACE_LIST
	#undef IFACE
}

void StageContextConnector::RefreshPipeline() {
	DLOG(DevSpec::GetName() << "StageContextConnector::RefreshPipeline begin");
	
	for(auto& gr : groups)
		gr.RefreshPipeline();
	
	for(auto& gr : groups)
		gr.UpdateDevBuffers();
	
	if (!CheckDevice()) {
		Close();
		return;
	}
	
	stream.Reset();
		
	
	DLOG(DevSpec::GetName() << "StageContextConnector::RefreshPipeline end");
}

void StageContextConnector::OnError(String fn, String msg) {
	LOG(DevSpec::GetName() << "StageContextConnector::" << fn << ": error: " << msg);
	last_error = msg;
	WhenError();
}

TMPL_DEVLIB(CLS::StageComponentGroup&) StageContextConnector::GetAddGroupContext(TypeCls val_spec) {
	for(StageComponentGroup& gr : groups)
		if (gr.val_spec == val_spec)
			return gr;
	StageComponentGroup& gr = groups.Add();
	gr.SetParent(this);
	gr.val_spec = val_spec;
	return gr;
}

bool StageContextConnector::ConnectComponentInputs() {
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
	
	for (Ref<StageComponent>& comp_sink : comps) {
		ComponentBase& sink_base = comp_sink->GetECS();
		Ref<DeveratorSink> sink = sink_base.AsDeveratorSink();
		if (!sink)
			continue;
		ASSERT(sink->GetConnections().IsEmpty());
		
		for (const DeveratorHeader& in : comp_sink->in) {
			if (in.IsTypeEmpty())
				continue;
			
			bool found = false;
			for (Ref<StageComponent>& comp_src : comps) {
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

bool StageContextConnector::ConnectComponentOutputs() {
	DLOG(DevSpec::GetName() + "StageContextConnector::ConnectComponentOutputs begin");
	bool ret = true;
	
	for (StageComponentGroup& gr : groups) {
		if (gr.comps.IsEmpty())
			continue;
		
		#define IFACE(x) \
		if (gr.val_spec == AsTypeCls<x##Spec>()) {\
			if (!ConnectComponentOutputsT<x##Spec>(gr)) {ret = false; break;}\
		}
		IFACE_LIST
		#undef IFACE
	}
	
	DLOG(DevSpec::GetName() + "StageContextConnector::ConnectComponentOutputs end");
	return ret;
}

bool StageContextConnector::ConnectComponentOutputsT(EcsTypeCls dst, StageComponentGroup& gr) {
	String fn_name = DevSpec::GetName() + "StageContextConnector::ConnectComponentOutputs";
	
	TODO
	#if 0
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
	using ToDevComp			= typename ScopeConvValDevLibT<ValSpec,DevSpec,ToDevSpec>::ConvertComponent;
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
	#endif
	
	return true;
}

bool StageContextConnector::CreateComponents(StageComponentConfVector& v) {
	TODO
	#if 0
	const char* fn_name = "CreateComponents";
	
	for(DeveratorHeader& in : v.in) {
		switch (in.GetType()) {
		case DeveratorHeader::TYPE_TEXTURE:
		case DeveratorHeader::TYPE_CUBEMAP:
		case DeveratorHeader::TYPE_VOLUME:
			if (!AddEntityStageComponent<PhotoContext, ConvertCenterDevPhotoComponent>(in))
				return false;
			break;
			
		case DeveratorHeader::TYPE_WEBCAM:
		case DeveratorHeader::TYPE_VIDEO:
		case DeveratorHeader::TYPE_MUSIC:
		case DeveratorHeader::TYPE_MUSICSTREAM:
			if (!AddEntityStageComponent<VideoContext, ConvertCenterDevVideoComponent>(in))
				return false;
			break;
			
		case DeveratorHeader::TYPE_KEYBOARD:
			if (!AddEntityStageComponent<EventContext, ConvertCenterDevEventComponent>(in))
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

void StageContextConnector::FindAdd(StageComponentRef c) {
	ASSERT(c);
	StageComponentGroup& g = GetAddGroupContext(c->GetValSpec());
	g.FindAdd(c);
}

void StageContextConnector::Remove(StageComponentRef c) {
	ASSERT(c);
	StageComponentGroup& g = GetAddGroupContext(c->GetValSpec());
	g.Remove(c);
}

#endif












//Callback DevSystem::WhenUninit;

bool DevSystem::Initialize() {
	
	
	return true;
}

void DevSystem::Start() {
	
}

void DevSystem::Update(double dt) {
	if (comps.IsEmpty())
		return;
	
	/*RTLOG(DevSpec::GetName() + "DevSystem::Update: begin");
	
	if (!stages.IsEmpty()) {
		for (StageContextConnectorRef& ctx : stages)
			ctx->Update(dt);
		
		for (StageContextConnectorRef& ctx : stages)
			ctx->ForwardPackets();
	}
	
	if (!devs.IsEmpty()) {
		for (DevContextConnectorRef& dev : devs)
			dev->Update(dt);
		
		for (DevContextConnectorRef& dev : devs)
			dev->ForwardPackets(dt);
	}
	
	
	RTLOG(DevSpec::GetName() + "DevSystem::Update: end");
	*/
}

void DevSystem::Stop() {
	
	
}

void DevSystem::Uninitialize() {
	//stages.Clear();
	//devs.Clear();
	comps.Clear();
	
	WhenUninit()();
}


NAMESPACE_ECS_END

//#undef CTX
//#undef CLS
