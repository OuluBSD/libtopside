#include "FusionCore.h"

NAMESPACE_TOPSIDE_BEGIN


int FusionContextComponent::id_counter;

FusionContextComponent::FusionContextComponent() {
	
}

void FusionContextComponent::Initialize() {
	DLOG("FusionContextComponent::Initialize");
	Ref<FusionSystem> fusion_sys = GetEntity()->GetMachine().Get<FusionSystem>();
	if (fusion_sys)
		fusion_sys	-> AddContext(*this);
	
}

void FusionContextComponent::Uninitialize() {
	Ref<FusionSystem> fusion_sys = GetEntity()->GetMachine().Get<FusionSystem>();
	if (fusion_sys)
		fusion_sys	-> RemoveContext(*this);
}

void FusionContextComponent::Update(double dt) {
	DLOG("FusionContextComponent::Update: begin");
	
	//lock.Enter();
	
	if (!post_load.IsVoid()) {
		DLOG("FusionContextComponent::Update: load new program");
		
		Object to_load;
		Swap(post_load, to_load);
		
		for(FusionComponentRef& comp : comps) {
			if (comp->IsTypeTemporary()) {
				comp->Close();
				comp->GetECS().Destroy();
			}
		}
		
		Clear();
		FindComponents();
		DumpEntityComponents();
		
		Load(to_load);
		Reset();
		
		//  Reload stage pointers
		RefreshStageQueue();
		DumpEntityComponents();
		
		is_open = true;
		for(FusionComponentRef& comp : comps) {
			if (!comp->IsOpen() && !comp->Open()) {
				DLOG("FusionContextComponent::Update: error: a component did not open properly");
				is_open = false;
			}
		}
		
		if (!is_open) {
			DLOG("FusionContextComponent::Update: error: did not open properly");
			return;
		}
		
		RefreshPipeline();
	}
	
	
	//lock.Leave();
	DLOG("FusionContextComponent::Update: end");
}

void FusionContextComponent::FindComponents() {
	comps.Clear();
	EntityRef e = GetEntity();
	for (ComponentRef& comp : e->GetComponents().GetValues()) {
		if (comp) {
			ComponentBase& base = *comp;
			FusionComponent* fcomp = dynamic_cast<FusionComponent*>(&base);
			if (fcomp) {
				ASSERT(!fcomp->ctx);
				fcomp->ctx = this;
				comps.Add(fcomp->AsRefT());
			}
		}
	}
}

void FusionContextComponent::DumpEntityComponents() {
	LOG("Entity: FusionComponents:");
	EntityRef e = GetEntity();
	int i = 0;
	for (ComponentRef& comp : e->GetComponents().GetValues()) {
		if (comp) {
			ComponentBase& base = *comp;
			FusionComponent* fcomp = dynamic_cast<FusionComponent*>(&base);
			if (fcomp) {
				LOG("\t" << i++ << ": FusionComponent: " << fcomp->ToString());
			}
			else {
				LOG("\t" << i++ << ": " << base.GetType().DemangledName());
			}
		}
	}
}

void FusionContextComponent::PostLoadFileAny(String path) {
	Object content;
	if (LoadFileAny(path, content)) {
		post_load = content;
	}
}

void FusionContextComponent::Reset() {
	stream.total_time.Reset();
}

void FusionContextComponent::Clear() {
	for(auto& comp : comps) {
		comp->Clear();
		if (comp->IsTypeTemporary())
			comp->GetECS().Destroy();
	}
	common_source.Clear();
	comps.Clear();
#if HAVE_OPENGL
	Ogl_ClearPipeline();
#endif
	last_error.Clear();
	post_load = Null;
	stream.Clear();
	is_open = false;
}

bool FusionContextComponent::Render() {
	if (is_open /*&& lock.TryEnter()*/ ) {
		ProcessStageQueue(MODE_DEFAULT);
		//lock.Leave();
		return true;
	}
	return false;
}

void FusionContextComponent::Play() {
	if (is_open)
		ProcessStageQueue(MODE_AUDIO);
}

void FusionContextComponent::ProcessStageQueue(Mode m) {
	ASSERT(is_open);
	if (!is_open)
		return;
	
	RefreshStreamValues(m);
	
	for(auto& comp : comps) {
		if (IsModeStage(*comp, m))
			comp->PreProcess();
	}
	
	int i = 0;
	for(FusionComponentRef& comp : comps) {
		if (IsModeStage(*comp, m)) {
#if HAVE_OPENGL
			Ogl_ProcessStage(*comp, gl_stages[i]);
#endif
		}
	}
	
	for(FusionComponentRef& comp : comps) {
		if (IsModeStage(*comp, m))
			comp->PostProcess();
	}
	
}

bool FusionContextComponent::IsModeStage(const FusionComponent& comp, Mode m) const {
	auto type = comp.GetFusionType();
	if (type == FusionComponent::FUSION_AUDIO_SINK ||
		type == FusionComponent::FUSION_AUDIO_BUFFER ||
		type == FusionComponent::FUSION_AUDIO_SOURCE)
		return m == MODE_AUDIO;
	else
		return m == MODE_DEFAULT;
}

void FusionContextComponent::RefreshStreamValues(Mode m) {
	if (m == MODE_DEFAULT) {
		stream.time = GetSysTime();
		#ifdef flagWIN32
		{
			SYSTEMTIME time;
			GetLocalTime(&time);
			stream.time_us = time.wMilliseconds * 1000;
		}
		#else
		{
			struct timeval start;
			gettimeofday(&start, NULL);
			stream.time_us = start.tv_usec;
		}
		#endif
		stream.vtotal_seconds = stream.total_time.Seconds();
		stream.frame_seconds = stream.vframe_time.Seconds();
	}
	else if (m == MODE_AUDIO) {
		if (stream.asink_frame == 0 || stream.is_audio_sync) {
			stream.audio_last_sync_sec = stream.total_time.Seconds();
			stream.atotal_seconds = stream.audio_last_sync_sec;
			stream.is_audio_sync = true;
			stream.aframes_after_sync = 0;
		}
		else {
			ASSERT(stream.aud_fmt.sample_rate != 0);
			int samples_after_last_sync =
				stream.aframes_after_sync * stream.aud_fmt.sample_rate;
			//DUMP(samples_after_last_sync);
			stream.atotal_seconds =
				stream.audio_last_sync_sec +
				(float)samples_after_last_sync / (float)stream.aud_fmt.freq;
			stream.is_audio_sync = false;
		}
	}
}

RefT_Entity<FusionComponent> FusionContextComponent::GetComponentById(int id) const {
	ASSERT(id >= 0);
	for (const auto& s : comps)
		if (s->id == id)
			return s;
	throw Exc("FusionComponent not found");
}

bool FusionContextComponent::LoadFileAny(String path, Object& dst) {
	if (DirectoryExists(path)) {
		if (path.Right(1) == DIR_SEPS)
			path = path.Left(path.GetCount()-1);
		String title = GetFileName(path);
		path = AppendFileName(path, title + ".toy");
	}
	
	String ext = GetFileExt(path);
	
	if (ext == ".toy")
		return LoadFileToy(path, dst);
	
	return false;
}

bool FusionContextComponent::LoadFileToy(String path, Object& dst) {
	const char* fn_name = "LoadFileToy";
	Clear();
	
	String file_dir = GetFileDirectory(path);
	
	if (!FileExists(path)) {
		OnError(fn_name, "file doesn't exist");
		return false;
	}
	try {
		dst = ParseJSON(LoadFile(path));
		
		ASSERT(dst.IsMap());
		ObjectMap& map = dst.GetMap();
		for(int i = 0; i < 100; i++) {
			String stage = "stage" + IntStr(i);
			String stage_file = AppendFileName(file_dir, "stage" + IntStr(i) + ".glsl");
			if (!FileExists(stage_file))
				break;
			String glsl = LoadFile(stage_file);
			if (glsl.IsEmpty())
				throw Exc("empty shader for stage " + IntStr(i));
			map.Add(IntStr(i), glsl);
		}
	}
	catch (Exc e) {
		OnError(fn_name, e);
		return false;
	}
	
	MakeUniqueIds(dst);
	
	return true;
}

void FusionContextComponent::OnError(FusionComponent::Type type, String fn, String msg) {
	LOG(FusionComponent::GetStringFromType(type) << ":" << fn << ": error: " << msg);
	last_error = msg;
	WhenError();
}

void FusionContextComponent::OnError(String fn, String msg) {
	LOG("FusionContextComponent::" << fn << ": error: " << msg);
	last_error = msg;
	WhenError();
}

void FusionContextComponent::MakeUniqueIds(Object& v) {
	if (!v.IsMap())
		return;
	//DLOG(GetObjectTreeString(v));
	ObjectMap& map = v.GetMap();
	Object& stages = map.GetAdd("stages", ObjectArray());
	if (!stages.IsArray())
		return;
	VectorMap<int,int> ids;
	ObjectArray& st_arr = stages.GetArray();
	VectorMap<int, Object> stage_ids;
	for(int i = 0; i < st_arr.GetCount(); i++) {
		int stage_id = -1;
		Object& st_el = st_arr.Get(i);
		if (st_el.IsMap()) {
			ObjectMap& st_map = st_el.GetMap();
			Object& inputs = st_map.GetAdd("inputs", ObjectArray());
			if (inputs.IsArray()) {
				ObjectArray& in_arr = inputs.GetArray();
				for(int i = 0; i < in_arr.GetCount(); i++) {
					Object& in_el = in_arr.Get(i);
					if (!in_el.IsMap())
						continue;
					ObjectMap& in_map = in_el.GetMap();
					int j = in_map.Find("id");
					if (j >= 0)
						in_map.SetAt(j, MakeUniqueId(ids, (int)in_map.GetObject(j).ToInt()));
				}
			}
			
			Object& outputs = st_map.GetAdd("outputs", ObjectArray());
			if (outputs.IsArray()) {
				ObjectArray& out_arr = outputs.GetArray();
				for(int i = 0; i < out_arr.GetCount(); i++) {
					Object& out_el = out_arr.Get(i);
					if (!out_el.IsMap())
						continue;
					ObjectMap& out_map = out_el.GetMap();
					int j = out_map.Find("id");
					if (j >= 0) {
						int id = MakeUniqueId(ids, (int)out_map.GetObject(j).ToInt());
						if (!i)
							stage_id = id;
						out_map.SetAt(j, id);
					}
				}
				if (out_arr.IsEmpty()) {
					ObjectMap map;
					stage_id = MakeUniqueId(ids, 10000 + i);
					map.Add("id", stage_id);
					out_arr.Add(map);
				}
			}
		}
		
		if (stage_id < 0)
			stage_id = MakeUniqueId(ids, 10000 + i);
		stage_ids.Add(stage_id);
	}
	
	for(int i = 0; i < stage_ids.GetCount(); i++) {
		int st_pos = map.Find(IntStr(i));
		ASSERT(st_pos >= 0);
		if (st_pos >= 0) {
			stage_ids[i] = map.GetObject(st_pos);
			map.Remove(st_pos);
		}
	}
	
	DLOG("FusionContextComponent::MakeUniqueIds: result");
	DLOG(GetObjectTreeString(v));
	for(int i = 0; i < stage_ids.GetCount(); i++) {
		DLOG("\t" << stage_ids.GetKey(i) << ": <source>");
	}
	
	for(int i = 0; i < stage_ids.GetCount(); i++) {
		int id = stage_ids.GetKey(i);
		map.Add(IntStr(id), stage_ids[i]);
	}
	
}

int FusionContextComponent::MakeUniqueId(VectorMap<int,int>& ids, int orig_id) {
	if (orig_id < 0)
		return -1;
	int i = ids.Find(orig_id);
	if (i >= 0)
		return ids[i];
	int id = ++id_counter;
	ids.Add(orig_id, id);
	return id;
}

bool FusionContextComponent::Load(Object json) {
	DLOG("FusionContextComponent::Load");
	const char* fn_name = "Load";
	if (!json.IsMap()) {
		OnError(fn_name, "invalid json");
		return false;
	}
	
	Index<String> dirs;
	dirs.Add( ShareDirFile("imgs") );
	dirs.Add( ShareDirFile("sounds") );
	dirs.Add( ShareDirFile("videos") );
	
	ObjectMap& map = json.GetMap();
	
	stream.name = map.GetAdd("name", "unnamed").ToString();
	stream.description = map.GetAdd("description", "").ToString();
	
	Object& stages = map.GetAdd("stages", ObjectArray());
	if (!stages.IsArray()) {
		OnError(fn_name, "no stages in");
		return false;
	}
	ObjectArray& st_arr = stages.GetArray();
	for(int i = 0; i < st_arr.GetCount(); i++) {
		Object& st_el = st_arr.Get(i);
		if (!st_el.IsMap()) {
			OnError(fn_name, "unexpected element in stages");
			return false;
		}
		
		ObjectMap& st_map = st_el.GetMap();
		
		String frag_code;
		Object& outputs = st_map.GetAdd("outputs", ObjectArray());
		if (outputs.IsArray()) {
			ObjectArray& out_arr = outputs.GetArray();
			for(int i = 0; i < out_arr.GetCount(); i++) {
				Object& out_el = out_arr.Get(i);
				if (!out_el.IsMap())
					continue;
				ObjectMap& out_map = out_el.GetMap();
				int j = out_map.Find("id");
				if (j >= 0) {
					int id = (int)out_map.GetObject(j).ToInt();
					frag_code = map.GetAdd(IntStr(id)).ToString();
				}
			}
		}
		
		String type_str = st_map.TryGet("type", "").ToString();
		
		if (type_str == "imagebuf" && st_arr.GetCount() == 1)
			type_str = "image";
		
		if (type_str == "library") {
			common_source.Add(frag_code);
		}
		else {
			FusionComponent::Type type = FusionComponent::GetTypeFromString(type_str);
			if (type == FusionComponent::FUSION_INVALID) {
				OnError(fn_name, "Invalid type string '" + type_str + "'");
				return false;
			}
			
			if (FusionComponent::IsTypeTemporary(type)) {
				
				// Create new comp
				RefT_Entity<FusionComponent> comp;
				switch (type) {
					case FusionComponent::FUSION_DATA_SINK:			comp = AddEntityComponent<FusionDataSink>(); break;
					//case FusionComponent::FUSION_CTRL_SOURCE:		comp = AddEntityComponent<FusionControllerSource>(); break;
					//case FusionComponent::FUSION_CTRL_BUFFER:		comp = AddEntityComponent<FusionControllerBuffer>(); break;
					case FusionComponent::FUSION_CTRL_SINK:			comp = AddEntityComponent<FusionControllerSink>(); break;
					case FusionComponent::FUSION_DISPLAY_SOURCE:	comp = AddEntityComponent<FusionDisplaySource>(); break;
					case FusionComponent::FUSION_DISPLAY_BUFFER:	comp = AddEntityComponent<FusionDisplayBuffer>(); break;
					//case FusionComponent::FUSION_DISPLAY_SINK:	comp = AddEntityComponent<FusionDisplaySink>(); break;
					case FusionComponent::FUSION_AUDIO_SOURCE:		comp = AddEntityComponent<FusionAudioSource>(); break;
					//case FusionComponent::FUSION_AUDIO_BUFFER:	comp = AddEntityComponent<FusionAudioBuffer>(); break;
					//case FusionComponent::FUSION_AUDIO_SINK:		comp = AddEntityComponent<FusionAudioSink>(); break;
					
					case FusionComponent::FUSION_INVALID:
					case FusionComponent::FUSION_TYPE_COUNT:
						OnError(fn_name, "Invalid fusion component type");
						
					default:
						OnError(fn_name, "Unimplemented fusion component type");
				}
				if (!comp)
					return false;
				
				if (!comp->Load(st_map, i, frag_code)) {
					comp->GetECS().Destroy();
					OnError(fn_name, "Loading stage " + IntStr(i) + " failed");
					return false;
				}
				
				for(AcceleratorHeader& in : comp->in) {ASSERT(in.GetId() < 0 || in.GetType() == AcceleratorHeader::BUFFER);}
				
				comps.Add(comp);
			}
			else {
				// Find existing component
				bool found = false;
				for (auto& comp : comps) {
					if (comp->GetFusionType() == type) {
						if (!comp->Load(st_map, i, frag_code)) {
							OnError(fn_name, "Loading stage " + IntStr(i) + " failed");
							return false;
						}
						found = true;
						break;
					}
				}
				if (!found) {
					OnError(fn_name, "did not find existing component for persistent type '" + type_str + "'");
					return false;
				}
			}
		}
	}
	
	// Find unique inputs
	AcceleratorHeaderVector v;
	for (auto& comp : comps)
		for(AcceleratorHeader& in : comp->in)
			if (/*in.IsTypeComponentSource() &&*/ v.Find(in) < 0)
				v.Add(in);
	
	if (v.in.GetCount()) {
		// Create components for unique inputs
		if (!CreateComponents(v))
			return false;
		
		// Connect created components for inputs
		DumpEntityComponents();
		for (auto& comp : comps) {
			for(AcceleratorHeader& in : comp->in) {
				if (in.IsTypeComponentSource()) {
					int i = v.Find(in);
					ASSERT(i >= 0);
					AcceleratorHeader& found = v.in[i];
					ASSERT(in.GetId() < 0);
					in.CopyIdStream(found);
					ASSERT(in.GetId() >= 0);
				}
			}
		}
		
		// Connect inputs
		if (!ConnectComponents())
			return false;
	}
	
	return true;
}

void FusionContextComponent::RefreshStageQueue() {
	DLOG("FusionContextComponent::RefreshStageQueue: begin");
	
	try {
		// Solve dependencies
		Graph g;
		for(auto& s : comps)
			if (s->id >= 0)
				g.AddKey(s->id);
		for(const FusionComponentRef& s : comps) {
			if (s->id >= 0) {
				for(int j = 0; j < s->in.GetCount(); j++) {
					const AcceleratorHeader& in = s->in[j];
					if (in.GetId() >= 0)
						g.AddEdgeKey(in.GetId(), s->id);
				}
			}
		}
		g.TopologicalSort();
		
		#if 0
		DLOG("\ttopologically sorted stage list:");
		for(int i = 0; i < g.GetSortedCount(); i++) {
			DLOG("\t\t" << i << ": " << g.GetKey(i).ToString());
		}
		#endif
		
		struct TopologicalStages {
			Graph& g;
			bool operator()(const RefT_Entity<FusionComponent>& a, const RefT_Entity<FusionComponent>& b) const {
				int a_pos = g.FindSorted(a->id);
				int b_pos = g.FindSorted(b->id);
				return a_pos < b_pos;
			}
		};
		TopologicalStages sorter {g};
		TODO
		//Sort(comps, sorter);
		
		#if 1
		DLOG("\ttopologically sorted stage list:");
		for(int i = 0; i < comps.GetCount(); i++) {
			DLOG("\t\t" << i << ": " << comps[i]->ToString());
		}
		#endif
	}
	catch (Exc e) {
		OnError("RefreshStageQueue", "Topological stage sorting failed: " + e);
		Close();
	}
	
	DLOG("FusionContextComponent::RefreshStageQueue: end");
}

void FusionContextComponent::RefreshPipeline() {
	DLOG("FusionContextComponent::RefreshPipeline begin");
	
#if HAVE_OPENGL
	Ogl_CreatePipeline();
#endif
	
	UpdateTexBuffers();
	UpdateSoundBuffers();
	
	if (!CheckInputTextures()) {
		Close();
		return;
	}
	
	for(auto& comp : comps)
		comp->Reset();
	
	DLOG("FusionContextComponent::RefreshPipeline end");
}

void FusionContextComponent::UpdateTexBuffers() {
	for(auto& comp : comps)
		if (comp->type != FusionComponent::FUSION_AUDIO_SINK &&
			comp->type != FusionComponent::FUSION_AUDIO_BUFFER &&
			comp->type != FusionComponent::FUSION_AUDIO_SOURCE)
				comp->UpdateTexBuffers();
}

void FusionContextComponent::UpdateSoundBuffers() {
	for(auto& comp : comps)
		if (comp->type == FusionComponent::FUSION_AUDIO_SINK ||
			comp->type == FusionComponent::FUSION_AUDIO_BUFFER ||
			comp->type == FusionComponent::FUSION_AUDIO_SOURCE)
				comp->UpdateTexBuffers();
}

bool FusionContextComponent::CheckInputTextures() {
#if HAVE_OPENGL
	for(auto& comp : comps)
		if (!comp->Ogl_CheckInputTextures())
			return false;
#endif
	return true;
}

void FusionContextComponent::Close() {
	for(auto& comp : comps)
		comp->Close();
	Clear();
}

bool FusionContextComponent::CreateComponents(AcceleratorHeaderVector& v) {
	const char* fn_name = "CreateComponents";
	
	for(AcceleratorHeader& in : v.in) {
		switch (in.GetType()) {
		case AcceleratorHeader::TEXTURE:
		case AcceleratorHeader::CUBEMAP:
		case AcceleratorHeader::VOLUME:
			if (!AddEntityFusionComponent<FusionDataSink>(in))
				return false;
			break;
			
		case AcceleratorHeader::WEBCAM:
		case AcceleratorHeader::VIDEO:
		case AcceleratorHeader::MUSIC:
		case AcceleratorHeader::MUSICSTREAM:
			if (!AddEntityFusionComponent<FusionMediaSink>(in))
				return false;
			break;
			
		case AcceleratorHeader::KEYBOARD:
			if (!AddEntityFusionComponent<FusionControllerSink>(in))
				return false;
			break;
			
		case AcceleratorHeader::EMPTY:
		case AcceleratorHeader::BUFFER:
			break;
			
		case AcceleratorHeader::INVALID:
			OnError(fn_name, "Invalid type");
			return false;
		}
		
	}
	return true;
}

bool FusionContextComponent::ConnectComponents() {
	const char* fn_name = "ConnectComponents";
	bool succ = true;
	
	DumpEntityComponents();
	DLOG("Component vector:");
	for(int i = 0; i < comps.GetCount(); i++) {
		DLOG("\t" << i << ": " << comps[i]->ToString());
	}
	
	for (Ref<FusionComponent>& comp_sink : comps) {
		ComponentBase& sink_base = comp_sink->GetECS();
		Ref<AcceleratorSink> sink = sink_base.AsAcceleratorSink();
		if (!sink)
			continue;
		ASSERT(sink->GetConnections().IsEmpty());
		
		for (const AcceleratorHeader& in : comp_sink->in) {
			if (in.IsTypeEmpty())
				continue;
			
			bool found = false;
			for (Ref<FusionComponent>& comp_src : comps) {
				ComponentBase& src_base = comp_src->GetECS();
				Ref<AcceleratorSource> src = src_base.AsAcceleratorSource();
				
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
				OnError(fn_name, "could not find AcceleratorSource for input sink " + comp_sink->ToString() + ", " + in.ToString());
				succ = false;
				break;
			}
		}
		
		if (!succ) break;
	}
	
	return succ;
}


NAMESPACE_TOPSIDE_END
