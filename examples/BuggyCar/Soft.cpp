#include "BuggyCar.h"


NAMESPACE_TOPSIDE_BEGIN



void BuggyCarVertexShader::Process(SdlCpuVertexShaderArgs& a) {
	int width = a.generic->iResolution[0];
	int height = a.generic->iResolution[1];
	vec4 pos = a.v.position.Splice().Embed();
	//pos[2] = -pos[2] + 1; // hack
	vec4 screen = a.va->view * pos;
	if (screen[3] != 0.0)
		screen.Project();
	//screen.Normalize();
	a.v.position[0] = (int)((screen[0] + 1.0) * width  / 2.0);
	a.v.position[1] = (int)((screen[1] + 1.0) * height / 2.0);
	a.v.position[2] = screen[2];
	a.v.position[3] = 1.0f;
	//ASSERT(a.v.position[2] >= 0.0f);
}

void BuggyCarFragmentShader::Process(SdlCpuFragmentShaderArgs& args) {
	#if 0
	float w = args.generic->iResolution[0];
	float h = args.generic->iResolution[1];
	float x = args.frag_coord[0] / w;
	float y = args.frag_coord[1] / h;
	args.frag_color_out = vec4(x, y, 0, 1);
	#endif
	
	#if 0
	float intensity = 0.5f;
	vec4& used_clr = args.frag_color_out;
	used_clr[3] = 0;
	used_clr[0] = intensity;
	used_clr[1] = intensity;
	used_clr[2] = intensity;
	
	#else
	
	ASSERT(args.fa);
	vec3& n = args.normal;
	vec3& light_dir = args.fa->light_dir;
	float m = dot(n, light_dir);
	
	vec4& used_clr = args.frag_color_out;
	used_clr[3] = 0;
	
	float intensity = std::max(0.0f, m);
	
	intensity = intensity * 0.5 + 0.5;
	
	auto& diffuse = args.tex_img[TEXTYPE_DIFFUSE];
	if (diffuse) {
		Texture& tex = diffuse->GetGeomTex();
		float tex_x = args.tex_coord[0];
		float tex_y = args.tex_coord[1];
		ASSERT(tex_x >= 0.0f && tex_x <= 1.0f);
		ASSERT(tex_y >= 0.0f && tex_y <= 1.0f);
		int tex_xi = tex_x * tex.GetWidth();
		int tex_yi = tex_y * tex.GetHeight();
		tex_xi = std::max(0, std::min(tex.GetWidth() - 1, tex_xi));
		tex_yi = std::max(0, std::min(tex.GetHeight() - 1, tex_yi));
		const byte* b = tex.GetIter(tex_xi, tex_yi);
		ASSERT(intensity <= 1.0f);
		float mul = intensity / 255.0;
		float R = b[0] * mul;
		float G = b[1] * mul;
		float B = b[2] * mul;
		ASSERT(R >= 0.0f && R <= 1.0f);
		ASSERT(G >= 0.0f && G <= 1.0f);
		ASSERT(B >= 0.0f && B <= 1.0f);
		used_clr[0] = B;
		used_clr[1] = G;
		used_clr[2] = R;
	}
	else {
		used_clr[0] = intensity;
		used_clr[1] = intensity;
		used_clr[2] = intensity;
	}
	#endif
}


NAMESPACE_TOPSIDE_END
