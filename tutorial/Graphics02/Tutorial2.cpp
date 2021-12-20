#include <EcsComplete/EcsComplete.h>

/*
Tutorial 2:
	This a variation of the tutorial "Lesson 2 Triangle rasterization and back face culling"
	It draws all the steps iteratively
	
	Source: https://github.com/ssloy/tinyrenderer/wiki/Lesson-2-Triangle-rasterization-and-back-face-culling
*/

using namespace TS;
using namespace TS::Ecs;


struct Tutorial2 :
	public Component<Tutorial2>,
	public BinderIfaceVideo
{
	RTTI_DECL2(Tutorial2, ComponentT, BinderIfaceVideo)
	
	ModelLoader loader;
	SdlCpuDataState state;
	vec2 t[3][3];
	int iter = 0;
	int phase = 0;
	int phases = 8+1;
	TimeStop ts;
	
	Tutorial2() {
		String data_dir = ShareDirFile("models");
		String obj_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head.obj");
		String tex_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head_diffuse.tga");
		auto& o = state.AddObject();
		if (!state.LoadModel(loader, o, obj_path))
			Panic("Couldn't load model: " + obj_path);
		loader.GetModel()->AddTextureFile(0, TEXTYPE_DIFFUSE, tex_path);
		if (!state.LoadModelTextures(loader, o))
			Panic("Couldn't load model textures: " + obj_path);
		
		t[0][0] = vec2(10, 70);
		t[0][1] = vec2(50, 160);
		t[0][2] = vec2(70, 80);
		t[1][0] = vec2(180, 50);
		t[1][1] = vec2(150, 1);
		t[1][2] = vec2(70, 180);
		t[2][0] = vec2(180, 150);
		t[2][1] = vec2(120, 160);
		t[2][2] = vec2(130, 180);
	}
	
	void Initialize() override {
		Serial::EcsVideoBase::Latest().AddBinder(this);
	}
	
	void operator=(const Tutorial2&) {}
	
	void Triangle1(DrawGeometry& fb, vec2 a, vec2 b, vec2 c, Color color) {
		fb.DrawLine(a, b, 1, color);
		fb.DrawLine(b, c, 1, color);
		fb.DrawLine(c, a, 1, color);
	}
	
	void Triangle2(DrawGeometry& fb, vec2 a, vec2 b, vec2 c) {
		Color red {255, 0, 0};
		Color green {0, 255, 0};
		// sort the vertices, t0, t1, t2 lower−to−upper (bubblesort yay!)
		if (a[1] > b[1]) Swap(a, b);
		if (a[1] > c[1]) Swap(a, c);
		if (b[1] > c[1]) Swap(b, c);
		fb.DrawLine(a, b, 1, green);
		fb.DrawLine(b, c, 1, green);
		fb.DrawLine(c, a, 1, red);
	}
	
	void Triangle3(DrawGeometry& fb, vec2 a, vec2 b, vec2 c, Color clr, bool lower, bool upper, bool border, bool fill) {
		Color white {255, 255, 255};
		Color red {255, 0, 0};
		Color green {0, 255, 0};
		
		// sort the vertices, t0, t1, t2 lower−to−upper (bubblesort yay!)
		if (a[1] > b[1]) Swap(a, b);
		if (a[1] > c[1]) Swap(a, c);
		if (b[1] > c[1]) Swap(b, c);
		int total_height = c[1] - a[1];
		if (lower) {
			for (int y = a[1]; y <= b[1]; y++) {
				int segment_height = b[1] - a[1] + 1;
				float alpha = (float)(y - a[1]) / total_height;
				float beta  = (float)(y - a[1]) / segment_height; // be careful with divisions by zero
				vec2 A = a + (c - a) * alpha;
				vec2 B = a + (b - a) * beta;
				if (A[0] > B[0]) Swap(A, B);
				if (border) {
					fb.DrawLine(A[0], y, A[0], y, 1, red);
					fb.DrawLine(B[0], y, B[0], y, 1, green);
					if (fill)
						fb.DrawHLine(A[0], B[0], y, 1, white);
				}
				else
					fb.DrawHLine(A[0], B[0], y, 1, clr);
			}
		}
		if (upper) {
			for (int y = b[1]; y <= c[1]; y++) {
				int segment_height =  c[1] - b[1] + 1;
				float alpha = (float)(y - a[1]) / total_height;
				float beta  = (float)(y - b[1]) / segment_height; // be careful with divisions by zero
				vec2 A = a + (c - a) * alpha;
				vec2 B = b + (c - b) * beta;
				if (A[0] > B[0]) Swap(A, B);
				if (border) {
					fb.DrawLine(A[0], y, A[0], y, 1, red);
					fb.DrawLine(B[0], y, B[0], y, 1, green);
					if (fill)
						fb.DrawHLine(A[0], B[0], y, 1, white);
				}
				else
					fb.DrawHLine(A[0], B[0], y, 1, clr);
			}
		}
	}
	
	
	vec3 Barycentric(vec2 *pts, vec2 P) {
		vec3 u = cross(
			vec3(	pts[2][0] - pts[0][0],
					pts[1][0] - pts[0][0],
					pts[0][0] - P[0]),
			vec3(	pts[2][1] - pts[0][1],
					pts[1][1] - pts[0][1],
					pts[0][1] - P[1]));
		/* `pts` and `P` has integer value as coordinates
		   so `abs(u[2])` < 1 means `u[2]` is 0, that means
		   triangle is degenerate, in this case return something with negative coordinates */
		if (std::abs(u[2]) < 1)
			return vec3(-1, 1, 1);
		return vec3(
			1.0 - (u[0] + u[1]) / u[2],
			              u[1]  / u[2],
			              u[0]  / u[2]);
	}
	
	void Triangle4(DrawGeometry& fb, vec2 pts[3], Color color, bool have_noise) {
		Size sz = fb.GetPageSize();
		int w = sz.cx;
		int h = sz.cy;
		
		vec2 bboxmin(w - 1,  h - 1);
		vec2 bboxmax(0, 0);
		vec2 clamp(w - 1, h - 1);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				bboxmin[j] = std::max<float>(0.0,      std::min<float>(bboxmin[j], pts[i][j]));
				bboxmax[j] = std::min<float>(clamp[j], std::max<float>(bboxmax[j], pts[i][j]));
			}
		}
		
		vec2 P;
		
		Color rand_color = RandomColor();

		for (P[0] = bboxmin[0]; P[0] <= bboxmax[0]; P[0]++) {
			for (P[1] = bboxmin[1]; P[1] <= bboxmax[1]; P[1]++) {
				vec3 bc_screen = Barycentric(pts, P);
				if (bc_screen[0] < 0 || bc_screen[1] < 0 || bc_screen[2] < 0)
					continue;
				
				fb.DrawLine(P[0], P[1], P[0], P[1], 1, have_noise && Randomf() < 0.05 ? rand_color : color);
			}
		}
	}
	
	void DrawObj(DrawGeometry& fb, bool clown_colors) {
		Size sz = fb.GetPageSize();
		int height = std::min(sz.cy, sz.cx);
		int width = height;
		Ref<EntityStore> store = GetEntity()->GetEngine().Get<EntityStore>();
		vec3 light_dir {0.0, 0.0, -1.0};
		PoolRef p = store->GetRoot();
		for(EntityRef& e : p->GetEntities()) {
			auto model = loader.GetModel();
			if (model) for(const Mesh& mesh : model->GetMeshes()) {
				int tri_count = mesh.GetTriangleCount();
				
				for(int i = 0; i < tri_count; i++) {
					ivec3 indices = mesh.GetTriangleIndices(i);
					vec2 screen_coord[3];
					vec3 world_coord[3];
					for(int j = 0; j < 3; j++) {
						const vec3& v = mesh.GetVertCoord(indices[j]);
						int x = (v[0] + 1.0) * width  / 2.0;
						int y = (v[1] + 1.0) * height / 2.0;
						screen_coord[j][0] = x;
						screen_coord[j][1] = y;
						world_coord[j] = v;
					}
					
					if (clown_colors) {
						Triangle4(fb, screen_coord, RandomColor(), false);
					}
					else {
						vec3 n =
							(world_coord[2] - world_coord[0]) ^
							(world_coord[1] - world_coord[0]);
						n.Normalize();
						float intensity = n * light_dir;
						if (intensity > 0) {
							Triangle4(fb, screen_coord, RandomColor(), false);
						}
					}
				}
			}
		}
	}
	
	void Render(Draw& draw) override {
		Size sz = draw.GetPageSize();
		draw.DrawRect(sz, Black());
		
		DrawGeometry fb(draw);
		
		Color white {255, 255, 255};
		Color red {255, 0, 0};
		Color green {0, 255, 0};
		Color clrs[3] {red, white, green};
		
		if (phase == 0) {
			for(int i = 0; i < 3; i++)
				Triangle1(fb, t[i][0], t[i][1], t[i][2], clrs[i]);
		}
		else if (phase == 1) {
			// Here boundary A is red, and boundary B is green.
			for(int i = 0; i < 3; i++)
				Triangle2(fb, t[i][0], t[i][1], t[i][2]);
		}
		else if (phase == 2) {
			// Unfortunately, boundary B is made of two parts. Let us draw the bottom half of the triangle by cutting it horizontally:
			for(int i = 0; i < 3; i++)
				Triangle3(fb, t[i][0], t[i][1], t[i][2], white, 1,0,1,0);
		}
		else if (phase == 3) {
			for(int i = 0; i < 3; i++)
				Triangle3(fb, t[i][0], t[i][1], t[i][2], white, 1,0,1,1);
		}
		else if (phase == 4) {
			for(int i = 0; i < 3; i++)
				Triangle3(fb, t[i][0], t[i][1], t[i][2], clrs[i], 1,1,0,1);
		}
		else if (phase == 5) {
			Color clrs[3] {red, white, green};
			for(int i = 0; i < 3; i++)
				Triangle4(fb, t[i], clrs[i], true);
		}
		else if (phase == 6) {
			DrawObj(fb, true);
		}
		else if (phase == 7) {
			DrawObj(fb, false);
		}
		
		iter++;
		if (ts.Seconds() > 1.0) {
			ts.Reset();
			iter = 0;
			phase = (phase + 1) % phases;
		}
	}
};

SIMPLE_ECS_APP_(Tutorial2, "geom_tutorial_base.eon", "FRAGMENT=;VERTEX=;DRAWMEM=true")

