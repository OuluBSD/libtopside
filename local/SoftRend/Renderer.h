#ifndef _SoftRend_Renderer_h_
#define _SoftRend_Renderer_h_

NAMESPACE_TOPSIDE_BEGIN


class SoftRend {
	bool verbose = false;
	Vector<SoftFramebuffer*> buffers;
	GVar::ShadeMode shading = GVar::FLAT;
	Size viewport_size;
	RGBA clear_color;
	byte clear_depth = 0;
	bool is_depth_test = false;
	bool is_depth_order_greater = false;
	bool is_fast_perspective_correction = false;
	bool is_triangle_backside_culling = false;
	bool is_triangle_frontside_cw = false;
	
	SoftVertexBuffer processed_vertices;
	SoftVertexBuffer* input_vertices = 0;
	SoftElementBuffer* input_indices = 0;
	const SoftFramebuffer* input_texture[TEXTYPE_COUNT];
	bool use_processed_vertices = false;
	
	Vector<Vertex> vertices;
	Vector<uint32> indices;
	
	
	struct DepthInfo : Moveable<DepthInfo> {
		uint32 triangle_i;
		vec3 bc_screen;
	};
	Vector<DepthInfo> zinfo;
	Vector<float> zbuffer;
	
	void ClearTemp();
	void ProcessVertexShader(SoftFramebuffer& fb, SoftProgram& prog, SoftShader& shdr, SoftVertexArray& vao);
	void Render(SoftFramebuffer& fb, SoftProgram& prog, SoftShader& shdr, SoftVertexArray& vao);
	void TriangleDepthTest(SoftFramebuffer& fb, SoftProgram& prog, DepthInfo& info, const Vertex& a, const Vertex& b, const Vertex& c);
	
	SoftVertexBuffer& GetVertices() {return use_processed_vertices ? processed_vertices : *input_vertices;}
	SoftElementBuffer& GetIndices() {return *input_indices;}
	
public:
	typedef SoftRend CLASSNAME;
	SoftRend();
	
	void SetDebugOutput(bool b) {verbose = b;}
	void ClearBuffers();
	void SetSmoothShading(bool b=true);
	void SetDepthTest(bool b=true);
	void SetDepthOrderLess(bool b=true);
	void SetClearValue(RGBA clr, byte depth);
	void SetFastPerspectiveCorrection(bool b=true);
	void SetTriangleBacksideCulling(bool b=true);
	void SetTriangleFrontsideCCW(bool b=true);
	void SetViewport(Size sz);
	
	void RenderScreenRect(SoftFramebuffer& fb, SoftProgram& prog, SoftShader& shdr, bool elements=false);
	void RenderScreenRect(SoftPipeline& pipe, SoftFramebuffer& fb);
	void Render(SoftPipeline& pipe, SoftFramebuffer& fb, SoftVertexArray& vao);
	
	float GetDepthResetValue() const {return is_depth_order_greater ? -1e10f : +1e10f;}
	
	void BindTexture(int type, const SoftFramebuffer* tex) {ASSERT(type >= 0 && type < TEXTYPE_COUNT); input_texture[type] = tex;}
	
};


NAMESPACE_TOPSIDE_END

#endif
