#ifndef _Geometry_ModelDraw_h_
#define _Geometry_ModelDraw_h_

NAMESPACE_TOPSIDE_BEGIN


class ModelDraw : public Draw3 {
	One<ModelPainter> d;
	
	Volf GetFrameSize() const;
	
public:
	DrawCommand cmd_screen_begin, cmd_screen_end;
	DrawCommand render_begin, render_end;
	
	
	void LinkRender();
public:
	RTTI_DECL1(ModelDraw, Draw3)
	ModelDraw();
	ModelDraw(Volf sz);
	ModelDraw(float w, float h, float z);
	
	void Create(Volf sz);
	void Create(Volf sz, DrawCommand& sub_begin, DrawCommand& sub_end);
	void Clear();
	void Finish();
	void DetachTo(ModelPainter& pp);
	
	operator Image() const;
	
	
	void SetSize(Volf sz) override;
	Volf GetPageSize() const override;
	void DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) override;
	void DrawCuboidOp(float x, float y, float z, float cx, float cy, float zy, Color color) override;
	void DrawTextOp(float x, float y, float z, float angle, const wchar *text, Font font,
		            Color ink, int n, const float *dx) override;
	void DrawPolyPolylineOp(const vec3 *vertices, int vertex_count,
	                        const int *counts, int count_count,
	                        float width, Color color, Color doxor) override;
	bool ClipOp(const Cubf& c) override;
	void EndOp() override;
	void DrawImage(float x, float y, float z, Image img, byte alpha=255) override;
	Draw& Alpha();
	
	ModelPainter& GetPainter();
	
	String Dump() const;
};


NAMESPACE_TOPSIDE_END

#endif
