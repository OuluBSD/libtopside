#ifndef _IGraphics_ProgDraw_h_
#define _IGraphics_ProgDraw_h_



NAMESPACE_PARALLEL_BEGIN


// DUMMY
/*class ProgDraw : public Draw {
	
public:
	DrawCommand cmd_screen_begin, cmd_screen_end;
	DrawCommand render_begin, render_end;
	
public:
	RTTI_DECL1(ProgDraw, Draw)
	ProgDraw();
	ProgDraw(Size sz);
	ProgDraw(int w, int h);
	
	void Create(Size sz);
	void Clear();
	void Finish();
	
	operator Image() const;
	
	
	Size GetPageSize() const override;
	void DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) override;
	void DrawRectOp(int x, int y, int cx, int cy, Color color) override;
	void DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
		            Color ink, int n, const int *dx) override;
	void DrawPolyPolylineOp(const Point *vertices, int vertex_count,
	                        const int *counts, int count_count,
	                        int width, Color color, Color doxor) override;
	bool ClipOp(const Rect& r) override;
	void EndOp() override;
	Draw& Alpha();
	
};*/


class ProgPainter {
	DrawCommand *prev;
	DrawCommand *next;
	DrawCommand *begin;
	DrawCommand *end;
	DrawCommand *cur_begin = NULL;
	DrawCommand *cur = NULL;
	
	Vector<Point> tmp0, tmp1;
	Vector<double> angles;
	
	DrawCommand& GetNext();
	
	
public:
	ProgPainter(DrawCommand& prev, DrawCommand& begin, DrawCommand& end, DrawCommand& next) : prev(&prev), begin(&begin), end(&end), next(&next) {}
	~ProgPainter() {Clear();}
	
	void Clear();
	
	void DrawLine(int x0, int y0, int x1, int y1, int line_width, RGBA c);
	void DrawImage(int x, int y, Image img, Byte alpha=255);
	void DrawRect(Rect r, RGBA clr);
	void DrawRect(int x, int y, int w, int h, RGBA clr);
	void DrawText(int x, int y, String txt, Font fnt, RGBA clr);
	void DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
		            Color ink, int n, const int *dx);
	void DrawPolyline(const Vector<Point>& pts, int line_width, RGBA c);
	void DrawPolyPolylineOp(const Point *vertices, int vertex_count,
	                        const int *counts, int count_count,
	                        int width, Color color, Color doxor);
	void DrawPolygon(const Vector<Point>& pts, RGBA c);
	
	void Offset(const Rect& r);
	void End();
	
	
	void Link();
};

#if 0

class ProgCpuShader : public CpuShader {
	
	
public:
	using CpuShader::CpuShader;
	
	void Process(CpuFramebufferState& state) override {TODO}
	
};

#endif

class ProgDraw : public Draw {
	One<ProgPainter> d;
	/*CpuDataObject fb;
	CpuFramebufferState state;
	ProgCpuShader shader;*/
	
	Size GetFrameSize() const;
	
public:
	DrawCommand cmd_screen_begin, cmd_screen_end;
	DrawCommand render_begin, render_end;
	
	
public:
	RTTI_DECL1(ProgDraw, Draw)
	ProgDraw();
	ProgDraw(Size sz);
	ProgDraw(int w, int h);
	
	void Create(Size sz);
	void Clear();
	void Finish();
	
	operator Image() const;
	
	
	Size GetPageSize() const override;
	void DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) override;
	void DrawRectOp(int x, int y, int cx, int cy, Color color) override;
	void DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
		            Color ink, int n, const int *dx) override;
	void DrawPolyPolylineOp(const Point *vertices, int vertex_count,
	                        const int *counts, int count_count,
	                        int width, Color color, Color doxor) override;
	bool ClipOp(const Rect& r) override;
	void EndOp() override;
	Draw& Alpha();
	
};

#if 0

class ModelProg {
	
public:
	FramebufferState* state = 0;
	Vector<mat4> offset;
	ModelMesh model;
	Size sz;
	
public:
	ModelProg();
	
	void Process(FramebufferState& state, const DrawCommand* ptr);
	
	void DrawLine(const DrawCommand& cmd);
	void DrawImage(const DrawCommand& cmd);
	void DrawRect(const DrawCommand& cmd);
	void DrawTriangles(const DrawCommand& cmd);
	void DrawPolyline(const DrawCommand& cmd);
	void DrawPolygon(const DrawCommand& cmd);
	void DrawOffset(const DrawCommand& cmd);
	void DrawEnd(const DrawCommand& cmd);
	
};

class DrawProg : public DrawProxy {
	
public:
	RTTI_DECL1(DrawProg, DrawProxy)
	DrawProg();
	void Process(const DrawCommand* ptr);
	
	void DrawLine(const DrawCommand& cmd);
	void DrawImage(const DrawCommand& cmd);
	void DrawRect(const DrawCommand& cmd);
	void DrawTriangles(const DrawCommand& cmd);
	void DrawPolyline(const DrawCommand& cmd);
	void DrawPolygon(const DrawCommand& cmd);
	void DrawOffset(const DrawCommand& cmd);
	void DrawEnd(const DrawCommand& cmd);
	
	
};

#endif

NAMESPACE_PARALLEL_END

#endif
