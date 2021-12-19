#include "Tutorial5b.h"

/*
Tutorial 5b:
	Same as tutorial 5a, but with more complex cpu shader class usage
	
*/

INITBLOCK_(Shaders) {
	using namespace TS;
	SoftShaderLibrary::AddShaderClass<VertexShader5>(GVar::VERTEX_SHADER, "tutorial5_vertex");
	SoftShaderLibrary::AddShaderClass<FragmentShader5>(GVar::FRAGMENT_SHADER, "tutorial5_fragment");
	
}



Tutorial5b::Tutorial5b() {
	
}

Tutorial5b::~Tutorial5b() {
	if (zbuffer) {
		delete zbuffer;
		delete zbuffer_empty;
	}
	zbuffer = 0;
	zbuffer_empty = 0;
}

void Tutorial5b::Initialize() {
	Serial::EcsVideoBase::Latest().AddBinder(this);
}

void Tutorial5b::Render(Draw& fb) {
	SdlCpuStateDraw* sd = CastPtr<SdlCpuStateDraw>(&fb);
	ASSERT(sd);
	
	if (frame == 0) {
		SdlCpuDataState& state = sd->GetState();
		String data_dir = ShareDirFile("models");
		String obj_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head.obj");
		String tex_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head_diffuse.tga");
		auto& o = state.AddObject();
		if (!state.LoadModel(loader, o, obj_path))
			Panic("Couldn't load model: " + obj_path);
		loader.GetModel()->AddTextureFile(0, TEXTYPE_DIFFUSE, tex_path);
		if (!state.LoadModelTextures(loader, o))
			Panic("Couldn't load model textures: " + obj_path);
	}
	
	Size sz = fb.GetPageSize();
	//height = width = std::min(sz.cx, sz.cy);
	width = 1280;
	height = 720;
	
	//fb.DrawRect(sz, Black());
	
	DrawObj(*sd, true);
	
	iter++;
	frame++;
	if (ts.Seconds() >= phase_time) {
		iter = 0;
		ts.Reset();
		phase = (phase + 1) % phases;
	}
}


SIMPLE_ECS_APP_(Tutorial5b, "geom_tutorial_base.eon", "FRAGMENT=tutorial5_fragment;VERTEX=tutorial5_vertex")
