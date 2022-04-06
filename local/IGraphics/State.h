#ifndef _IGraphics_State_h_
#define _IGraphics_State_h_

NAMESPACE_PARALLEL_BEGIN


struct GfxShaderState : RTTIBase {
	 RTTI_DECL0(GfxShaderState)
	
	using ShaderType = GVar::ShaderType;
	
	virtual ~GfxShaderState() {}
	
	// meta
	bool enabled;
	
	// shader stage
	ShaderType	type = GVar::SHADERTYPE_NULL;
	String		code;
	String		library;
	
	// vertex shader
	mat4	view;
	mat4	projection;
	mat4	scale;
	mat4	offset;
	
	
	
	void Clear() {
		enabled = 0;
		type = GVar::SHADERTYPE_NULL;
		code.Clear();
		library.Clear();
		view.Clear();
		projection.Clear();
		scale.Clear();
		offset.Clear();
	}
	
};

#if 0
class StateDraw : public Draw {
	FramebufferState* state = 0;
	
	
public:
	RTTI_DECL1(StateDraw, Draw)
	
	void SetTarget(FramebufferState& state) {this->state = &state;}
	
	bool HasTarget() const {return state != 0;}
	FramebufferState& GetState() {return *state;}
	
	Size GetPageSize() const override {return state ? state->size : Size(0,0);}
	void DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) override;
	void DrawRectOp(int x, int y, int cx, int cy, Color color) override;
	void DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
		             Color ink, int n, const int *dx) override;
	void DrawPolyPolylineOp(const Point *vertices, int vertex_count,
	                        const int *counts, int count_count,
	                        int width, Color color, Color doxor) override;
	bool ClipOp(const Rect& r) override;
	void EndOp() override;
	
	void DrawImageMemory(const  byte* mem, int sz, int x, int y, int w, int h, int ch_var_size, int channels);
	
};
#endif


NAMESPACE_PARALLEL_END


#endif
