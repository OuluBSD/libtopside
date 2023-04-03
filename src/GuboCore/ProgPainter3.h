#ifndef _GuboCore_ProgPainter3_h_
#define _GuboCore_ProgPainter3_h_

NAMESPACE_TOPSIDE_BEGIN


class ProgPainter3 : public SDraw3 {
	DrawCommand3 *prev;
	DrawCommand3 *next;
	DrawCommand3 *begin;
	DrawCommand3 *end;
	DrawCommand3 *cur_begin = NULL;
	DrawCommand3 *cur = NULL;
	
	Vector<Point3f> tmp0;
	Vector<double> angles;
	Volf size;
	Cubf drawingclip;
	hash_t uniq = 0;
	
	DrawCommand3& CreateCommand();
	
	
public:
	RTTI_DECL1(ProgPainter3, SDraw3);
	
	ProgPainter3(void* hash, Volf sz, DrawCommand3& prev, DrawCommand3& begin, DrawCommand3& end, DrawCommand3& next);
	ProgPainter3(void* hash, Volf sz, ProgPainter3& p, DrawCommand3& begin, DrawCommand3& end);
	~ProgPainter3() {/*Clear();*/}
	
	void Clear();
	DrawCommand3* GetCurrentBegin() const;
	DrawCommand3* GetBegin() const;
	DrawCommand3* GetEnd() const;
	
	void Link();
	void Dump();
	
	void Attach(DrawCommand3& begin, DrawCommand3& end);
	void AppendPick(DrawCommand3* begin, DrawCommand3* end);
		
	// libtopside draw functions (could be deprecated probably)
	void BindWindow(hash_t h);
	void UnbindWindow();
	void WindowOffset(const Cubf& r);
	void WindowEnd();
	
	void SetSize(Volf sz);
	void DrawImage(int x, int y, Image img, byte alpha=255);
	void CtrlDrawBegin(hash_t h);
	void CtrlDrawEnd();
	
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


NAMESPACE_TOPSIDE_END

#endif
