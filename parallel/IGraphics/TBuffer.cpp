#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN

template <class Gfx>
Callback2<String, BufferT<Gfx>*> BufferT<Gfx>::WhenLinkInit;


/*template <class Gfx>
bool BufferT<Gfx>::LoadStereoShader(String vtx_path, String frag_path) {
	if (!LoadShaderFile(stereo_rt, GVar::FRAGMENT_SHADER, frag_path, "")) {
		LOG("BufferT<Gfx>::LoadStereoShader: error: shader loading failed from '" + frag_path + "'");
		return false;
	}
	if (!LoadShaderFile(stereo_rt, GVar::VERTEX_SHADER, vtx_path, "")) {
		LOG("BufferT<Gfx>::LoadStereoShader: error: shader loading failed from '" + vtx_path + "'");
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
bool BufferT<Gfx>::Initialize() {
	DLOG("BufferT::Initialize: load new program");
	
	auto& fb = Single();
	
	TODO
	
	#if 0
	ASSERT(!initialized);
	ASSERT(fb.fps > 0);
	ctx.frame_time = 1.0 / fb.fps;
	ctx.time = GetSysTime();
	ctx.block_offset = 0;
	
	if (!SetupLoopback())
		return false;
	
	EnableGfxAccelDebugMessages(true);
	
	if (!CompilePrograms())
		return false;
	
	RefreshPipeline();
	// not here, because opengl will crash: FindVariables();
	
	for (String& s : link_ids)
		WhenLinkInit(s, this);
	
	EnableGfxAccelDebugMessages(false);
	
	initialized = true;
	#endif
	return true;
}

template <class Gfx>
void BufferT<Gfx>::Reset() {
	ctx.time_total = 0;
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
void BufferT<Gfx>::Process(ShaderPipeline& pipe) {
	
	TODO
	
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
	ctx.frames++;
	
	
	TODO
	
	#if 0
	if (env) {
		if (fb.is_audio) {
			
		}
		else {
			Size& video_size = env->Set<Size>(SCREEN0_SIZE);
			if (video_size.cx == 0 || video_size.cy == 0)
				video_size = fb.size;
			else if (video_size != fb.size) {
				fb.size = video_size;
				UpdateTexBuffers();
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
	
	
	#endif
}













template <class Gfx>
bool BufferT<Gfx>::SetupLoopback() {
	TODO
	
	#if 0
	
	if (loopback < 0)
		return true;
	
	if (loopback >= GVar::INPUT_COUNT) {
		LOG("SetupLoopback: error: too large loopback id #" << loopback);
		return false;
	}
	
	InputState& in = rt.inputs[loopback];
	in.buf = this;
	in.id = rt.id;
	in.type = GVar::BUFFER_INPUT;
	ASSERT(in.buf);
	
	return true;
	#endif
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
	
	v.SetText("gfxbuf");
	v.ptr = static_cast<GfxBuffer*>(this);
}




GFX3D_EXCPLICIT_INITIALIZE_CLASS(BufferT)


NAMESPACE_PARALLEL_END
