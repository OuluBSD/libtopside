#ifndef _SharedCore_Draw_h_
#define _SharedCore_Draw_h_


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
	Vector<float> triangles;
	Vector<Point> pts;
	bool is_cached = false;
	
	String GetTypeString() const;
	String ToString() const;
	String GetQueueString() const;
	void Check() const;
	
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


END_UPP_NAMESPACE


#endif
