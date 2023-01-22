#ifndef _Geometry_ModelPainter_h_
#define _Geometry_ModelPainter_h_

NAMESPACE_TOPSIDE_BEGIN


class ModelPainter : public Draw3 {
	DrawCommand *prev;
	DrawCommand *next;
	DrawCommand *begin;
	DrawCommand *end;
	DrawCommand *cur_begin = NULL;
	DrawCommand *cur = NULL;
	
	Vector<vec3> tmp0;
	Vector<double> angles;
	Volf sz;
	
	DrawCommand& CreateCommand();
	
	
public:
	ModelPainter(Volf sz, DrawCommand& prev, DrawCommand& begin, DrawCommand& end, DrawCommand& next);
	ModelPainter(Volf sz, ModelPainter& p, DrawCommand& begin, DrawCommand& end);
	~ModelPainter() {/*Clear();*/}
	
	void Clear();
	DrawCommand* GetBegin() const;
	DrawCommand* GetEnd() const;
	
	void SetSize(Volf v) override;
	Volf GetPageSize() const override;
	void CtrlDrawBegin(hash_t h) override;
	void CtrlDrawEnd() override;
	void DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) override;
	void DrawCuboidOp(float x, float y, float z, float cx, float cy, float zy, Color color) override;
	void DrawTextOp(float x, float y, float z, float angle, const wchar *text, Font font,
		            Color ink, int n, const float *dx) override;
	void DrawPolyPolylineOp(const vec3 *vertices, int vertex_count,
	                        const int *counts, int count_count,
	                        float width, Color color, Color doxor) override;
	bool ClipOp(const Cubf& r) override;
	void EndOp() override;
	
	
	void BindWindow(hash_t h);
	void UnbindWindow();
	void DrawLine(float x0, float y0, float z0, float x1, float y1, float z1, float line_width, RGBA c);
	#ifdef UPP_VERSION
	void DrawImageOp(float x1, float y1, float z1, float x2, float y2, float z2, const Image& img, const Rect& src, Color color) override {TODO};
	void DrawImage(float x, float y, float z, Image img, byte alpha=255);
	#else
	void DrawImage(float x, float y, float z, Image img, byte alpha=255) override;
	#endif
	void DrawCuboid(Cubf r, RGBA clr);
	void DrawCuboid(float x, float y, float z, float w, float h, float d, RGBA clr);
	void DrawText(float x, float y, float z, String txt, Font fnt, RGBA clr);
	void DrawPolyline(const vec3* pts, int pt_count, float line_width, RGBA c);
	void DrawPolygon(const Vector<vec3>& pts, RGBA c);
	
	void Offset(const Cubf& r);
	void End();
	void WindowOffset(const Cubf& r);
	void WindowEnd();
	
	
	void Link();
	void Dump();
	
	//void Attach(Ctrl& c);
	void Attach(DrawCommand& begin, DrawCommand& end);
	void AppendPick(DrawCommand* begin, DrawCommand* end);
	
};

NAMESPACE_TOPSIDE_END

#endif
