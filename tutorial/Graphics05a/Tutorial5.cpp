#include "Tutorial5.h"

/*
Tutorial 5:
	This a variation of the tutorial "Lesson 5 Moving the camera"
	
	Source: https://github.com/ssloy/tinyrenderer/wiki/Lesson-5-Moving-the-camera
*/


Tutorial5::Tutorial5() {
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

Tutorial5::~Tutorial5() {
	if (zbuffer) {
		delete zbuffer;
		delete zbuffer_empty;
	}
	zbuffer = 0;
	zbuffer_empty = 0;
}

void Tutorial5::Initialize() {
	Serial::EcsVideoBase::Latest().AddBinder(this);
}

void Tutorial5::Render(Draw& fb) {
	Size sz = fb.GetPageSize();
	//height = width = std::min(sz.cx, sz.cy);
	width = 1280;
	height = 720;
	fb.DrawRect(sz, Black());
	
	DrawObj(fb, true);
	
	iter++;
	if (ts.Seconds() >= phase_time) {
		iter = 0;
		ts.Reset();
		phase = (phase + 1) % phases;
	}
	
}

SIMPLE_ECS_APP_(Tutorial5, "geom_tutorial_base.eon", "FRAGMENT=;VERTEX=;DRAWMEM=true")
