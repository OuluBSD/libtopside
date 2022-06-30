#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN

template <class Gfx>
Callback2<String, BufferT<Gfx>*> BufferT<Gfx>::WhenLinkInit;


/*template <class Gfx>
bool BufferT<Gfx>::LoadStereoShader(String shdr_vtx_path, String shdr_frag_path) {
	if (!LoadShaderFile(stereo_rt, GVar::FRAGMENT_SHADER, shdr_frag_path, "")) {
		LOG("BufferT<Gfx>::LoadStereoShader: error: shader loading failed from '" + shdr_frag_path + "'");
		return false;
	}
	if (!LoadShaderFile(stereo_rt, GVar::VERTEX_SHADER, shdr_vtx_path, "")) {
		LOG("BufferT<Gfx>::LoadStereoShader: error: shader loading failed from '" + shdr_vtx_path + "'");
		return false;
	}
	return true;
}*/

template <class Gfx>
void BufferT<Gfx>::Update(double dt) {
	ctx.time_us += dt;
	if (ctx.time_us >= 1.0) {
		ctx.time_us = fmod(ctx.time_us, 1.0);
		ctx.time = GetSysTime();
		RTLOG("Update: " << dt << ", time=" << ctx.time.ToString());
	}
}

template <class Gfx>
BufferStageT<Gfx>& BufferT<Gfx>::InitSingle() {
	ASSERT(stages.GetCount() <= 1);
	if (stages.GetCount())
		return stages.Top();
	
	stages.SetCount(1);
	BufferStage& s = stages[0];
	s.buf = this;
	return s;
}

template <class Gfx>
bool BufferT<Gfx>::Initialize(AtomBase& a, const Script::WorldState& ws) {
	String type = ws.Get(".type");
	
	ASSERT(stages.IsEmpty());
	
	if (type.IsEmpty()) {
		mode = SINGLE_IMAGEBUF;
		stages.SetCount(1);
	}
	else if (type == "audio") {
		mode = SINGLE_SOUND;
		snd_sample_rate = ws.GetInt(".samplerate", 44100);
		snd_frame_samples = ws.GetInt(".frame.samples", 1024);
		ctx.sample_rate = snd_sample_rate;
		stages.SetCount(1);
	}
	else if (type == "stereo") {
		mode = MULTI_STEREO;
		stages.SetCount(3);
		stages[0].SetStereo(0);
		stages[1].SetStereo(1);
		stages[2].SetStereoLens();
		stereo_data.is_stereo = true;
		SetStereoDataState(&stereo_data);
	}
	else if (type == "custom") {
		mode = MULTI_CUSTOM;
		int stage_count = ws.GetInt(".stages", 0);
		if (stage_count <= 0 || stage_count > 16) {
			LOG("BufferT<Gfx>::Initialize: error: stage count should be between 1 and 16");
			return false;
		}
		stages.SetCount(stage_count);
	}
	else {
		TODO
	}
	
	for (BufferStage& s : stages) {
		s.buf = this;
	}
	
	SetLocalTime(ws.GetBool(".retarded.local.time", false));
	
	
	String env_name = ws.Get(".env");
	if (!env_name.IsEmpty()) {
		SpaceRef l = a.GetSpace();
		env = l->FindNearestState(env_name);
		if (!env) {
			LOG("GfxBufferFieldT<Gfx>::Initialize: error: environment state with name '" << env_name << "' not found");
			return false;
		}
	}
	
	
	AddLink(ws.Get(".link")); // deprecated: ecs link id (could be used to handle buffer in ecs)
	
	
	/*ISourceRef src = a.GetSource();
	if (IsAudio()) {
		for(int i = 1; i < src->GetSourceCount(); i++) {
			Value& val = src->GetSourceValue(i);
			Format fmt = val.GetFormat();
			if (fmt.IsFbo()) {
				FboFormat& ffmt = fmt;
				ffmt.res[0] = frame_samples;
				ffmt.res[1] = 1;
				val.SetFormat(fmt);
			}
		}
	}*/
	//if (IsAudio())
	//	a.GetSink()->GetValue(0).SetMinQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
	
	
	int id = 0;
	for (BufferStage& s : stages) {
		if (!s.Initialize(id++, a, ws))
			return false;
	}
	
	
	return true;
}

template <class Gfx>
bool BufferT<Gfx>::PostInitialize() {
	ASSERT(stages.GetCount());
	if (stages.IsEmpty())
		return false;
	
	for (BufferStage& s : stages) {
		s.fb.is_audio = mode == SINGLE_SOUND;
		
		if (!s.PostInitialize())
			return false;
	}
	
	if (!InitializeRenderer()){
		LOG("BufferT<Gfx>::PostInitialize: error: " << GetError());
		return false;
	}
	
	is_initialized = true;
	return true;
}

template <class Gfx>
bool BufferT<Gfx>::ImageInitialize(bool is_win_fbo, Size screen_sz) {
	if (screen_sz.cx == 0 && screen_sz.cy == 0) {
		if (env) {
			Size* video_size = env->Get<Size>(SCREEN0_SIZE);
			if (video_size)
				screen_sz = *video_size;
		}
		if (screen_sz.cx == 0 && screen_sz.cy == 0)
			screen_sz = Size(TS::default_width,TS::default_height);
	}
	
	{
		auto& fb = stages.Top().fb;
		fb.is_win_fbo = is_win_fbo;
		fb.size = screen_sz;
		fb.fps = 60;
		if (mode == MULTI_STEREO) {
			for(int i = 0; i < 2; i++) {
				auto& eye_fb = stages[i].fb;
				eye_fb.is_win_fbo = false;
				eye_fb.size = Size(fb.size.cx / 2, fb.size.cy);
				eye_fb.fps = fb.fps;
			}
		}
	}
	
	for (BufferStage& s : stages) {
		if (!s.ImageInitialize())
			return false;
	}
	
	return true;
}

template <class Gfx>
bool BufferT<Gfx>::InitializeRenderer() {
	DLOG("BufferT::Initialize: load new program");
	
	auto& fb = stages.Top().fb;
	
	ASSERT(!is_initialized);
	ASSERT(fb.fps > 0);
	ctx.frame_time = 1.0 / fb.fps;
	ctx.time = GetSysTime();
	ctx.block_offset = 0;
	
	EnableGfxAccelDebugMessages(true);
	
	for (BufferStage& s : stages) {
		if (!s.SetupLoopback())
			return false;
		
		if (!s.CompilePrograms())
			return false;
		
		s.RefreshPipeline();
	}
	
	Reset();
	
	// not here, because opengl will crash: FindVariables();
	
	// Send signal to ecs
	for (String& s : link_ids)
		WhenLinkInit(s, this);
	
	EnableGfxAccelDebugMessages(false);
	
	is_initialized = true;
	
	return true;
}

template <class Gfx>
void BufferT<Gfx>::Reset() {
	ctx.time_total = 0;
}


template <class Gfx>
bool BufferT<Gfx>::LoadInputLink(int in_id, const InternalPacketData& v) {
	if (mode == MULTI_STEREO) {
		return
			stages[0].LoadInputLink(in_id, v) &&
			stages[1].LoadInputLink(in_id, v);
	}
	else {
		return
			stages[0].LoadInputLink(in_id, v);
	}
}

template <class Gfx>
typename BufferT<Gfx>::NativeColorBufferConstRef
BufferT<Gfx>::GetOutputTexture(bool reading_self) const {
	return stages.Top().GetOutputTexture(reading_self);
}

template <class Gfx>
DataStateT<Gfx>& BufferT<Gfx>::GetState() {
	if (mode == MULTI_STEREO) {
		return stereo_data;
	}
	else if (stages.GetCount() == 1) {
		return stages[0].GetState();
	}
	else {
		TODO
	}
}

template <class Gfx>
void BufferT<Gfx>::SetStereoDataState(DataState* s) {
	ASSERT(mode == MULTI_STEREO);
	if (mode == MULTI_STEREO) {
		ASSERT(!s || s->is_stereo);
		ASSERT(stages.GetCount() == 3);
		stages[0].SetStereoDataState(s);
		stages[1].SetStereoDataState(s);
	}
}

template <class Gfx>
void BufferT<Gfx>::SetDataStateOverride(DataState* s) {
	if (mode == MULTI_STEREO) {
		ASSERT(!s || s->is_stereo);
		ASSERT(stages.GetCount() == 3);
		stages[0].SetDataStateOverride(s);
		stages[1].SetDataStateOverride(s);
	}
	else {
		ASSERT(stages.GetCount() == 1);
		auto& stage = stages[0];
		stage.SetDataStateOverride(s);
	}
}

template <class Gfx>
void BufferT<Gfx>::SetFramebufferSize(Size sz) {
	ASSERT(sz.cx > 0 && sz.cy > 0);
	
	TODO
	/*fb.size = sz;
	if (is_stereo) {
		for(int i = 0; i < 2; i++) {
			auto& sfb = stereo_fb[i];
			sfb.size = Size(fb.size.cx / 2, fb.size.cy);
		}
	}*/
	
	TODO /*if (initialized)
		UpdateTexBuffers();*/
}


template <class Gfx>
void BufferT<Gfx>::Process(const RealtimeSourceConfig& cfg) {
	RTLOG("Process " << HexStr(this) << " time: " << ctx.time_total);
	
	if (is_local_time) {
		ASSERT(ctx.frame_time != 0.0);
		ctx.time_total += ctx.frame_time;
	}
	else
		ctx.time_total = cfg.time_total;
	//RTLOG("Process: " << time_total);
	
	
	if (stages.GetCount() == 1) {
		auto& stage = stages[0];
		auto& fb = stage.fb;
		auto& rt = stage.rt;
		
		if (env) {
			if (fb.is_audio) {
				
			}
			else {
				Size& video_size = env->Set<Size>(SCREEN0_SIZE);
				if (video_size.cx == 0 || video_size.cy == 0)
					video_size = fb.size;
				else if (video_size != fb.size) {
					fb.size = video_size;
					stage.UpdateTexBuffers();
				}
			}
		}
		
		ASSERT(rt.prog);
		if (rt.prog == 0)
			return;
		
		if (fb.is_audio) {
			ctx.block_offset += fb.size.cx;
		}
		else {
			ctx.block_offset += 1.0;
		}
		
		stage.Process(cfg);
	}
	else if (stages.GetCount() > 1) {
		ctx.block_offset += 1.0;
		
		if (mode == MULTI_STEREO) {
			ASSERT(stages.GetCount() == 3);
			
			if (env) {
				auto& top_stage = stages.Top();
				auto& top_fb = stages.Top().fb;
				Size& video_size = env->Set<Size>(SCREEN0_SIZE);
				if (video_size.cx == 0 || video_size.cy == 0)
					video_size = top_fb.size;
				else if (video_size != top_fb.size) {
					top_fb.size = video_size;
					top_stage.UpdateTexBuffers();
					
					Size eye_sz(video_size.cx / 2, video_size.cy);
					for(int i = 0; i < 2; i++) {
						auto& eye_stage = stages[i];
						auto& eye_fb = eye_stage.fb;
						eye_fb.size = eye_sz;
						eye_stage.UpdateTexBuffers();
					}
				}
			}
			
			auto& left = stages[0];
			auto& right = stages[1];
			auto& top_stage = stages.Top();
			if (top_stage.data.objects.IsEmpty())
				for(int i = 0; i < 2; i++)
					top_stage.MakeFrameQuad();
			ASSERT(top_stage.data.objects.GetCount() == 2);
			mat4 scale_mat = Scale(vec3(0.5, 1.0, 1.0));
			for(int i = 0; i < 2; i++) {
				DataObject& o = top_stage.data.objects[i];
				//mat4 trans_mat = Translate(vec3(i == 0 ? -1 : +1, i == 0 ? 0 : -0.2, 0));
				mat4 trans_mat = Translate(vec3(i == 0 ? -1 : +1, 0, 0));
				mat4 model = scale_mat * trans_mat;
				o.model = model;
			}
			
			top_stage.data.textures.SetCount(2);
			for(int i = 0; i < 2; i++) {
				BufferStage& stage = stages[i];
				DataObject& o = top_stage.data.objects[i];
				o.tex_id[TEXTYPE_DIFFUSE] = i;
				o.tex_filter[TEXTYPE_DIFFUSE] = 1;
				top_stage.data.textures[i] = stage.fb.color_buf[stage.fb.buf_i];
			}
			
			for (BufferStage& s : stages)
				s.Process(cfg);
			
			top_stage.data.textures.SetCount(0); // top_stage doesn't own textures
			
		}
		else TODO
	}
	
	ctx.frames++;
}













template <class Gfx>
void BufferT<Gfx>::OnError(const char* fn, String s) {
	LOG("BufferT: error: " << (String)fn << ": " << s);
	String e;
	e << fn << ": " << s;
	SetError(e);
}

template <class Gfx>
void BufferT<Gfx>::StoreOutputLink(InternalPacketData& v) {
	static_assert(sizeof(v.u32) == sizeof(uint32), "Unexpected GLuint size");
	
	if (stages.GetCount()) {
		v.SetText("gfxbuf");
		v.ptr = static_cast<GfxBufferStage*>(&stages.Top());
	}
}




GFX3D_EXCPLICIT_INITIALIZE_CLASS(BufferT)


NAMESPACE_PARALLEL_END
