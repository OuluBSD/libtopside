#include "IPhysics.h"

NAMESPACE_PARALLEL_BEGIN


template <class Fys>
ObjectT<Fys>::ObjectT() {
	//model.LoadModel(ShareDirFile("models" DIR_SEPS "cube.obj"));
	geom = Null;
	body = Null;
	Fys::GetDefaultOrientation(orient);
}

template <class Fys>
ObjectT<Fys>::~ObjectT() {
	Fys::ClearGeom(geom);
	Fys::ClearBody(body);
}

template <class Fys>
void ObjectT<Fys>::AttachContent() {
	ASSERT(geom);
	ASSERT(body);
	
	// Set mass of the physics body
	Fys::SetBodyMass(body, mass);
	
	// Set physics body of a geometry
	Fys::SetGeomBody(geom, body);
	
	// Set orientation of a physics body
	Fys::SetBodyQuaternion(body, orient);
	
	//LOG(ToString());
	
	auto space = this->GetSystem()->GetSpace().GetNative();
	ASSERT(space);
	Fys::AddGeomToSpace(space, geom);
	
}

template <class Fys>
void ObjectT<Fys>::DetachContent() {
	ASSERT(geom);
	ASSERT(body);
	Fys::RemoveGeomFromSpace(this->GetSpace()->GetNative(), geom);
}

template <class Fys>
void ObjectT<Fys>::Refresh() {
	
	
	TODO
	#if 0
	ASSERT(fb_obj);
	if (!fb_obj)
		return;
	
	
	
	if (is_override_phys_geom) {
		mat4 v = model_geom * override_geom;
		fb_obj->Set(v, Identity<mat4>());
	}
	else {
		vec3 v3 = Fys::GetGeomPosition(geom);
		mat4 trans = Translate(Identity<mat4>(), v3);
		quat q = Fys::GetGeomQuaternion(geom);
		mat4 rot = QuatMat(q);
		mat4 v = model_geom * rot * trans;
		fb_obj->Set(v, Identity<mat4>());
	}
	#endif
}

template <class Fys>
bool ObjectT<Fys>::LoadModel(GfxModelState& s) {
	if (!s.LoadModel(loader))
		Panic("Couldn't load model: ModelComponent");
	return true;
}


FYS_EXCPLICIT_INITIALIZE_CLASS(ObjectT)

NAMESPACE_PARALLEL_END
