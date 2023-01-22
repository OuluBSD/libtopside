#ifndef _Draw_Draw3Classes_h_
#define _Draw_Draw3Classes_h_


NAMESPACE_UPP

template <class T, int I> struct Vec;

typedef Vec<float, 1> vec1;
typedef Vec<float, 2> vec2;
typedef Vec<float, 3> vec3;
typedef Vec<float, 4> vec4;
typedef Vec<double, 1> dvec1;
typedef Vec<double, 2> dvec2;
typedef Vec<double, 3> dvec3;
typedef Vec<double, 4> dvec4;
typedef Vec<float, 2> axes2;
typedef Vec<float, 3> axes3;
typedef Vec<float, 3> axes2s; // stereo angle [left yaw, right yaw, pitch]
typedef Vec<float, 4> axes3s; // stereo angle [left yaw, right yaw, pitch, roll]

typedef Vec<int, 2> ivec2;
typedef Vec<int, 3> ivec3;
typedef Vec<int, 4> ivec4;


class Drawing3 {
	
};

class Painting3 {
	
};


Color DefaultInk(); // { return SpecialColor(254); }


class Draw3 :
	NoCopy,
	RTTIBase
{
	struct DrawingPos;
	
public:
	RTTI_DECL0(Draw3)
	
	virtual ~Draw3() {}
	
	/*
	void DrawLine(float x1, float y1, float z1, float x2, float y2, float z2, float width = 0, Color color = DefaultInk());
	void DrawText(float x, float y, float z, const char* text, Font font = StdFont(),
		          Color ink = DefaultInk(), const float *dx = NULL);
	void DrawText(float x, float y, float z, const String& text, Font font = StdFont(),
		          Color ink = DefaultInk(), const float *dx = NULL);
	void DrawText(float x, float y, float z, const WString& text, Font font = StdFont(),
		          Color ink = DefaultInk(), const float *dx = NULL);
	
	void DrawCuboid(float x, float y, float z, float cx, float cy, float zy, Color color);
	void DrawCuboid(const Cuboid& rect, Color color);
	
	void DrawPolyline(const Pofloat *vertices, float count,
		              float width = 0, Color color = DefaultInk(), Color doxor = Null);
	void DrawPolyline(const Vector<Point>& vertices,
		              float width = 0, Color color = DefaultInk(), Color doxor = Null);

	void DrawImage(float x, float y, float z, const Image& img);
	void DrawImage(float x, float y, float z, const Image& img, const Cuboid& src);
	void DrawImage(float x, float y, float z, float cx, float cy, float zy, const Image& img);
	
	void DrawPolygon(const Vector<Point>& vertices,
	                 Color color = DefaultInk(), float width = 0, Color outline = Null, uint64 pattern = 0, Color doxor = Null);

	void DrawEllipse(const Cuboid& r, Color color = DefaultInk(),
	                 float pen = Null, Color pencolor = DefaultInk());
	void DrawEllipse(float x, float y, float z, float cx, float cy, float zy, Color color = DefaultInk(),
		             float pen = Null, Color pencolor = DefaultInk());
	*/
	
	virtual void CtrlDrawBegin(hash_t) {}
	virtual void CtrlDrawEnd() {}
	
	virtual void SetSize(Volf sz) = 0;
	virtual Volf GetPageSize() const = 0;
	virtual void DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) = 0;
	virtual	void DrawCuboidOp(float x, float y, float z, float cx, float cy, float zy, Color color) = 0;
	virtual void DrawTextOp(float x, float y, float z, float angle, const wchar *text, Font font,
		                    Color ink, int n, const float *dx) = 0;
	virtual void DrawPolyPolylineOp(const vec3 *vertices, int vertex_count,
	                                const int *counts, int count_count,
	                                float width, Color color, Color doxor) = 0;
	virtual bool ClipOp(const Cubf& c) = 0;
	virtual void EndOp() = 0;
	virtual void DrawImage(float x, float y, float z, Image img, byte alpha) = 0;
	
	virtual void DrawTriangle(const vec3& a, const vec3& b, const vec3& c, RGBA clr) {Panic("unimplemented");}
	
};



struct DrawProxy3 : Draw3 {
	Draw3 *ptr = 0;
	
	void SetTarget(Draw3 *w) { ptr = w; }
	
	
	DrawProxy3() {}
	DrawProxy3(Draw3& d) : ptr(&d) {}
	
	void SetTarget(Draw3& d) {ptr = &d;}
	
	void SetSize(Volf sz) override;
	Volf GetPageSize() const override;
	void DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) override;
	void DrawCuboidOp(float x, float y, float z, float cx, float cy, float cz, Color color) override;
	void DrawTextOp(float x, float y, float z, float angle, const wchar *text, Font font,
		                    Color ink, int n, const float *dx) override;
	void DrawPolyPolylineOp(const vec3 *vertices, int vertex_count,
	                        const int *counts, int count_count,
	                        float width, Color color, Color doxor) override;
	
	bool ClipOp(const Cubf& r) override;
	void EndOp() override;
	void DrawImage(float x, float y, float z, Image img, byte alpha=255) override;
	void DrawTriangle(const vec3& a, const vec3& b, const vec3& c, RGBA clr) override;
	
};


END_UPP_NAMESPACE

#endif
