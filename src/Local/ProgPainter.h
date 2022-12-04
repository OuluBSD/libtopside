#ifndef _Local_ProgPainter_h_
#define _Local_ProgPainter_h_


NAMESPACE_TOPSIDE_BEGIN


class TriangulatePointf {

public:

	static bool Process(const Vector<Pointf>& contour, Vector<float>& result);

	static double Area(const Vector<Pointf>& contour);

	static bool InsideTriangle(double Ax, double Ay,
		double Bx, double By,
		double Cx, double Cy,
		double Px, double Py);


private:
	static bool Snip(const Vector<Pointf>& contour, int u, int v, int w, int n, int* V);

};


Pointf GetPointOffsets(const Pointf& a, const Pointf& b, double width);


class ProgPainter : public Draw {
	DrawCommand *prev;
	DrawCommand *next;
	DrawCommand *begin;
	DrawCommand *end;
	DrawCommand *cur_begin = NULL;
	DrawCommand *cur = NULL;
	
	Vector<Point> tmp0;
	Vector<double> angles;
	Size sz;
	
	DrawCommand& CreateCommand();
	
	
public:
	ProgPainter(Size sz, DrawCommand& prev, DrawCommand& begin, DrawCommand& end, DrawCommand& next);
	ProgPainter(Size sz, ProgPainter& p, DrawCommand& begin, DrawCommand& end);
	~ProgPainter() {/*Clear();*/}
	
	void Clear();
	DrawCommand* GetBegin() const;
	DrawCommand* GetEnd() const;
	
	void CtrlDrawBegin(hash_t h) override;
	void CtrlDrawEnd() override;
	void SetSize(Size sz) override;
	Size GetPageSize() const override;
	void DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) override;
	void DrawRectOp(int x, int y, int cx, int cy, Color color) override;
	void DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
		                    Color ink, int n, const int *dx) override;
	void DrawPolyPolylineOp(const Point *vertices, int vertex_count,
	                                const int *counts, int count_count,
	                                int width, Color color, Color doxor) override;
	bool ClipOp(const Rect& r) override;
	void EndOp() override;
	
	
	void BindWindow(hash_t h);
	void UnbindWindow();
	void DrawLine(int x0, int y0, int x1, int y1, int line_width, RGBA c);
	#ifdef UPP_VERSION
	void DrawImageOp(int x, int y, int cx, int cy, const Image& img, const Rect& src, Color color) override {TODO};
	void DrawImage(int x, int y, Image img, byte alpha=255);
	#else
	void DrawImage(int x, int y, Image img, byte alpha=255) override;
	#endif
	void DrawRect(Rect r, RGBA clr);
	void DrawRect(int x, int y, int w, int h, RGBA clr);
	void DrawText(int x, int y, String txt, Font fnt, RGBA clr);
	void DrawPolyline(const Point* pts, int pt_count, int line_width, RGBA c);
	void DrawPolygon(const Vector<Point>& pts, RGBA c);
	
	void Offset(const Rect& r);
	void End();
	void WindowOffset(const Rect& r);
	void WindowEnd();
	
	
	void Link();
	void Dump();
	
	//void Attach(Ctrl& c);
	void Attach(DrawCommand& begin, DrawCommand& end);
	void AppendPick(DrawCommand* begin, DrawCommand* end);
	
};



NAMESPACE_TOPSIDE_END


#endif
