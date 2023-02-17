#ifndef _SharedCore_Draw_h_
#define _SharedCore_Draw_h_


NAMESPACE_UPP

#if 0
#define DRAWCMD_LIST \
	DRAWCMD(NULL) \
	DRAWCMD(META_SIZE) \
	DRAWCMD(META_SIZE3) \
	\
	DRAWCMD(BEGIN) /* dummy */ \
	DRAWCMD(BIND_WINDOW) \
	DRAWCMD(UNBIND_WINDOW) \
	DRAWCMD(LINE) \
	DRAWCMD(TEXT) \
	DRAWCMD(IMAGE) \
	DRAWCMD(IMAGE_SIZED) \
	DRAWCMD(IMAGEBUFFER) \
	DRAWCMD(RECT) \
	DRAWCMD(TRIANGLES) \
	DRAWCMD(POLYLINE) \
	DRAWCMD(CLIPOFF) \
	DRAWCMD(OFFSET) \
	DRAWCMD(OFFSET_POINT) \
	DRAWCMD(END) \
	DRAWCMD(WINDOW_OFFSET) \
	DRAWCMD(WINDOW_END) \
	DRAWCMD(CUBF) \
	
#endif

#define DRAWCMD_LIST \
	DRAWCMD(NULL) \
	/*DRAWCMD(GET_INFO)*/ \
	/*DRAWCMD(GET_PAGE_SIZE)*/ \
	DRAWCMD(START_PAGE) \
	DRAWCMD(END_PAGE) \
	DRAWCMD(BEGIN_OP) \
	DRAWCMD(END_OP) \
	DRAWCMD(OFFSET_OP) \
	DRAWCMD(CLIP_OP) \
	DRAWCMD(CLIPOFF_OP) \
	DRAWCMD(EXCLUDE_CLIP_OP) \
	DRAWCMD(INTERSECT_CLIP_OP) \
	/*DRAWCMD(IS_PAINTING_OP)*/ \
	/*DRAWCMD(GET_PAINT_RECT)*/ \
	DRAWCMD(RECT_OP) \
	DRAWCMD(SYSDRAW_IMAGE_OP) \
	DRAWCMD(IMAGE_OP) \
	DRAWCMD(DATA_OP) \
	DRAWCMD(LINE_OP) \
	DRAWCMD(POLY_POLYLINE_OP) \
	DRAWCMD(POLY_POLY_POLYGON_OP) \
	DRAWCMD(ARC_OP) \
	DRAWCMD(ELLIPSE_OP) \
	DRAWCMD(TEXT_OP) \
	DRAWCMD(DRAWING_OP) \
	DRAWCMD(PAINTING_OP) \
	/*DRAWCMD(GET_NATIVE_DPI)*/ \
	DRAWCMD(BEGIN_NATIVE) \
	DRAWCMD(END_NATIVE) \
	/*DRAWCMD(GET_CLOFF_LEVEL)*/ \
	DRAWCMD(ESCAPE) \
	DRAWCMD(BIND_WINDOW) \
	DRAWCMD(UNBIND_WINDOW) \
	


enum {
	#define DRAWCMD(x) DRAW_##x,
	DRAWCMD_LIST
	#undef DRAWCMD
	
	DRAW_CMD_COUNT,
};

struct DrawCommand {
	DrawCommand *prev = NULL, *next = NULL;
	Byte type = 0;
	Point pt, pt2;
	Size sz;
	Rect r, crop;
	hash_t hash;
	uint64 pattern;
	RGBA rgba;
	Color color, outline, doxor;
	Image img;
	Font fnt;
	String txt, id;
	void* ptr;
	int width, angle;
	Vector<Point> points;
	Vector<int> ints, subpolygon_counts, disjunct_polygon_counts;
	Value value;
	bool is_cached = false;
	
	String GetTypeString() const;
	String ToString() const;
	String GetQueueString() const;
	String ColorString() const;
	void Check() const;
	
	~DrawCommand() {prev = 0; next = 0; img.Clear(); txt.Clear(); points.Clear(); ints.Clear(); subpolygon_counts.Clear(); disjunct_polygon_counts.Clear(); value = Value();}
};

class DrawCommandCache {
	Array<DrawCommand> owned;
	Vector<DrawCommand*> unused;
	
public:
	DrawCommand& CreateCommand();
	void Return(DrawCommand* cmd);
	void Clear() {unused.Clear(); owned.Clear();}
	
	static DrawCommandCache& Local() {thread_local static DrawCommandCache c; return c;}
	
};


END_UPP_NAMESPACE


#endif
