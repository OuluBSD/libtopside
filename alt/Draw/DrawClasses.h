#ifndef _DrawAlt_DrawClasses_h_
#define _DrawAlt_DrawClasses_h_


NAMESPACE_UPP

class Drawing {
	
};

class Painting {
	
};


Color DefaultInk(); // { return SpecialColor(254); }


class Draw :
	NoCopy,
	RTTIBase
{
	struct DrawingPos;
	
public:
	RTTI_DECL0(Draw)
	
	virtual ~Draw() {}
	
	void DrawLine(int x1, int y1, int x2, int y2, int width = 0, Color color = DefaultInk());
	void DrawText(int x, int y, const char* text, Font font = StdFont(),
		          Color ink = DefaultInk(), const int *dx = NULL);
	void DrawText(int x, int y, const String& text, Font font = StdFont(),
		          Color ink = DefaultInk(), const int *dx = NULL);
	void DrawText(int x, int y, const WString& text, Font font = StdFont(),
		          Color ink = DefaultInk(), const int *dx = NULL);
	
	void DrawRect(int x, int y, int cx, int cy, Color color);
	void DrawRect(const Rect& rect, Color color);
	
	void DrawPolyline(const Point *vertices, int count,
		              int width = 0, Color color = DefaultInk(), Color doxor = Null);
	void DrawPolyline(const Vector<Point>& vertices,
		              int width = 0, Color color = DefaultInk(), Color doxor = Null);

	void DrawImage(int x, int y, const Image& img);
	void DrawImage(int x, int y, const Image& img, const Rect& src);
	void DrawImage(int x, int y, int cx, int cy, const Image& img);
	
	void DrawPolygon(const Vector<Point>& vertices,
	                   Color color = DefaultInk(), int width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);

	void DrawEllipse(const Rect& r, Color color = DefaultInk(),
	                 int pen = Null, Color pencolor = DefaultInk());
	void DrawEllipse(int x, int y, int cx, int cy, Color color = DefaultInk(),
		             int pen = Null, Color pencolor = DefaultInk());
	
	virtual void SetSize(Size sz) = 0;
	virtual Size GetPageSize() const = 0;
	virtual void DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) = 0;
	virtual	void DrawRectOp(int x, int y, int cx, int cy, Color color) = 0;
	virtual void DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
		                    Color ink, int n, const int *dx) = 0;
	virtual void DrawPolyPolylineOp(const Point *vertices, int vertex_count,
	                                const int *counts, int count_count,
	                                int width, Color color, Color doxor) = 0;
	virtual bool ClipOp(const Rect& r) = 0;
	virtual void EndOp() = 0;
	virtual void DrawImage(int x, int y, Image img, byte alpha) = 0;
	
	virtual void DrawTriangle(Point a, Point b, Point c, RGBA clr) {Panic("unimplemented");}
	
};



struct DrawProxy : Draw {
	Draw *ptr = 0;
	
	void SetTarget(Draw *w) { ptr = w; }
	
	
	DrawProxy() {}
	DrawProxy(Draw& d) : ptr(&d) {}
	
	void SetTarget(Draw& d) {ptr = &d;}
	
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
	void DrawTriangle(Point a, Point b, Point c, RGBA clr) override;
	
};


END_UPP_NAMESPACE


#endif
