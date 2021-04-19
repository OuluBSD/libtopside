#include "Tutorial6.h"

/*
Tutorial 6b:
	This a variation of the tutorial "Lesson 6 Shaders for the software renderer"
	
	Source: https://github.com/ssloy/tinyrenderer/wiki/Lesson-6-Shaders-for-the-software-renderer
*/

NAMESPACE_OULU_BEGIN


void Graphics6Startup() {
	Machine& mach = GetMachine();
	mach.Add<PhysicsSystem>();
	
	EntityStore& ents = *mach.Get<EntityStore>();
	SharedEntity obj = ents.Create<StaticModel>();
	obj->Find<Connector>()->ConnectAll();
	Shared<ModelComponent> mdl = obj->GetShared<ModelComponent>();
	
	String data_dir = ShareDirFile("models");
	String obj_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head.obj");
	String tex_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head_diffuse.tga");
	String nrm_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head_nm_tangent.tga");
	String spec_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head_spec.tga");
	if (!mdl->LoadModel(obj_path))
		throw Exc("Couldn't load " + obj_path);
	mdl->AddTextureFile(0, TEXTYPE_DIFFUSE, tex_path);
	mdl->AddTextureFile(0, TEXTYPE_NORMALS, nrm_path);
	mdl->AddTextureFile(0, TEXTYPE_SPECULAR, spec_path);
	mdl->Dispatch();
}


NAMESPACE_OULU_END


RENDER_APP_(Oulu::DefaultRenderApp)
APP_STARTUP_(Oulu::Graphics6Startup);
APP_DEFAULT_GFX_(GFX_OPENGL);
