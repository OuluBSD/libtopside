#include "SoftRend.h"

NAMESPACE_TOPSIDE_BEGIN




PassVertex::PassVertex() {
	this->UseUniform(GVar::VAR_COMPAT_RESOLUTION);
	
}


void PassVertex::Process(VertexShaderArgs& a) {
	#if 0
	auto& pos = a.v.position;
	auto& tex = a.v.tex_coord;
	pos[0] = (pos[0] + 1) * 0.5;
	pos[1] = (pos[1] + 1) * 0.5;
	tex = pos.template Splice<0,2>();
	pos[0] *= a.generic->iResolution[0];
	pos[1] *= a.generic->iResolution[1];
	#endif
}


void PassFragment::Process(FragmentShaderArgs& args) {
	float w = args.generic->iResolution[0];
	float h = args.generic->iResolution[1];
	float x = args.frag_coord[0] / w;
	float y = args.frag_coord[1] / h;
	args.frag_color_out = vec4(x, y, 0, 1);
	
	vec4& used_clr = args.frag_color_out;
	used_clr[3] = 0;
	
	
	auto& diffuse = args.fa->color_buf[TEXTYPE_DIFFUSE];
	
	TODO
	#if 0
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


void ColorTestFragment::Process(FragmentShaderArgs& args) {
	const vec3& res = args.generic->iResolution;
	
	float t = args.generic->iTime;
	
	vec3 shift = vec3(			sinf(t),
								sinf(t + M_PIf / 3.0f),
								sinf(t + M_PIf * 2.0f / 3.0f));
	
	args.frag_color_out = vec4(	args.frag_coord[0] / res[0] + shift[0],
								args.frag_coord[1] / res[1] + shift[1],
								1.0f - args.frag_coord[1] / res[1] + shift[2],
								0);
}


ProxyInput0Fragment::ProxyInput0Fragment() {
	this->UseUniform(GVar::VAR_COMPAT_CHANNEL0);
	this->UseUniform(GVar::VAR_COMPAT_CHANNELRESOLUTION);
	
}

vec4 texture(const ByteImage* ch, const vec2& uv) {
	int x = (int)(uv[0] * (ch->GetWidth()-1));
	int y = (int)((1.0f - uv[1]) * (ch->GetHeight()-1));
	
	if (x >= 0              && y >= 0 &&
		x <  ch->GetWidth() && y <  ch->GetHeight()) {
		const byte* it = ch->GetIter(x, y);
		ASSERT(ch->GetChannels() == 3 || ch->GetChannels() == 4);
		return vec4(	it[0] / 255.0f,
						it[1] / 255.0f,
						it[2] / 255.0f,
						1.0f);
	}
	return vec4{0,0,0,0};
}


void ProxyInput0Fragment::Process(FragmentShaderArgs& args) {
	const ByteImage* iChannel0 = args.GetTexture(args.generic->iChannel0);
	ASSERT(iChannel0);
	
	const auto& iResolution = args.generic->iResolution;
	const auto& fragCoord = args.frag_coord;
	auto& fragColor = args.frag_color_out;
	
	vec2 uv = fragCoord / iResolution.Splice();
	vec4 clr = texture(iChannel0, uv);
	//clr[0] = 1.0;
    fragColor = clr;
}










StereoShader::StereoShader() {
	this->UseUniform(GVar::VAR_COMPAT_RESOLUTION);
	this->UseUniform(GVar::VAR_DIFFUSE);
	this->UseUniform(GVar::VAR_MODEL);
	
}


void StereoShader::Process(VertexShaderArgs& a) {
	vec4 pos = a.v.position.Splice().Embed();
	vec4 screen = a.va->model * pos;
	screen.Project();
	a.v.position = screen;
}


void StereoShader::Process(FragmentShaderArgs& a) {
	const ByteImage* diffuse = a.fa->color_buf[TEXTYPE_DIFFUSE];
	ASSERT(diffuse);
	
	vec4 clr;
	
	if (0 && (int)a.frag_coord[0] % 2) {
		const auto& iResolution = a.generic->iResolution;
		const auto& fragCoord = a.frag_coord;
		auto& fragColor = a.frag_color_out;
		
		#if 0
		vec2 uv = fragCoord / iResolution.Splice();
		clr[0] = uv[0];
		clr[1] = uv[1];
		clr[2] = uv[0];
		#else
		clr[0] = a.tex_coord[0];
		clr[1] = a.tex_coord[1];
		clr[2] = a.tex_coord[0];
		#endif
	}
	else {
		clr = texture(diffuse, a.tex_coord);
	}
	clr[3] = 1;
	
    a.frag_color_out = clr;
}





ObjViewVertex::ObjViewVertex() {
	this->UseUniform(GVar::VAR_VIEW);
}


void ObjViewVertex::Process(VertexShaderArgs& a) {
	vec4 pos = a.v.position.Splice().Embed();
	vec4 screen = a.va->view * pos;
	if (screen[3] != 0) {
		screen.Project();
		a.v.position = screen;
		//LOG(a.v.position.ToString());
	}
}


ObjViewFragment::ObjViewFragment() {
	this->UseUniform(GVar::VAR_DIFFUSE);
	this->UseUniform(GVar::VAR_SPECULAR);
	this->UseUniform(GVar::VAR_CUBE_DIFFUSE);
	this->UseUniform(GVar::VAR_CUBE_IRRADIANCE);
}


void ObjViewFragment::Process(FragmentShaderArgs& args) {
	ASSERT(args.fa);
	vec3& n = args.normal;
	vec3& light_dir = args.fa->light_dir;
	float m = Dot(n, light_dir);
	
	vec4& used_clr = args.frag_color_out;
	used_clr[3] = 0;
	
	float intensity = std::max(0.0f, m);
	
	intensity = intensity * 0.5f + 0.5f;
	
	auto& diffuse = args.fa->color_buf[TEXTYPE_DIFFUSE];
	if (diffuse) {
		const ByteImage& tex = *diffuse;
		float tex_x = args.tex_coord[0];
		float tex_y = args.tex_coord[1];
		ASSERT(tex_x >= 0.0f && tex_x <= 1.0f);
		ASSERT(tex_y >= 0.0f && tex_y <= 1.0f);
		int tex_xi = (int)(tex_x * tex.GetWidth());
		int tex_yi = (int)(tex_y * tex.GetHeight());
		tex_xi = std::max(0, std::min(tex.GetWidth() - 1, tex_xi));
		tex_yi = std::max(0, std::min(tex.GetHeight() - 1, tex_yi));
		const byte* b = tex.GetIter(tex_xi, tex_yi);
		ASSERT(intensity <= 1.0f);
		float mul = intensity / 255.0f;
		float R = b[0] * mul;
		float G = b[1] * mul;
		float B = b[2] * mul;
		ASSERT(R >= 0.0f && R <= 1.0f);
		ASSERT(G >= 0.0f && G <= 1.0f);
		ASSERT(B >= 0.0f && B <= 1.0f);
		used_clr[0] = R;
		used_clr[1] = G;
		used_clr[2] = B;
	}
	else {
		used_clr[0] = intensity;
		used_clr[1] = intensity;
		used_clr[2] = intensity;
	}
}



NAMESPACE_TOPSIDE_END
