#ifndef _GuboCore_SDraw3_h_
#define _GuboCore_SDraw3_h_

NAMESPACE_TOPSIDE_BEGIN


class SDraw3 : public Draw3 {
	
	struct Op : Moveable<Op> {
		Cubf cur_area;
	};
	Vector<Op> ops;
		
	
	byte AtRGBA(RGBA rgba, int i);
	void DrawPixel0(byte* data, int stride, int pitch, int x, int y, Color color);
	
	bool DoOpsX(float& x);
	bool DoOpsY(float& y);
	bool DoOpsZ(float& z);
	//bool DoOpsHorz(float& x0, int& x1);
	bool DoOps(Cubf& r);
	
	
protected:
	Volf sz;
	
	Cubf cur_area;
	
public:
	RTTI_DECL1(SDraw3, Draw3)
	virtual ~SDraw3() {}
	
	void Init(const Cubf& r);
	
	void Finish();
	int GetWidth() const {return sz.cx;}
	int GetHeight() const {return sz.cy;}
	int GetDepth() const {return sz.cz;}
	
	void DrawPixel(float x, float y, float z, Color c);
	
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
	void DrawTextOp(float x, float y, float z, int angle, const wchar *text, Font font,
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
