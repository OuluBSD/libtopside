#ifndef _Geometry_Draw_h_
#define _Geometry_Draw_h_

NAMESPACE_OULU_BEGIN


class GeometryDraw : public DrawProxy {
	
	
public:
	GeometryDraw(Draw& d) {SetTarget(&d);}
	
	void DrawLine(const vec2& a, const vec2& b, int line_width, Color c);
	void DrawLine(int x0, int y0, int x1, int y1, int line_width, Color c);
	void DrawHLine(int x0, int x1, int y, int line_width, Color c);
	
};


NAMESPACE_OULU_END

#endif
