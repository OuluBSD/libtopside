#include "GuboCore.h"

NAMESPACE_TOPSIDE_BEGIN



void ProgDraw3::SetSize(Volf sz) {
	TODO
}

Volf ProgDraw3::GetPageSize() const {
	TODO
}

void ProgDraw3::DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) {
	TODO
}

void ProgDraw3::DrawCuboidOp(float x, float y, float z, float cx, float cy, float cz, Color color) {
	TODO
}

void ProgDraw3::DrawTextOp(float x, float y, float z, float angle, const wchar *text, Font font,
						Color ink, int n, const float *dx) {
	TODO
}

void ProgDraw3::DrawPolyPolylineOp(const vec3 *vertices, int vertex_count,
						const int *counts, int count_count,
						float width, Color color, Color doxor) {
	TODO
}


bool ProgDraw3::ClipOp(const Cubf& r) {
	TODO
}

void ProgDraw3::EndOp() {
	TODO
}

void ProgDraw3::DrawImage(float x, float y, float z, Image img, byte alpha) {
	TODO
}

void ProgDraw3::DrawTriangle(const vec3& a, const vec3& b, const vec3& c, RGBA clr) {
	TODO
}




NAMESPACE_TOPSIDE_END
