#ifndef _Local_Draw3D_h_
#define _Local_Draw3D_h_

NAMESPACE_TOPSIDE_BEGIN

class Model;


template <class T, int I> struct Vec;

typedef Vec<float, 1> vec1;
typedef Vec<float, 2> vec2;
typedef Vec<float, 3> vec3;
typedef Vec<float, 4> vec4;
typedef Vec<double, 1> dvec1;
typedef Vec<double, 2> dvec2;
typedef Vec<double, 3> dvec3;
typedef Vec<double, 4> dvec4;
typedef Vec<float, 2> axes2;
typedef Vec<float, 3> axes3;
typedef Vec<float, 3> axes2s; // stereo angle [left yaw, right yaw, pitch]
typedef Vec<float, 4> axes3s; // stereo angle [left yaw, right yaw, pitch, roll]

typedef Vec<int, 2> ivec2;
typedef Vec<int, 3> ivec3;
typedef Vec<int, 4> ivec4;


class Drawing3 {
	
};

class Painting3 {
	
};


Color DefaultInk();


class Draw3 :
	NoCopy,
	RTTIBase
{
	struct DrawingPos;
	
public:
	RTTI_DECL0(Draw3)
	
	enum {
		DOTS = 0x001,
		PRINTER = 0x004,
		NATIVE = 0x008,
		DATABANDS = 0x010,
		DRAWTEXTLINES = 0x020,
		DRAWING = 0x040,
	};

	virtual dword GetInfo() const = 0;

	virtual Volf GetPageSize() const;
	virtual void StartPage();
	virtual void EndPage();

	virtual void BeginOp() = 0;
	virtual void EndOp() = 0;
	virtual void OffsetOp(Point3f p) = 0;
	virtual bool ClipOp(const Cubf& r) = 0;
	virtual bool ClipoffOp(const Cubf& r) = 0;
	virtual bool ExcludeClipOp(const Cubf& r) = 0;
	virtual bool IntersectClipOp(const Cubf& r) = 0;
	virtual bool IsPaintingOp(const Cubf& r) const = 0;
	virtual Cubf GetPaintCubf() const;

	virtual	void DrawBoxOp(float x, float y, float z, float cx, float cy, float cz, Color color) = 0;
	virtual void SysDrawImageOp(float x, float y, float z, Sizef imgsz, const Image& img, Color color);
	virtual void SysDrawImageOp(float x, float y, float z, Sizef imgsz, const Image& img, const Rect& src, Color color);
	virtual void DrawImageOp(float x, float y, float z, float cx, float cy, float cz, const Image& img, const Rect& src, Color color);
	virtual void DrawDataOp(float x, float y, float z, float cx, float cy, float cz, const String& data, const char *id);
	virtual void DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) = 0;

	virtual void DrawPolyPolylineOp(const Point3f *vertices, int vertex_count,
	                                const int *counts, int count_count,
	                                float width, Color color, Color doxor) = 0;
	virtual void DrawPolyPolyPolygonOp(const Point3f *vertices, int vertex_count,
	                                   const int *subpolygon_counts, int scc,
	                                   const int *disjunct_polygon_counts, int dpcc,
	                                   Color color, float width, Color outline,
	                                   uint64 pattern, Color doxor) = 0;
	virtual void DrawArcOp(const Cubf& rc, Point3f start, Point3f end, float width, Color color) = 0;

	virtual void DrawEllipseOp(const Cubf& r, Color color, float pen, Color pencolor) = 0;
	virtual void DrawTextOp(float x, float y, float z, float angle, const wchar *text, Font font,
		                    Color ink, int n, const int *dx) = 0;
	virtual void DrawDrawingOp(const Cubf& target, const Drawing& w);
	virtual void DrawPaintingOp(const Cubf& target, const Painting& w);
	
	virtual Volf GetNativeDpi() const;
	virtual void BeginNative();
	virtual void EndNative();

	virtual int  GetCloffLevel() const;
	
	virtual void Escape(const String& data);
	
	virtual Color GetDefaultInk() const;
	
	virtual ~Draw3();
	

	void DrawBox(float x, float y, float z, float cx, float cy, float cz, Color color);
	void DrawBox(const Cubf& rect, Color color);

	void DrawImage(float x, float y, float z, float cx, float cy, float cz, const Image& img, const Cubf& src);
	void DrawImage(float x, float y, float z, float cx, float cy, float cz, const Image& img);
	void DrawImage(float x, float y, float z, float cx, float cy, float cz, const Image& img, const Cubf& src, Color color);
	void DrawImage(float x, float y, float z, float cx, float cy, float cz, const Image& img, Color color);

	void DrawImage(const Cubf& r, const Image& img, const Cubf& src);
	void DrawImage(const Cubf& r, const Image& img);
	void DrawImage(const Cubf& r, const Image& img, const Cubf& src, Color color);
	void DrawImage(const Cubf& r, const Image& img, Color color);

	void DrawImage(float x, float y, float z, const Image& img, const Cubf& src);
	void DrawImage(float x, float y, float z, const Image& img);
	void DrawImage(float x, float y, float z, const Image& img, const Cubf& src, Color color);
	void DrawImage(float x, float y, float z, const Image& img, Color color);

	void DrawData(float x, float y, float z, float cx, float cy, float cz, const String& data, const char *type);
	void DrawData(const Cubf& r, const String& data, const char *type);

	void DrawLine(float x1, float y1, float z1, float x2, float y2, float z2, float width = 0, Color color = DefaultInk());
	void DrawLine(Point3f p1, Point3f p2, float width = 0, Color color = DefaultInk());

	void DrawEllipse(const Cubf& r, Color color = DefaultInk(),
	                 int pen = Null, Color pencolor = DefaultInk());
	void DrawEllipse(float x, float y, float z, float cx, float cy, float cz, Color color = DefaultInk(),
		             int pen = Null, Color pencolor = DefaultInk());

	void DrawArc(const Cubf& rc, Point3f start, Point3f end, float width = 0, Color color = DefaultInk());

	void DrawPolyPolyline(const Point3f *vertices, int vertex_count,
	                      const int *counts, int count_count,
	                      float width = 0, Color color = DefaultInk(), Color doxor = Null);
	void DrawPolyPolyline(const Vector<Point3f>& vertices, const Vector<int>& counts,
		                  float width = 0, Color color = DefaultInk(), Color doxor = Null);
	void DrawPolyline(const Point3f *vertices, int count,
		              float width = 0, Color color = DefaultInk(), Color doxor = Null);
	void DrawPolyline(const Vector<Point3f>& vertices,
		              float width = 0, Color color = DefaultInk(), Color doxor = Null);

	void   DrawPolyPolyPolygon(const Point3f *vertices, int vertex_count,
		                       const int *subpolygon_counts, int subpolygon_count_count,
		                       const int *disjunct_polygon_counts, int disjunct_polygon_count_count,
		                       Color color = DefaultInk(), float width = 0, Color outline = Null,
		                       uint64 pattern = 0, Color doxor = Null);
	void   DrawPolyPolyPolygon(const Vector<Point3f>& vertices,
	                           const Vector<int>& subpolygon_counts,
	                           const Vector<int>& disjunct_polygon_counts,
	                           Color color = DefaultInk(), float width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);
	void   DrawPolyPolygon(const Point3f *vertices, int vertex_count,
	                       const int *subpolygon_counts, int subpolygon_count_count,
	                       Color color = DefaultInk(), float width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);
	void   DrawPolyPolygon(const Vector<Point3f>& vertices, const Vector<int>& subpolygon_counts,
	                       Color color = DefaultInk(), float width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);
	void   DrawPolygons(const Point3f *vertices, int vertex_count,
	                    const int *polygon_counts, int polygon_count_count,
	                    Color color = DefaultInk(), float width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);
	void   DrawPolygons(const Vector<Point3f>& vertices, const Vector<int>& polygon_counts,
	                    Color color = DefaultInk(), float width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);
	void   DrawPolygon(const Point3f *vertices, int vertex_count,
	                   Color color = DefaultInk(), float width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);
	void   DrawPolygon(const Vector<Point3f>& vertices,
	                   Color color = DefaultInk(), float width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);

	void DrawDrawing(const Cubf& r, const Drawing& iw) { DrawDrawingOp(r, iw); }
	void DrawDrawing(float x, float y, float z, float cx, float cy, float cz, const Drawing& iw);
	void DrawDrawing(float x, float y, float z, const Drawing& iw);

	void DrawPainting(const Cubf& r, const Painting& iw) { DrawPaintingOp(r, iw); }
	void DrawPainting(float x, float y, float z, float cx, float cy, float cz, const Painting& iw);
	void DrawPainting(float x, float y, float z, const Painting& iw);

	void DrawText(float x, float y, float z, int angle, const wchar *text, Font font = StdFont(),
		          Color ink = DefaultInk(), int n = -1, const int *dx = NULL);
	void DrawText(float x, float y, float z, const wchar *text, Font font = StdFont(),
		          Color ink = DefaultInk(), int n = -1, const int *dx = NULL);

	void DrawText(float x, float y, float z, const WString& text, Font font = StdFont(),
		          Color ink = DefaultInk(), const int *dx = NULL);
	void DrawText(float x, float y, float z, int angle, const WString& text, Font font = StdFont(),
		          Color ink = DefaultInk(), const int *dx = NULL);

	void DrawText(float x, float y, float z, int angle, const char *text, byte charset,
	              Font font = StdFont(), Color ink = DefaultInk(), int n = -1, const int *dx = NULL);
	void DrawText(float x, float y, float z, const char *text, byte charset, Font font = StdFont(),
		          Color ink = DefaultInk(), int n = -1, const int *dx = NULL);

	void DrawText(float x, float y, float z, int angle, const char *text,
	              Font font = StdFont(), Color ink = DefaultInk(), int n = -1, const int *dx = NULL);
	void DrawText(float x, float y, float z, const char *text, Font font = StdFont(),
		          Color ink = DefaultInk(), int n = -1, const int *dx = NULL);

	void DrawText(float x, float y, float z, const String& text, Font font = StdFont(),
		          Color ink = DefaultInk(), const int *dx = NULL);
	void DrawText(float x, float y, float z, int angle, const String& text, Font font = StdFont(),
		          Color ink = DefaultInk(), const int *dx = NULL);

	void  Begin()                                       { BeginOp(); }
	void  End()                                         { EndOp(); }
	void  Offset(Point3f p)                               { OffsetOp(p); }
	void  Offset(float x, float y, float z);
	bool  Clip(const Cubf& r)                           { return ClipOp(r); }
	bool  Clip(float x, float y, float z, float cx, float cy, float cz);
	bool  Clipoff(const Cubf& r)                        { return ClipoffOp(r); }
	bool  Clipoff(float x, float y, float z, float cx, float cy, float cz);
	bool  ExcludeClip(const Cubf& r)                    { return ExcludeClipOp(r); }
	bool  ExcludeClip(float x, float y, float z, float cx, float cy, float cz);
	bool  IntersectClip(const Cubf& r)                  { return IntersectClipOp(r); }
	bool  IntersectClip(float x, float y, float z, float cx, float cy, float cz);
	bool  IsPainting(const Cubf& r) const               { return IsPaintingOp(r); }
	bool  IsPainting(float x, float y, float z, float cx, float cy, float cz) const;
	
protected:
	Color ResolveInk(Color c) const                     { return c == DefaultInk() ? GetDefaultInk() : c; }
	
};


struct DrawProxy3 : Draw3 {
	Draw3 *ptr = 0;
	
	
	
	DrawProxy3() {}
	DrawProxy3(Draw3& d) : ptr(&d) {}
	
	void SetTarget(Draw3* d) {ptr = d;}
	
	dword GetInfo() const override;
	Volf GetPageSize() const override;
	void StartPage() override;
	void EndPage() override;
	void BeginOp() override;
	void EndOp() override;
	void OffsetOp(Point3f p) override;
	bool ClipOp(const Cubf& r) override;
	bool ClipoffOp(const Cubf& r) override;
	bool ExcludeClipOp(const Cubf& r) override;
	bool IntersectClipOp(const Cubf& r) override;
	bool IsPaintingOp(const Cubf& r) const override;
	Cubf GetPaintCubf() const override;
	void DrawBoxOp(float x, float y, float z, float cx, float cy, float cz, Color color) override;
	void SysDrawImageOp(float x, float y, float z, Sizef imgsz, const Image& img, Color color) override;
	void SysDrawImageOp(float x, float y, float z, Sizef imgsz, const Image& img, const Rect& src, Color color) override;
	void DrawImageOp(float x, float y, float z, float cx, float cy, float cz, const Image& img, const Rect& src, Color color) override;
	void DrawDataOp(float x, float y, float z, float cx, float cy, float cz, const String& data, const char *id) override;
	void DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) override;
	void DrawPolyPolylineOp(const Point3f *vertices, int vertex_count,
	                        const int *counts, int count_count,
	                        float width, Color color, Color doxor) override;
	void DrawPolyPolyPolygonOp(const Point3f *vertices, int vertex_count,
	                           const int *subpolygon_counts, int scc,
	                           const int *disjunct_polygon_counts, int dpcc,
	                           Color color, float width, Color outline,
	                           uint64 pattern, Color doxor) override;
	void DrawArcOp(const Cubf& rc, Point3f start, Point3f end, float width, Color color) override;
	void DrawEllipseOp(const Cubf& r, Color color, float pen, Color pencolor) override;
	void DrawTextOp(float x, float y, float z, float angle, const wchar *text, Font font,
		            Color ink, int n, const int *dx) override;
	void DrawDrawingOp(const Cubf& target, const Drawing& w) override;
	void DrawPaintingOp(const Cubf& target, const Painting& w) override;
	Volf GetNativeDpi() const override;
	void BeginNative() override;
	void EndNative() override;
	int  GetCloffLevel() const override;
	void Escape(const String& data) override;
	
};


class NilDraw3 : public Draw3 {
public:
	virtual dword GetInfo() const;
	virtual Volf  GetPageSize() const;
	virtual void BeginOp();
	virtual void EndOp();
	virtual void OffsetOp(Point3f p);
	virtual bool ClipOp(const Cubf& r);
	virtual bool ClipoffOp(const Cubf& r);
	virtual bool ExcludeClipOp(const Cubf& r);
	virtual bool IntersectClipOp(const Cubf& r);
	virtual bool IsPaintingOp(const Cubf& r) const;
	virtual Cubf GetPaintCubf() const;

	virtual	void DrawBoxOp(float x, float y, float z, float cx, float cy, float cz, Color color);
	virtual void DrawImageOp(float x, float y, float z, float cx, float cy, float cz, const Image& img, const Cubf& src, Color color);
	virtual void DrawDataOp(float x, float y, float z, float cx, float cy, float cz, const String& data, const char *id);
	virtual void DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color);
	virtual void DrawPolyPolylineOp(const Point3f *vertices, int vertex_count,
	                                const int *counts, int count_count,
	                                float width, Color color, Color doxor);
	virtual void DrawPolyPolyPolygonOp(const Point3f *vertices, int vertex_count,
	                                   const int *subpolygon_counts, int scc,
	                                   const int *disjunct_polygon_counts, int dpcc,
	                                   Color color, float width, Color outline,
	                                   uint64 pattern, Color doxor);
	virtual void DrawArcOp(const Cubf& rc, Point3f start, Point3f end, float width, Color color);
	virtual void DrawEllipseOp(const Cubf& r, Color color, int pen, Color pencolor);
	virtual void DrawTextOp(float x, float y, float z, int angle, const wchar *text, Font font,
		                    Color ink, int n, const int *dx);
	virtual void DrawDrawingOp(const Cubf& target, const Drawing& w);
	virtual void DrawPaintingOp(const Cubf& target, const Painting& w);
};
	


NAMESPACE_TOPSIDE_END

#endif
