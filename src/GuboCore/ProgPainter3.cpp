#include "GuboCore.h"

NAMESPACE_TOPSIDE_BEGIN

ProgPainter3::ProgPainter3(Volf sz, DrawCommand& prev, DrawCommand& begin, DrawCommand& end, DrawCommand& next) {
	TODO
}

ProgPainter3::ProgPainter3(Volf sz, ProgPainter& p, DrawCommand& begin, DrawCommand& end) {
	TODO
}

void ProgPainter3::Clear() {
	TODO
}

DrawCommand* ProgPainter3::GetCurrentBegin() const {
	TODO
}

DrawCommand* ProgPainter3::GetBegin() const {
	TODO
}

DrawCommand* ProgPainter3::GetEnd() const {
	TODO
}

void ProgPainter3::Link() {
	TODO
}

void ProgPainter3::Dump() {
	TODO
}

void ProgPainter3::Attach(DrawCommand& begin, DrawCommand& end) {
	TODO
}

void ProgPainter3::AppendPick(DrawCommand* begin, DrawCommand* end) {
	TODO
}

	
void ProgPainter3::Init(Volf sz) {
	TODO
}

void ProgPainter3::SetSize(Volf sz) {
	TODO
}

dword ProgPainter3::GetInfo() const {
	TODO
}

Volf ProgPainter3::GetPageSize() const {
	TODO
}

void ProgPainter3::StartPage() {
	TODO
}

void ProgPainter3::EndPage() {
	TODO
}

void ProgPainter3::BeginOp() {
	TODO
}

void ProgPainter3::EndOp() {
	TODO
}

void ProgPainter3::OffsetOp(Point3f p) {
	TODO
}

bool ProgPainter3::ClipOp(const Cubf& r) {
	TODO
}

bool ProgPainter3::ClipoffOp(const Cubf& r) {
	TODO
}

bool ProgPainter3::ExcludeClipOp(const Cubf& r) {
	TODO
}

bool ProgPainter3::IntersectClipOp(const Cubf& r) {
	TODO
}

bool ProgPainter3::IsPaintingOp(const Cubf& r) const {
	TODO
}

Cubf ProgPainter3::GetPaintCubf() const {
	TODO
}

void ProgPainter3::DrawBoxOp(float x, float y, float z, float cx, float cy, float cz, Color color) {
	TODO
}

void ProgPainter3::SysDrawImageOp(float x, float y, float z, const Image& img, Color color) {
	TODO
}

void ProgPainter3::SysDrawImageOp(float x, float y, float z, const Image& img, const Cubf& src, Color color) {
	TODO
}

void ProgPainter3::DrawImageOp(float x, float y, float z, float cx, float cy, float cz, const Image& img, const Cubf& src, Color color) {
	TODO
}

void ProgPainter3::DrawDataOp(float x, float y, float z, float cx, float cy, float cz, const String& data, const char *id) {
	TODO
}

void ProgPainter3::DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) {
	TODO
}

void ProgPainter3::DrawPolyPolylineOp(const Point3f *vertices, int vertex_count,
						const int *counts, int count_count,
						float width, Color color, Color doxor) {
	TODO
}

void ProgPainter3::DrawPolyPolyPolygonOp(const Point3f *vertices, int vertex_count,
							const int *subpolygon_counts, int scc,
							const int *disjunct_polygon_counts, int dpcc,
							Color color, float width, Color outline,
							uint64 pattern, Color doxor) {
	TODO
}

void ProgPainter3::DrawArcOp(const Cubf& rc, Point3f start, Point3f end, float width, Color color) {
	TODO
}

void ProgPainter3::DrawEllipseOp(const Cubf& r, Color color, float pen, Color pencolor) {
	TODO
}

void ProgPainter3::DrawTextOp(float x, float y, float z, int angle, const wchar *text, Font font,
				Color ink, int n, const int *dx) {
	TODO
}

void ProgPainter3::DrawDrawingOp(const Cubf& target, const Drawing& w) {
	TODO
}

void ProgPainter3::DrawPaintingOp(const Cubf& target, const Painting& w) {
	TODO
}

Volf ProgPainter3::GetNativeDpi() const {
	TODO
}

void ProgPainter3::BeginNative() {
	TODO
}

void ProgPainter3::EndNative() {
	TODO
}

int ProgPainter3::GetCloffLevel() const {
	TODO
}

void ProgPainter3::Escape(const String& data) {
	TODO
}


NAMESPACE_TOPSIDE_END
