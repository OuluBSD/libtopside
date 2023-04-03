#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


namespace Colors {

#define FLTCLR(r, g, b) r / 255.0f, g / 255.0f, b / 255.0f, 1.0f

vec4 Red			{FLTCLR(128,	  0,	  0)};
vec4 Chocolate		{FLTCLR(128,	 90,	 70)};
vec4 Yellow			{FLTCLR(255,	255,	  0)};
vec4 Lime			{FLTCLR(199,	234,	 70)};
vec4 Cyan			{FLTCLR(  0,	255,	255)};
vec4 Blue			{FLTCLR(  0,	  0,	255)};
vec4 MediumPurple	{FLTCLR(147,	112,	219)};
vec4 White			{FLTCLR(255,	255,	255)};
vec4 DimGray		{FLTCLR(105,	105,	105)};
vec4 Black			{FLTCLR(  0,	  0,	  0)};
vec4 Gray			{FLTCLR(128,	128,	128)};
vec4 Aquamarine		{FLTCLR(127,	255,	212)};
vec4 DarkSlateBlue	{FLTCLR(72,		61,		139)};

#undef FLTCLR

};

void DrawGeometry::DrawLine(const vec2& a, const vec2& b, int line_width, Color c) {
	DrawProxy::DrawLine((int)a[0], (int)a[1], (int)b[0], (int)b[1], line_width, c);
}

void DrawGeometry::DrawLine(int x0, int y0, int x1, int y1, int line_width, Color c) {
	DrawProxy::DrawLine(x0, y0, x1, y1, line_width, c);
}

void DrawGeometry::DrawHLine(int x0, int x1, int y, int line_width, Color c) {
	DrawProxy::DrawLine(x0, y, x1, y, line_width, c);
}



NAMESPACE_TOPSIDE_END
