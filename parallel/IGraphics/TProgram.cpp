#include "IGraphics.h"


NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
bool ProgramStateT<Gfx>::LoadShaderContent(GVar::ShaderType shader_type, String content) {
	DLOG("ProgramStateT::LoadShaderContent");
	
	ASSERT(shader_type > GVar::SHADERTYPE_NULL && shader_type < GVar::SHADERTYPE_COUNT);
	ShaderState& shader = shaders[shader_type];
	
	shader.code = content;
	shader.library = "";
	
	return true;
}

template <class Gfx>
bool ProgramStateT<Gfx>::LoadShaderFile(GVar::ShaderType shader_type, String shader_path, String library_path) {
	DLOG("ProgramStateT::LoadShaderFile: " << shader_path);
	
	ASSERT(shader_type > GVar::SHADERTYPE_NULL && shader_type < GVar::SHADERTYPE_COUNT);
	ShaderState& shader = shaders[shader_type];
	
	Vector<String> libraries = Split(library_path, ";");
	String library;
	bool succ = true;
	for (String& lib : libraries) {
		String path = RealizeShareFile(lib);
		if (FileExists(path)) {
			if (libraries.GetCount() > 1)
				library << "// FILE: " << path << "\n\n";
			library << LoadFile(path) << "\n\n";
		}
		else {
			LOG("LoadShaderFile: error: file does not exist: " << path);
			succ = false;
		}
	}
	if (!succ) return false;
	
	if (!FileExists(shader_path))
		shader_path = ShareDirFile(shader_path);
	
	if (!FileExists(shader_path)) {
		LOG("LoadShaderFile: error: file does not exist: " << shader_path);
		return false;
	}
	
	String content = LoadFile(shader_path);
	if (content.IsEmpty()) {
		LOG("LoadShaderFile: error: got empty shader file from: " << shader_path);
		return false;
	}
	
	//DUMP(content);
	shader.code = content;
	shader.library = library;
	
	return true;
}

template <class Gfx>
bool ProgramStateT<Gfx>::LoadShader(GVar::ShaderType shader_type, String str, bool is_path, bool is_content, String library_paths) {
	
	if (str.IsEmpty()) {
		LOG("ProgramStateT<Gfx>::LoadShader: error: no shader given");
		return false;
	}
	
	if (is_path) {
		if (!LoadShaderFile(shader_type, str, library_paths)) {
			LOG("ProgramStateT<Gfx>::LoadShader: error: shader loading failed from '" + str + "'");
			return false;
		}
	}
	else if (is_content) {
		if (!LoadShaderContent(shader_type, str)) {
			LOG("ProgramStateT<Gfx>::LoadShader: error: shader loading failed from content string");
			return false;
		}
	}
	else {
		if (!LoadBuiltinShader(shader_type, str)) {
			LOG("ProgramStateT<Gfx>::LoadShader: error: shader loading failed from name '" + str + "'");
			return false;
		}
	}
	
	return true;
}

template <class Gfx>
void ProgramStateT<Gfx>::FindVariables() {
	int n_uniforms = 0;
	Gfx::GetProgramiv(native, GVar::ACTIVE_UNIFORMS, n_uniforms);
	
	memset(var_idx, -1, sizeof(var_idx));
	user_vars.Clear();
	RendVer(OnClearVars);
	for (int i = 0; i < n_uniforms; i++) {
		int size = 0;
		int type = 0;
		String name_str = Gfx::GetActiveUniform(native, i, &size, &type);
		const char* name = name_str;
		
		bool found = false;
		bool state_var = false;
		for(int j = 0; j < GVar::VAR_COUNT; j++) {
			const char* var_name = GVar::names[j];
			if (strncmp(var_name, name, 128) == 0) {
				var_idx[j] = i;
				if (j == GVar::VAR_COMPAT_DATE && !is_time_used)
					is_time_used = true;
				found = true;
				state_var = !GVar::is_obj_var[j];
				break;
			}
		}
		
		if (!found) {
			user_vars << name_str;
		}
		
		RendVer2(OnRealizeVar, name_str, state_var);
	}
	
	is_searched_vars = true;
}

template <class Gfx>
void ProgramStateT<Gfx>::RealizeCompilation() {
	if (pending_compilation) {
		pending_compilation = false;
		
		Compile(GfxCompilerArgs());
		owner->Realize();
	}
}

template <class Gfx>
void ProgramStateT<Gfx>::SetVars(ContextState& c, ModelState& m, const DataObject& o, ViewTarget vtgt) {
	for(int i = 0; i < GVar::VAR_COUNT; i++)
		if (GVar::is_obj_var[i] && var_idx[i] >= 0)
			SetVar(c, m, i, o, vtgt);
}

template <class Gfx>
void ProgramStateT<Gfx>::SetVar(ContextState& ctx, ModelState& mdl, int var, const DataObject& o, ViewTarget vtgt) {
	using namespace GVar;
	
	DataState& data = *owner->owner;
	
	int uindex = var_idx[var];
	ASSERT(uindex >= 0);
	if (var == VAR_AUDIOTIME) {
		//LOG("VAR_AUDIOTIME: " << ctx.time_total);
		Gfx::Uniform1f(uindex, (float)ctx.time_total);
	}
	else if (var == VAR_MODELCOLOR) {
		Gfx::Uniform4f(uindex, o.color[0], o.color[1], o.color[2], o.color[3]);
	}
	else if (var == VAR_VIEW) {
		if (vtgt == VIEW_TARGET_STEREO_LEFT) {
			/*mat4 m = data.view_stereo[0] * Translate(vec3(0,1.76,-6));
			vec3 pos = Position(m);
			Gfx::UniformMatrix4fv(uindex, m);*/
			
			ASSERT(data.is_stereo);
			Gfx::UniformMatrix4fv(uindex, data.view_stereo[0]);
		}
		else if (vtgt == VIEW_TARGET_STEREO_RIGHT) {
			/*mat4 m = data.view_stereo[1] * Translate(vec3(0,1.76,-6));
			vec3 pos = Position(m);
			Gfx::UniformMatrix4fv(uindex, m);*/
			
			ASSERT(data.is_stereo);
			Gfx::UniformMatrix4fv(uindex, data.view_stereo[1]);
		}
		else
			Gfx::UniformMatrix4fv(uindex, data.view);
	}
	else if (var == VAR_LIGHTDIR) {
		Gfx::Uniform3f(uindex, data.light_dir[0], data.light_dir[1], data.light_dir[2]);
	}
	else if (var == VAR_PROJECTIONOVERRIDE) {
		Gfx::UniformMatrix4fv(uindex, o.proj_override);
	}
	else if (var == VAR_SCALE) {
		Gfx::UniformMatrix4fv(uindex, o.scale);
	}
	else if (var == VAR_VIEWOVERRIDE) {
		Gfx::UniformMatrix4fv(uindex, o.view_override);
	}
	else if (var == VAR_MODEL) {
		Gfx::UniformMatrix4fv(uindex, o.model);
	}
	else if (var >= VAR_NONE && var <= VAR_UNKNOWN) {
		int tex_ch = var - VAR_NONE;
		if (o.material < 0)
			return;
		auto& mat = mdl.materials.Get(o.material);
		int tex_i = mat.tex_id[tex_ch];
		int tex_f = mat.tex_filter[tex_ch];
		if (tex_i >= 0) {
			auto& tex = mdl.textures[tex_i];
			Gfx::ActiveTexture(tex_ch);
			Gfx::BindTextureRO(GVar::TEXTYPE_2D, tex);
			if (tex_f == 0)
				Gfx::TexParameteri(GVar::TEXTYPE_2D, GVar::FILTER_NEAREST, GVar::WRAP_REPEAT);
			else if (tex_f == 1)
				Gfx::TexParameteri(GVar::TEXTYPE_2D, GVar::FILTER_LINEAR, GVar::WRAP_REPEAT);
			Gfx::Uniform1i(uindex, tex_ch);
			Gfx::DeactivateTexture();
		}
	}
	else if (var >= VAR_COMPAT_CHANNEL0 && var <= VAR_COMPAT_CHANNEL1) {
		TODO
	}
	else if (var == VAR_COMPAT_CHANNELRESOLUTION) {
		TODO
	}
	else {
		TODO
	}
	#if 0
	if (var == VAR_VIEW) {
		if (o.is_global_view)
			Gfx::UniformMatrix4fv(uindex, data.view);
		else
			Gfx::UniformMatrix4fv(uindex, o.view);
	}
	else if (var == VAR_PROJECTION) {
		/*if (o.is_global_proj)
			TODO
		else*/
		Gfx::UniformMatrix4fv(uindex, o.proj);
	}
	else if (var == VAR_SCALE) {
		Gfx::UniformMatrix4fv(uindex, o.scale);
	}
	else if (var == VAR_MODEL) {
		Gfx::UniformMatrix4fv(uindex, o.model);
	}
	#endif
}

template <class Gfx>
void ProgramStateT<Gfx>::SetVars(ContextState& ctx, EnvStateRef& env, const RealtimeSourceConfig& cfg) {
	for(int i = 0; i < GVar::VAR_COUNT; i++)
		if (!GVar::is_obj_var[i] && var_idx[i] >= 0)
			SetVar(ctx, env, i, cfg);
}

template <class Gfx>
void ProgramStateT<Gfx>::SetVar(ContextState& ctx, EnvStateRef& env, int var, const RealtimeSourceConfig& cfg) {
	using namespace GVar;
	int uindex = var_idx[var];
	ASSERT(uindex >= 0);
	if (uindex < 0)
		return;
	
	DataState& data = *owner->owner;
	
	RendVer1(OnUpdateVar, GVar::names[var]);
	
	if (var == VAR_AUDIOTIME) {
		Gfx::Uniform1f(uindex, (float)ctx.time_total);
	}
	
	else if (var == VAR_VIEW) {
		ASSERT(0); // pass
	}
	else if (var == VAR_VIEWOVERRIDE) {
		ASSERT(0); // pass
	}
	else if (var == VAR_PROJECTIONOVERRIDE) {
		ASSERT(0); // pass
	}
	else if (var == VAR_SCALE) {
		ASSERT(0); // pass
	}
	else if (var == VAR_MODEL) {
		ASSERT(0); // pass
	}
	else if (var == VAR_COMPAT_RESOLUTION) {
		// from fb.size
		ASSERT(data.resolution[0] > 0 && data.resolution[1] > 0);
		Gfx::Uniform3f(uindex, (float)data.resolution[0], (float)data.resolution[1], 1.0f);
	}
	
	else if (var == VAR_COMPAT_TIME) {
		//RTLOG("SetVar: " << time_total);
		Gfx::Uniform1f(uindex, (float)ctx.time_total);
	}
	
	else if (var == VAR_COMPAT_TIMEDELTA) {
		ASSERT(ctx.frame_time != 0.0);
		Gfx::Uniform1f(uindex, (float)ctx.frame_time);
	}
	
	else if (var == VAR_COMPAT_FRAME) {
		Gfx::Uniform1i(uindex, ctx.frames);
	}
	
	else if (var == VAR_COMPAT_MOUSE) {
		if (env) {
			#ifdef flagSCREEN
			Point& mouse_drag = env->Set<Point>(MOUSE_TOYCOMPAT_DRAG);
			Point& mouse_click = env->Set<Point>(MOUSE_TOYCOMPAT_CLICK);
			Gfx::Uniform4f(uindex,
				(float)mouse_drag.x,
				(float)mouse_drag.y,
				(float)mouse_click.x,
				(float)mouse_click.y);
			#endif
		}
	}
	
	else if (var == VAR_COMPAT_DATE) {
		double sec = ((int)ctx.time.hour * 60 + (int)ctx.time.minute) * 60 + (int)ctx.time.second;
		sec += ctx.time_us;
		Gfx::Uniform4f(uindex, (float)ctx.time.year, (float)ctx.time.month, (float)ctx.time.day, (float)sec);
	}
	
	else if (var == VAR_COMPAT_SAMPLERATE) {
		ASSERT(ctx.sample_rate > 0);
		Gfx::Uniform1f(uindex, (float)ctx.sample_rate);
	}
	
	else if (var == VAR_COMPAT_OFFSET) {
		vec2 res = data.resolution;
		vec2 off = data.offset;
		
		if (res[0] > 0 && res[1] > 0) {
			int x = off[0];
			int y = -off[1];
			Gfx::Uniform2f(uindex, (float)x, (float)y);
		} else {
			Gfx::Uniform2f(uindex, 0.0f, 0.0f);
		}
	}
	
	else if (var >= VAR_COMPAT_CHANNEL0 && var <= VAR_COMPAT_CHANNEL3) {
		int ch = var - VAR_COMPAT_CHANNEL0;
		int tex_ch = COMPAT_OFFSET + ch;
		NativeColorBufferConstRef tex = GetInputTex(ch);
		// may fail in early program: ASSERT(tex);
		if (tex) {
			//typename Gfx::NativeColorBufferConstRef clr = Gfx::GetFrameBufferColor(*tex, TEXTYPE_NONE);
			Gfx::ActiveTexture(tex_ch);
			Gfx::BindTextureRO(GetTexType(ch), tex);
			Gfx::TexParameteri(GVar::TEXTYPE_2D, GVar::FILTER_LINEAR, GVar::WRAP_REPEAT);
			Gfx::Uniform1i(uindex, tex_ch);
			Gfx::DeactivateTexture();
		}
	}
	
	else if (var == VAR_COMPAT_CHANNELTIME) {
		float values[INPUT_COUNT];
		for(int j = 0; j < INPUT_COUNT; j++) {
			InputState& in = inputs[j];
			values[j] = in.stage ? in.stage->buf->ctx.time_total : 0;
		}
		//Gfx::Uniform1fv(uindex, 4, values);
		Gfx::Uniform4f(uindex, (float)values[0], (float)values[1], (float)values[2], (float)values[3]);
	}
	
	else if (var == VAR_COMPAT_CHANNELRESOLUTION) {
		float values[3*4] = {0,0,0, 0,0,0, 0,0,0, 0,0,0};
		for(int j = 0; j < INPUT_COUNT; j++) {
			InputState& in = inputs[j];
			const BufferStage* in_stage = in.stage;
			if (in_stage){
				int off = j * 3;
				auto& in_fb = in_stage->fb;
				values[off + 0] = (float)in_fb.size.cx;
				values[off + 1] = (float)in_fb.size.cy;
				values[off + 2] = (float)in_fb.depth;
			}
		}
		Gfx::Uniform3fv(uindex, 4, values);
	}
	
	else if (var == VAR_COMPAT_BLOCKOFFSET) {
		Gfx::Uniform1f(uindex, (float)ctx.block_offset);
	}
	else {
		ASSERT_(false, "Invalid variable");
	}
}

template <class Gfx>
void ProgramStateT<Gfx>::SetInputVolume(int in_id) {
	ASSERT(in_id >= 0 && in_id < GVar::INPUT_COUNT);
	InputState& in = inputs[in_id];
	in.type = GVar::VOLUME_INPUT;
}

template <class Gfx>
void ProgramStateT<Gfx>::SetInputCubemap(int in_id) {
	ASSERT(in_id >= 0 && in_id < GVar::INPUT_COUNT);
	InputState& in = inputs[in_id];
	in.type = GVar::CUBEMAP_INPUT;
}

template <class Gfx>
template <int>
int ProgramStateT<Gfx>::BuiltinShaderT() {
	bool succ = false;
	if (!owner->native)
		owner->native.Create();
	int shdr_count = 0;
	for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
		ShaderState& s = shaders[i];
		if (s.native) {
			shdr_count++;
			/*GVar::ShaderType t = (GVar::ShaderType)i;
			ASSERT(!s.shader);
			if (!Gfx::CreateShader((GVar::ShaderType)i, s.shader)) {
				LOG("BufferStageT<Gfx>::BuiltinShaderT: error: could not create shader");
				SetError("could not create shader (at BufferT<Gfx>::BuiltinShaderT)");
				return -1;
			}
			ASSERT(s.shader);
			if (!s.shader) continue;
			//s.shader.Create(t);
			s.shader->SetShaderBase(*soft[i]);
			s.enabled = true;
			if (!native) {
				native.Create();
			}*/
			native.Attach(*s.native);
			owner->native.Use(native, 1 << i);
			if (i == GVar::FRAGMENT_SHADER)
				succ = true;
		}
	}
	if (!succ) {
		if (shdr_count == 0)
			SetError("PipelineState got no shaders");
		else
			SetError("PipelineState got no soft fragment shader");
	}
	
	return succ ? 1 : -1;
}

template <class Gfx>
int ProgramStateT<Gfx>::BuiltinShader() {return 0;}

template <class Gfx>
bool ProgramStateT<Gfx>::LoadBuiltinShader(GVar::ShaderType shader_type, String id) {
	return false;
}

template <class Gfx>
template <int>
bool ProgramStateT<Gfx>::LoadBuiltinShaderT(GVar::ShaderType shader_type, String id) {
	int i = SoftShaderLibrary::GetMap(shader_type).Find(id);
	if (i < 0) {
		SetError("could not find shader");
		return false;
	}
	
	shaders[shader_type].native->SetShaderBase(SoftShaderLibrary::GetMap(shader_type)[i]());
	
	return true;
}

#ifdef flagSDL2
template <>
int ProgramStateT<SdlSwGfx>::BuiltinShader() {
	return BuiltinShaderT<0>();
}
template <>
bool ProgramStateT<SdlSwGfx>::LoadBuiltinShader(GVar::ShaderType shader_type, String id) {
	return LoadBuiltinShaderT<0>(shader_type, id);
}
#endif

#ifdef flagPOSIX
template <>
int ProgramStateT<X11SwGfx>::BuiltinShader() {
	return BuiltinShaderT<0>();
}
template <>
bool ProgramStateT<X11SwGfx>::LoadBuiltinShader(GVar::ShaderType shader_type, String id) {
	return LoadBuiltinShaderT<0>(shader_type, id);
}
#endif

template <class Gfx>
bool ProgramStateT<Gfx>::Compile(const GfxCompilerArgs& args) {
	/*const char* fn_name = "CompilePrograms";
	for(int i = 0; i < PROG_COUNT; i++) {
		if (i == FRAGMENT_SHADER && !CompileFragmentShader())
			return false;
		if (i == VERTEX_SHADER && !CompileVertexShader())
			return false;
	}*/
	
	int r;
	if ((r = BuiltinShader()) != 0) {
		//breaks simple quad rendering: use_user_data = true;
		return r > 0;
	}
	//use_user_data = false;
	
	Compiler comps[GVar::SHADERTYPE_COUNT];
	Linker linker;
	linker.EnableLog();
	for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
		auto& s = shaders[i];
		if (s.code.IsEmpty())
			continue;
		
		Compiler& comp = comps[i];
		s.enabled = true;
		
		if (!comp.Compile(args, *this, s, (GVar::ShaderType)i)) {
			SetError(comp.GetError());
			return false;
		}
	}
	
	if (!linker.Link(*this)) {
		SetError(linker.GetError());
		return false;
	}
	
	owner->Realize();
	
	return true;
}

template <class Gfx>
bool ProgramStateT<Gfx>::LoadInputLink(int in_id, const InternalPacketData& v) {
	if (in_id >= 0 && in_id < GVar::INPUT_COUNT) {
		//LOG("LoadInputLink: " << name << " #" << in_id);
		GfxBufferStage* gstage = (GfxBufferStage*)v.ptr;
		BufferStage* stage = CastPtr<BufferStage>(gstage);
		if (!stage) {
			ASSERT_(0, "Buffer's Gfx type differs");
			return false;
		}
		ASSERT(v.ptr);
		InputState& in = inputs[in_id];
		in.id = in_id;
		in.stage = stage;
		
		auto& fb = stage->fb;
		ASSERT(fb.size.cx > 0 && fb.size.cy > 0);
		
		if (fb.is_cubemap)
			in.type = GVar::CUBEMAP_INPUT;
		else if (fb.depth > 0)
			in.type = GVar::VOLUME_INPUT;
		else {
			ASSERT(in.type != GVar::VOLUME_INPUT);
			in.type = GVar::TEXTURE_INPUT;
		}
		
		return true;
	}
	
	RTLOG("LoadInputLink: error: unexpected data");
	return false;
}

template <class Gfx>
bool ProgramStateT<Gfx>::SetupLoopback(int loopback, BufferStage& s) {
	if (loopback < 0)
		return true;
	
	if (loopback >= GVar::INPUT_COUNT) {
		LOG("SetupLoopback: error: too large loopback id #" << loopback);
		return false;
	}
	
	InputState& in = inputs[loopback];
	in.stage = &s;
	in.id = id;
	in.type = GVar::BUFFER_INPUT;
	in.is_loopback = true;
	
	return true;
}

template <class Gfx>
void ProgramStateT<Gfx>::RefreshProgramStages() {
	if (native >= 0) {
		int bmask = 0;
		for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
			if (shaders[(GVar::ShaderType)i].enabled) {
				int bit = 1 << i;
				bmask |= bit;
			}
		}
		ASSERT(bmask != 0);
		Gfx::UseProgramStages(owner->native, bmask, native);
	}
}

template <class Gfx>
TNG NativeColorBufferConstRef ProgramStateT<Gfx>::GetInputTex(int input_i) const {
	const char* fn_name = "GetInputTex";
	//DLOG("BufferT::GetInputTex");
	if (input_i < 0 || input_i >= GVar::INPUT_COUNT)
		return 0;
	
	const InputState& in = inputs[input_i];
	if (in.stage == 0) {
		RTLOG("GetInputTex: warning: no input fbo stage");
		return 0;
	}
	
	NativeColorBufferConstRef tex = in.stage->GetOutputTexture(in.is_loopback);
	ASSERT(tex);
	
	return tex;
}

template <class Gfx>
GVar::TextureType ProgramStateT<Gfx>::GetTexType(int input_i) const {
	if (input_i < 0 || input_i >= GVar::INPUT_COUNT)
		return GVar::TEXTYPE_2D;
	
	const InputState& in = inputs[input_i];
	
	if (in.type == GVar::VOLUME_INPUT)
		return GVar::TEXTYPE_3D;
	
	else if (in.type == GVar::CUBEMAP_INPUT)
		return GVar::TEXTYPE_CUBE_MAP;
	
	else
		return GVar::TEXTYPE_2D;
}


GFX3D_EXCPLICIT_INITIALIZE_CLASS(ProgramStateT)


NAMESPACE_PARALLEL_END
