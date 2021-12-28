#include "Physics.h"

NAMESPACE_TOPSIDE_BEGIN


template <class Fys>
ObjectT<Fys>::ObjectT() {
	//model.LoadModel(ShareDirFile("models" DIR_SEPS "cube.obj"));
	Fys::GetDefaultOrientation(orient);
}

template <class Fys>
ObjectT<Fys>::~ObjectT() {
	if (geom) dGeomDestroy(geom);
	if (body) dBodyDestroy(body);
}

template <class Fys>
void ObjectT<Fys>::AttachContent() {
	ASSERT(geom != 0);
	ASSERT(body != 0);
	dBodySetMass(body, &mass);						// Set mass of the physics body
	dGeomSetBody(geom, body);						// Set physics body of a geometry
	dBodySetQuaternion(body, orient);				// Set orientation of a physics body
	
	
	//LOG(ToString());
	
	
	dSpaceID space = this->GetSpace()->GetSpace();
	dSpaceAdd(space, geom);
}

template <class Fys>
void ObjectT<Fys>::DetachContent() {
	ASSERT(geom != 0);
	ASSERT(body != 0);
	dSpaceRemove(this->GetSpace()->GetSpace(), geom);
}

template <class Fys>
void ObjectT<Fys>::Refresh() {
	/*if (!fb_obj && !model_err) {
		LOG("Object::Refresh: warning: loading model while painting");
		fb_obj = s.CreateObject();
		if (fb_obj)
			LoadModel(s);
	}*/
	
	ASSERT(fb_obj);
	if (!fb_obj)
		return;
	
	
	/*
	int width = 1280, height = 720;
	mat4 projection = ortho(-width, width, -height, height, -1024.0f, 1024.0f);
    mat4 view = LookAt(vec3(0.0f, 0.0f, -1.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f, 1.0f, 0.0f));
    mat4 model = identity<mat4>();
	fb_obj->SetMat4("projection", projection);
	fb_obj->SetMat4("model", model);
	fb_obj->SetMat4("view", view);*/
	
	if (is_override_phys_geom) {
		mat4 v = override_geom * model_geom;
		fb_obj->Set(v, identity<mat4>());
	}
	else {
		dVector3 pos;
		dGeomCopyPosition (geom, pos);
		vec3 v3 = MakeVec3(pos);
		mat4 trans = translate(identity<mat4>(), v3);
		
		dQuaternion result;
		dGeomGetQuaternion (geom, result);
		quat q;
		q[3] = result[0];
		q[0] = result[1];
		q[1] = result[2];
		q[2] = result[3];
		/*q[0] = result[0];
		q[1] = result[1];
		q[2] = result[2];
		q[3] = result[3];*/
		mat4 rot = ToMat4(q);
		
		mat4 v = trans * rot * model_geom;
		fb_obj->Set(v, identity<mat4>());
	}
}

template <class Fys>
bool ObjectT<Fys>::LoadModel(GfxDataState& s) {
	ASSERT(!fb_obj);
	fb_obj = &s.CreateObject();
	if (!s.LoadModel(loader, *fb_obj))
		Panic("Couldn't load model: ModelComponent");
	if (!s.LoadModelTextures(loader, *fb_obj))
		Panic("Couldn't load model textures: ModelComponent");
	return true;
}
/*
template <class Fys>
void ObjectT<Fys>::LoadModel(CpuDataState& state) {
	auto& o = cpu_obj ? *cpu_obj : state.AddObject();
	cpu_obj = cpu_obj ? cpu_obj : &o;
	fb_obj = cpu_obj;
	if (!state.LoadModel(loader, o))
		Panic("Couldn't load model: ModelComponent");
	if (!state.LoadModelTextures(loader, o))
		Panic("Couldn't load model textures: ModelComponent");
}

template <class Fys>
void ObjectT<Fys>::LoadModel(OglDataState& state) {
	auto& o = ogl_obj ? *ogl_obj : state.AddObject();
	ogl_obj = ogl_obj ? ogl_obj : &o;
	fb_obj = ogl_obj;
	if (!state.LoadModel(loader, o))
		Panic("Couldn't load model: ModelComponent");
	if (!state.LoadModelTextures(loader, o))
		Panic("Couldn't load model textures: ModelComponent");
}
*/

FYS_EXCPLICIT_INITIALIZE_CLASS(ObjectT)

NAMESPACE_TOPSIDE_END
