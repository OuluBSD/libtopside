#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
void PassVertexT<Gfx>::Process(VertexShaderArgsT<Gfx>& a) {
	auto& pos = a.v.position;
	auto& tex = a.v.tex_coord;
	pos[0] = (pos[0] + 1) * 0.5;
	pos[1] = (pos[1] + 1) * 0.5;
	tex = pos.template Splice<0,2>();
	pos[0] *= a.generic->iResolution[0];
	pos[1] *= a.generic->iResolution[1];
}

template <class Gfx>
void PassFragmentT<Gfx>::Process(FragmentShaderArgsT<Gfx>& args) {
	float w = args.generic->iResolution[0];
	float h = args.generic->iResolution[1];
	float x = args.frag_coord[0] / w;
	float y = args.frag_coord[1] / h;
	args.frag_color_out = vec4(x, y, 0, 1);
	
	vec4& used_clr = args.frag_color_out;
	used_clr[3] = 0;
	
	
	auto& diffuse = args.tex_img[TEXTYPE_DIFFUSE];
	
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

template <class Gfx>
void ColorTestFragmentT<Gfx>::Process(FragmentShaderArgsT<Gfx>& args) {
	const vec3& res = args.generic->iResolution;
	
	float t = args.generic->iTime;
	
	vec3 shift = vec3(			sin(t),
								sin(t + M_PI / 3.0),
								sin(t + M_PI * 2.0 / 3.0));
	
	args.frag_color_out = vec4(	args.frag_coord[0] / res[0] + shift[0],
								args.frag_coord[1] / res[1] + shift[1],
								1.0 - args.frag_coord[1] / res[1] + shift[2],
								0);
}

template <class Gfx>
ProxyInput0FragmentT<Gfx>::ProxyInput0FragmentT() {
	this->UseUniform(GVar::VAR_COMPAT_CHANNEL0);
	this->UseUniform(GVar::VAR_COMPAT_CHANNELRESOLUTION);
	
}

vec4 texture(const ByteImage* ch, const vec2& uv) {
	int x = uv[0] * (ch->GetWidth()-1);
	int y = uv[1] * (ch->GetHeight()-1);
	
	if (x >= 0 && y >= 0 &&
		x < ch->GetWidth() && y < ch->GetHeight()) {
		const byte* it = ch->GetIter(x, y);
		ASSERT(ch->GetChannels() == 3 || ch->GetChannels() == 4);
		return vec4(	it[0] / 255.0,
						it[1] / 255.0,
						it[2] / 255.0,
						1.0);
	}
	return vec4{0,0,0,0};
}

template <class Gfx>
void ProxyInput0FragmentT<Gfx>::Process(FragmentShaderArgsT<Gfx>& args) {
	NativeColorBufferConstRef iChannel0 = Gfx::GetLocalTexture(args.generic->iChannel0);
	ASSERT(iChannel0);
	
	const auto& iResolution = args.generic->iResolution;
	const auto& fragCoord = args.frag_coord;
	auto& fragColor = args.frag_color_out;
	
	vec2 uv = fragCoord / iResolution.Splice();
	vec4 clr = texture(iChannel0, uv);
	clr[0] = 1.0;
    fragColor = clr;
}

X11SW_EXCPLICIT_INITIALIZE_CLASS(PassVertexT)
X11SW_EXCPLICIT_INITIALIZE_CLASS(PassFragmentT)
X11SW_EXCPLICIT_INITIALIZE_CLASS(ColorTestFragmentT)
X11SW_EXCPLICIT_INITIALIZE_CLASS(ProxyInput0FragmentT)

NAMESPACE_PARALLEL_END
