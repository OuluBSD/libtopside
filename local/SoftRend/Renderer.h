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
	
	Vector<Vertex> vertices;
	Vector<uint32> indices;
	
	
	void ClearTemp();
	
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
	
	void RenderScreenRect(SoftFramebuffer& fb, SoftShader& shdr);
	void RenderScreenRect(SoftPipeline& pipe, SoftFramebuffer& fb);
	void Render(SoftPipeline& pipe, SoftFramebuffer& fb);
	
};


NAMESPACE_TOPSIDE_END

#endif
