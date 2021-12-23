#include <Graphics/Graphics.h>

NAMESPACE_TOPSIDE_BEGIN


SoftRend::SoftRend() {
	viewport_size = Size(0,0);
	SET_ZERO(input_texture);
	
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

void SoftRend::RenderScreenRect(bool elements) {
	ASSERT(tgt_pipe && tgt_fb);
	SoftPipeline& pipe = *tgt_pipe;
	SoftFramebuffer& fb = *tgt_fb;
	
	SDL_Texture* tex = fb.tex;
	
	SDL_Surface* surf = 0;
	SDL_Rect r {0, 0, w, h};
	if (SDL_LockTextureToSurface(tex, &r, &surf) < 0 || !surf)
		return;
	
	int stride = surf->format->BytesPerPixel;
	int pitch = surf->pitch;
	byte* data = (byte*)surf->pixels;
	
	SdlCpuFragmentShaderArgs frag_args;
	
	for(int i = 0; i < TEXTYPE_COUNT; i++)
		frag_args.tex_img[i] = input_texture[i];
	
	vec2& coord = frag_args.frag_coord;
	vec4& out = frag_args.frag_color_out;
	vec3& normal = frag_args.normal;
	vec3& bc_screen = frag_args.bc_screen;
	vec2& tex_coord = frag_args.tex_coord;
	
	if (!elements) {
		SoftShaderBase& fs = tmp_sources[0].frag->Get();
		for (int y = 0; y < h; y++) {
			byte* it = data + (h - 1 - y) * pitch;
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
		//const Vertex* vertices = GetVertices().vertices.Begin();
		//const uint32* indices = GetIndices().indices.Begin();
		ASSERT(stride >= 1 && stride <= 4);
		for (int y = 0; y < h; y++) {
			byte* it = data + (h - 1 - y) * pitch;
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
					const RenderSource& rs = tmp_sources[zinfo->src_id];
					const Vertex* vertices = rs.GetVertices().vertices.Begin();
					const uint32* indices = rs.ebo->indices.Begin();
					SoftVertexBuffer* input_vertices = rs.vbo;
					SoftShaderBase& fs = rs.frag->Get();
					
					SoftProgram& prog = *rs.prog;
					GenericShaderArgs& g = prog.args;
					frag_args.generic = &g;
					frag_args.fa = &prog.fargs;
					if (g.iResolution[0] == 0 || g.iResolution[1] == 0)
						g.iResolution = vec3(w, h, 0);
					
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
						normal = (in_c - in_a) ^ (in_b - in_a);
						normal.Normalize();
					}
					else
						normal.Clear();
					
					bc_screen = zinfo->bc_screen;
					
					
					tex_coord.Clear();
					for(int i = 0; i < 2; i++) tex_coord[i] += a.tex_coord[i] * bc_screen[0];
					for(int i = 0; i < 2; i++) tex_coord[i] += b.tex_coord[i] * bc_screen[1];
					for(int i = 0; i < 2; i++) tex_coord[i] += c.tex_coord[i] * bc_screen[2];
					ASSERT(tex_coord[0] >= 0.0f && tex_coord[0] <= 1.0f);
					ASSERT(tex_coord[1] >= 0.0f && tex_coord[1] <= 1.0f);
					
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

void SoftRend::RenderScreenRect() {
	ASSERT(tgt_pipe && tgt_fb);
	for (SoftPipeline::Stage& stage : tgt_pipe->stages) {
		SoftProgram& prog = *stage.prog;
		for (SoftShader* shader : prog.shaders) {
			GVar::ShaderType type = shader->GetType();
			if (type == GVar::FRAGMENT_SHADER) {
				RenderScreenRect(false);
			}
		}
	}
}

void SoftRend::ProcessVertexShader(SoftShader& shdr, SoftVertexArray& vao, uint16 src_id) {
	RenderSource& rs = tmp_sources[src_id];
	SoftVertexBuffer& processed_vertices = rs.processed_vertices;
	ASSERT(vao.vbo && vao.ebo);
	SoftVertexBuffer& vbo = *vao.vbo;
	SoftElementBuffer& ebo = *vao.ebo;
	SoftShaderBase& vs = shdr.Get();
	SoftProgram& prog = *rs.prog;
	
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
	
	rs.use_processed_vertices = true;
}

void SoftRend::TriangleDepthTest(DepthInfo& info, const Vertex& a, const Vertex& b, const Vertex& c, uint16 src_id) {
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
			if ((greater && z > 0.0f && zmem < z) || (!greater && z < 0.0f && zmem > z)) {
				zmem = z;
				auto& i = zinfo[pos];
				i.triangle_i = info.triangle_i;
				i.bc_screen = bc_screen;
				i.src_id = src_id;
			}
		}
	}
}

void SoftRend::DepthTest(SoftVertexArray& vao, uint16 src_id) {
	SoftElementBuffer& ebo = *vao.ebo;
	SoftVertexBuffer& vbo = tmp_sources[src_id].GetVertices();
	Vertex* vert = (Vertex*)vbo.vertices.Begin();
	uint32* iter = (uint32*)ebo.indices.Begin();
	uint32 vtx_count = vbo.vertices.GetCount();
	uint32 idx_count = ebo.indices.GetCount();
	uint32 triangles = idx_count / 3;
	
	DepthInfo info;
		
	for(info.triangle_i = 0; info.triangle_i < triangles; info.triangle_i++) {
		uint32 tri_a = iter[0];
		uint32 tri_b = iter[1];
		uint32 tri_c = iter[2];
		ASSERT(tri_a < vtx_count && tri_b < vtx_count && tri_c < vtx_count);
		const Vertex& a = vert[tri_a];
		const Vertex& b = vert[tri_b];
		const Vertex& c = vert[tri_c];
		
		TriangleDepthTest(info, a, b, c, src_id);
		
		iter += 3;
	}
	
	//input_indices = &ebo;
	//RenderScreenRect(fb, prog, shdr, true);
}

void SoftRend::Render(SoftVertexArray& vao) {
	ASSERT(vao.vbo && vao.ebo);
	ASSERT(tgt_pipe && tgt_fb);
	SoftPipeline& pipe = *tgt_pipe;
	SoftFramebuffer& fb = *tgt_fb;
	
	//SoftShader* shdrs[GVar::SHADERTYPE_COUNT] = {0,0,0,0,0};
	
	
	//input_vertices = vao.vbo;
	
	for (SoftPipeline::Stage& stage : pipe.stages) {
		SoftProgram& prog = *stage.prog;
		
		if (tmp_sources.GetCount() >= UINT16_MAX)
			Panic("SoftRend render source limit exceeded");
		uint16 src_id = tmp_sources.GetCount();
		RenderSource& rs = tmp_sources.Add();
		//rs.pipe = &pipe;
		//rs.fb = &fb;
		rs.vbo = vao.vbo;
		rs.ebo = vao.ebo;
		rs.prog = &prog;
		
		//ClearTemp();
		
		for (SoftShader* shader : prog.shaders) {
			GVar::ShaderType type = shader->GetType();
			if (type == GVar::VERTEX_SHADER) {
				ProcessVertexShader(*shader, vao, src_id);
				DepthTest(vao, src_id);
			}
			else if (type == GVar::FRAGMENT_SHADER) {
				rs.frag = shader;
			}
			else {
				TODO
			}
		}
	}
}

void SoftRend::Begin() {
	ASSERT(tgt_fb && tgt_pipe);
	
	tmp_sources.SetCount(0);
	
	// query target dimension
	SDL_Texture* tex = tgt_fb->tex;
	uint32 fmt = 0;
	int access;
	w = 0, h = 0;
	SDL_QueryTexture(tex, &fmt, &access, &w, &h);
	
	// reset z-buffer
	int len = w * h;
	zinfo.SetCount(len);
	memset((DepthInfo*)zinfo.Begin(), 0, len * sizeof(DepthInfo));
	zbuffer.SetCount(len);
	float reset_f = GetDepthResetValue();
	for (float& f : zbuffer) f = reset_f;
	
}

void SoftRend::End() {
	RenderScreenRect(true);
}

/*void SoftRend::ClearTemp() {
	vertices.SetCount(0);
	indices.SetCount(0);
}*/


NAMESPACE_TOPSIDE_END
