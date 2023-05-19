#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN


void DrawRect(Size sz, Draw& d, const mat4& view, const vec3& p, Size rect_sz, const Color& c, bool z_cull) {
	vec3 pp = VecMul(view, p);
	/*if (z_cull && pp[2] * SCALAR_FWD_Z > 0)
		return;*/
	float x = (pp[0] + 1) * 0.5 * sz.cx - rect_sz.cx / 2;
	float y = (-pp[1] + 1) * 0.5 * sz.cy - rect_sz.cy / 2;
	d.DrawRect(x, y, rect_sz.cx, rect_sz.cy, c);
}

void DrawLine(Size sz, Draw& d, const mat4& view, const vec3& a, const vec3& b, int line_width, const Color& c, bool z_cull) {
	vec3 ap = VecMul(view, a);
	vec3 bp = VecMul(view, b);
	/*if (z_cull && (ap[2] * SCALAR_FWD_Z > 0 || bp[2] * SCALAR_FWD_Z > 0))
		return;*/
	if ((ap[0] < -1 || ap[0] > +1) && (ap[1] < -1 || ap[1] > +1) &&
		(bp[0] < -1 || bp[0] > +1) && (bp[0] < -1 || bp[0] > +1))
		return;
	float x0 = (ap[0] + 1) * 0.5 * sz.cx;
	float x1 = (bp[0] + 1) * 0.5 * sz.cx;
	float y0 = (-ap[1] + 1) * 0.5 * sz.cy;
	float y1 = (-bp[1] + 1) * 0.5 * sz.cy;
	d.DrawLine(x0, y0, x1, y1, line_width, c);
}

void DrawLine(Size sz, Draw& d, const mat4& view, const Vertex& a, const Vertex& b, int line_width, const Color& c, bool z_cull) {
	DrawLine(sz, d, view, a.position.Splice(), b.position.Splice(), line_width, c, z_cull);
}








EditRenderer::EditRenderer() {
	SetFrame(BlackFrame());
	WantFocus();
	
}

void EditRenderer::PaintObject(Draw& d, const GeomObjectState& os, const mat4& view, const Frustum& frustum) {
	GeomObject& go = *os.obj;
	Size sz = GetSize();
	Color clr = White();
	int lw = 1;
	bool z_cull = view_mode == VIEWMODE_PERSPECTIVE;
	
	mat4 o_world = (QuatMat(os.orientation) * Translate(os.position)).GetInverse();
	mat4 o_view = view * o_world;
	
	if (go.IsModel()) {
		if (!go.mdl)
			return;
		
		const Model& mdl = *go.mdl;
		for (const Mesh& mesh : mdl.meshes) {
			int tri_count = mesh.indices.GetCount() / 3;
			const uint32* tri_idx = mesh.indices.Begin();
			for(int i = 0; i < tri_count; i++) {
				const Vertex& v0 = mesh.vertices[tri_idx[0]];
				const Vertex& v1 = mesh.vertices[tri_idx[1]];
				const Vertex& v2 = mesh.vertices[tri_idx[2]];
				
				bool b0 = frustum.Intersects(v0.position.Splice());
				bool b1 = frustum.Intersects(v1.position.Splice());
				bool b2 = frustum.Intersects(v2.position.Splice());
				
				if (b0 || b1) DrawLine(sz, d, o_view, v0, v1, lw, clr, z_cull);
				if (b1 || b2) DrawLine(sz, d, o_view, v1, v2, lw, clr, z_cull);
				if (b2 || b0) DrawLine(sz, d, o_view, v2, v0, lw, clr, z_cull);
				
				tri_idx += 3;
			}
		}
		
	}
	else if (go.IsOctree()) {
		Octree& o = go.octree_ptr ? *go.octree_ptr : go.octree.octree;
		OctreeFrustumIterator iter = o.GetFrustumIterator(frustum);
		
		while (iter) {
			const OctreeNode& n = *iter;
			
			for (const auto& one_obj : n.objs) {
				
				const OctreeObject& obj = *one_obj;
				vec3 pos = obj.GetPosition();
				
				if (!frustum.Intersects(pos))
					continue;
				
				vec3 cam_pos = VecMul(o_view, pos);
				
				float x = (cam_pos[0] + 1) * 0.5 * sz.cx;
				float y = (-cam_pos[1] + 1) * 0.5 * sz.cy;
				
				d.DrawRect(x, y, 1, 1, clr);
			}
			
			iter++;
		}
	}
}

void EditRenderer::Paint(Draw& d) {
	Size sz = GetSize();
	d.DrawRect(sz, owner->conf.background_clr);
	
	GeomWorldState& state = owner->state;
	GeomScene& scene = state.GetActiveScene();
	GeomCamera& camera = GetGeomCamera();
	
	Camera cam;
	camera.LoadCamera(view_mode, cam, sz);
	Frustum frustum = cam.GetFrustum();
	mat4 view = cam.GetViewMatrix();
	bool z_cull = view_mode == VIEWMODE_PERSPECTIVE;
	
	/*if (view_mode == VIEWMODE_PERSPECTIVE) {
		mat4 world = cam.GetWorldMatrix();
		mat4 proj = cam.GetProjectionMatrix();
		//proj.SetPerspectiveRH_NO(DEG2RAD(120/2), (float)sz.cx / sz.cy, 0.1, 100.0);
		view = proj * world;
	}*/
	
	if (cam_src == CAMSRC_VIDEOIMPORT_FOCUS ||
		cam_src == CAMSRC_VIDEOIMPORT_PROGRAM) {
		int frame_i = owner->anim.position;
		if (frame_i < 0 || frame_i >= owner->video.uncam.frames.GetCount())
			return;
		UncameraFrame& frame = owner->video.uncam.frames[frame_i];
		
		GeomObjectState os;
		GeomObject go;
		go.type = GeomObject::O_OCTREE;
		os.obj = &go;
		go.octree_ptr = &frame.otree;
		PaintObject(d, os, view, frustum);
	}
	if (owner->anim.is_playing) {
		for (GeomObjectState& os : state.objs) {
			PaintObject(d, os, view, frustum);
		}
	}
	else {
		GeomObjectCollection iter(scene);
		GeomObjectState os;
		for (GeomObject& go : iter) {
			os.obj = &go;
			PaintObject(d, os, view, frustum);
		}
	}
	
	
	if (&camera != &owner->state.program) {
		Color clr = Color(255, 255, 172);
		
		Vector<vec3> corners;
		{
			Camera cam;
			owner->state.program.LoadCamera(VIEWMODE_PERSPECTIVE, cam, sz, 3.0);
			Frustum frustum = cam.GetFrustum();
			corners.SetCount(8);
			frustum.GetCorners(corners.Begin());
		}
		
		DrawRect(sz, d, view, owner->state.program.position, Size(2,2), clr, z_cull);
		
		int lw = 1;
		DrawLine(sz, d, view, corners[0], corners[1], lw, clr, z_cull);
		DrawLine(sz, d, view, corners[2], corners[3], lw, clr, z_cull);
		DrawLine(sz, d, view, corners[4], corners[5], lw, clr, z_cull);
		DrawLine(sz, d, view, corners[6], corners[7], lw, clr, z_cull);
		
		DrawLine(sz, d, view, corners[0], corners[2], lw, clr, z_cull);
		DrawLine(sz, d, view, corners[1], corners[3], lw, clr, z_cull);
		DrawLine(sz, d, view, corners[4], corners[6], lw, clr, z_cull);
		DrawLine(sz, d, view, corners[5], corners[7], lw, clr, z_cull);
		
		DrawLine(sz, d, view, corners[0], corners[4], lw, clr, z_cull);
		DrawLine(sz, d, view, corners[1], corners[5], lw, clr, z_cull);
		DrawLine(sz, d, view, corners[2], corners[6], lw, clr, z_cull);
		DrawLine(sz, d, view, corners[3], corners[7], lw, clr, z_cull);
	}
	
	// Draw red-green-blue unit-vectors
	if (1) {
		vec3 axes[3] = {vec3(1,0,0), vec3(0,1,0), vec3(0,0,1)};
		Color clr[3] = {LtRed(), LtGreen(), LtBlue()};
		int pad = 20;
		Point pt0(pad, sz.cy - pad);
		float len = 20;
		mat4 view_orient = QuatMat(MatQuat(view));
		for(int i = 0; i < 3; i++) {
			vec3 orig = VecMul(view_orient, vec3(0));
			vec3 ax = VecMul(view_orient, axes[i]);
			vec3 diff = ax - orig;
				diff[1] *= -1; // 3d space top is +1 and bottom is -1 and 2d space top is 0 and bottom is sz.cy
			diff.Normalize();
			if (view_mode != VIEWMODE_PERSPECTIVE)
				diff *= -1;
			Point pt1(pt0.x - diff[0] * len, pt0.y - diff[1] * len);
			d.DrawLine(pt0, pt1, 1, clr[i]);
		}
	}
	//LOG("");
	
}

void EditRenderer::LeftDown(Point p, dword keyflags) {
	GeomCamera& camera = GetGeomCamera();
	
	cap_mouse_pos = p;
	is_captured_mouse = true;
	cap_begin_pos = camera.position;
	cap_begin_orientation = camera.orientation;
	
	bool is_shift = keyflags & K_SHIFT;
	bool is_ctrl = keyflags & K_CTRL;
	if (is_shift)
		cap_mode = CAPMODE_MOVE_YZ;
	else if (is_ctrl)
		cap_mode = CAPMODE_ROTATE;
	else
		cap_mode = CAPMODE_MOVE_XY;
	
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
		switch (cap_mode) {
			case CAPMODE_MOVE_XY: MoveRel(vec3(-diff.x * s, diff.y * s, 0)); break;
			case CAPMODE_MOVE_YZ: MoveRel(vec3(-diff.x * s, 0, -diff.y * s * SCALAR_FWD_Z)); break;
			case CAPMODE_ROTATE: RotateRel(vec3(-diff.x * s, -diff.y * s, 0)); break;
			default: break;
		}
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

void EditRenderer::RotateRel(const axes3& v) {
	GeomCamera& camera = GetGeomCamera();
	
	camera.orientation = MatQuat(QuatMat(cap_begin_orientation) * AxesMat(v));
	
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
	case CAMSRC_VIDEOIMPORT_FOCUS:
		return owner->state.focus;
		break;
		
	case CAMSRC_PROGRAM:
	case CAMSRC_VIDEOIMPORT_PROGRAM:
		return owner->state.program;
		break;
		
	}
	Panic("Invalid view mode in EditRenderer");
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
