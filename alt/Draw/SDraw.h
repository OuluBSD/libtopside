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
	Vector<Trianglef> triangles;
	Vector<Pointf> pts;
	bool is_cached = false;
	
	~DrawCommand() {img.Clear(); triangles.Clear(); pts.Clear();}
};

class DrawCommandCache {
	Array<DrawCommand> owned;
	Vector<DrawCommand*> unused;
	
public:
	DrawCommand& Get();
	void Return(DrawCommand* cmd);
	void Clear() {unused.Clear(); owned.Clear();}
};

//inline DrawCommandCache& GetDrawCommandCache() {return Single<DrawCommandCache>();}





class SDraw {
	DrawCommandCache* cache = NULL;
	DrawCommand *prev;
	DrawCommand *next;
	DrawCommand *begin;
	DrawCommand *end;
	DrawCommand *cur_begin = NULL;
	DrawCommand *cur = NULL;
	
	Vector<Pointf> tmp0, tmp1;
	Vector<double> angles;
	
	DrawCommand& GetNext();
public:
	SDraw(DrawCommand& prev, DrawCommand& begin, DrawCommand& end, DrawCommand& next) : prev(&prev), begin(&begin), end(&end), next(&next) {}
	
	void DrawLine(int x0, int y0, int x1, int y1, int line_width, RGBA c);
	void DrawImage(int x, int y, Image img, Byte alpha=255);
	void DrawRect(Rect r, RGBA clr);
	void DrawRect(int x, int y, int w, int h, RGBA clr);
	void DrawText(int x, int y, String txt, Font fnt, RGBA clr);
	void DrawPolyline(const Vector<Pointf>& pts, int line_width, RGBA c);
	void DrawPolygon(const Vector<Pointf>& pts, RGBA c);
	
	void Offset(const Rect& r);
	void End();
	
	
	void Link();
};

END_UPP_NAMESPACE


#endif
