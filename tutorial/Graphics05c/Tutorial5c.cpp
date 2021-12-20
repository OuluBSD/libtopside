#include "Tutorial5c.h"

/*
Tutorial 5c:
	Same as tutorial 5b, but with more complex ogl shader class usage
	
*/


Tutorial5c::Tutorial5c() {
	
}

void Tutorial5c::Initialize() {
	Serial::EcsVideoBase::Latest().AddBinder(this);
}

void Tutorial5c::Render(Draw& fb) {
	SdlOglStateDraw* sd = CastPtr<SdlOglStateDraw>(&fb);
	ASSERT(sd);
	
	if (frame == 0) {
		SdlOglDataState& state = sd->GetState();
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
	
	DrawObj(*sd, true);
	
	iter++;
	frame++;
	if (ts.Seconds() >= phase_time) {
		iter = 0;
		ts.Reset();
		phase = (phase + 1) % phases;
	}
}

void Tutorial5c::DrawObj(SdlOglStateDraw& fb, bool use_texture) {
	ASSERT(fb.HasTarget());
	SdlOglDataState& state = fb.GetState();
	
	float ratio = (float)height / (float)width;
	float aspect = (float)width / (float)height;
	float f = ts.Seconds() / phase_time;
	float f2 = 1 - fabs(2 * f - 1);
	float angle = f * (2.0 * M_PI);
	float x = cos(angle);
	float y = sin(angle);
	
	float eye_angle = (use_texture ? -1 : +1) * f /** 0.25*/ * M_2PI;
	float eye_x = cos(eye_angle);
	float eye_y = sin(eye_angle);
	float x_mod = 0.2 * eye_x;
	float y_mod = 0.2 * eye_y;
	mat4 perspective {
		vec4{1,		0,	    0,		0},
		vec4{0,		1,	    0,		0},
		vec4{0,		0,	    1,		0},
		vec4{0,		0, -1./5.,		1}
	};
	
	vec3 eye {0.3f * eye_x, 0.3f * eye_y, 1};
	vec3 center {0, 0, -1};
	vec3 up {0, 1, 0};
	mat4 lookat = LookAt(eye, center, up);
	mat4 port;
	
	/*if (phase == 0)
		port = GetViewport((-1 + x_mod) * ratio, -1 + y_mod, (2 - x_mod) * ratio, 2 + y_mod, 1);
	else*/
		port = GetViewport(-1 * ratio, -1, 2 * ratio, 2, 1);
	
	state.view = port * perspective * lookat;
	state.light_dir = vec3 {sin(angle), 0.0, cos(angle)};
	
}

SIMPLE_ECS_APP_(Tutorial5c, "geom_tutorial_base_ogl.eon", "FRAGMENT=fragment.glsl;VERTEX=vertex.glsl")
