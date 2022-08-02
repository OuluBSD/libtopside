#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN


GeomKeypoint& GeomTimeline::GetAddKeypoint(int i) {
	GeomKeypoint& kp = keypoints.GetAdd(i);
	kp.frame_id = i;
	kp.position = Identity<vec3>();
	kp.orientation = Identity<quat>();
	return kp;
}

Camera& GeomProjectFile::GetAddCamera(String name) {
	int i = dictionary.FindAdd(name);
	int j = cameras.Find(i);
	if (j >= 0)
		return cameras[j];
	Camera& p = cameras.Add(i);
	//p.owner = this;
	p.id = i;
	return p;
}

OctreePointModel& GeomProjectFile::GetAddOctree(String name) {
	int i = dictionary.FindAdd(name);
	int j = octrees.Find(i);
	if (j >= 0)
		return octrees[j];
	OctreePointModel& p = octrees.Add(i);
	//p.owner = this;
	p.id = i;
	return p;
}

GeomProgram& GeomProjectFile::GetAddProgram(String name) {
	int i = dictionary.FindAdd(name);
	int j = programs.Find(i);
	if (j >= 0)
		return programs[j];
	GeomProgram& p = programs.Add(i);
	p.owner = this;
	p.id = i;
	return p;
}




void GeomWorldState::LoadCamera(ViewMode m, Camera& camera, Size sz) const {
	float ratio = (float)sz.cy / (float)sz.cx;
	float aspect = (float)sz.cx / (float)sz.cy;
	
	vec3 position;
	quat orientation;
	float scale = 1.0;
	float len = 2;
	bool move_camera = true;
	switch (m) {
		case CAMERA_YZ:
			position = focus_position;
			orientation = MatQuat(YRotation(M_PI/2));
			camera.SetOrthographic(len * ratio, len, 0.1, 100.0);
			scale = focus_scale;
			break;
			
		case CAMERA_XZ:
			position = focus_position;
			orientation = MatQuat(XRotation(-M_PI/2));
			camera.SetOrthographic(len * ratio, len, 0.1, 100.0);
			scale = focus_scale;
			break;
			
		case CAMERA_XY:
			position = focus_position;
			orientation = MatQuat(YRotation(0));
			camera.SetOrthographic(len * ratio, len, 0.1, 100.0);
			scale = focus_scale;
			break;
			
		case CAMERA_PERSPECTIVE:
			position = focus_position;
			orientation = focus_orientation;
			camera.SetPerspective(focus_fov, aspect, 0.1, 100.0);
			scale = focus_scale;
			break;
			
		case CAMERA_CAMERA:
			position = camera_position;
			orientation = camera_orientation;
			camera.SetPerspective(focus_fov, aspect, 0.1, 100.0);
			move_camera = false;
			break;
			
		default:
			return;
	}
	
	if (move_camera)
		position = position + VecMul(QuatMat(orientation), VEC_BWD) * scale;
	
	//camera.SetWorld(position, orientation);
	camera.SetWorld(position, orientation, scale);
}

mat4 GeomWorldState::GetViewMatrix(ViewMode m, Size sz) const {
	Camera cam;
	LoadCamera(m, cam, sz);
	return cam.GetViewMatrix();
}

Frustum GeomWorldState::GetFrustum(ViewMode m, Size sz) const {
	Camera cam;
	LoadCamera(m, cam, sz);
	return cam.GetFrustum();
}


NAMESPACE_TOPSIDE_END
