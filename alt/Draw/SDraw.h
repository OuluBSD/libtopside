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
	
	static DrawCommandCache& Local() {thread_local static DrawCommandCache c; return c;}
	
};






class SDraw {
	
public:
	virtual ~SDraw() {}
	
};

struct SImageDraw : Draw {
	
public:
	SImageDraw() {}
	SImageDraw(Size sz) {}
	SImageDraw(int cx, int cy) {}
};

END_UPP_NAMESPACE


#endif
