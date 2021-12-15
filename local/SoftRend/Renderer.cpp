#include "SoftRend.h"

NAMESPACE_TOPSIDE_BEGIN


SoftRend::SoftRend() {
	viewport_size = Size(0,0);
	
}

void SoftRend::ClearBuffers() {
	for (SoftFramebuffer* fb : buffers) {
		fb->Clear();
	}
}

void SoftRend::SetSmoothShading(bool b) {
	shading = b ? GVar::SMOOTH : GVar::FLAT;
}

void SoftRend::SetDepthTest(bool b) {
	is_depth_test = b;
}

void SoftRend::SetDepthOrderLess(bool b) {
	is_depth_order_greater = !b;
}

void SoftRend::SetClearValue(RGBA clr, byte depth) {
	clear_color = clr;
	clear_depth = depth;
}

void SoftRend::SetFastPerspectiveCorrection(bool b) {
	is_fast_perspective_correction = b;
}

void SoftRend::SetTriangleBacksideCulling(bool b) {
	is_triangle_backside_culling = b;
}

void SoftRend::SetTriangleFrontsideCCW(bool b) {
	is_triangle_frontside_cw = !b;
}

void SoftRend::SetViewport(Size sz) {
	viewport_size = sz;
}

void SoftRend::RenderScreenRect(SoftFramebuffer& fb, SoftShader& shdr) {
	SDL_Texture* tex = fb.tex;
	
	uint32 fmt = 0;
	int access, w = 0, h = 0;
	if (SDL_QueryTexture(tex, &fmt, &access, &w, &h) < 0 || w == 0 || h == 0)
		return;
	
	SDL_Surface* surf = 0;
	SDL_Rect r {0, 0, w, h};
	if (SDL_LockTextureToSurface(tex, &r, &surf) < 0 || !surf)
		return;
	
	int stride = surf->format->BytesPerPixel;
	int pitch = surf->pitch;
	byte* data = (byte*)surf->pixels;
	
	
	/*
	SDL_PixelFormat* pf = (SDL_PixelFormat*)
	SDL_Rect r {0, 0, w, h};
	void* pixels;
	int pitch = 0;
	SDL_LockTexture(fb, &r, &pixels, &pitch);
	byte* data = (byte*)pixels;
	*/
	
	SoftShaderLibrary::FragmentShader fs = shdr.GetFragment();
	
	if (Shaders::iResolution[0] == 0 || Shaders::iResolution[1] == 0)
		Shaders::iResolution = vec3(w, h, 0);
	
	if (fs) {
		for (int y = 0; y < h; y++) {
			byte* it = data + y * pitch;
			vec2 coord;
			//coord[1] = (float)y / (float)(h-1);
			coord[1] = y;
			for (int x = 0; x < w; x++) {
				//coord[0] = (float)x / (float)(w-1);
				coord[0] = x;
				vec4 out;
				
				fs(out, coord);
				
				for(int i = 0; i < stride; i++) {
					*it = max(0, min(255, (int)(out[i] * 255)));
					it++;
				}
			}
		}
	}
	else TODO;
	
	
	
	SDL_UnlockTexture(tex);
}

void SoftRend::RenderScreenRect(SoftPipeline& pipe, SoftFramebuffer& fb) {
	
	for (SoftPipeline::Stage& stage : pipe.stages) {
		SoftProgram& prog = *stage.prog;
		for (SoftShader* shader : prog.shaders) {
			GVar::ShaderType type = shader->GetType();
			if (type == GVar::FRAGMENT_SHADER) {
				RenderScreenRect(fb, *shader);
			}
		}
	}
	
}

void SoftRend::RenderTriangle(SoftFramebuffer& fb, SoftShader& shdr, const Vertex& a, const Vertex& b, const Vertex& c) {
	
	TODO
	
}

void SoftRend::Render(SoftFramebuffer& fb, SoftShader& shdr, SoftVertexArray& vao) {
	int triangles = vao.ebo->indices.GetCount() / 3;
	
	Vertex* iter = (Vertex*)vao.vbo->vertices.Begin();
	
	for(int i = 0; i < triangles; i++) {
		const Vertex& a = iter[0];
		const Vertex& b = iter[1];
		const Vertex& c = iter[2];
		
		RenderTriangle(fb, shdr, a, b, c);
		
		iter += 3;
	}
	
}

void SoftRend::Render(SoftPipeline& pipe, SoftFramebuffer& fb, SoftVertexArray& vao) {
	ASSERT(pipe && fb);
	ASSERT(vao.vbo && vao.ebo);
	
	SoftShader* shdrs[GVar::SHADERTYPE_COUNT] = {0,0,0,0,0};
	
	for (SoftPipeline::Stage& stage : pipe.stages) {
		SoftProgram& prog = *stage.prog;
		
		ClearTemp();
		
		for (SoftShader* shader : prog.shaders) {
			GVar::ShaderType type = shader->GetType();
			if (type == GVar::FRAGMENT_SHADER) {
				Render(fb, *shader, vao);
			}
		}
	}
	
	
	/*
	VERTEX_SHADER,
	FRAGMENT_SHADER,
	GEOMETRY_SHADER,
	TESS_CONTROL_SHADER,
	TESS_EVALUATION_SHADER
	*/
	
	TODO
	
}

void SoftRend::ClearTemp() {
	vertices.SetCount(0);
	indices.SetCount(0);
}


NAMESPACE_TOPSIDE_END
