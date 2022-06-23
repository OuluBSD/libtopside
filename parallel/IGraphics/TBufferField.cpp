#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
bool GfxBufferFieldT<Gfx>::Initialize(AtomBase& a, const Script::WorldState& ws) {
	
	if (ws.IsTrue(".is.stereo"))
		buf.SetStereoImage();
	
	sample_rate = ws.GetInt(".samplerate", 44100);
	frame_samples = ws.GetInt(".frame_samples", 1024);
	is_audio = ws.Get(".type") == "audio";
	buf.SetLocalTime(ws.GetBool(".retarded_local_time", false));
	
	buf.AddLink(ws.Get(".link"));
	
	frag_path = ws.Get(".fragment");
	vtx_path = ws.Get(".vertex");
	frag_shdr = ws.Get(".fragshader");
	vtx_shdr = ws.Get(".vtxshader");
	library_paths = ws.Get(".library");
	stereo_frag_path = ws.Get(".stereo.fragment");
	stereo_vtx_path = ws.Get(".stereo.vertex");
	
	if (frag_path.IsEmpty()) frag_path = ws.Get(".filepath");
	
	
	String program_str = ws.Get(".program");
	if (program_str.GetCount()) {
		frag_path = "<builtin>";
		vtx_path = "<builtin>";
		frag_shdr = program_str + "_fragment";
		vtx_shdr = program_str + "_vertex";
	}
	else {
		if (frag_shdr.GetCount()) frag_shdr += "_fragment";
		if (vtx_shdr.GetCount())  vtx_shdr  += "_vertex";
	}
	
	
	if (frag_path.IsEmpty() && frag_shdr.IsEmpty()) {
		LOG("GfxBufferFieldT<Gfx>::Initialize: error: no fragment shader given");
		return false;
	}
	if (frag_path.GetCount())
		is_user_shader = true;
	
	frag_path = RealizeShareFile(frag_path);
	vtx_path = RealizeShareFile(vtx_path);
	
	
	
	String loopback = ws.Get(".loopback");
	if (loopback.GetCount()) {
		if (!buf.stages[0].SetLoopback(loopback)) {
			LOG("GfxBufferFieldT<Gfx>::Initialize: error: assigning loopback failed");
			return false;
		}
	}
	
	
	// SDL2ScreenBase duplicate
	TODO
	/*for(int i = 0; i < 4; i++) {
		String key = ".buf" + IntStr(i);
		String value = ws.Get(key);
		if (value.IsEmpty())
			;
		else if (value == "volume")
			buf.SetInputVolume(i);
		else if (value == "cubemap")
			buf.SetInputCubemap(i);
		else
			TODO
	}*/
	
	
	String env_name = ws.Get(".env");
	if (!env_name.IsEmpty()) {
		SpaceRef l = a.GetSpace();
		env = l->FindNearestState(env_name);
		if (!env) {
			LOG("GfxBufferFieldT<Gfx>::Initialize: error: environment state with name '" << env_name << "' not found");
			return false;
		}
	}
	buf.SetEnvState(env);
	buf.AddLink(ws.Get(".link"));
	
	
	//SetShaderFile(frag_path, vtx_path, library_paths);
	SetFragmentShader(frag_shdr);
	SetVertexShader(vtx_shdr);
	
	
	
	/*ISourceRef src = a.GetSource();
	if (is_audio) {
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
	//if (is_audio)
	//	a.GetSink()->GetValue(0).SetMinQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
	
	return true;
}

template <class Gfx>
bool GfxBufferFieldT<Gfx>::ImageInitialize(bool is_win_fbo, Size screen_sz) {
	if (screen_sz.cx == 0 && screen_sz.cy == 0) {
		if (env) {
			Size* video_size = env->Get<Size>(SCREEN0_SIZE);
			if (video_size)
				screen_sz = *video_size;
		}
		if (screen_sz.cx == 0 && screen_sz.cy == 0)
			screen_sz = Size(1280,720);
	}
	
	TODO
	
	#if 0
	{
		auto& fb = buf.GetFramebuffer();
		fb.is_win_fbo = is_win_fbo;
		fb.size = screen_sz;
		fb.fps = 60;
	}
	
	
	
	if (!buf.LoadShader(GVar::FRAGMENT_SHADER, frag_shdr, frag_path, library_paths))
		return false;
	
	if (vtx_shdr.IsEmpty() && vtx_path.IsEmpty())
		; // pass
	else if (!buf.LoadShader(GVar::VERTEX_SHADER, vtx_shdr, vtx_path, library_paths))
		return false;
	
	if (stereo_vtx_path.GetCount() &&
		stereo_frag_path.GetCount() &&
		!buf.LoadStereoShader(stereo_vtx_path, stereo_frag_path))
		return false;
	
	/*if (!buf.Initialize()) {
		LOG("GfxBufferFieldT<Gfx>::ImageInitialize: error: " << buf.GetError());
		return false;
	}*/
	
	#endif
	
	return true;
}

template <class Gfx>
bool GfxBufferFieldT<Gfx>::PostInitialize() {
	auto& fb = buf.GetFramebuffer();
	fb.is_audio = is_audio;
	
	buf.ctx.sample_rate = sample_rate;
	
	if (!fb.is_win_fbo) {
		if (!is_audio) {
			fb.size = Size(1280,720);
			fb.channels = 4;
			fb.fps = 60;
			fb.sample = GVar::SAMPLE_FLOAT;
		}
		else {
			fb.size = Size(frame_samples,1);
			fb.channels = 2;
			fb.fps = (double)sample_rate / frame_samples;
			fb.sample = GVar::SAMPLE_U16;
		}
	}
	
	if (!buf.Initialize()){
		LOG("GfxBufferFieldT<Gfx>::PostInitialize: error: " << buf.GetError());
		return false;
	}
	
	return true;
}



GFX3D_EXCPLICIT_INITIALIZE_CLASS(GfxBufferFieldT)


NAMESPACE_PARALLEL_END
