#include "FusionCore.h"

NAMESPACE_OULU_BEGIN

void RemoveToken(String& glsl, String token) {
	if (glsl.Left(token.GetCount() + 1) == token + " ") glsl = glsl.Mid(token.GetCount() + 1);
	glsl.Replace((String)" " + token + " ", " ");
	glsl.Replace((String)"\n" + token + " ", "\n");
}





#define VALUE(str, i) if (t == i) return #str;

String FusionComponentInput::GetStringFromType(FusionComponentInput::Type t) {
	VALUE(texture, TEXTURE);
	VALUE(cubemap, CUBEMAP);
	VALUE(webcam, WEBCAM);
	VALUE(music, MUSIC);
	VALUE(musicstream, MUSICSTREAM);
	VALUE(keyboard, KEYBOARD);
	VALUE(volume, VOLUME);
	VALUE(video, VIDEO);
	VALUE(buffer, BUFFER);
	VALUE(empty, EMPTY);
	return "invalid";
}

#undef VALUE

#define VALUE(str, i) if (s == #str) return i;

FusionComponentInput::Type FusionComponentInput::GetTypeFromString(String s) {
	VALUE(texture, TEXTURE);
	VALUE(cubemap, CUBEMAP);
	VALUE(webcam, WEBCAM);
	VALUE(music, MUSIC);
	VALUE(musicstream, MUSICSTREAM);
	VALUE(keyboard, KEYBOARD);
	VALUE(volume, VOLUME);
	VALUE(video, VIDEO);
	VALUE(buffer, BUFFER);
	VALUE(empty, EMPTY);
	return INVALID;
}

int FusionComponentInput::GetFilterFromString(String s) {
	VALUE(nearest, FILTER_NEAREST);
	VALUE(linear, FILTER_LINEAR);
	VALUE(mipmap, FILTER_MIPMAP);
	return DEFAULT_FILTER;
}

int FusionComponentInput::GetWrapFromString(String s) {
	VALUE(clamp, WRAP_CLAMP);
	VALUE(repeat, WRAP_REPEAT);
	return DEFAULT_WRAP;
}

bool FusionComponentInput::IsEqualHeader(const FusionComponentInput& i) const {
	return	filepath == i.filepath &&
			type == i.type &&
			wrap == i.wrap &&
			filter == i.filter &&
			vflip == i.vflip;
}

void FusionComponentInput::SetHeader(const FusionComponentInput& i) {
	filepath = i.filepath;
	type = i.type;
	wrap = i.wrap;
	filter = i.filter;
	vflip = i.vflip;
}

#undef VALUE






int FusionComponentInputVector::Find(const FusionComponentInput& a) const {
	for(int i = 0; i < in.GetCount(); i++) {
		const FusionComponentInput& b = in[i];
		if (a.IsEqualHeader(b))
			return i;
	}
	return -1;
}

void FusionComponentInputVector::Add(const FusionComponentInput& a) {
	FusionComponentInput& b = in.Add();
	b.filepath = a.filepath;
	b.type = a.type;
	b.wrap = a.wrap;
	b.filter = a.filter;
	b.vflip = a.vflip;
}




bool FusionComponentInput::IsTypeComponentSource(Type type) {
	return type != INVALID && type != BUFFER && type != EMPTY;
}




void FusionComponent::Update0(double dt) {
	if (!ctx && IsOpen())
		Close();
	else
		Update(dt);
}

bool FusionComponent::Open() {
	DLOG("FusionComponent(" << GetTypeString() << ")::Open: begin");
	const char* fn_name = "Open";
	if (!ctx) {OnError(fn_name, "no context"); return false;}
	
	if (is_open)
		Close();
	
	if (!LoadResources())
		return false;
	
#ifdef flagOPENGL
	if (!Ogl_CompilePrograms())
		return false;
	
	if (!Ogl_LinkStages())
		return false;
#endif
	
	DLOG("FusionComponent(" << GetTypeString() << ")::Open: end");
	is_open = true;
	return true;
}

void FusionComponent::Close() {
	DLOG("FusionComponent(" << GetTypeString() << ")::Close");
	
	if (is_open)
		is_open = false;
}

void FusionComponent::Initialize() {
	DLOG("FusionComponent(" << GetTypeString() << ")::Initialize");
	
	Ref<FusionSystem> fusion_sys = GetECS().GetEntity().GetMachine().Get<FusionSystem>();
	if (fusion_sys)
		fusion_sys	-> AddComponent(*this);
}

void FusionComponent::Uninitialize() {
	DLOG("FusionComponent(" << GetTypeString() << ")::Uninitialize");
	
	if (ctx) {
		ctx->RemoveComponent(AsRefT());
		ctx = 0;
	}
	
	Ref<FusionSystem> fusion_sys = GetECS().GetEntity().GetMachine().Get<FusionSystem>();
	if (fusion_sys)
		fusion_sys	-> RemoveComponent(*this);
	
	//Clear();
}

FusionStream* FusionComponent::Stream() {
	return ctx ? &ctx->stream : 0;
}

int FusionComponent::NewWriteBuffer() {
	if (is_doublebuf)
		buf_i = (buf_i + 1) % 2;
	return buf_i;
}

String FusionComponent::GetStringFromType(Type i) {
	switch (i) {
		case FUSION_DATA_SINK:		return "DataSink";
		case FUSION_MEDIA_SINK:		return "MediaSink";
		
		case FUSION_CTRL_SOURCE:	return "ControllerSource";
		case FUSION_CTRL_BUFFER:	return "ControllerBuffer";
		case FUSION_CTRL_SINK:		return "ControllerSink";
		
		case FUSION_DISPLAY_SOURCE:	return "DisplaySource";
		case FUSION_DISPLAY_BUFFER:	return "DisplayBuffer";
		case FUSION_DISPLAY_SINK:	return "DisplaySink";
		
		case FUSION_AUDIO_SOURCE:	return "AudioSource";
		case FUSION_AUDIO_BUFFER:	return "AudioBuffer";
		case FUSION_AUDIO_SINK:		return "AudioSink";
		
		case FUSION_INVALID:
		case FUSION_TYPE_COUNT:
			break;
	}
	return "invalid";
}

#define VALUE(str, i) if (s == #str) return i;

FusionComponent::Type FusionComponent::GetTypeFromString(String s) {
	VALUE(image,		FUSION_DISPLAY_SOURCE);
	VALUE(imagebuf,		FUSION_DISPLAY_BUFFER);
	VALUE(imagebuffer,	FUSION_DISPLAY_BUFFER);
	VALUE(sound,		FUSION_AUDIO_SOURCE);
	VALUE(soundbuf,		FUSION_AUDIO_BUFFER);
	VALUE(cubemap,		FUSION_DATA_SINK);
	VALUE(vertex,		FUSION_DATA_SINK);
	VALUE(data,			FUSION_DATA_SINK);
	VALUE(ctrl,			FUSION_CTRL_SINK);
	//VALUE(library,		);
	return FUSION_INVALID;
}

#undef VALUE

void FusionComponent::Clear() {
	DLOG("FusionComponent(" << GetTypeString() << ")::Clear");
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

void FusionComponent::ClearTex() {
#ifdef flagOPENGL
	Ogl_ClearTex();
#endif
}

void FusionComponent::ClearProg() {
#ifdef flagOPENGL
	Ogl_ClearProg();
#endif
}

bool FusionComponent::Load(ObjectMap& st_map, int stage_i, String frag_code) {
	const char* fn_name = "FusionComponent::Load";
	Clear();
	
	
	Index<String> dirs;
	dirs.Add( ShareDirFile("imgs") );
	dirs.Add( ShareDirFile("sounds") );
	dirs.Add( ShareDirFile("videos") );
	
	
	name = st_map.TryGet("name", "").ToString();
	description = st_map.TryGet("description", "").ToString();
	
	if (type == FUSION_INVALID) {
		OnError(fn_name, "stage has invalid type");
		return false;
	}
	
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
		FusionComponentInput& in = this->in.Add();
		if (in_map.IsEmpty()) {
			in.type = FusionComponentInput::EMPTY;
			continue;
		}
		in.id		= (int)in_map.TryGet("id", -1).ToInt(); // TODO fix all of these, not safe now
		in.type		= FusionComponentInput::GetTypeFromString(in_map.TryGet("type", "").ToString());
		in.filepath	= in_map.TryGet("filename", "").ToString();
		in.filter	= FusionComponentInput::GetFilterFromString(in_map.TryGet("filter", "linear").ToString());
		in.wrap		= FusionComponentInput::GetWrapFromString(in_map.TryGet("wrap", "clamp").ToString());
		in.vflip	= ScanBoolString(in_map.TryGet("vflip", "false").ToString());
		
		if (in.type != FusionComponentInput::BUFFER) {
			in.id = -1;
		}
		
		if (in.filepath.GetCount() && GetFileDirectory(in.filepath).IsEmpty()) {
			String filename = GetFileName(in.filepath);
			String title = GetFileTitle(filename);
			filename = CommonHashToName().Get(title, title) + GetFileExt(filename);
			
			bool found = false;
			for (String dir : dirs) {
				String filepath = AppendFileName(dir, filename);
				if (FileExists(filepath)) {
					in.filepath = filepath;
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
	
	
	// Load GLSL code
	String& glsl = frag_code;
	if (glsl.IsEmpty()) {
		OnError(fn_name, "shader is empty for stage " + IntStr(id));
		return false;
	}
	
	// Hotfixes for GLSL code
	RemoveToken(glsl, "lowp");
	RemoveToken(glsl, "mediump");
	RemoveToken(glsl, "highp");
	if (glsl.GetCount() && glsl[glsl.GetCount()-1] == 0) // Remove trailing 0
		glsl = glsl.Left(glsl.GetCount()-1);
	
	code[PROG_FRAGMENT] = glsl;
	
	
	return true;
}

void FusionComponent::OnError(String fn, String msg) {
	if (ctx) {
		ctx->OnError(type, fn, msg);
	}
	else {
		LOG("FusionComponent::" << fn << ": error: " << msg);
	}
}

NAMESPACE_OULU_END
