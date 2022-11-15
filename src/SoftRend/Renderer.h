#ifndef _SoftRend_Renderer_h_
#define _SoftRend_Renderer_h_

NAMESPACE_TOPSIDE_BEGIN


class SoftRend {
	bool verbose = false;
	//Vector<SoftFramebuffer*> buffers;
	GVar::ShadeMode shading = GVar::FLAT;
	Size viewport_size;
	RGBA clear_color;
	byte clear_depth = 0;
	bool is_depth_test = false;
	bool is_depth_order_less = false;
	bool is_fast_perspective_correction = false;
	bool is_triangle_backside_culling = false;
	bool is_triangle_frontside_cw = false;
	int w = 0, h = 0;
	GVar::RenderTarget draw_buffers;
	
	//SoftVertexBuffer processed_vertices;
	//SoftVertexBuffer* input_vertices = 0;
	//SoftElementBuffer* input_indices = 0;
	//ConstByteImage* input_texture[TEXTYPE_COUNT];
	
	SoftPipeline* tgt_pipe = 0;
	SoftFramebuffer* tgt_fb = 0;
	
	SoftShader vtx_passthrough;
	
	//Vector<Vertex> vertices;
	//Vector<uint32> indices;
	
	struct RenderSource : Moveable<RenderSource> {
		//SoftPipeline* pipe = 0;
		//SoftFramebuffer* fb = 0;
		SoftVertexBuffer* vbo = 0;
		SoftElementBuffer* ebo = 0;
		SoftProgram* prog = 0;
		SoftShader* frag = 0;
		SoftShader* vtx = 0;
		
		bool use_processed_vertices = false;
		SoftVertexBuffer processed_vertices;
		SoftVertexBuffer& GetVertices() {return use_processed_vertices ? processed_vertices : *vbo;}
		const SoftVertexBuffer& GetVertices() const {return use_processed_vertices ? processed_vertices : *vbo;}
	};
	Vector<RenderSource> tmp_sources;
	
	
	//void ClearTemp();
	void ProcessVertexShader(SoftShader& shdr, SoftVertexArray& vao, uint16 src_id);
	void DepthTest(SoftVertexArray& vao, uint16 src_id, bool use_quad);
	void DepthTestTriangle(DepthImage::Info& info, const Vertex& a, const Vertex& b, const Vertex& c, uint16 src_id);
	void DepthTestQuad(DepthImage::Info& info, const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d, uint16 src_id);
	
	//SoftVertexBuffer& GetVertices() {return use_processed_vertices ? processed_vertices : *input_vertices;}
	//SoftElementBuffer& GetIndices() {return *input_indices;}
	
public:
	typedef SoftRend CLASSNAME;
	SoftRend();
	
	void Begin();
	void End();
	void DrawDefault(SoftFramebuffer& fb);
	void ClearTargets();
	//void AddBuffer(SoftFramebuffer& fb);
	GVar::RenderTarget GetTargets() const {return draw_buffers;}
	
	void SetDebugOutput(bool b) {verbose = b;}
	//void ClearBuffers();
	void SetSmoothShading(bool b=true);
	void SetDepthTest(bool b=true);
	void SetDepthOrderLess(bool b=true);
	void SetClearValue(RGBA clr, byte depth);
	void SetFastPerspectiveCorrection(bool b=true);
	void SetTriangleBacksideCulling(bool b=true);
	void SetTriangleFrontsideCCW(bool b=true);
	void SetViewport(Size sz);
	void SetDrawBuffers(GVar::RenderTarget t) {draw_buffers = t;}
	
	void RenderScreenRect0(bool elements);
	void RenderScreenRect();
	void SetTarget(SoftPipeline& pipe, SoftFramebuffer& fb) {tgt_pipe = &pipe; tgt_fb = &fb;}
	//void SetPipeline(SoftPipeline& pipe) {tgt_pipe = &pipe;}
	void Render(SoftProgram& prog, SoftVertexArray& vao, bool use_quad);
	
	float GetDepthResetValue() const {return is_depth_order_less ? +1e10f : -1e10f;}
	
	//void BindTexture(int type, ConstByteImage* tex) {ASSERT(type >= 0 && type < TEXTYPE_COUNT); input_texture[type] = tex;}
	


	static bool LockTextureToSurface(SoftFramebuffer* tex, Rect r, ByteImage*& surf);
	static void QueryTexture(SoftFramebuffer* tex, uint32& fmt, int& access, int& w, int& h);
	static void UnlockTextureToSurface(SoftFramebuffer* tex);
};


NAMESPACE_TOPSIDE_END

#endif
