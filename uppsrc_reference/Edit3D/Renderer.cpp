#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN


EditRenderer::EditRenderer() {
	SetFrame(BlackFrame());
	
	
}

void EditRenderer::Paint(Draw& d) {
	Size sz = GetSize();
	d.DrawRect(sz, owner->conf.background_clr);
	
	Frustum frustum = owner->state.GetFrustum(view_mode, sz);
	mat4 view = owner->state.GetViewMatrix(view_mode, sz);
	
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
				
				d.DrawRect(x, y, 1, 1, White());
			}
			
			iter++;
		}
	}
	
	//LOG("");
	
}

void EditRenderer::LeftDown(Point p, dword keyflags) {
	cap_mouse_pos = p;
	is_captured_mouse = true;
	if (view_mode == CAMERA_CAMERA)
		cap_begin_pos = owner->state.camera_position;
	else
		cap_begin_pos = owner->state.focus_position;
	
	SetCapture();
}

void EditRenderer::LeftUp(Point p, dword keyflags) {
	is_captured_mouse = false;
	
	ReleaseCapture();
}

void EditRenderer::MouseMove(Point p, dword keyflags) {
	if (is_captured_mouse) {
		Point diff = p - cap_mouse_pos;
		float s = 0.01; // owner->state.focus_scale;
		vec3 d(-diff.x * s, -diff.y * s, 0);
		
		switch (view_mode) {
			case CAMERA_YZ:
				owner->state.focus_position = cap_begin_pos + VecMul(YRotation(+M_PI/2), d);
				break;
				
			case CAMERA_XZ:
				owner->state.focus_position = cap_begin_pos + VecMul(XRotation(-M_PI/2), d);
				break;
				
			case CAMERA_XY:
				owner->state.focus_position = cap_begin_pos + VecMul(YRotation(0), d);
				break;
				
			case CAMERA_PERSPECTIVE:
				break;
				
			case CAMERA_CAMERA:
				break;
				
		}
		
		owner->RefrehRenderers();
	}
}


NAMESPACE_TOPSIDE_END
