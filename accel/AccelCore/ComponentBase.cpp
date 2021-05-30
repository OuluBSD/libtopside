#include "AccelCore.h"

NAMESPACE_TOPSIDE_BEGIN


ArrayMap<String,String>& CommonHashToName() {
	static ArrayMap<String,String> map;
	if (map.IsEmpty()) {
		map.Add("85a6d68622b36995ccb98a89bbb119edf167c914660e4450d313de049320005c", "grid");
		map.Add("cbcbb5a6cfb55c36f8f021fbb0e3f69ac96339a39fa85cd96f2017a2192821b5", "nyan");
		map.Add("0681c014f6c88c356cf9c0394ffe015acc94ec1474924855f45d22c3e70b5785", "bg1");
		map.Add("793a105653fbdadabdc1325ca08675e1ce48ae5f12e37973829c87bea4be3232", "bg2");
		map.Add("0a40562379b63dfb89227e6d172f39fdce9022cba76623f1054a2c83d6c0ba5d", "noise1");
		map.Add("550a8cce1bf403869fde66dddf6028dd171f1852f4a704a465e1b80d23955663", "bg3");
		map.Add("3083c722c0c738cad0f468383167a0d246f91af2bfa373e9c5c094fb8c8413e0", "noise2");
		map.Add("27012b4eadd0c3ce12498b867058e4f717ce79e10a99568cca461682d84a4b04", "noise3");
		map.Add("488bd40303a2e2b9a71987e48c66ef41f5e937174bf316d3ed0e86410784b919", "bg4");
		map.Add("95b90082f799f48677b4f206d856ad572f1d178c676269eac6347631d4447258", "metal");
		map.Add("0c7bf5fe9462d5bffbd11126e82908e39be3ce56220d900f633d58fb432e56f5", "noise4");
		map.Add("10eb4fe0ac8a7dc348a2cc282ca5df1759ab8bf680117e4047728100969e7b43", "stonewall");
		map.Add("e6e5631ce1237ae4c05b3563eda686400a401df4548d0f9fad40ecac1659c46c", "wall");
		map.Add("8de3a3924cb95bd0e95a443fff0326c869f9d4979cd1d5b6e94e2a01f5be53e9", "uk_street");
		map.Add("585f9546c092f53ded45332b343144396c0b2d70d9965f585ebc172080d8aa58", "yard");
		map.Add("94284d43be78f00eb6b298e6d78656a1b34e2b91b34940d02f1ca8b22310e8a0", "bg5");
		map.Add("ad56fba948dfba9ae698198c109e71f118a54d209c0ea50d77ea546abad89c57", "stone1");
		map.Add("52d2a8f514c4fd2d9866587f4d7b2a5bfa1a11a0e772077d7682deb8b3b517e5", "stone2");
		map.Add("aea6b99da1d53055107966b59ac5444fc8bc7b3ce2d0bbb6a4a3cbae1d97f3aa", "noise5");
		map.Add("bd6464771e47eed832c5eb2cd85cdc0bfc697786b903bfd30f890f9d4fc36657", "brown_grid");
		map.Add("1f7dca9c22f324751f2a5a59c9b181dfe3b5564a04b724c657732d0bf09c99db", "wood1");
		map.Add("92d7758c402f0927011ca8d0a7e40251439fba3a1dac26f5b8b62026323501aa", "stone3");
		map.Add("cd4c518bc6ef165c39d4405b347b51ba40f8d7a065ab0e8d2e4f422cbc1e8a43", "stone4");
		map.Add("8979352a182bde7c3c651ba2b2f4e0615de819585cc37b7175bcefbca15a6683", "stone5");
		map.Add("fb918796edc3d2221218db0811e240e72e340350008338b0c07a52bd353666a6", "wood2");
		map.Add("f735bee5b64ef98879dc618b016ecf7939a5756040c2cde21ccb15e69a6e1cfb", "noise6");
		map.Add("3871e838723dd6b166e490664eead8ec60aedd6b8d95bc8e2fe3f882f0fd90f0", "stone6");
		map.Add("79520a3d3a0f4d3caa440802ef4362e99d54e12b1392973e4ea321840970a88a", "stone7");
		map.Add("08b42b43ae9d3c0605da11d0eac86618ea888e62cdd9518ee8b9097488b31560", "alphabet");
		map.Add("3c33c415862bb7964d256f4749408247da6596f2167dca2c86cc38f83c244aa6", "toymusic");
		map.Add("29de534ed5e4a6a224d2dfffab240f2e19a9d95f5e39de8898e850efdb2a99de", "toymusic");
		map.Add("48e2d9ef22ca6673330b8c38a260c87694d2bbc94c19fec9dfa4a1222c364a99", "toymusic");
		map.Add("894a09f482fb9b2822c093630fc37f0ce6cfec02b652e4e341323e4b6e4a4543", "toymusic");
		map.Add("a6a1cf7a09adfed8c362492c88c30d74fb3d2f4f7ba180ba34b98556660fada1", "toymusic");
		map.Add("d96b229eeb7a08d53adfcf1ff89e54c9ffeebed193d317d1a01cc8125c0f5cca", "toymusic");
		map.Add("ec8a6ea755d34600547a5353f21f0a453f9f55ff95514383b2d80b8d71283eda", "toymusic");
		map.Add("3405e48f74815c7baa49133bdc835142948381fbe003ad2f12f5087715731153", "oldie");
		map.Add("c3a071ecf273428bc72fc72b2dd972671de8da420a2d4f917b75d20e1c24b34c", "img_forces");
		map.Add("35c87bcb8d7af24c54d41122dadb619dd920646a0bd0e477e7bdc6d12876df17", "van_damme");
		map.Add("e81e818ac76a8983d746784b423178ee9f6cdcdf7f8e8d719341a6fe2d2ab303", "britney");
	}
	return map;
}






const char* AccelComponent::names[VAR_COUNT+1] = {
	#define ACCEL_VAR(v, n) n,
	ACCEL_VAR_LIST
	#undef ACCEL_VAR
	0
};


AccelComponent::AccelComponent() {
	DLOG("AccelComponent::AccelComponent: constructing")
}

AccelComponent::~AccelComponent() {
	DLOG("AccelComponent::~AccelComponent: destructing")
}

void AccelComponent::Update0(double dt) {
	if (!ctx && IsOpen())
		Close();
	else
		Update(dt);
}

bool AccelComponent::IsSinkInAccelerator() const {
	return IsContext(AsTypeCls<VideoContext>()) && ctx->IsLast(this);
}

bool AccelComponent::Open() {
	DLOG("AccelComponent(" << GetTypeString() << ")::Open: begin");
	const char* fn_name = "Open";
	if (!ctx) {OnError(fn_name, "no context"); return false;}
	
	if (is_open)
		Close();
	
	if (!LoadResources())
		return false;
	
#if HAVE_OPENGL
	if (!Ogl_CompilePrograms())
		return false;
	
	if (!Ogl_LinkStages())
		return false;
#endif
	
	DLOG("AccelComponent(" << GetTypeString() << ")::Open: end");
	is_open = true;
	return true;
}

void AccelComponent::Close() {
	DLOG("AccelComponent(" << GetTypeString() << ")::Close");
	
	if (is_open)
		is_open = false;
}

void AccelComponent::Initialize() {
	DLOG("AccelComponent(" << GetTypeString() << ")::Initialize");
	
	Ref<AccelSystem> accel_sys = CastRef<ComponentBase>(this).GetEntity()->GetMachine().Get<AccelSystem>();
	if (accel_sys)
		accel_sys	-> Add(AsRef<AccelComponent>());
}

void AccelComponent::Uninitialize() {
	DLOG("AccelComponent(" << GetTypeString() << ")::Uninitialize");
	
	if (ctx) {
		ctx->Remove(AsRefT());
		ctx.Clear();
	}
	
	Ref<AccelSystem> accel_sys = CastRef<ComponentBase>(this).GetEntity()->GetMachine().Get<AccelSystem>();
	if (accel_sys)
		accel_sys	-> Remove(AsRef<AccelComponent>());
	
	//Clear();
}

AccelStream* AccelComponent::Stream() {
	return ctx ? &ctx->stream : 0;
}

int AccelComponent::NewWriteBuffer() {
	if (is_doublebuf)
		buf_i = (buf_i + 1) % 2;
	return buf_i;
}

void AccelComponent::Clear() {
	DLOG("AccelComponent(" << GetTypeString() << ")::Clear");
	ClearData();
	
	name.Clear();
	description.Clear();
	for(int i = 0; i < PROG_COUNT; i++)
		code[i].Clear();
	id = -1;
	buf_i = 0;
	is_doublebuf = false;
	is_searched_vars = false;
	
	ClearTex();
	ClearProg();
}

void AccelComponent::ClearTex() {
#if HAVE_OPENGL
	Ogl_ClearTex();
#endif
}

void AccelComponent::ClearProg() {
#if HAVE_OPENGL
	Ogl_ClearProg();
#endif
}

bool AccelComponent::Load(ObjectMap& st_map, int stage_i, String frag_code) {
	const char* fn_name = "AccelComponent::Load";
	Clear();
	
	
	Index<String> dirs;
	dirs.Add( ShareDirFile("imgs") );
	dirs.Add( ShareDirFile("sounds") );
	dirs.Add( ShareDirFile("videos") );
	
	
	name = st_map.TryGet("name", "").ToString();
	description = st_map.TryGet("description", "").ToString();
	
	Object& inputs = st_map.GetAdd("inputs", ObjectArray());
	if (!inputs.IsArray()) {
		OnError(fn_name, "no inputs");
		return false;
	}
	ObjectArray& in_arr = inputs.GetArray();
	for(int i = 0; i < in_arr.GetCount(); i++) {
		Object& in_el = in_arr.Get(i);
		if (!in_el.IsMap())
			continue;
		ObjectMap& in_map = in_el.GetMap();
		AcceleratorHeader& in = this->in.Add();
		if (in_map.IsEmpty()) {
			in.SetType(AcceleratorHeader::TYPE_EMPTY);
			continue;
		}
		String path = in_map.TryGet("filename", "").ToString();
		
		in.Set(		(int)in_map.TryGet("id", -1).ToInt(), // TODO fix all of these, not safe now
					AcceleratorHeader::GetTypeFromString(in_map.TryGet("type", "").ToString()),
					path,
					AcceleratorHeader::GetFilterFromString(in_map.TryGet("filter", "linear").ToString()),
					AcceleratorHeader::GetWrapFromString(in_map.TryGet("wrap", "clamp").ToString()),
					ScanBoolString(in_map.TryGet("vflip", "false").ToString()));
		
		/*if (in.GetType() != AcceleratorHeader::TYPE_BUFFER) {
			in.SetId(-1);
		}*/
		
		if (path.GetCount() && GetFileDirectory(path).IsEmpty()) {
			String filename = GetFileName(path);
			String title = GetFileTitle(filename);
			filename = CommonHashToName().Get(title, title) + GetFileExt(filename);
			
			bool found = false;
			for (String dir : dirs) {
				String filepath = AppendFileName(dir, filename);
				if (FileExists(filepath)) {
					in.SetPath(filepath);
					found = true;
					break;
				}
			}
			if (!found) {
				OnError(fn_name, "file does not exist: \"" + filename + "\"");
				return false;
			}
		}
	}
	
	Object& outputs = st_map.GetAdd("outputs", ObjectArray());
	if (!outputs.IsArray()) {
		OnError(fn_name, "no outputs");
		return false;
	}
	ObjectArray& out_arr = outputs.GetArray();
	for(int i = 0; i < out_arr.GetCount(); i++) {
		Object& out_el = out_arr.Get(i);
		if (!out_el.IsMap())
			continue;
		ObjectMap& out_map = out_el.GetMap();
		
		if (!i) {
			id = (int)out_map.TryGet("id", -1).ToInt();
		}
		else {
			OnError(fn_name, "only 1 output is supported currently");
			return false;
		}
	}
	
	#if HAVE_OPENGL
	
	// Load GLSL code
	String& glsl = frag_code;
	if (glsl.IsEmpty()) {
		OnError(fn_name, "shader is empty for stage " + IntStr(id));
		return false;
	}
	
	// Hotfixes for GLSL code
	Ogl_RemoveToken(glsl, "lowp");
	Ogl_RemoveToken(glsl, "mediump");
	Ogl_RemoveToken(glsl, "highp");
	if (glsl.GetCount() && glsl[glsl.GetCount()-1] == 0) // Remove trailing 0
		glsl = glsl.Left(glsl.GetCount()-1);
	
	code[PROG_FRAGMENT] = glsl;
	
	#else
	Panic("not implemented");
	#endif
	
	return true;
}

void AccelComponent::OnError(String fn, String msg) {
	if (ctx && ctx->GetParent()) {
		ctx->GetParent()->OnError(GetRTTI().GetTypeId(), fn, msg);
	}
	else {
		LOG("AccelComponent::" << fn << ": error: " << msg);
	}
}

String AccelComponent::GetStringFromType(TypeCls i) {
	#define IFACE(x) \
		if (i == AsTypeCls<Accel##x##Source>()) return "Accel" #x "Source"; \
		if (i == AsTypeCls<Accel##x##Sink>()) return "Accel" #x "Sink"; \
		if (i == AsTypeCls<Accel##x##PipeComponent>()) return "Accel" #x "PipeComponent"; \
		if (i == AsTypeCls<ConvertCenterAccel##x##InputComponent>()) return "ConvertCenterAccel" #x "InputComponent"; \
		if (i == AsTypeCls<ConvertCenterAccel##x##OutputComponent>()) return "ConvertCenterAccel" #x "OutputComponent";
	IFACE_LIST
	#undef IFACE
	return "invalid";
}

#define VALUE(str, i) if (s == #str) return AsTypeCls<i>();

TypeCls AccelComponent::GetTypeFromString(String s) {
	VALUE(image,		AccelVideoPipeComponent);
	VALUE(imagebuf,		AccelVideoPipeComponent);
	VALUE(imagebuffer,	AccelVideoPipeComponent);
	VALUE(sound,		AccelAudioPipeComponent);
	VALUE(soundbuf,		AccelAudioPipeComponent);
	VALUE(cubemap,		ConvertCenterAccelPhotoInputComponent);
	//VALUE(vertex,		Accel_DATA_SINK);
	//VALUE(data,			Accel_DATA_SINK);
	//VALUE(ctrl,			Accel_CTRL_SINK);
	//VALUE(library,		);
	return AsVoidTypeCls();
}

#undef VALUE

bool AccelComponent::IsTypeTemporary(TypeCls type) {
	#define IFACE(x) if (type == AsTypeCls<Accel##x##PipeComponent>()) return true;
	IFACE_LIST
	#undef IFACE
	return false;
}



















AccelComponentGroup::AccelComponentGroup() {
	
}

bool AccelComponentGroup::Open() {
	int dbg_i = 0;
	for(AccelComponentRef& comp : comps) {
		if (!comp->IsOpen() && !comp->Open()) {
			DLOG("AccelComponentGroup::Open: error: a component did not open properly (comp #" + IntStr(dbg_i) + ")");
			return false;
		}
		++dbg_i;
	}
	return true;
}

void AccelComponentGroup::Close() {
	for(AccelComponentRef& comp : comps) {
		comp->Close();
		comp->AsRef<ComponentBase>()->Destroy();
	}
}

void AccelComponentGroup::CloseTemporary() {
	for(AccelComponentRef& comp : comps) {
		if (comp->IsTypeTemporary()) {
			comp->Close();
			comp->AsRef<ComponentBase>()->Destroy();
		}
	}
}

void AccelComponentGroup::Clear() {
	Close();
	#if HAVE_OPENGL
	Ogl_ClearPipeline();
	#endif
	comps.Clear();
	gl_stages.Clear();
	stream.Clear();
}

void AccelComponentGroup::Reset() {
	stream.Reset();
}

void AccelComponentGroup::FindComponents() {
	comps.Clear();
	ASSERT(GetParent());
	EntityRef e = GetParent()->GetEntity();
	for (ComponentRef& comp : e->GetComponents().GetValues()) {
		if (comp) {
			ComponentBase& base = *comp;
			AccelComponent* fcomp = CastPtr<AccelComponent>(&base);
			if (fcomp) {
				TypeCls comp_ctx = base.GetContextType();
				if (group_classes.Find(comp_ctx)) {
					ASSERT(!fcomp->ctx);
					fcomp->ctx = AsRefT();
					comps.Add(fcomp->AsRefT());
				}
			}
		}
	}
}

AccelComponentRef AccelComponentGroup::GetComponentById(int id) const {
	ASSERT(id >= 0);
	for (const auto& s : comps)
		if (s->id == id)
			return s;
	THROW(Exc("AccelComponent not found"));
}

void AccelComponentGroup::FindUniqueInputs(AcceleratorHeaderVector& v) {
	for (auto& comp : comps)
		for(AcceleratorHeader& in : comp->in)
			if (/*in.IsTypeComponentSource() &&*/ v.Find(in) < 0)
				v.Add(in);
}

bool AccelComponentGroup::LoadExisting(TypeCls type, ObjectMap& st_map, int stage_i, String frag_code) {
	static const char* fn_name = "AccelComponentGroup::LoadExisting";
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

void AccelComponentGroup::ConnectInputs(AcceleratorHeaderVector& v) {
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
}

void AccelComponentGroup::UpdateBuffers() {
	for(auto& comp : comps)
		comp->UpdateTexBuffers();
}

bool AccelComponentGroup::CheckInputTextures() {
#if HAVE_OPENGL
	for(auto& comp : comps)
		if (!comp->Ogl_CheckInputTextures())
			return false;
#endif
	return true;
}

void AccelComponentGroup::Process() {
	ASSERT(GetParent()->is_open);
	RefreshStreamValues();
	
	for(auto& comp : comps)
		comp->PreProcess();
	
	int i = 0;
	for(AccelComponentRef& comp : comps) {
#if HAVE_OPENGL
		Ogl_ProcessStage(*comp, gl_stages[i]);
#endif
	}
	
	for(AccelComponentRef& comp : comps)
		comp->PostProcess();
	
}

void AccelComponentGroup::RefreshStreamValues() {
	if (HasContext<VideoContext>()) {
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
	else if (HasContext<AudioContext>()) {
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

bool AccelComponentGroup::IsLast(const AccelComponent* comp) const {
	return comps.GetCount() && comps.Top() == comp;
}



NAMESPACE_TOPSIDE_END
