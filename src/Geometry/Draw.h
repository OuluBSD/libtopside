#ifndef _Geometry_Draw_h_
#define _Geometry_Draw_h_

NAMESPACE_TOPSIDE_BEGIN

namespace Colors {

extern vec4 Red;
extern vec4 Chocolate;
extern vec4 Yellow;
extern vec4 Lime;
extern vec4 Cyan;
extern vec4 Blue;
extern vec4 MediumPurple;
extern vec4 White;
extern vec4 DimGray;
extern vec4 Black;
extern vec4 Gray;
extern vec4 Aquamarine;
extern vec4 DarkSlateBlue;

};

class DrawGeometry : public DrawProxy {
	
	
public:
	RTTI_DECL1_(DrawGeometry, DrawProxy)
	DrawGeometry(Draw& d) {SetTarget(&d);}
	
	void DrawLine(const vec2& a, const vec2& b, int line_width, Color c);
	void DrawLine(int x0, int y0, int x1, int y1, int line_width, Color c);
	void DrawHLine(int x0, int x1, int y, int line_width, Color c);
	
};






template <class T>
T GetOffsets(const T& a, const T& b, double width) {
	double dx = b.x - a.x;
	double dy = b.y - a.y;
	double len = sqrt(dx * dx + dy * dy);
	double scale = width / (2 * len);
	return T(-scale * dy, scale * dx);
}


NAMESPACE_TOPSIDE_END

#endif
