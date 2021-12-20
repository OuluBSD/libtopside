#include "Tutorial4.h"

/*
Tutorial 4:
	This a variation of the tutorial "Lesson 4 Perspective projection"
	
	Source: https://github.com/ssloy/tinyrenderer/wiki/Lesson-4-Perspective-projection
*/


Tutorial4::Tutorial4() {
	String data_dir = ShareDirFile("models");
	String obj_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head.obj");
	String tex_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head_diffuse.tga");
	auto& o = state.AddObject();
	if (!state.LoadModel(loader, o, obj_path))
		Panic("Couldn't load model: " + obj_path);
	loader.GetModel()->AddTextureFile(0, TEXTYPE_DIFFUSE, tex_path);
	if (!state.LoadModelTextures(loader, o))
		Panic("Couldn't load model textures: " + obj_path);
	
	vec3 tl(-1, +1, 1);
	vec3 tc( 0, +1, 1);
	vec3 cr(+1,  0, 1);
	vec3 br(+1, -1, 1);
	vec3 bl(-1, -1, 1);
	lines.Add().Set(tl, tc);
	lines.Add().Set(tc, cr);
	lines.Add().Set(cr, br);
	lines.Add().Set(br, bl);
	lines.Add().Set(bl, tl);
	unit_x.Set(vec3{0,0,0}, vec3{1,0,0});
	unit_y.Set(vec3{0,0,0}, vec3{0,1,0});
}

Tutorial4::~Tutorial4() {
	if (zbuffer) {
		delete zbuffer;
		delete zbuffer_empty;
	}
	zbuffer = 0;
	zbuffer_empty = 0;
}

void Tutorial4::Initialize() {
	Serial::EcsVideoBase::Latest().AddBinder(this);
}

void Tutorial4::Begin() {trans_lines <<= lines;}

void Tutorial4::DrawLine(Draw& fb, const line3& l, Color clr) {
	double mul = 0.2;
	int x0 = (l.a[0] * mul + 1.0) * width * 0.5;
	int x1 = (l.b[0] * mul + 1.0) * width * 0.5;
	int y0 = (l.a[1] * mul + 1.0) * height * 0.5;
	int y1 = (l.b[1] * mul + 1.0) * height * 0.5;
	fb.DrawLine(x0, y0, x1, y1, 1, clr);
}

void Tutorial4::Draw0(Draw& fb) {
	DrawLine(fb, unit_x, red);
	DrawLine(fb, unit_y, green);
	for(line3& l: lines)       DrawLine(fb, l, white);
	for(line3& l: trans_lines) DrawLine(fb, l, yellow);
}

void Tutorial4::MultiplyBy(mat2 v) {
	for(line3& l: trans_lines) {
		vec2 a = l.a.Splice<0, 2>(), b = l.b.Splice<0, 2>();
		a = v * a;
		b = v * b;
		l.a.SetFromSplice<0, 2>(a);
		l.b.SetFromSplice<0, 2>(b);
	}
}

void Tutorial4::MultiplyBy(mat3 v) {
	for(line3& l: trans_lines) {
		l.a = v * l.a;
		l.b = v * l.b;
	}
}

void Tutorial4::Add(vec2 v) {
	for(line3& l: trans_lines) {
		l.a += v;
		l.b += v;
	}
}

void Tutorial4::Project() {
	for(line3& l: trans_lines) {
		l.a.Project();
		l.b.Project();
	}
}

void Tutorial4::Render(Draw& fb) {
	Size sz = fb.GetPageSize();
	height = width = std::min(sz.cx, sz.cy);
	fb.DrawRect(sz, Black());
	
	float f = (float)iter / (float)iters_in_phase;
	float f2 = 1 - fabs(2 * f - 1);
	float angle = f2 * 0.25 * M_2PI;
	float x = cos(angle);
	float y = sin(angle);

	if (phase == 0) {
		Begin();
		MultiplyBy(mat2 {vec2{1.0f + f2, 0.0f}, vec2{0.0f, 1.0f + f2}});
		Draw0(fb);
	}
	else if (phase == 1) {
		Begin();
		MultiplyBy(mat2 {vec2{1.0f, f2}, vec2{0.0f, 1.0f}});
		Draw0(fb);
	}
	else if (phase == 2) {
		Begin();
		MultiplyBy(mat2 {vec2{x, -y}, vec2{y, x}});
		Draw0(fb);
	}
	else if (phase == 3) {
		Begin();
		Add(vec2{f2, f2});
		Draw0(fb);
	}
	else if (phase == 4) {
		Begin();
		MultiplyBy(mat3 {vec3 {x, -1*y, 2*f2}, vec3 {y, x, -2*f2}, vec3 {0,0,1}});
		Project();
		Draw0(fb);
	}
	else if (phase == 5) {
		Begin();
		MultiplyBy(mat3 {vec3 {1,0,0}, vec3 {0,1,0}, vec3 {f2/-4.f, 0,1}});
		Project();
		Draw0(fb);
	}
	else if (phase == 6) {
		DrawObj(f2, fb, false);
	}
	else if (phase == 7) {
		DrawObj(f2, fb, true);
	}
	
	iter++;
	if (iter >= iters_in_phase) {
		iter = 0;
		phase = (phase + 1) % phases;
	}
	
}

SIMPLE_ECS_APP_(Tutorial4, "geom_tutorial_base.eon", "FRAGMENT=;VERTEX=;DRAWMEM=true")

