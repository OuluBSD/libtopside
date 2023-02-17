#ifndef _IGraphics_ProgDraw_h_
#define _IGraphics_ProgDraw_h_



NAMESPACE_PARALLEL_BEGIN


class DrawProg : public DrawProxy {
	int bind_win_count = 0;
	bool skip_window_commands = false;
	
public:
	RTTI_DECL1_(DrawProg, DrawProxy)
	DrawProg();
	void Process(const DrawCommand* begin, const DrawCommand* end);
	void SkipWindowCommands(bool b=true);
	
	void SetSize(const DrawCommand& cmd);
	//void DrawImage(const DrawCommand& cmd);
	void CtrlDrawBegin(const DrawCommand& cmd);
	void CtrlDrawEnd(const DrawCommand& cmd);
	void GetInfo(const DrawCommand& cmd);
	//void GetPageSize(const DrawCommand& cmd);
	void StartPage(const DrawCommand& cmd);
	void EndPage(const DrawCommand& cmd);
	void BeginOp(const DrawCommand& cmd);
	void EndOp(const DrawCommand& cmd);
	void OffsetOp(const DrawCommand& cmd);
	void ClipOp(const DrawCommand& cmd);
	void ClipoffOp(const DrawCommand& cmd);
	void ExcludeClipOp(const DrawCommand& cmd);
	void IntersectClipOp(const DrawCommand& cmd);
	//void GetPaintRect(const DrawCommand& cmd);
	void RectOp(const DrawCommand& cmd);
	void SysdrawImageOp(const DrawCommand& cmd);
	void ImageOp(const DrawCommand& cmd);
	void DataOp(const DrawCommand& cmd);
	void LineOp(const DrawCommand& cmd);
	void PolyPolylineOp(const DrawCommand& cmd);
	void PolyPolyPolygonOp(const DrawCommand& cmd);
	void ArcOp(const DrawCommand& cmd);
	void EllipseOp(const DrawCommand& cmd);
	void TextOp(const DrawCommand& cmd);
	void DrawingOp(const DrawCommand& cmd);
	void PaintingOp(const DrawCommand& cmd);
	void BeginNative(const DrawCommand& cmd);
	void EndNative(const DrawCommand& cmd);
	void Escape(const DrawCommand& cmd);
	void BindWindow(const DrawCommand& cmd);
	void UnbindWindow(const DrawCommand& cmd);
	
	#if 0
	void DrawLine(const DrawCommand& cmd);
	void DrawImage(const DrawCommand& cmd);
	void DrawImageOp(const DrawCommand& cmd);
	void DrawImageBuffer(const DrawCommand& cmd);
	void DrawRect(const DrawCommand& cmd);
	void DrawTriangles(const DrawCommand& cmd);
	void DrawPolyline(const DrawCommand& cmd);
	void DrawPolygon(const DrawCommand& cmd);
	void Clipoff(const DrawCommand& cmd);
	void DrawOffset(const DrawCommand& cmd);
	void DrawOffsetPoint(const DrawCommand& cmd);
	void DrawEnd(const DrawCommand& cmd);
	void DrawWindowOffset(const DrawCommand& cmd);
	void DrawWindowEnd(const DrawCommand& cmd);
	void DrawText(const DrawCommand& cmd);
	#endif
	
};

class ProgImage {
	DrawProg draw;
	
public:
	ProgImage();
	void Paint(const DrawCommand* begin, const DrawCommand* end, ImageDraw& id);
	
	void SkipWindowCommands(bool b=true);
};

class DrawCommandImageRenderer {
	ProgImage pi;
	One<ImageDraw> id;
	Image img;
	Size sz;
	
	
public:
	typedef DrawCommandImageRenderer CLASSNAME;
	DrawCommandImageRenderer();
	
	void ProcessWindowCommands(DrawCommand* begin, DrawCommand* end);
	Image GetImage();
	
	static bool TrimBegin(DrawCommand*& begin);
	static void FindBegin(DrawCommand*& begin);
	static DrawCommand* FindEnd(DrawCommand* begin);
	static DrawCommand* MoveEnd(DrawCommand* end);
	
};



NAMESPACE_PARALLEL_END

#endif
