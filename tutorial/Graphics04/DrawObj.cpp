#include "Tutorial4.h"


vec3 Tutorial4::Barycentric(vec3 pts[3], vec2 P) {
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

void Tutorial4::Triangle4(Draw& fb, vec3 pts[3], vec2 tex[3], Texture* tex_img, float intensity, bool have_noise) {
	int w = width;
	int h = height;
	
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
	for (P[0] = bboxmin[0]; P[0] <= bboxmax[0]; P[0]++) {
		for (P[1] = bboxmin[1]; P[1] <= bboxmax[1]; P[1]++) {
			vec3 bc_screen = Barycentric(pts, P);
			if (bc_screen[0] < 0 || bc_screen[1] < 0 || bc_screen[2] < 0)
				continue;
			
			// calculate z-value
			float z = 0;
			for (int i = 0; i < 3; i++)
				z += pts[i][2] * bc_screen[i];
			
			int pos = (int)P[0] + (int)P[1] * w;
			float& zmem = zbuffer[pos];
			if (zmem < z) {
				zmem = z;

				RGBA used_clr;
				used_clr.a = 0;
				if (tex_img) {
					float tex_x = 0, tex_y = 0, bary_sum = 0;
					for(int i = 0; i < 3; i++) {
						tex_x += tex[i][0] * bc_screen[i];
						tex_y += tex[i][1] * bc_screen[i];
					}
					int tex_xi = tex_x * tex_img->GetWidth();
					int tex_yi = tex_y * tex_img->GetHeight();
					tex_xi = std::max(0, std::min(tex_img->GetWidth() - 1, tex_xi));
					tex_yi = std::max(0, std::min(tex_img->GetHeight() - 1, tex_yi));
					const byte* b = tex_img->GetIter(tex_xi, tex_yi);
					used_clr.r = b[2] * intensity;
					used_clr.g = b[1] * intensity;
					used_clr.b = b[0] * intensity;
				}
				else {
					used_clr.r = used_clr.g = used_clr.b = 255 * intensity;
				}
				
				fb.DrawLine(P[0], P[1], P[0], P[1], 1, used_clr);
			}
		}
	}
}

void Tutorial4::DrawObj(float f2, Draw& fb, bool use_texture) {
	if (!zbuffer) {
		int size = width * height;
		zbuffer = new float[size];
		zbuffer_empty = new float[size];
		
		float* it = zbuffer_empty;
		float* end = it + size;
		while (it != end)
			*it++ = -FLT_MAX;
	}
	memcpy(zbuffer, zbuffer_empty, width * height * 4);
	
	float c = 1.0 + 5 * (1 - f2);
	mat4 perspective {
		vec4{1,		0,	    0,		0},
		vec4{0,		1,	    0,		0},
		vec4{0,		0,	    1,		0},
		vec4{0,		0,	 -1/c,		1}
	};
	
	float angle = (use_texture ? -1 : +1) * (float)iter / (float)iters_in_phase * (2.0 * M_PI);
	Ref<EntityStore> store = GetEntity()->GetEngine().Get<EntityStore>();
	vec3 light_dir {sin(angle), 0.0, cos(angle)};
	PoolRef p = store->GetRoot();
	for(EntityRef& e : p->GetEntities()) {
		if (loader.model) {
			for(const Mesh& mesh : loader.model->GetMeshes()) {
				const uint32* idx = (const uint32*)mesh.indices.Begin();
				const Vertex* vtx = (const Vertex*)mesh.vertices.Begin();
				int tri_count = mesh.indices.GetCount() / 3;
				
				Texture* tex_img = NULL;
				if (use_texture && mesh.tex_id[TEXTYPE_DIFFUSE] >= 0)
					tex_img = &loader.model->textures[mesh.tex_id[TEXTYPE_DIFFUSE]];
				
				for(int i = 0; i < tri_count; i++) {
					vec3 screen_coord[3];
					vec3 world_coord[3];
					vec2 tex_coord[3];
					for(int j = 0; j < 3; j++) {
						const Vertex& V = vtx[idx[j]];
						vec3 v = V.position.Splice();
						
						vec4 screen;
						if (1) {
							vec4 v4 {v[0], v[1], v[2], 1.0};
							screen = perspective * v4;
							screen.Normalize();
						}
						else {
							float mul = 1.0 / (1.0 - v[2] / c);
							for(int i = 0; i < 3; i++)
								screen[i] = v[i] * mul;
						}
						
						screen_coord[j][0] = (int)((screen[0] + 1.0) * width / 2.0);
						screen_coord[j][1] = (int)((screen[1] + 1.0) * height / 2.0);
						screen_coord[j][2] = screen[2];
						world_coord[j] = v;
						tex_coord[j] = V.tex_coord;
					}
					
					vec3 n = (world_coord[2] - world_coord[0]) ^
							 (world_coord[1] - world_coord[0]);
					n.Normalize();
					
					float intensity = std::max(0.0f, n * light_dir);
					intensity = intensity * 0.5 + 0.5;
					Triangle4(fb, screen_coord, tex_coord, tex_img, intensity, false);
				}
			}
		}
	}
}
