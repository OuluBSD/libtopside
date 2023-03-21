#ifndef _GuboCore_DrawCommand_h_
#define _GuboCore_DrawCommand_h_

NAMESPACE_TOPSIDE_BEGIN


#define DRAWCMD3_LIST \
	DRAWCMD3(NULL) \
	/*DRAWCMD3(GET_INFO)*/ \
	/*DRAWCMD3(GET_PAGE_SIZE)*/ \
	DRAWCMD3(START_PAGE) \
	DRAWCMD3(END_PAGE) \
	DRAWCMD3(BEGIN_OP) \
	DRAWCMD3(END_OP) \
	DRAWCMD3(OFFSET_OP) \
	DRAWCMD3(CLIP_OP) \
	DRAWCMD3(CLIPOFF_OP) \
	DRAWCMD3(EXCLUDE_CLIP_OP) \
	DRAWCMD3(INTERSECT_CLIP_OP) \
	/*DRAWCMD3(IS_PAINTING_OP)*/ \
	/*DRAWCMD3(GET_PAINT_RECT)*/ \
	DRAWCMD3(RECT_OP) \
	DRAWCMD3(SYSDRAW_IMAGE_OP) \
	DRAWCMD3(IMAGE_OP) \
	DRAWCMD3(DATA_OP) \
	DRAWCMD3(LINE_OP) \
	DRAWCMD3(POLY_POLYLINE_OP) \
	DRAWCMD3(POLY_POLY_POLYGON_OP) \
	DRAWCMD3(ARC_OP) \
	DRAWCMD3(ELLIPSE_OP) \
	DRAWCMD3(TEXT_OP) \
	DRAWCMD3(DRAWING_OP) \
	DRAWCMD3(PAINTING_OP) \
	/*DRAWCMD3(GET_NATIVE_DPI)*/ \
	DRAWCMD3(BEGIN_NATIVE) \
	DRAWCMD3(END_NATIVE) \
	/*DRAWCMD3(GET_CLOFF_LEVEL)*/ \
	DRAWCMD3(ESCAPE) \
	DRAWCMD3(BIND_WINDOW) \
	DRAWCMD3(UNBIND_WINDOW) \
	DRAWCMD3(SET_SIZE) \
	


typedef enum {
	#define DRAWCMD3(x) DRAW3_##x,
	DRAWCMD3_LIST
	#undef DRAWCMD3
	
	DRAW3_CMD_COUNT,
} DrawCmd3Type;


struct DrawCommand3 {
	DrawCommand3 *prev = NULL, *next = NULL;
	DrawCmd3Type type = DRAW3_NULL;
	Point3f pt, pt2;
	Volf sz;
	Cubf r, crop;
	Rect rect;
	hash_t hash;
	uint64 pattern;
	RGBA rgba;
	Color color, outline, doxor;
	Image img;
	Font fnt;
	String txt, id;
	WString wtxt;
	void* ptr;
	int width, angle;
	Vector<Point3f> points;
	Vector<int> ints, subpolygon_counts, disjunct_polygon_counts;
	Value value;
	bool is_cached = false;
	
	String GetTypeString() const;
	String ToString() const;
	String GetQueueString() const;
	String ColorString() const;
	void Check() const;
	
	~DrawCommand3() {prev = 0; next = 0; img.Clear(); txt.Clear(); wtxt.Clear(); points.Clear(); ints.Clear(); subpolygon_counts.Clear(); disjunct_polygon_counts.Clear(); value = Value();}
	
};

class DrawCommand3Cache {
	Array<DrawCommand3> owned;
	Vector<DrawCommand3*> unused;
	
public:
	DrawCommand3& CreateCommand();
	void Return(DrawCommand3* cmd);
	void Clear() {unused.Clear(); owned.Clear();}
	
	static DrawCommand3Cache& Local() {thread_local static DrawCommand3Cache c; return c;}
	
};

NAMESPACE_TOPSIDE_END

#endif
