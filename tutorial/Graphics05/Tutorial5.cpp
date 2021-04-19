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
	if (!loader.LoadModel(obj_path))
		Panic("Couldn't load model: " + obj_path);
	loader.model->AddTextureFile(0, TEXTYPE_DIFFUSE, tex_path);
}

Tutorial5::~Tutorial5() {
	if (zbuffer) {
		delete zbuffer;
		delete zbuffer_empty;
	}
	zbuffer = 0;
	zbuffer_empty = 0;
}

void Tutorial5::Render(SystemDraw& fb) {
	Size sz = fb.GetPageSize();
	height = width = std::min(sz.cx, sz.cy);
	fb.DrawRect(sz, Black());
	
	DrawObj(fb, true);
	
	iter++;
	if (iter >= iters_in_phase) {
		iter = 0;
		phase = (phase + 1) % phases;
	}
}


RENDER_APP_(Tutorial5)
