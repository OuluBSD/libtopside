#ifndef _Local_ProgDraw_h_
#define _Local_ProgDraw_h_


NAMESPACE_TOPSIDE_BEGIN


class ProgDraw : public DrawProxy
{
	One<ProgPainter> d;
	
	Size GetFrameSize() const;
	
public:
	DrawCommand cmd_screen_begin, cmd_screen_end;
	DrawCommand render_begin, render_end;
	
	
	void LinkRender();
public:
	#if IS_TS_CORE
	RTTI_DECL1(ProgDraw, Draw)
	#endif
	ProgDraw();
	ProgDraw(Size sz);
	ProgDraw(int w, int h);
	
	void Realize(Size sz);
	void Create(Size sz);
	void Create(Size sz, DrawCommand& sub_begin, DrawCommand& sub_end);
	void Clear();
	void Finish();
	void DetachTo(ProgPainter& pp);
	
	operator Image() const;
	
	ProgPainter& GetPainter();
	
	String Dump() const;
	
	
	
};


NAMESPACE_TOPSIDE_END

#endif
