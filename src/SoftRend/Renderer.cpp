#include "SoftRend.h"

NAMESPACE_TOPSIDE_BEGIN




SoftRend::SoftRend() {
	viewport_size = Size(TS::default_width, TS::default_height);
	//SET_ZERO(input_texture);
}


void SoftRend::DrawDefault(SoftFramebuffer& fb) {
	fb.Zero((GVar::RenderTarget)255, clear_color);
}


void SoftRend::ClearTargets() {
	draw_buffers = (GVar::RenderTarget)0;
}

void SoftRend::SetSmoothShading(bool b) {
	shading = b ? GVar::SMOOTH : GVar::FLAT;
}


void SoftRend::SetDepthTest(bool b) {
	is_depth_test = b;
}


void SoftRend::SetDepthOrderLess(bool b) {
	is_depth_order_less = b;
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


void SoftRend::RenderScreenRect0(bool elements) {
	ASSERT(tgt_pipe && tgt_fb);
	SoftPipeline& pipe = *tgt_pipe;
	SoftFramebuffer& fb = *tgt_fb;
	
	ASSERT(w > 0 && h > 0);
	
	DepthImage* depth = tgt_fb->GetDepth();
	ByteImage* surf = 0;
	Rect r = RectC(0, 0, w, h);
	if (!LockTextureToSurface(tgt_fb, r, surf) || !surf)
		return;
	
	int stride = surf->GetChannels();
	int pitch = surf->GetPitch();
	byte* data = (byte*)surf->Begin();
	
	FragmentShaderArgs frag_args;
	
	//for(int i = 0; i < TEXTYPE_COUN; i++)
	//	frag_args.tex_img[i] = input_texture[i];
	
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
		ASSERT(depth);
		if (!depth)
			return;
		
		ASSERT(depth->info.GetCount() == h*w);
		ASSERT(depth->data.GetCount() == h*w);
		DepthImage::Info* zinfo = (DepthImage::Info*)depth->info.Begin();
		float* zbuffer = (float*)depth->data.Begin();
		float reset_f = GetDepthResetValue();
		//const Vertex* vertices = GetVertices().vertices.Begin();
		//const uint32* indices = GetIndices().indices.Begin();
		ASSERT(stride >= 1 && stride <= 4);
		
		// NOTE: non-accelerated y is top-left (not bottom-left). Don't blame me... not my decision.
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
					int src_id = zinfo->src_id;
					const RenderSource& rs = tmp_sources[zinfo->src_id];
					const Vertex* vertices = rs.GetVertices().vertices.Begin();
					const uint32* indices = rs.ebo->indices.Begin();
					SoftVertexBuffer* input_vertices = rs.vbo;
					SoftShaderBase& fs = rs.frag->Get();
					
					SoftProgram& prog = *rs.prog;
					GenericShaderArgs& g = prog.GetArgs();
					frag_args.generic = &g;
					frag_args.fa = &prog.GetFragmentArgs(src_id);
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
					ASSERT(tex_coord[0] >= -1.0f && tex_coord[0] <= 1.0f);
					ASSERT(tex_coord[1] >= -1.0f && tex_coord[1] <= 1.0f);
					
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
	
	UnlockTextureToSurface(tgt_fb);
}


void SoftRend::RenderScreenRect() {
	ASSERT(tgt_pipe && tgt_fb);
	using Stage = typename SoftPipeline::Stage;
	for (Stage& stage : tgt_pipe->stages) {
		SoftProgram& prog = *stage.prog;
		for (SoftShader* shader : prog.GetShaders()) {
			GVar::ShaderType type = shader->GetType();
			if (type == GVar::FRAGMENT_SHADER) {
				RenderScreenRect0(false);
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
	
	VertexShaderArgs vtx_args;
	GenericShaderArgs& g = prog.GetArgs();
	vtx_args.generic = &g;
	vtx_args.va = &prog.GetVertexArgs(src_id);
	
	int vtx_count = vbo.vertices.GetCount();
	processed_vertices.vertices.SetCount(vtx_count);
	if (!vtx_count)
		return;
	
	const Vertex* iter_in     = (Vertex*)vbo.vertices.Begin();
	const Vertex* iter_in_end = iter_in + vtx_count;
	Vertex*       iter_out    = (Vertex*)processed_vertices.vertices.Begin();
	
	int width = vtx_args.generic->iResolution[0];
	int height = vtx_args.generic->iResolution[1];
	ASSERT(width && height); // crash here: vertex shdaer did not call this in ctor: UseUniform(GVar::VAR_COMPAT_RESOLUTION);
	while (iter_in != iter_in_end) {
		vtx_args.v = *iter_in++;
		
		//LOG(vtx_args.v.position.ToString());
		
		vs.Process(vtx_args);
		
		//LOG("\t\t\t\t\t" << vtx_args.v.position.ToString());
		
		auto& pos = vtx_args.v.position;
		pos[0] = (int)((pos[0] + 1.0) * width  / 2.0);
		pos[1] = (int)((pos[1] + 1.0) * height / 2.0);
		
		*iter_out++ = vtx_args.v;
	}
	
	rs.use_processed_vertices = true;
}


void SoftRend::TriangleDepthTest(DepthImage::Info& info, const Vertex& a, const Vertex& b, const Vertex& c, uint16 src_id) {
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
	
	DepthImage* depth = tgt_fb ? tgt_fb->GetDepth() : 0;
	ASSERT(depth);
	if (!depth) return;
	
	int pos_limit = depth->GetSize();
	float* zbuffer = (float*)depth->data.Begin();
	DepthImage::Info* zinfo = (DepthImage::Info*)depth->info.Begin();
	
	bool less_or_equal = is_depth_order_less;
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
			
			//z *= SCALAR_FWD_Z;
			
			int pos = (int)P[0] + (int)P[1] * w;
			ASSERT(pos >= 0 && pos < pos_limit);
			float& zmem = zbuffer[pos];
			if ((!less_or_equal && z <= 0.0f && zmem < z) || (less_or_equal && z >= 0.0f && zmem > z)) {
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
	
	DepthImage::Info info;
		
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


void SoftRend::Render(SoftProgram& prog, SoftVertexArray& vao) {
	ASSERT(vao.vbo && vao.ebo);
	ASSERT(tgt_pipe && tgt_fb);
	SoftFramebuffer& fb = *tgt_fb;
	SoftPipeline& pipe = *tgt_pipe;
	
	ASSERT(prog.pipeline == tgt_pipe);
	
	//SoftShader* shdrs[GVar::SHADERTYPE_COUNT] = {0,0,0,0,0};
	
	
	//input_vertices = vao.vbo;
	using Stage = typename SoftPipeline::Stage;
	
	for (Stage& stage : pipe.stages) {
		SoftProgram& p = *stage.prog;
		if (&p != &prog)
			continue;
		
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
		
		rs.vtx = 0;
		rs.frag = 0;
		for (SoftShader* shader : prog.GetShaders()) {
			GVar::ShaderType type = shader->GetType();
			if (type == GVar::VERTEX_SHADER) {
				rs.vtx = shader;
			}
			else if (type == GVar::FRAGMENT_SHADER) {
				rs.frag = shader;
			}
			else {
				TODO
			}
		}
		
		if (!rs.vtx) {
			vtx_passthrough.SetPassthroughVertexShader(prog, new PassthroughSoftShaderBase());
			rs.vtx = &vtx_passthrough;
		}
		
		ProcessVertexShader(*rs.vtx, vao, src_id);
		DepthTest(vao, src_id);
		
		return;
	}
	
	Panic("error");
}


void SoftRend::Begin() {
	ASSERT(tgt_fb && tgt_pipe);
	
	tmp_sources.SetCount(0);
	
	// query target dimension
	ASSERT(tgt_fb);
	uint32 fmt = 0;
	int access;
	w = 0, h = 0;
	
	QueryTexture(tgt_fb, fmt, access, w, h);
	
	if (w == 0 || h == 0) {
		ASSERT(viewport_size.cx > 0 && viewport_size.cy > 0);
		w = viewport_size.cx;
		h = viewport_size.cy;
		tgt_fb->SetSize(draw_buffers, viewport_size);
	}
	
	// reset color buffer
	tgt_fb->Zero(draw_buffers, Black());
	
	// reset z-buffer
	DepthImage* depth = tgt_fb->GetDepth();
	if (depth) {
		depth->Set(Size(w,h), 1);
		depth->Zero(GetDepthResetValue());
	}
}


void SoftRend::End() {
	RenderScreenRect0(true);
}

/*

void SoftRend::ClearTemp() {
	vertices.SetCount(0);
	indices.SetCount(0);
}*/






bool SoftRend::LockTextureToSurface(SoftFramebuffer* tex, Rect r, ByteImage*& surf) {
	surf = tex->Get(0);
	ASSERT(surf);
	return true;
}

void SoftRend::QueryTexture(SoftFramebuffer* tex, uint32& fmt, int& access, int& w, int& h) {
	ASSERT(tex);
	fmt = 0;
	access = 0;
	Size sz = tex->GetSize();
	w = sz.cx;
	h = sz.cy;
}

void SoftRend::UnlockTextureToSurface(SoftFramebuffer* tex) {
	
}


NAMESPACE_TOPSIDE_END
