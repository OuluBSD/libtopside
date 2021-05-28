#include "AccelCore.h"

NAMESPACE_TOPSIDE_BEGIN


int AccelContextComponent::id_counter;


void AccelContextComponent::Initialize() {
	DLOG("AccelContextComponent::Initialize");
	Ref<AccelSystem> fusion_sys = GetEntity()->GetMachine().Get<AccelSystem>();
	if (fusion_sys)
		fusion_sys	-> Add(AsRef<AccelContextComponent>());
	
}

void AccelContextComponent::Uninitialize() {
	Ref<AccelSystem> fusion_sys = GetEntity()->GetMachine().Get<AccelSystem>();
	if (fusion_sys)
		fusion_sys	-> Remove(AsRef<AccelContextComponent>());
}

void AccelContextComponent::Update(double dt) {
	DLOG("AccelContextComponent::Update: begin");
	
	//lock.Enter();
	
	if (!post_load.IsVoid()) {
		DLOG("AccelContextComponent::Update: load new program");
		
		Object to_load;
		Swap(post_load, to_load);
		
		for(AccelComponentGroup& g : groups)
			g.CloseTemporary();
		
		Clear();
		FindComponents();
		DumpEntityComponents();
		
		Load(to_load);
		Reset();
		
		//  Reload stage pointers
		if (!RefreshStageQueue())
			return;
		DumpEntityComponents();
		
		is_open = true;
		for(AccelComponentGroup& g : groups)
			if (!g.Open())
				{is_open = false; break;}
		
		if (!is_open) {
			DLOG("AccelContextComponent::Update: error: did not open properly");
			return;
		}
		
		RefreshPipeline();
	}
	
	//lock.Leave();
	
	DLOG("AccelContextComponent::Update: end");
}


void AccelContextComponent::FindComponents() {
	for(AccelComponentGroup& g : groups)
		g.FindComponents();
}

void AccelContextComponent::DumpEntityComponents() {
	LOG("Entity: AccelComponents:");
	EntityRef e = GetEntity();
	int i = 0;
	for (ComponentRef& comp : e->GetComponents().GetValues()) {
		if (comp) {
			ComponentBase& base = *comp;
			AccelComponent* fcomp = CastPtr<AccelComponent>(&base);
			if (fcomp) {
				LOG("\t" << i++ << ": AccelComponent: " << fcomp->ToString());
			}
			else {
				LOG("\t" << i++ << ": " << base.GetDynamicName());
			}
		}
	}
}

void AccelContextComponent::PostLoadFileAny(String path) {
	Object content;
	if (LoadFileAny(path, content)) {
		post_load = content;
	}
}

void AccelContextComponent::Reset() {
	stream.total_time.Reset();
}

void AccelContextComponent::Clear() {
	for(auto& comp : groups) {
		comp.Clear();
		//if (comp->IsTypeTemporary())
		//	comp->GetECS().Destroy();
	}
	common_source.Clear();
	groups.Clear();
#if HAVE_OPENGL
	Ogl_ClearPipeline();
#endif
	last_error.Clear();
	post_load = Null;
	stream.Clear();
	is_open = false;
	
	AddDefaultGroups();
}

void AccelContextComponent::AddDefaultGroups() {
	AccelComponentGroup& video = groups.Add();
	video.SetParent(this);
	video.AddContext<VideoContext>();
	video.AddContext<DisplayContext>();
	video.AddContext<PhotoContext>();
	video.AddContext<DeviceContext>();
	
	AccelComponentGroup& audio = groups.Add();
	audio.SetParent(this);
	audio.AddContext<AudioContext>();
	audio.AddContext<DeviceContext>();
}

bool AccelContextComponent::Render() {
	TODO
	#if 0
	if (is_open /*&& lock.TryEnter()*/ ) {
		ProcessStageQueue(MODE_DEFAULT);
		//lock.Leave();
		return true;
	}
	return false;
	#endif
}

/*void AccelContextComponent::Play() {
	TODO
	#if 0
	if (is_open)
		ProcessStageQueue(MODE_AUDIO);
	#endif
}*/

void AccelContextComponent::ProcessStageQueue(TypeCls m) {
	TODO
	#if 0
	ASSERT(is_open);
	if (!is_open)
		return;
	
	RefreshStreamValues(m);
	
	
	for(auto& comp : comps) {
		if (IsModeStage(*comp, m))
			comp->PreProcess();
	}
	
	int i = 0;
	for(AccelComponentRef& comp : comps) {
		if (IsModeStage(*comp, m)) {
#if HAVE_OPENGL
			Ogl_ProcessStage(*comp, gl_stages[i]);
#endif
		}
	}
	
	for(AccelComponentRef& comp : comps) {
		if (IsModeStage(*comp, m))
			comp->PostProcess();
	}
	
	#endif
}

/*bool AccelContextComponent::IsModeStage(ComponentBaseRef comp, TypeCls m) const {
	auto type = comp.GetAccelType();
	if (type == AccelComponent::FUSION_AUDIO_SINK ||
		type == AccelComponent::FUSION_AUDIO_BUFFER ||
		type == AccelComponent::FUSION_AUDIO_SOURCE)
		return m == MODE_AUDIO;
	else
		return m == MODE_DEFAULT;
}*/

void AccelContextComponent::RefreshStreamValues(TypeCls m) {
	TODO
	#if 0
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
	#endif
}

/*ComponentBaseRef AccelContextComponent::GetComponentById(int id) const {
	TODO
	#if 0
	ASSERT(id >= 0);
	for (const auto& s : comps)
		if (s->id == id)
			return s;
	THROW(Exc("AccelComponent not found"));
	#endif
}*/

bool AccelContextComponent::LoadFileAny(String path, Object& dst) {
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

bool AccelContextComponent::LoadFileToy(String path, Object& dst) {
	const char* fn_name = "LoadFileToy";
	Clear();
	
	String file_dir = GetFileDirectory(path);
	
	if (!FileExists(path)) {
		OnError(fn_name, "file doesn't exist");
		return false;
	}
	
	bool fail = false;
	dst = ParseJSON(LoadFile(path));
	
	ASSERT(dst.IsMap());
	ObjectMap& map = dst.GetMap();
	for(int i = 0; i < 100; i++) {
		String stage = "stage" + IntStr(i);
		String stage_file = AppendFileName(file_dir, "stage" + IntStr(i) + ".glsl");
		if (!FileExists(stage_file))
			break;
		String glsl = LoadFile(stage_file);
		if (glsl.IsEmpty()) {
			fail = true;
			last_error = "empty shader for stage " + IntStr(i);
		}
		else {
			map.Add(IntStr(i), glsl);
		}
	}
	
	if (fail) {
		OnError(fn_name, last_error);
		return false;
	}
	
	MakeUniqueIds(dst);
	
	return true;
}

void AccelContextComponent::OnError(TypeCls type, String fn, String msg) {
	LOG(AccelComponent::GetStringFromType(type) << ":" << fn << ": error: " << msg);
	last_error = msg;
	WhenError();
}

void AccelContextComponent::OnError(String fn, String msg) {
	LOG("AccelContextComponent::" << fn << ": error: " << msg);
	last_error = msg;
	WhenError();
}

void AccelContextComponent::MakeUniqueIds(Object& v) {
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
	
	DLOG("AccelContextComponent::MakeUniqueIds: result");
	DLOG(GetObjectTreeString(v));
	for(int i = 0; i < stage_ids.GetCount(); i++) {
		DLOG("\t" << stage_ids.GetKey(i) << ": <source>");
	}
	
	for(int i = 0; i < stage_ids.GetCount(); i++) {
		int id = stage_ids.GetKey(i);
		map.Add(IntStr(id), stage_ids[i]);
	}
	
}

int AccelContextComponent::MakeUniqueId(VectorMap<int,int>& ids, int orig_id) {
	if (orig_id < 0)
		return -1;
	int i = ids.Find(orig_id);
	if (i >= 0)
		return ids[i];
	int id = ++id_counter;
	ids.Add(orig_id, id);
	return id;
}

bool AccelContextComponent::Load(Object json) {
	DLOG("AccelContextComponent::Load");
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
			TypeCls type = AccelComponent::GetTypeFromString(type_str);
			if (type == AsVoidTypeCls()) {
				OnError(fn_name, "Invalid type string '" + type_str + "'");
				return false;
			}
			
			if (AccelComponent::IsTypeTemporary(type)) {
				AccelComponentGroup* group = 0;
				ASSERT(groups.GetCount());
				
				// Find group
				if (0)
					;
				#define IFACE(x) \
					else if (type == AsTypeCls<Accel##x##PipeComponent>()) group = FindGroupContext<x##Context>(); \
					else if (type == AsTypeCls<Accel##x##ConvertInputComponent>()) group = FindGroupContext<x##Context>(); \
					else if (type == AsTypeCls<Accel##x##ConvertOutputComponent>()) group = FindGroupContext<x##Context>();
				IFACE_LIST
				#undef IFACE
				if (!group) {
					OnError(fn_name, "No group exists for type '" + type_str + "'");
					return false;
				}
				
				// Create new comp
				RefT_Entity<AccelComponent> comp;
				if (0)
					;
				#define IFACE(x) \
					else if (type == AsTypeCls<Accel##x##PipeComponent>()) comp = AddEntityComponent<Accel##x##PipeComponent>(*group); \
					else if (type == AsTypeCls<Accel##x##ConvertInputComponent>()) comp = AddEntityComponent<Accel##x##ConvertInputComponent>(*group); \
					else if (type == AsTypeCls<Accel##x##ConvertOutputComponent>()) comp = AddEntityComponent<Accel##x##ConvertOutputComponent>(*group);
				IFACE_LIST
				#undef IFACE
			/*	switch (type) {
					case AccelComponent::FUSION_DATA_SINK:			comp = AddEntityComponent<AccelDataSink>(); break;
					//case AccelComponent::FUSION_CTRL_SOURCE:		comp = AddEntityComponent<AccelControllerSource>(); break;
					//case AccelComponent::FUSION_CTRL_BUFFER:		comp = AddEntityComponent<AccelControllerBuffer>(); break;
					case AccelComponent::FUSION_CTRL_SINK:			comp = AddEntityComponent<AccelControllerSink>(); break;
					case AccelComponent::FUSION_DISPLAY_SOURCE:	comp = AddEntityComponent<AccelDisplaySource>(); break;
					case AccelComponent::FUSION_DISPLAY_BUFFER:	comp = AddEntityComponent<AccelDisplayBuffer>(); break;
					//case AccelComponent::FUSION_DISPLAY_SINK:	comp = AddEntityComponent<AccelDisplaySink>(); break;
					case AccelComponent::FUSION_AUDIO_SOURCE:		comp = AddEntityComponent<AccelAudioSource>(); break;
					//case AccelComponent::FUSION_AUDIO_BUFFER:	comp = AddEntityComponent<AccelAudioBuffer>(); break;
					//case AccelComponent::FUSION_AUDIO_SINK:		comp = AddEntityComponent<AccelAudioSink>(); break;
					
					case AccelComponent::FUSION_INVALID:
					case AccelComponent::FUSION_TYPE_COUNT:
						OnError(fn_name, "Invalid accel component type");
						
					default:
						OnError(fn_name, "Unimplemented accel component type");
				}*/
				if (!comp)
					return false;
				
				if (!comp->Load(st_map, i, frag_code)) {
					comp->AsRef<ComponentBase>()->GetEntity()->Destroy();
					OnError(fn_name, "Loading stage " + IntStr(i) + " failed");
					return false;
				}
				
				for(AcceleratorHeader& in : comp->in) {ASSERT(in.GetId() < 0 || in.GetType() == AcceleratorHeader::TYPE_BUFFER);}
			}
			else {
				// Find existing component
				bool found = false;
				for (auto& group : groups)
					if ((found = group.LoadExisting(type, st_map, i, frag_code)))
						break;
				if (!found) {
					OnError(fn_name, "did not find existing component for persistent type '" + type_str + "'");
					return false;
				}
			}
		}
	}
	
	// Find unique inputs
	AcceleratorHeaderVector v;
	for (AccelComponentGroup& g : groups)
		g.FindUniqueInputs(v);
	
	
	if (v.in.GetCount()) {
		// Create components for unique inputs
		if (!CreateComponents(v))
			return false;
		
		// Connect created components for inputs
		DumpEntityComponents();
		for (auto& group : groups)
			group.ConnectInputs(v);
		
		// Connect inputs
		if (!ConnectComponents())
			return false;
	}
	
	return true;
}

bool AccelContextComponent::RefreshStageQueue() {
	DLOG("AccelContextComponent::RefreshStageQueue: begin");
	
	// Solve dependencies
	
	Graph g;
	for(auto& gr : groups)
		for(auto& s : gr.comps)
			if (s->id >= 0)
				g.AddKey(s->id);
	for(auto& gr : groups) {
		for(const AccelComponentRef& s : gr.comps) {
			if (s->id >= 0) {
				for(const AcceleratorHeader& in : s->in) {
					if (in.GetId() >= 0)
						g.AddEdgeKey(in.GetId(), s->id);
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
		bool operator()(const RefT_Entity<AccelComponent>& a, const RefT_Entity<AccelComponent>& b) const {
			int a_pos = g.FindSorted(a->id);
			int b_pos = g.FindSorted(b->id);
			return a_pos < b_pos;
		}
	};
	TopologicalStages sorter {{},g};
	
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
	
	
	DLOG("AccelContextComponent::RefreshStageQueue: end");
	return true;
}

void AccelContextComponent::RefreshPipeline() {
	DLOG("AccelContextComponent::RefreshPipeline begin");
	
#if HAVE_OPENGL
	Ogl_CreatePipeline();
#endif
	
	for(auto& gr : groups)
		gr.UpdateBuffers();
	
	if (!CheckInputTextures()) {
		Close();
		return;
	}
	
	for(auto& gr : groups)
		for(auto& comp : gr.comps)
			comp->Reset();
	
	DLOG("AccelContextComponent::RefreshPipeline end");
}

bool AccelContextComponent::CheckInputTextures() {
	for(auto& gr : groups)
		if (!gr.CheckInputTextures())
			return false;
	return true;
}

void AccelContextComponent::Close() {
	for(auto& gr : groups)
		for(auto& comp : gr.comps)
			comp->Close();
	Clear();
}

bool AccelContextComponent::CreateComponents(AcceleratorHeaderVector& v) {
	const char* fn_name = "CreateComponents";
	
	for(AcceleratorHeader& in : v.in) {
		switch (in.GetType()) {
		case AcceleratorHeader::TYPE_TEXTURE:
		case AcceleratorHeader::TYPE_CUBEMAP:
		case AcceleratorHeader::TYPE_VOLUME:
			if (!AddEntityAccelComponent<PhotoContext, AccelPhotoConvertInputComponent>(in))
				return false;
			break;
			
		case AcceleratorHeader::TYPE_WEBCAM:
		case AcceleratorHeader::TYPE_VIDEO:
		case AcceleratorHeader::TYPE_MUSIC:
		case AcceleratorHeader::TYPE_MUSICSTREAM:
			if (!AddEntityAccelComponent<VideoContext, AccelVideoConvertInputComponent>(in))
				return false;
			break;
			
		case AcceleratorHeader::TYPE_KEYBOARD:
			if (!AddEntityAccelComponent<DeviceContext, AccelDeviceConvertInputComponent>(in))
				return false;
			break;
			
		case AcceleratorHeader::TYPE_EMPTY:
		case AcceleratorHeader::TYPE_BUFFER:
			break;
			
		case AcceleratorHeader::TYPE_INVALID:
		default:
			OnError(fn_name, "Invalid type");
			return false;
		}
		
	}
	return true;
}

bool AccelContextComponent::ConnectComponents() {
	TODO
	#if 0
	const char* fn_name = "ConnectComponents";
	bool succ = true;
	
	DumpEntityComponents();
	DLOG("Component vector:");
	int i = 0;
	for(auto& comp : comps) {
		DLOG("\t" << i << ": " << comp->ToString());
	}
	
	for (Ref<AccelComponent>& comp_sink : comps) {
		ComponentBase& sink_base = comp_sink->GetECS();
		Ref<AcceleratorSink> sink = sink_base.AsAcceleratorSink();
		if (!sink)
			continue;
		ASSERT(sink->GetConnections().IsEmpty());
		
		for (const AcceleratorHeader& in : comp_sink->in) {
			if (in.IsTypeEmpty())
				continue;
			
			bool found = false;
			for (Ref<AccelComponent>& comp_src : comps) {
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
	#endif
}


NAMESPACE_TOPSIDE_END
