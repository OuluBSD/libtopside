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
	int list_i = i * O_COUNT + O_CAMERA;
	list.FindAdd(list_i);
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
	int list_i = i * O_COUNT + O_OCTREE;
	list.FindAdd(list_i);
	return p;
}

GeomScene& GeomProjectFile::AddScene() {
	GeomScene& s = scenes.Add();
	s.owner = this;
	return s;
}







GeomProgram& GeomScene::GetAddProgram(String name) {
	int i = owner->dictionary.FindAdd(name);
	int j = programs.Find(i);
	if (j >= 0)
		return programs[j];
	GeomProgram& p = programs.Add(i);
	p.owner = this;
	p.id = i;
	return p;
}







GeomWorldState::GeomWorldState() {
	focus.scale = 100;
	program.scale = 100;
	//program.orientation = AxesQuat(M_PI/4, -M_PI/4, 0);
	
}

void GeomCamera::LoadCamera(ViewMode m, Camera& cam, Size sz) const {
	float ratio = (float)sz.cy / (float)sz.cx;
	float aspect = (float)sz.cx / (float)sz.cy;
	
	vec3 position = this->position;
	quat orientation = this->orientation;
	float scale = this->scale;
	float len = 2;
	bool move_camera = true;
	switch (m) {
		
	case VIEWMODE_YZ:
		orientation = MatQuat(YRotation(M_PI/2));
		cam.SetOrthographic(len * aspect, len, 0.1, 100.0);
		break;
		
	case VIEWMODE_XZ:
		orientation = MatQuat(XRotation(-M_PI/2));
		cam.SetOrthographic(len * aspect, len, 0.1, 100.0);
		break;
		
	case VIEWMODE_XY:
		orientation = MatQuat(YRotation(0));
		cam.SetOrthographic(len * aspect, len, 0.1, 100.0);
		break;
		
	case VIEWMODE_PERSPECTIVE:
		cam.SetPerspective(fov, aspect, 0.01, 1000.0);
		break;
		
	default:
		return;
		
	}
	
	if (move_camera)
		position = position - VecMul(QuatMat(orientation), VEC_FWD) * scale * 0.01;
	
	cam.SetWorld(position, orientation, scale);
}

mat4 GeomCamera::GetViewMatrix(ViewMode m, Size sz) const {
	Camera cam;
	LoadCamera(m, cam, sz);
	return cam.GetViewMatrix();
}

Frustum GeomCamera::GetFrustum(ViewMode m, Size sz) const {
	Camera cam;
	LoadCamera(m, cam, sz);
	return cam.GetFrustum();
}


NAMESPACE_TOPSIDE_END
