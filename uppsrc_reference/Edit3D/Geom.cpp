#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN


GeomObjectCollection::GeomObjectCollection(GeomDirectory& d) {
	iter.addr[0] = &d;
}

bool GeomObjectIterator::Next() {
	if (!*this)
		return false;
	
	while (1) {
		ASSERT(level >= 0);
		
		{
			GeomDirectory* a = addr[level];
			int oc = a->objs.GetCount();
			int sc = a->subdir.GetCount();
			int& p = pos[level];
			p++;
			
			if (p < oc)
				; // pass
			else if (p == oc + sc) {
				if (!level)
					break;
				level--;
				continue;
			}
			else {
				ASSERT(p >= oc && p < oc + sc);
				int s = p - oc;
				addr[level+1] = &a->subdir[s];
				pos[level+1] = -1;
				level++;
				continue;
			}
		}
		
		return true;
	}
	
	return false;
}

GeomObjectIterator::operator bool() const {
	if (!level) {
		GeomDirectory* a = addr[level];
		if (!a)
			return false;
		int oc = a->objs.GetCount();
		int sc = a->subdir.GetCount();
		if (pos[0] >= oc + sc)
			return false;
	}
	return true;
}

GeomObject& GeomObjectIterator::operator*() {
	GeomDirectory* a = addr[level];
	int& p = pos[level];
	return a->objs[p];
}

GeomObject* GeomObjectIterator::operator->() {
	GeomDirectory* a = addr[level];
	if (!a)
		return 0;
	int& p = pos[level];
	if (p < 0 || p >= a->objs.GetCount())
		return 0;
	return &a->objs[p];
}










GeomKeypoint& GeomTimeline::GetAddKeypoint(int i) {
	GeomKeypoint& kp = keypoints.GetAdd(i);
	kp.frame_id = i;
	kp.position = Identity<vec3>();
	kp.orientation = Identity<quat>();
	return kp;
}

GeomScene& GeomProjectFile::AddScene() {
	GeomScene& s = scenes.Add();
	s.owner = this;
	return s;
}

/*GeomModel& GeomProjectFile::AddModel() {
	GeomModel& m = models.Add();
	m.owner = this;
	return m;
}*/







GeomObject* GeomDirectory::FindObject(String name) {
	for(GeomObject& o : objs)
		if (o.name == name)
			return &o;
	return 0;
}

GeomObject& GeomDirectory::GetAddModel(String name) {
	GeomObject* o = FindObject(name);
	if (o)
		return *o;
	
	o = &objs.Add();
	o->name = name;
	o->type = GeomObject::O_MODEL;
	return *o;
}

GeomObject& GeomDirectory::GetAddCamera(String name) {
	GeomObject* o = FindObject(name);
	if (o)
		return *o;
	
	o = &objs.Add();
	o->name = name;
	o->type = GeomObject::O_CAMERA;
	return *o;
}

GeomObject& GeomDirectory::GetAddOctree(String name) {
	GeomObject* o = FindObject(name);
	if (o)
		return *o;
	
	o = &objs.Add();
	o->name = name;
	o->type = GeomObject::O_OCTREE;
	return *o;
}













GeomWorldState::GeomWorldState() {
	//focus.scale = 100;
	//program.scale = 100;
	//program.orientation = AxesQuat(M_PI/4, -M_PI/4, 0);
	
}

void GeomCamera::LoadCamera(ViewMode m, Camera& cam, Size sz, float far) const {
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
		cam.SetOrthographic(len * aspect, len, 0.1, far);
		break;
		
	case VIEWMODE_XZ:
		orientation = MatQuat(XRotation(-M_PI/2));
		cam.SetOrthographic(len * aspect, len, 0.1, far);
		break;
		
	case VIEWMODE_XY:
		orientation = MatQuat(YRotation(0));
		cam.SetOrthographic(len * aspect, len, 0.1, far);
		break;
		
	case VIEWMODE_PERSPECTIVE:
		cam.SetPerspective(fov, aspect, 0.1, far);
		move_camera = false;
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
