#ifndef _IGraphics_ProgDraw_h_
#define _IGraphics_ProgDraw_h_



NAMESPACE_PARALLEL_BEGIN

class ProgDraw : public Draw {
	One<ProgPainter> d;
	
	Size GetFrameSize() const;
	
public:
	DrawCommand cmd_screen_begin, cmd_screen_end;
	DrawCommand render_begin, render_end;
	
	
	void LinkRender();
public:
	RTTI_DECL1(ProgDraw, Draw)
	ProgDraw();
	ProgDraw(Size sz);
	ProgDraw(int w, int h);
	
	void Create(Size sz);
	void Create(Size sz, DrawCommand& sub_begin, DrawCommand& sub_end);
	void Clear();
	void Finish();
	void DetachTo(ProgPainter& pp);
	
	operator Image() const;
	
	
	void SetSize(Size sz) override;
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
	void DrawImage(int x, int y, Image img, byte alpha=255) override;
	Draw& Alpha();
	
	ProgPainter& GetProgPainter();
	
	String Dump() const;
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

class ProgImage {
	DrawProg draw;
	
public:
	ProgImage();
	void Paint(DrawCommand& c, ImageDraw& id);
	
};


NAMESPACE_PARALLEL_END

#endif
