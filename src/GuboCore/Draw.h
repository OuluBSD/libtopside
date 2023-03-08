#ifndef _GuboCore_Draw_h_
#define _GuboCore_Draw_h_

NAMESPACE_TOPSIDE_BEGIN


class ProgDraw3 : public Draw3 {
	
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


NAMESPACE_TOPSIDE_END

#endif
