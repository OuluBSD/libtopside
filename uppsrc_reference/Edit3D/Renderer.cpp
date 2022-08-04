#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN


void DrawRect(Size sz, Draw& d, const mat4& view, const vec3& p, Size rect_sz, const Color& c) {
	vec3 pp = VecMul(view, p);
	float x = (pp[0] + 1) * 0.5 * sz.cx - rect_sz.cx / 2;
	float y = (pp[1] + 1) * 0.5 * sz.cy - rect_sz.cy / 2;
	d.DrawRect(x, y, rect_sz.cx, rect_sz.cy, c);
}

void DrawLine(Size sz, Draw& d, const mat4& view, const vec3& a, const vec3& b, int line_width, const Color& c) {
	vec3 ap = VecMul(view, a);
	vec3 bp = VecMul(view, b);
	float x0 = (ap[0] + 1) * 0.5 * sz.cx;
	float x1 = (bp[0] + 1) * 0.5 * sz.cx;
	float y0 = (ap[1] + 1) * 0.5 * sz.cy;
	float y1 = (bp[1] + 1) * 0.5 * sz.cy;
	d.DrawLine(x0, y0, x1, y1, line_width, c);
}








EditRenderer::EditRenderer() {
	SetFrame(BlackFrame());
	WantFocus();
	
}

void EditRenderer::Paint(Draw& d) {
	Size sz = GetSize();
	d.DrawRect(sz, owner->conf.background_clr);
	
	GeomCamera& camera = GetGeomCamera();
	Camera cam;
	camera.LoadCamera(view_mode, cam, sz);
	Frustum frustum = cam.GetFrustum();
	mat4 view = cam.GetViewMatrix();
	
	{
		Color clr = White();
		
		for (OctreePointModel& o : owner->prj.octrees) {
			OctreeFrustumIterator iter = o.octree.GetFrustumIterator(frustum);
			
			while (iter) {
				const OctreeNode& n = *iter;
				
				for (const auto& one_obj : n.objs) {
					const OctreeObject& obj = *one_obj;
					vec3 pos = obj.GetPosition();
					vec3 cam_pos = VecMul(view, pos);
					//DUMP(pos);
					//DUMP(cam_pos);
					
					float x = (cam_pos[0] + 1) * 0.5 * sz.cx;
					float y = (cam_pos[1] + 1) * 0.5 * sz.cy;
					
					d.DrawRect(x, y, 1, 1, clr);
				}
				
				iter++;
			}
		}
	}
	
	if (1) {
		Color clr = Color(255, 255, 172);
		
		Vector<vec3> corners;
		{
			Camera cam;
			owner->state.program.LoadCamera(VIEWMODE_PERSPECTIVE, cam, sz);
			mat4 view = cam.GetViewMatrix();
			Frustum frustum = cam.GetFrustum();
			
			corners.SetCount(8);
			frustum.GetCorners(corners.Begin());
		}
		
		DrawRect(sz, d, view, owner->state.program.position, Size(2,2), clr);
		
		int lw = 1;
		DrawLine(sz, d, view, corners[0], corners[1], lw, clr);
		DrawLine(sz, d, view, corners[2], corners[3], lw, clr);
		DrawLine(sz, d, view, corners[4], corners[5], lw, clr);
		DrawLine(sz, d, view, corners[6], corners[7], lw, clr);
		
		DrawLine(sz, d, view, corners[0], corners[2], lw, clr);
		DrawLine(sz, d, view, corners[1], corners[3], lw, clr);
		DrawLine(sz, d, view, corners[4], corners[6], lw, clr);
		DrawLine(sz, d, view, corners[5], corners[7], lw, clr);
		
		DrawLine(sz, d, view, corners[0], corners[7], lw, clr);
		DrawLine(sz, d, view, corners[1], corners[6], lw, clr);
		DrawLine(sz, d, view, corners[2], corners[5], lw, clr);
		DrawLine(sz, d, view, corners[3], corners[4], lw, clr);
	}
	
	//LOG("");
	
}

void EditRenderer::LeftDown(Point p, dword keyflags) {
	GeomCamera& camera = GetGeomCamera();
	
	cap_mouse_pos = p;
	is_captured_mouse = true;
	cap_begin_pos = camera.position;
	
	SetCapture();
	
	SetFocus();
}

void EditRenderer::LeftUp(Point p, dword keyflags) {
	is_captured_mouse = false;
	
	ReleaseCapture();
}

void EditRenderer::MouseMove(Point p, dword keyflags) {
	GeomCamera& camera = GetGeomCamera();
	
	if (is_captured_mouse) {
		Point diff = p - cap_mouse_pos;
		float s = owner->conf.mouse_move_sensitivity * camera.scale;
		vec3 v(diff.x * s, -diff.y * s, 0);
		MoveRel(v);
	}
}

void EditRenderer::Move(const vec3& v) {
	GeomCamera& camera = GetGeomCamera();
	
	switch (view_mode) {
		case VIEWMODE_YZ:
			camera.position += VecMul(YRotation(M_PI/2), v);
			break;
			
		case VIEWMODE_XZ:
			camera.position += VecMul(XRotation(-M_PI/2), v);
			break;
			
		case VIEWMODE_XY:
			camera.position += VecMul(YRotation(0), v);
			break;
			
		case VIEWMODE_PERSPECTIVE:
			camera.position += VecMul(QuatMat(camera.orientation), v);
			break;
			
	}

	owner->RefrehRenderers();
}

void EditRenderer::MoveRel(const vec3& v) {
	GeomCamera& camera = GetGeomCamera();
	
	switch (view_mode) {
		case VIEWMODE_YZ:
			camera.position = cap_begin_pos + VecMul(YRotation(M_PI/2), v);
			break;
			
		case VIEWMODE_XZ:
			camera.position = cap_begin_pos + VecMul(XRotation(-M_PI/2), v);
			break;
			
		case VIEWMODE_XY:
			camera.position = cap_begin_pos + VecMul(YRotation(0), v);
			break;
			
		case VIEWMODE_PERSPECTIVE:
			camera.position = cap_begin_pos + VecMul(QuatMat(camera.orientation), v);
			break;
			
	}

	owner->RefrehRenderers();
}

void EditRenderer::Rotate(const axes3& v) {
	GeomCamera& camera = GetGeomCamera();
	
	camera.orientation = MatQuat(QuatMat(camera.orientation) * AxesMat(v));
	
	owner->RefrehRenderers();
}

void EditRenderer::MouseWheel(Point p, int zdelta, dword keyflags) {
	const double scale = 0.75;
	GeomCamera& camera = GetGeomCamera();
	
	if (zdelta < 0) {
		camera.scale /= scale;
	}
	else {
		camera.scale *= scale;
	}
	
	owner->RefrehRenderers();
}

GeomCamera& EditRenderer::GetGeomCamera() const {
	switch (cam_src) {
		
	case CAMSRC_FOCUS:
		return owner->state.focus;
		break;
		
	case CAMSRC_PROGRAM:
		return owner->state.program;
		break;
		
	}
	Panic("Invalid viewm mode in EditRenderer");
	NEVER();
}

bool EditRenderer::Key(dword key, int count) {
	GeomCamera& camera = GetGeomCamera();
	float step = camera.scale * 0.1;
	
	bool is_shift = key & K_SHIFT;
	bool is_ctrl = key & K_CTRL;
	bool is_release = key & K_UP;
	key &= 0xFFFF | K_DELTA;
	
	if (is_shift) {
		if (key == K_LEFT) {
			Move(VEC_LEFT * step);
			return true;
		}
		else if (key == K_RIGHT) {
			Move(VEC_RIGHT * step);
			return true;
		}
		else if (key == K_UP) {
			Move(VEC_FWD * step);
			return true;
		}
		else if (key == K_DOWN) {
			Move(VEC_BWD * step);
			return true;
		}
	}
	else if (is_ctrl) {
		step = 0.1;
		if (key == K_LEFT) {
			Rotate(VEC_ROT_LEFT * step);
			return true;
		}
		else if (key == K_RIGHT) {
			Rotate(VEC_ROT_RIGHT * step);
			return true;
		}
		else if (key == K_UP) {
			Rotate(VEC_ROT_UP * step);
			return true;
		}
		else if (key == K_DOWN) {
			Rotate(VEC_ROT_DOWN * step);
			return true;
		}
	}
	else {
		if (key == K_LEFT) {
			Move(VEC_LEFT * step);
			return true;
		}
		else if (key == K_RIGHT) {
			Move(VEC_RIGHT * step);
			return true;
		}
		else if (key == K_UP) {
			Move(VEC_UP * step);
			return true;
		}
		else if (key == K_DOWN) {
			Move(VEC_DOWN * step);
			return true;
		}
	}
	
	return false;
}


NAMESPACE_TOPSIDE_END
