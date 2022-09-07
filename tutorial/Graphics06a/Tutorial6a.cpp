#include "Tutorial6a.h"

/*
Tutorial 6a:
	This tutorial shows how shaders are used by the engine.
*/

NAMESPACE_TOPSIDE_BEGIN


void Graphics6a::Initialize() {
	String path = GetDataFile("cornell_box_variant.toy");
	const auto& c = CommandLine();
	if (c.GetCount())
		path = c[c.GetCount()-1];
	
	if (!ms.Load(path))
		Panic("Couldn't load the dhader");
	
}

void Graphics6a::Render(SystemDraw& draw) {
	//Size sz = draw.GetPageSize();
	//draw.DrawRect(sz, RandomColor(64, 64));
	if (fail)
		return;
	
	Size sz = draw.GetPageSize();
	if (!ms.IsOpen()) {
		if (!ms.Open(sz)) {
			LOG("error: multistage open failed: " << ms.GetLastError());
			fail = true;
			return;
		}
	}
	else
		ms.SetSize(sz);
	
	ms.Paint();
}



void Graphics6aInitializer() {
	/*Machine& mach = GetMachine();
	
	EntityStore& ents = *mach.Get<EntityStore>();
	EntityRef obj = ents.Create<StaticModel>();
	obj->Find<Connector>()->ConnectAll();
	Ref<ModelComponent> mdl = obj->GetRef<ModelComponent>();
	
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
	mdl->Dispatch();*/
	
}


NAMESPACE_TOPSIDE_END


RENDER_APP_(TS::Graphics6a)
APP_INITIALIZE_(TS::Graphics6aStartup);
APP_DEFAULT_GFX_(GFX_OPENGL);
