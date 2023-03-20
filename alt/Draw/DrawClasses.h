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
	
public:
	// U++ compatible section
	
	enum {
		DOTS = 0x001,
		PRINTER = 0x004,
		NATIVE = 0x008,
		DATABANDS = 0x010,
		DRAWTEXTLINES = 0x020,
		DRAWING = 0x040,
	};

	virtual dword GetInfo() const = 0;

	virtual Size GetPageSize() const;
	virtual void StartPage();
	virtual void EndPage();

	virtual void BeginOp() = 0;
	virtual void EndOp() = 0;
	virtual void OffsetOp(Point p) = 0;
	virtual bool ClipOp(const Rect& r) = 0;
	virtual bool ClipoffOp(const Rect& r) = 0;
	virtual bool ExcludeClipOp(const Rect& r) = 0;
	virtual bool IntersectClipOp(const Rect& r) = 0;
	virtual bool IsPaintingOp(const Rect& r) const = 0;
	virtual Rect GetPaintRect() const;

	virtual	void DrawRectOp(int x, int y, int cx, int cy, Color color) = 0;
	virtual void SysDrawImageOp(int x, int y, const Image& img, Color color);
	virtual void SysDrawImageOp(int x, int y, const Image& img, const Rect& src, Color color);
	virtual void DrawImageOp(int x, int y, int cx, int cy, const Image& img, const Rect& src, Color color);
	virtual void DrawDataOp(int x, int y, int cx, int cy, const String& data, const char *id);
	virtual void DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) = 0;

	virtual void DrawPolyPolylineOp(const Point *vertices, int vertex_count,
	                                const int *counts, int count_count,
	                                int width, Color color, Color doxor) = 0;
	virtual void DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count,
	                                   const int *subpolygon_counts, int scc,
	                                   const int *disjunct_polygon_counts, int dpcc,
	                                   Color color, int width, Color outline,
	                                   uint64 pattern, Color doxor) = 0;
	virtual void DrawArcOp(const Rect& rc, Point start, Point end, int width, Color color) = 0;

	virtual void DrawEllipseOp(const Rect& r, Color color, int pen, Color pencolor) = 0;
	virtual void DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
		                    Color ink, int n, const int *dx) = 0;
	virtual void DrawDrawingOp(const Rect& target, const Drawing& w);
	virtual void DrawPaintingOp(const Rect& target, const Painting& w);
	
	virtual Size GetNativeDpi() const;
	virtual void BeginNative();
	virtual void EndNative();

	virtual int  GetCloffLevel() const;
	
	virtual void Escape(const String& data);
	
	virtual Color GetDefaultInk() const;
	
	virtual ~Draw();
	

	void DrawRect(int x, int y, int cx, int cy, Color color);
	void DrawRect(const Rect& rect, Color color);

	void DrawImage(int x, int y, int cx, int cy, const Image& img, const Rect& src);
	void DrawImage(int x, int y, int cx, int cy, const Image& img);
	void DrawImage(int x, int y, int cx, int cy, const Image& img, const Rect& src, Color color);
	void DrawImage(int x, int y, int cx, int cy, const Image& img, Color color);

	void DrawImage(const Rect& r, const Image& img, const Rect& src);
	void DrawImage(const Rect& r, const Image& img);
	void DrawImage(const Rect& r, const Image& img, const Rect& src, Color color);
	void DrawImage(const Rect& r, const Image& img, Color color);

	void DrawImage(int x, int y, const Image& img, const Rect& src);
	void DrawImage(int x, int y, const Image& img);
	void DrawImage(int x, int y, const Image& img, const Rect& src, Color color);
	void DrawImage(int x, int y, const Image& img, Color color);

	void DrawData(int x, int y, int cx, int cy, const String& data, const char *type);
	void DrawData(const Rect& r, const String& data, const char *type);

	void DrawLine(int x1, int y1, int x2, int y2, int width = 0, Color color = DefaultInk());
	void DrawLine(Point p1, Point p2, int width = 0, Color color = DefaultInk());

	void DrawEllipse(const Rect& r, Color color = DefaultInk(),
	                 int pen = Null, Color pencolor = DefaultInk());
	void DrawEllipse(int x, int y, int cx, int cy, Color color = DefaultInk(),
		             int pen = Null, Color pencolor = DefaultInk());

	void DrawArc(const Rect& rc, Point start, Point end, int width = 0, Color color = DefaultInk());

	void DrawPolyPolyline(const Point *vertices, int vertex_count,
	                      const int *counts, int count_count,
	                      int width = 0, Color color = DefaultInk(), Color doxor = Null);
	void DrawPolyPolyline(const Vector<Point>& vertices, const Vector<int>& counts,
		                  int width = 0, Color color = DefaultInk(), Color doxor = Null);
	void DrawPolyline(const Point *vertices, int count,
		              int width = 0, Color color = DefaultInk(), Color doxor = Null);
	void DrawPolyline(const Vector<Point>& vertices,
		              int width = 0, Color color = DefaultInk(), Color doxor = Null);

	void   DrawPolyPolyPolygon(const Point *vertices, int vertex_count,
		                       const int *subpolygon_counts, int subpolygon_count_count,
		                       const int *disjunct_polygon_counts, int disjunct_polygon_count_count,
		                       Color color = DefaultInk(), int width = 0, Color outline = Null,
		                       uint64 pattern = 0, Color doxor = Null);
	void   DrawPolyPolyPolygon(const Vector<Point>& vertices,
	                           const Vector<int>& subpolygon_counts,
	                           const Vector<int>& disjunct_polygon_counts,
	                           Color color = DefaultInk(), int width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);
	void   DrawPolyPolygon(const Point *vertices, int vertex_count,
	                       const int *subpolygon_counts, int subpolygon_count_count,
	                       Color color = DefaultInk(), int width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);
	void   DrawPolyPolygon(const Vector<Point>& vertices, const Vector<int>& subpolygon_counts,
	                       Color color = DefaultInk(), int width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);
	void   DrawPolygons(const Point *vertices, int vertex_count,
	                    const int *polygon_counts, int polygon_count_count,
	                    Color color = DefaultInk(), int width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);
	void   DrawPolygons(const Vector<Point>& vertices, const Vector<int>& polygon_counts,
	                    Color color = DefaultInk(), int width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);
	void   DrawPolygon(const Point *vertices, int vertex_count,
	                   Color color = DefaultInk(), int width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);
	void   DrawPolygon(const Vector<Point>& vertices,
	                   Color color = DefaultInk(), int width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);

	void DrawDrawing(const Rect& r, const Drawing& iw) { DrawDrawingOp(r, iw); }
	void DrawDrawing(int x, int y, int cx, int cy, const Drawing& iw);
	void DrawDrawing(int x, int y, const Drawing& iw);

	void DrawPainting(const Rect& r, const Painting& iw) { DrawPaintingOp(r, iw); }
	void DrawPainting(int x, int y, int cx, int cy, const Painting& iw);
	void DrawPainting(int x, int y, const Painting& iw);

	void DrawText(int x, int y, int angle, const wchar *text, Font font = StdFont(),
		          Color ink = DefaultInk(), int n = -1, const int *dx = NULL);
	void DrawText(int x, int y, const wchar *text, Font font = StdFont(),
		          Color ink = DefaultInk(), int n = -1, const int *dx = NULL);

	void DrawText(int x, int y, const WString& text, Font font = StdFont(),
		          Color ink = DefaultInk(), const int *dx = NULL);
	void DrawText(int x, int y, int angle, const WString& text, Font font = StdFont(),
		          Color ink = DefaultInk(), const int *dx = NULL);

	void DrawText(int x, int y, int angle, const char *text, byte charset,
	              Font font = StdFont(), Color ink = DefaultInk(), int n = -1, const int *dx = NULL);
	void DrawText(int x, int y, const char *text, byte charset, Font font = StdFont(),
		          Color ink = DefaultInk(), int n = -1, const int *dx = NULL);

	void DrawText(int x, int y, int angle, const char *text,
	              Font font = StdFont(), Color ink = DefaultInk(), int n = -1, const int *dx = NULL);
	void DrawText(int x, int y, const char *text, Font font = StdFont(),
		          Color ink = DefaultInk(), int n = -1, const int *dx = NULL);

	void DrawText(int x, int y, const String& text, Font font = StdFont(),
		          Color ink = DefaultInk(), const int *dx = NULL);
	void DrawText(int x, int y, int angle, const String& text, Font font = StdFont(),
		          Color ink = DefaultInk(), const int *dx = NULL);

	void  Begin()                                       { BeginOp(); }
	void  End()                                         { EndOp(); }
	void  Offset(Point p)                               { OffsetOp(p); }
	void  Offset(int x, int y);
	bool  Clip(const Rect& r)                           { return ClipOp(r); }
	bool  Clip(int x, int y, int cx, int cy);
	bool  Clipoff(const Rect& r)                        { return ClipoffOp(r); }
	bool  Clipoff(int x, int y, int cx, int cy);
	bool  ExcludeClip(const Rect& r)                    { return ExcludeClipOp(r); }
	bool  ExcludeClip(int x, int y, int cx, int cy);
	bool  IntersectClip(const Rect& r)                  { return IntersectClipOp(r); }
	bool  IntersectClip(int x, int y, int cx, int cy);
	bool  IsPainting(const Rect& r) const               { return IsPaintingOp(r); }
	bool  IsPainting(int x, int y, int cx, int cy) const;

protected:
	Color ResolveInk(Color c) const                     { return c == DefaultInk() ? GetDefaultInk() : c; }
	
};



struct DrawProxy : Draw {
	Draw *ptr = 0;
	
	
	
	DrawProxy() {}
	DrawProxy(Draw& d) : ptr(&d) {}
	
	void SetTarget(Draw* d) {ptr = d;}
	Draw* GetTarget() const {return ptr;}
	
	dword GetInfo() const override;
	Size GetPageSize() const override;
	void StartPage() override;
	void EndPage() override;
	void BeginOp() override;
	void EndOp() override;
	void OffsetOp(Point p) override;
	bool ClipOp(const Rect& r) override;
	bool ClipoffOp(const Rect& r) override;
	bool ExcludeClipOp(const Rect& r) override;
	bool IntersectClipOp(const Rect& r) override;
	bool IsPaintingOp(const Rect& r) const override;
	Rect GetPaintRect() const override;
	void DrawRectOp(int x, int y, int cx, int cy, Color color) override;
	void SysDrawImageOp(int x, int y, const Image& img, Color color) override;
	void SysDrawImageOp(int x, int y, const Image& img, const Rect& src, Color color) override;
	void DrawImageOp(int x, int y, int cx, int cy, const Image& img, const Rect& src, Color color) override;
	void DrawDataOp(int x, int y, int cx, int cy, const String& data, const char *id) override;
	void DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) override;
	void DrawPolyPolylineOp(const Point *vertices, int vertex_count,
	                        const int *counts, int count_count,
	                        int width, Color color, Color doxor) override;
	void DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count,
	                           const int *subpolygon_counts, int scc,
	                           const int *disjunct_polygon_counts, int dpcc,
	                           Color color, int width, Color outline,
	                           uint64 pattern, Color doxor) override;
	void DrawArcOp(const Rect& rc, Point start, Point end, int width, Color color) override;
	void DrawEllipseOp(const Rect& r, Color color, int pen, Color pencolor) override;
	void DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
		            Color ink, int n, const int *dx) override;
	void DrawDrawingOp(const Rect& target, const Drawing& w) override;
	void DrawPaintingOp(const Rect& target, const Painting& w) override;
	Size GetNativeDpi() const override;
	void BeginNative() override;
	void EndNative() override;
	int  GetCloffLevel() const override;
	void Escape(const String& data) override;
	
};


class NilDraw : public Draw {
public:
	virtual dword GetInfo() const;
	virtual Size  GetPageSize() const;
	virtual void BeginOp();
	virtual void EndOp();
	virtual void OffsetOp(Point p);
	virtual bool ClipOp(const Rect& r);
	virtual bool ClipoffOp(const Rect& r);
	virtual bool ExcludeClipOp(const Rect& r);
	virtual bool IntersectClipOp(const Rect& r);
	virtual bool IsPaintingOp(const Rect& r) const;
	virtual Rect GetPaintRect() const;

	virtual	void DrawRectOp(int x, int y, int cx, int cy, Color color);
	virtual void DrawImageOp(int x, int y, int cx, int cy, const Image& img, const Rect& src, Color color);
	virtual void DrawDataOp(int x, int y, int cx, int cy, const String& data, const char *id);
	virtual void DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color);
	virtual void DrawPolyPolylineOp(const Point *vertices, int vertex_count,
	                                const int *counts, int count_count,
	                                int width, Color color, Color doxor);
	virtual void DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count,
	                                   const int *subpolygon_counts, int scc,
	                                   const int *disjunct_polygon_counts, int dpcc,
	                                   Color color, int width, Color outline,
	                                   uint64 pattern, Color doxor);
	virtual void DrawArcOp(const Rect& rc, Point start, Point end, int width, Color color);
	virtual void DrawEllipseOp(const Rect& r, Color color, int pen, Color pencolor);
	virtual void DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
		                    Color ink, int n, const int *dx);
	virtual void DrawDrawingOp(const Rect& target, const Drawing& w);
	virtual void DrawPaintingOp(const Rect& target, const Painting& w);
};


inline bool IsDarkTheme() {return false;}
inline Color AdjustIfDark(Color c)   { return IsDarkTheme() ? DarkThemeCached(c) : c; }

Color SBlack();
Color SGray();
Color SLtGray();
Color SWhiteGray();
Color SWhite();
Color SRed();
Color SGreen();
Color SBrown();
Color SBlue();
Color SMagenta();
Color SCyan();
Color SYellow();
Color SLtRed();
Color SLtGreen();
Color SLtYellow();
Color SLtBlue();
Color SLtMagenta();
Color SLtCyan();

Color SColorPaper();
Color SColorText();
Color SColorFace();
Color SColorHighlight();
Color SColorHighlightText();
Color SColorMenu();
Color SColorMenuText();
Color SColorInfo();
Color SColorInfoText();
Color SColorMark();
Color SColorMenuMark();
Color SColorDisabled();
Color SColorLight();
Color SColorLabel();
Color SColorShadow();

Color SColorLtFace();
Color SColorDkShadow();


void DrawTextEllipsis(Draw& w, int x, int y, int cx, const char *text, const char *ellipsis,
				      Font font = StdFont(), Color ink = SColorText(), int n = -1);
void DrawTextEllipsis(Draw& w, int x, int y, int cx, const wchar *text, const char *ellipsis,
				      Font font = StdFont(), Color ink = SColorText(), int n = -1);


inline Color InvertColor() { return Color::Special(255); } // Special color that with DrawRect actually inverts the rectangle
inline Color DefaultInk() { return Color::Special(254); } // SColorText on screen, Black on other outputs


void Subtract(Vector<Rect>& rr, const Rect& sub);


END_UPP_NAMESPACE


#endif
