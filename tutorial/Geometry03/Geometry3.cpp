#include "Geometry3.h"


Geometry3::Geometry3() {
	int w = 800, h = 600;
	float aspect = (float)h / (float)w;
	
	// Set projection for the Draw function
	mat4 persp;
	float vert = (1 + 0.1) * 2;
	float horz = vert / aspect;
	persp.SetOrtographic(-horz, +horz, -vert, +vert, 4, -4);
	
	// The default area is between -1 and +1. Project it to 0 and +600.
	mat4 vport = GetViewport(0, 0, w, h, 255); // default
	
	// Use LookAt function to "move the camera"
	vec3 eye {0, 0, -1};
	vec3 center {0, 0, 0};
	vec3 up {0, 1, 0};
	mat4 lookat = LookAt(eye, center, up);
	
	// The leftmost matrix is processed first for the line
	view = vport * persp * lookat;
}

Geometry3::~Geometry3() {
	
}

void Geometry3::Initialize() {
	Serial::EcsVideoBase::Latest().AddBinder(this);
}

void Geometry3::Render(Draw& draw) {
	draw.DrawRect(draw.GetPageSize(), Black());
	
	DrawGeometry fb(draw);

	Color white {255, 255, 255};
	Color red {255, 0, 0};
	Color green {0, 255, 0};
	Color blue {0, 0, 255};
	Color orange {255, 128, 0};
	Color yellow {255, 255, 0};
	Color pink {255, 42, 150};
	Color purple {170, 42, 150};
	Color lt_blue {28, 255, 255};
	
	
	if (!launched) {
		launched = true;
		a_avel = RandomAngularVel();
		b_avel = RandomAngularVel();
		
		if (phase == 0) {ResetShape(a, SHAPE2_LINE, 0);			ResetShape(b, SHAPE2_CIRCLE, 1);}
		if (phase == 1) {ResetShape(a, SHAPE2_LINE, 0);			ResetShape(b, SHAPE2_RECT, 1);}
		if (phase == 2) {ResetShape(a, SHAPE2_LINE, 0);			ResetShape(b, SHAPE2_ORIENTRECT, 1);}
		if (phase == 3) {ResetShape(a, SHAPE2_CIRCLE, 0);		ResetShape(b, SHAPE2_CIRCLE, 1);}
		if (phase == 4) {ResetShape(a, SHAPE2_CIRCLE, 0);		ResetShape(b, SHAPE2_RECT, 1);}
		if (phase == 5) {ResetShape(a, SHAPE2_CIRCLE, 0);		ResetShape(b, SHAPE2_ORIENTRECT, 1);}
		if (phase == 6) {ResetShape(a, SHAPE2_RECT, 0);			ResetShape(b, SHAPE2_RECT, 1);}
		if (phase == 7) {ResetShape(a, SHAPE2_RECT, 0);			ResetShape(b, SHAPE2_ORIENTRECT, 1);}
		if (phase == 8) {ResetShape(a, SHAPE2_ORIENTRECT, 0);	ResetShape(b, SHAPE2_ORIENTRECT, 1);}
	}
	
	float step_mul = 0.001;
	
	float step = ts.Elapsed();
	vec2 right {step * step_mul * vel, 0};
	vec2 left {-step * step_mul * vel, 0};
	ts.Reset();
	a.shape->Move(right);
	b.shape->Move(left);
	
	a.shape->Rotate(step * step_mul * a_avel);
	b.shape->Rotate(step * step_mul * b_avel);
	
	static Vector<line2> a_lines, b_lines;
	a_lines.SetCount(0);
	b_lines.SetCount(0);
	a.shape->GetFaces(a_lines);
	b.shape->GetFaces(b_lines);
	for(line2& l : a_lines)
		DrawLine(fb, l.a, l.b, red);
	for(line2& l : b_lines)
		DrawLine(fb, l.a, l.b, blue);
	
	vec2 tl {-1, 1}, tr {1, 1}, br {1, -1}, bl {-1, -1};
	DrawLine(fb, tl, tr, white);
	DrawLine(fb, tr, br, white);
	DrawLine(fb, br, bl, white);
	DrawLine(fb, bl, tl, white);
	
	if (a.shape->GetPos()[0] >= 1.0 ||
		b.shape->GetPos()[0] <= -1.0 ||
		a.shape->Intersects(*b.shape)) {
		phase = (phase + 1) % phases;
		launched = false;
	}
}

void Geometry3::DrawLine(DrawGeometry& fb, vec2 a, vec2 b, Color clr) {
	a = (view * a.Embed<4>()).Project().Splice<0,2>();
	b = (view * b.Embed<4>()).Project().Splice<0,2>();
	fb.DrawLine(a, b, 1, clr);
}

void Geometry3::ResetShape(Shape2DWrapper& s, ShapeId shape_type, bool is_right) {
	vec2 a {0, 0}, b {0, 0};
	float f = 0;
	float w = 0.1 + Randomf() * 0.4;
	float h = 0.1 + Randomf() * 0.4;
	if (shape_type == SHAPE2_LINE) {
		b = vec2 {0, w};
	}
	else if (shape_type == SHAPE2_CIRCLE) {
		f = w;
	}
	else if (shape_type == SHAPE2_RECT) {
		a.Set(w / -2.0f, w / -2.0f);
		b.Set(w, w);
	}
	else if (shape_type == SHAPE2_ORIENTRECT) {
		b.Set(w * 0.5f, h * 0.5f);
		f = Randomf() * M_2PI;
	}
	s.Create(shape_type, a, b, f);
	
	if (!is_right)	s.shape->Move(vec2 {-1, 0});
	else			s.shape->Move(vec2 {+1, 0});
}

SIMPLE_ECS_APP_(Geometry3, "geom_tutorial_base.eon", "FRAGMENT=;VERTEX=;DRAWMEM=true")
