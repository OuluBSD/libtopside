#ifndef _DrawAlt_SDraw_h_
#define _DrawAlt_SDraw_h_


NAMESPACE_UPP


class SDraw : public Draw {
	
	struct Op : Moveable<Op> {
		Rect cur_area;
	};
	Vector<Op> ops;
		
	
	byte AtRGBA(RGBA rgba, int i);
	void DrawPixel0(byte* data, int stride, int pitch, int x, int y, Color color);
	
	bool DoOpsX(int& x);
	bool DoOpsY(int& y);
	bool DoOpsHorz(int& x0, int& x1);
	bool DoOps(Rect& r);
	
	
protected:
	Size sz;
	byte* pixels = 0;
	int pitch = 0;
	int stride = 0;
	
	Rect cur_area;
	
public:
	RTTI_DECL1(SDraw, Draw)
	virtual ~SDraw() {}
	
	void Init(const Rect& r);
	
	void Finish();
	int GetWidth() const {return sz.cx;}
	int GetHeight() const {return sz.cy;}
	int GetPitch() const {return pitch;}
	int GetStride() const {return stride;}
	int GetLength() const {return sz.cy * pitch;}
	
	byte* GetIterator(int x, int y);
	void Zero();
	void SwapRG();
	
	void DrawPixel(int x, int y, RGBA color);
	void DrawPixel(int x, int y, Color color);
	void DrawHLine(int x0, int x1, int y, Color color);
	void DrawLine(int x0, int y0, int x1, int y1, Color color);
	
	operator Image() {return GetImage();}
	Image GetImage();
	
	virtual void PutImage(Point p, const Image& img, const Rect& src) = 0;
	virtual void PutRect(const Rect& r, Color color) = 0;
	
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
	
};

class SImageDraw : public SDraw {
	Vector<byte> data;
	
public:
	RTTI_DECL1(SImageDraw, SDraw)
	SImageDraw() {}
	SImageDraw(Size sz) {Create(sz);}
	SImageDraw(Size sz, int stride) {Create(sz, stride);}
	SImageDraw(int cx, int cy) {Create(Size(cx,cy));}
	
	void Create(Size sz);
	void Create(Size sz, int stride);
	
	Vector<byte>& Data() {return data;}
	const Vector<byte>& GetData() const{return data;}
	
	void PutImage(Point p, const Image& img, const Rect& src) override {TODO}
	void PutRect(const Rect& r, Color color) override {TODO}
	
	SImageDraw& Alpha();
	
};

END_UPP_NAMESPACE


#endif
