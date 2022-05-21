#ifndef _SoftRend_Renderer_h_
#define _SoftRend_Renderer_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
class SoftRendT {
	using SoftFramebuffer		= SoftFramebufferT<Gfx>;
	using SoftPipeline			= SoftPipelineT<Gfx>;
	using SoftShader			= SoftShaderT<Gfx>;
	using FragmentShaderArgs	= FragmentShaderArgsT<Gfx>;
	using SoftProgram			= SoftProgramT<Gfx>;
	using SoftShaderBase		= SoftShaderBaseT<Gfx>;
	using NativeTexture				= typename Gfx::NativeTexture;
	using NativeDepthBufferRef		= typename Gfx::NativeDepthBufferRef;
	using NativeColorBufferRef		= typename Gfx::NativeColorBufferRef;
	using NativeColorBufferConstRef	= typename Gfx::NativeColorBufferConstRef;
	
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
	NativeColorBufferConstRef input_texture[TEXTYPE_COUNT];
	
	SoftPipeline* tgt_pipe = 0;
	SoftFramebuffer* tgt_fb = 0;
	
	SoftShader vtx_passthrough;
	PassthroughSoftShaderBaseT<Gfx> vtx_passthrough_base;
	
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
	void DepthTest(SoftVertexArray& vao, uint16 src_id);
	void TriangleDepthTest(DepthImage::Info& info, const Vertex& a, const Vertex& b, const Vertex& c, uint16 src_id);
	
	//SoftVertexBuffer& GetVertices() {return use_processed_vertices ? processed_vertices : *input_vertices;}
	//SoftElementBuffer& GetIndices() {return *input_indices;}
	
public:
	typedef SoftRendT CLASSNAME;
	SoftRendT();
	
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
	void Render(SoftVertexArray& vao);
	
	float GetDepthResetValue() const {return is_depth_order_less ? -1e10f : +1e10f;}
	
	void BindTexture(int type, NativeColorBufferConstRef tex) {ASSERT(type >= 0 && type < TEXTYPE_COUNT); input_texture[type] = tex;}
	
};


NAMESPACE_PARALLEL_END

#endif
