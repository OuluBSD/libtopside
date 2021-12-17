#include <Graphics/Graphics.h>

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

void SoftRend::RenderScreenRect(SoftFramebuffer& fb, SoftProgram& prog, SoftShader& shdr, bool elements) {
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
	
	SoftShaderBase& fs = shdr.Get();
	
	SdlCpuFragmentShaderArgs frag_args;
	GenericShaderArgs& g = prog.args;
	frag_args.generic = &g;
	frag_args.fa = &prog.fargs;
	
	if (g.iResolution[0] == 0 || g.iResolution[1] == 0)
		g.iResolution = vec3(w, h, 0);
	
	vec2& coord = frag_args.frag_coord;
	vec4& out = frag_args.frag_color_out;
	vec3& normal = frag_args.normal;
	
	if (!elements) {
		for (int y = 0; y < h; y++) {
			byte* it = data + y * pitch;
			coord[1] = y;
			for (int x = 0; x < w; x++) {
				coord[0] = x;
				fs.Process(frag_args);
				for(int i = 0; i < stride; i++) {
					*it = max(0, min(255, (int)(out[i] * 255)));
					it++;
				}
			}
		}
	}
	else {
		ASSERT(zinfo.GetCount() == h*w);
		ASSERT(zbuffer.GetCount() == h*w);
		DepthInfo* zinfo = (DepthInfo*)this->zinfo.Begin();
		float* zbuffer = (float*)this->zbuffer.Begin();
		float reset_f = GetDepthResetValue();
		const Vertex* vertices = GetVertices().vertices.Begin();
		const uint32* indices = GetIndices().indices.Begin();
		ASSERT(stride >= 1 && stride <= 4);
		for (int y = 0; y < h; y++) {
			byte* it = data + y * pitch;
			coord[1] = y;
			for (int x = 0; x < w; x++) {
				coord[0] = x;
				
				if (*(uint32*)zbuffer == *(uint32*)&reset_f) {
					for(int i = 0; i < stride; i++) {
						*it = 0;
						it++;
					}
				}
				else {
					int idx_base = zinfo->triangle_i * 3;
					int idx_a = indices[idx_base + 0];
					int idx_b = indices[idx_base + 1];
					int idx_c = indices[idx_base + 2];
					const Vertex& a = vertices[idx_a];
					const Vertex& b = vertices[idx_b];
					const Vertex& c = vertices[idx_c];
					
					if (input_vertices) {
						vec3 in_a = input_vertices->vertices[idx_a].position.Splice();
						vec3 in_b = input_vertices->vertices[idx_b].position.Splice();
						vec3 in_c = input_vertices->vertices[idx_c].position.Splice();
						normal = (in_c - in_a) ^
								 (in_b - in_a);
						normal.Normalize();
					}
					else
						normal.Clear();
					
					fs.Process(frag_args);
					
					for(int i = 0; i < stride; i++) {
						*it = max(0, min(255, (int)(out[i] * 255)));
						it++;
					}
				}
				
				zinfo++;
				zbuffer++;
			}
		}
	}
	
	SDL_UnlockTexture(tex);
}

void SoftRend::RenderScreenRect(SoftPipeline& pipe, SoftFramebuffer& fb) {
	
	for (SoftPipeline::Stage& stage : pipe.stages) {
		SoftProgram& prog = *stage.prog;
		for (SoftShader* shader : prog.shaders) {
			GVar::ShaderType type = shader->GetType();
			if (type == GVar::FRAGMENT_SHADER) {
				RenderScreenRect(fb, prog, *shader);
			}
		}
	}
	
}

void SoftRend::ProcessVertexShader(SoftFramebuffer& fb, SoftProgram& prog, SoftShader& shdr, SoftVertexArray& vao) {
	ASSERT(vao.vbo && vao.ebo);
	SoftVertexBuffer& vbo = *vao.vbo;
	SoftElementBuffer& ebo = *vao.ebo;
	SoftShaderBase& vs = shdr.Get();
	
	SdlCpuVertexShaderArgs vtx_args;
	GenericShaderArgs& g = prog.args;
	vtx_args.generic = &g;
	vtx_args.va = &prog.vargs;
	
	int vtx_count = vbo.vertices.GetCount();
	processed_vertices.vertices.SetCount(vtx_count);
	if (!vtx_count)
		return;
	
	const Vertex* iter_in     = (Vertex*)vbo.vertices.Begin();
	const Vertex* iter_in_end = iter_in + vtx_count;
	Vertex*       iter_out    = (Vertex*)processed_vertices.vertices.Begin();
	
	#if 1
	while (iter_in != iter_in_end) {
		vtx_args.v = *iter_in++;
		vs.Process(vtx_args);
		*iter_out++ = vtx_args.v;
	}
	#else
	int dbg_i = 0;
	while (iter_in != iter_in_end) {
		Vertex dbg_in = *iter_in;
		vtx_args.v = *iter_in++;
		vs.Process(vtx_args);
		Vertex dbg_out = vtx_args.v;
		*iter_out++ = vtx_args.v;
		
		if (dbg_i < 10) LOG(dbg_i << ": " << dbg_in.position.ToString() << " --> " << dbg_out.position.ToString());
		dbg_i++;
	}
	#endif
	
	use_processed_vertices = true;
}

void SoftRend::TriangleDepthTest(SoftFramebuffer& fb, SoftProgram& prog, DepthInfo& info, const Vertex& a, const Vertex& b, const Vertex& c) {
	int w = prog.args.iResolution[0];
	int h = prog.args.iResolution[1];
	vec2 bboxmin(w - 1,  h - 1);
	vec2 bboxmax(0, 0);
	vec2 clamp(w - 1, h - 1);
	const vec3 pts[3] = {a.position.Splice(), b.position.Splice(), c.position.Splice()};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			bboxmin[j] = std::max<float>(0.0,      std::min<float>(bboxmin[j], pts[i][j]));
			bboxmax[j] = std::min<float>(clamp[j], std::max<float>(bboxmax[j], pts[i][j]));
		}
	}
	
	int pos_limit = zbuffer.GetCount();
	float* zbuffer = (float*)this->zbuffer.Begin();
	DepthInfo* zinfo = (DepthInfo*)this->zinfo.Begin();
	
	bool greater = is_depth_order_greater;
	vec2 P;
	for (P[0] = bboxmin[0]; P[0] <= bboxmax[0]; P[0]++) {
		for (P[1] = bboxmin[1]; P[1] <= bboxmax[1]; P[1]++) {
			vec3 bc_screen = GetBarycentric(pts, P);
			if (bc_screen[0] < 0 || bc_screen[1] < 0 || bc_screen[2] < 0)
				continue;
			
			// calculate z-value
			float z = 0;
			for (int i = 0; i < 3; i++)
				z += pts[i][2] * bc_screen[i];
			
			int pos = (int)P[0] + (int)P[1] * w;
			ASSERT(pos >= 0 && pos < pos_limit);
			float& zmem = zbuffer[pos];
			if ((greater && zmem < z) || (!greater && zmem > z)) {
				zmem = z;
				zinfo[pos] = info;
			}
		}
	}
}

void SoftRend::Render(SoftFramebuffer& fb, SoftProgram& prog, SoftShader& shdr, SoftVertexArray& vao) {
	SoftElementBuffer& ebo = *vao.ebo;
	SoftVertexBuffer& vbo = GetVertices();
	Vertex* vert = (Vertex*)vbo.vertices.Begin();
	uint32* iter = (uint32*)ebo.indices.Begin();
	uint32 vtx_count = vbo.vertices.GetCount();
	uint32 idx_count = ebo.indices.GetCount();
	uint32 triangles = idx_count / 3;
	
	int w = prog.args.iResolution[0];
	int h = prog.args.iResolution[1];
	int len = w * h;
	zinfo.SetCount(len);
	memset((DepthInfo*)zinfo.Begin(), 0, len * sizeof(DepthInfo));
	zbuffer.SetCount(len);
	float reset_f = GetDepthResetValue();
	for (float& f : zbuffer) f = reset_f;
	
	DepthInfo info;
		
	for(info.triangle_i = 0; info.triangle_i < triangles; info.triangle_i++) {
		uint32 tri_a = iter[0];
		uint32 tri_b = iter[1];
		uint32 tri_c = iter[2];
		ASSERT(tri_a < vtx_count && tri_b < vtx_count && tri_c < vtx_count);
		const Vertex& a = vert[tri_a];
		const Vertex& b = vert[tri_b];
		const Vertex& c = vert[tri_c];
		
		TriangleDepthTest(fb, prog, info, a, b, c);
		
		iter += 3;
	}
	
	input_indices = &ebo;
	RenderScreenRect(fb, prog, shdr, true);
}

void SoftRend::Render(SoftPipeline& pipe, SoftFramebuffer& fb, SoftVertexArray& vao) {
	ASSERT(pipe && fb);
	ASSERT(vao.vbo && vao.ebo);
	
	//SoftShader* shdrs[GVar::SHADERTYPE_COUNT] = {0,0,0,0,0};
	
	input_vertices = vao.vbo;
	
	for (SoftPipeline::Stage& stage : pipe.stages) {
		SoftProgram& prog = *stage.prog;
		
		ClearTemp();
		
		use_processed_vertices = false;
		for (SoftShader* shader : prog.shaders) {
			GVar::ShaderType type = shader->GetType();
			if (type == GVar::VERTEX_SHADER) {
				ProcessVertexShader(fb, prog, *shader, vao);
			}
			else if (type == GVar::FRAGMENT_SHADER) {
				Render(fb, prog, *shader, vao);
			}
			else {
				TODO
			}
		}
	}
}

void SoftRend::ClearTemp() {
	vertices.SetCount(0);
	indices.SetCount(0);
}


NAMESPACE_TOPSIDE_END
