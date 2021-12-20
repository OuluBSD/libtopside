#include <EcsComplete/EcsComplete.h>

/*
Tutorial 1:
	This a variation of the tutorial "Lesson 1 Bresenham’s Line Drawing Algorithm"
	Random lines and the face model is being drawn.
	
	Source: https://github.com/ssloy/tinyrenderer/wiki/Lesson-1-Bresenham%E2%80%99s-Line-Drawing-Algorithm
*/

using namespace TS;
using namespace TS::Ecs;


struct Tutorial1 :
	public Component<Tutorial1>,
	public BinderIfaceVideo
{
	RTTI_DECL2(Tutorial1, ComponentT, BinderIfaceVideo)
	
	ModelLoader loader;
	SdlCpuDataState state;
	
	Tutorial1() {
		String data_dir = ShareDirFile("models");
		String obj_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head.obj");
		String tex_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head_diffuse.tga");
		auto& o = state.AddObject();
		if (!state.LoadModel(loader, o, obj_path))
			Panic("Couldn't load model: " + obj_path);
		loader.GetModel()->AddTextureFile(0, TEXTYPE_DIFFUSE, tex_path);
	}
	void operator=(const Tutorial1&) {}
	void Visit(RuntimeVisitor& vis) override {}
	
	void Initialize() override {
		Serial::EcsVideoBase::Latest().AddBinder(this);
	}
	
	void Render(Draw& fb) override {
		Size sz = fb.GetPageSize();
		fb.DrawRect(sz, Black());
		
		
		
		if (1) {
			for(int i = 0; i < 10; i++) {
				
				// Draw random pixel
				if (0) {
					int x = Random(sz.cx);
					int y = Random(sz.cy);
					fb.DrawLine(x, y, x, y, 1, RandomColor());
				}
				
				// Draw random line
				else {
					int x0 = Random(sz.cx);
					int x1 = Random(sz.cx);
					int y0 = Random(sz.cy);
					int y1 = Random(sz.cy);
					fb.DrawLine(x0, y0, x1, y1, 1, RandomColor());
				}
			}
		}
		
		int height = std::min(sz.cy, sz.cx);
		int width = height;
		Ref<EntityStore> store = GetEntity()->GetEngine().Get<EntityStore>();
		PoolRef p = store->GetRoot();
		for(EntityRef& e : p->GetEntities()) {
			auto model = loader.GetModel();
			if (model) for(const Mesh& mesh : model->GetMeshes()) {
				int tri_count = mesh.GetTriangleCount();
				
				for(int i = 0; i < tri_count; i++) {
					ivec3 indices = mesh.GetTriangleIndices(i);
					for(int j = 0; j < 3; j++) {
						const vec3& v0 = mesh.GetVertCoord(indices[j]);
						const vec3& v1 = mesh.GetVertCoord(indices[(j + 1) % 3]);
						
						int x0 = (v0[0] + 1.0) * width  / 2.0;
						int y0 = (v0[1] + 1.0) * height / 2.0;
						int x1 = (v1[0] + 1.0) * width  / 2.0;
						int y1 = (v1[1] + 1.0) * height / 2.0;
						
						fb.DrawLine(x0, y0, x1, y1, 1, RandomColor());
					}
				}
			}
		}
	}
};


SIMPLE_ECS_APP_(Tutorial1, "geom_tutorial_base.eon", "FRAGMENT=;VERTEX=;DRAWMEM=true")
