#ifndef _Local_ProgDraw_h_
#define _Local_ProgDraw_h_

NAMESPACE_TOPSIDE_BEGIN


class ProgDraw : public Draw2 {
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
	
	
	void SetDimensions(const Size& sz);
	Size GetPageDimensions();
	
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
	
	bool ClipoffOp(const Rect& r) override;
	dword GetInfo() const override;
	void BeginOp() override;
	void OffsetOp(Point p) override;
	bool ExcludeClipOp(const Rect& r) override;
	bool IntersectClipOp(const Rect& r) override;
	bool IsPaintingOp(const Rect& r) const override;
	void DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count,
	                                   const int *subpolygon_counts, int scc,
	                                   const int *disjunct_polygon_counts, int dpcc,
	                                   Color color, int width, Color outline,
	                                   uint64 pattern, Color doxor) override;
	void DrawArcOp(const Rect& rc, Point start, Point end, int width, Color color) override;
	void DrawEllipseOp(const Rect& r, Color color, int pen, Color pencolor) override;
	
	Draw& Alpha();
	
	ProgPainter& GetPainter();
	
	String Dump() const;
};


NAMESPACE_TOPSIDE_END

#endif
