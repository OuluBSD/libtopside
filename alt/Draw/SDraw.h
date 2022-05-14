#ifndef _DrawAlt_SDraw_h_
#define _DrawAlt_SDraw_h_


NAMESPACE_UPP



enum {
	DRAW_NULL,
	DRAW_LINE,
	DRAW_IMAGE,
	DRAW_RECT,
	DRAW_TRIANGLES,
	DRAW_POLYLINE,
	DRAW_OFFSET,
	DRAW_END,
	
	DRAW_CMD_COUNT,
};

struct DrawCommand {
	DrawCommand *prev = NULL, *next = NULL;
	Byte type = 0;
	int i[5];
	RGBA clr;
	Image img;
	Vector<Trif> triangles;
	Vector<Point> pts;
	bool is_cached = false;
	
	String GetTypeString() const;
	String ToString() const;
	String GetQueueString() const;
	~DrawCommand() {img.Clear(); triangles.Clear(); pts.Clear();}
};

class DrawCommandCache {
	Array<DrawCommand> owned;
	Vector<DrawCommand*> unused;
	
public:
	DrawCommand& Get();
	void Return(DrawCommand* cmd);
	void Clear() {unused.Clear(); owned.Clear();}
	
	static DrawCommandCache& Local() {thread_local static DrawCommandCache c; return c;}
	
};



class ProgPainter : public Draw {
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
	~ProgPainter() {/*Clear();*/}
	
	void Clear();
	
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
	
	
	
	void DrawLine(int x0, int y0, int x1, int y1, int line_width, RGBA c);
	void DrawImage(int x, int y, Image img, Byte alpha=255);
	void DrawRect(Rect r, RGBA clr);
	void DrawRect(int x, int y, int w, int h, RGBA clr);
	void DrawText(int x, int y, String txt, Font fnt, RGBA clr);
	void DrawPolyline(const Vector<Point>& pts, int line_width, RGBA c);
	void DrawPolygon(const Vector<Point>& pts, RGBA c);
	
	void Offset(const Rect& r);
	void End();
	
	
	void Link();
	
	//void Attach(Ctrl& c);
	void Attach(DrawCommand& begin, DrawCommand& end);
	
};




class SDraw {
	
public:
	virtual ~SDraw() {}
	
};

struct SImageDraw : Draw {
	Size sz;
	int pitch = 0;
	int stride = 0;
	Vector<byte> pixels;
	
	byte AtRGBA(RGBA rgba, int i);
	void DrawPixel0(byte* data, int stride, int pitch, int x, int y, Color color);
	
public:
	SImageDraw() {}
	SImageDraw(Size sz) : sz(0,0) {Create(sz);}
	SImageDraw(int cx, int cy) : sz(0,0) {Create(Size(cx,cy));}
	
	void Create(Size sz);
	void Create(Size sz, int stride);
	void Finish();
	int GetWidth() const {return sz.cx;}
	int GetHeight() const {return sz.cy;}
	int GetPitch() const {return pitch;}
	int GetStride() const {return stride;}
	
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
	
	Vector<byte>& Data() {return pixels;}
	
	byte* GetIterator(int x, int y);
	void Zero();
	
	void DrawPixel(int x, int y, RGBA color);
	void DrawPixel(int x, int y, Color color);
	void DrawHLine(int x0, int x1, int y, Color color);
	void DrawLine(int x0, int y0, int x1, int y1, Color color);
	
};

END_UPP_NAMESPACE


#endif
