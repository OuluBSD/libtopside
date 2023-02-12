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
	
	void BindWindow(const DrawCommand& cmd);
	void UnbindWindow(const DrawCommand& cmd);
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
