#ifndef _Local_ProgPainter_h_
#define _Local_ProgPainter_h_


NAMESPACE_TOPSIDE_BEGIN


class TriangulatePointf {

public:

	static bool Process(const Vector<Pointf>& contour, Vector<float>& result);

	static double Area(const Vector<Pointf>& contour);

	static bool InsideTriangle(double Ax, double Ay,
		double Bx, double By,
		double Cx, double Cy,
		double Px, double Py);


private:
	static bool Snip(const Vector<Pointf>& contour, int u, int v, int w, int n, int* V);

};


Pointf GetPointOffsets(const Pointf& a, const Pointf& b, double width);


class ProgPainter : public SDraw {
	DrawCommand *prev;
	DrawCommand *next;
	DrawCommand *begin;
	DrawCommand *end;
	DrawCommand *cur_begin = NULL;
	DrawCommand *cur = NULL;
	
	Vector<Point> tmp0;
	Vector<double> angles;
	Size size;
	Rect drawingclip;
	
	DrawCommand& CreateCommand();
	
	
public:
	#if IS_UPP_CORE
	RTTI_DECL0_(ProgPainter);
	#else
	RTTI_DECL1(ProgPainter, SDraw);
	#endif
	
	ProgPainter(Size sz, DrawCommand& prev, DrawCommand& begin, DrawCommand& end, DrawCommand& next);
	ProgPainter(Size sz, ProgPainter& p, DrawCommand& begin, DrawCommand& end);
	~ProgPainter() {/*Clear();*/}
	
	void Clear();
	DrawCommand* GetCurrentBegin() const;
	DrawCommand* GetBegin() const;
	DrawCommand* GetEnd() const;
	
	void Link();
	void Dump();
	
	//void Attach(Ctrl& c);
	void Attach(DrawCommand& begin, DrawCommand& end);
	void AppendPick(DrawCommand* begin, DrawCommand* end);
	
	
	// libtopside draw functions (could be deprecated probably)
	void BindWindow(hash_t h);
	void UnbindWindow();
	void WindowOffset(const Rect& r);
	void WindowEnd();
	
	
	
	
	void SetSize(Size sz);
	void DrawImage(int x, int y, Image img, byte alpha=255);
	void CtrlDrawBegin(hash_t h);
	void CtrlDrawEnd();
	
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
	Color GetDefaultInk() const override;
	void PutImage(Point p, const Image& img, const Rect& src) override;
	void PutRect(const Rect& r, Color color) override;
	
	
	
};



NAMESPACE_TOPSIDE_END


#endif
