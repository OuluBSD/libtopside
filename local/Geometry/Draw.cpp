#include "Geometry.h"

NAMESPACE_OULU_BEGIN


void GeometryDraw::DrawLine(const vec2& a, const vec2& b, int line_width, Color c) {
	DrawProxy::DrawLine(a[0], a[1], b[0], b[1], line_width, c);
}

void GeometryDraw::DrawLine(int x0, int y0, int x1, int y1, int line_width, Color c) {
	DrawProxy::DrawLine(x0, y0, x1, y1, line_width, c);
}

void GeometryDraw::DrawHLine(int x0, int x1, int y, int line_width, Color c) {
	DrawProxy::DrawLine(x0, y, x1, y, line_width, c);
}

NAMESPACE_OULU_END
