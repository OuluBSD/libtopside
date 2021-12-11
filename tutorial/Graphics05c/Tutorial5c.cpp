#include "Tutorial5c.h"

/*
Tutorial 5b:
	Same as tutorial 5a, but with more complex cpu shader class usage
	
*/


Tutorial5c::Tutorial5c() {
	
}

Tutorial5c::~Tutorial5c() {
	if (zbuffer) {
		delete zbuffer;
		delete zbuffer_empty;
	}
	zbuffer = 0;
	zbuffer_empty = 0;
}

void Tutorial5c::Initialize() {
	Serial::EcsVideoBase::Latest().AddBinder(this);
}

void Tutorial5c::Render(Draw& fb) {
	StateDraw* sd = CastPtr<StateDraw>(&fb);
	ASSERT(sd);
	
	if (frame == 0) {
		FramebufferState& state = sd->GetState();
		String data_dir = ShareDirFile("models");
		String obj_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head.obj");
		String tex_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head_diffuse.tga");
		if (!loader.LoadModel(state, state.NewObject(), obj_path))
			Panic("Couldn't load model: " + obj_path);
		loader.GetModel()->AddTextureFile(0, TEXTYPE_DIFFUSE, tex_path);
		state.stages[GVar::VERTEX_SHADER] = &vtx;
		state.stages[GVar::FRAGMENT_SHADER] = &frag;
	}
	
	Size sz = fb.GetPageSize();
	height = width = std::min(sz.cx, sz.cy);
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

SIMPLE_ECS_APP(Tutorial5c, "geom_tutorial_base_ogl.eon")
