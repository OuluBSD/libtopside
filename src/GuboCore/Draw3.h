#ifndef _GuboCore_Draw_h_
#define _GuboCore_Draw_h_

NAMESPACE_TOPSIDE_BEGIN


class ProgPainter3;


class ProgDraw3 : public DrawProxy3 {
	One<ProgPainter3> d;
	
	Volf GetFrameSize() const;
	
public:
	DrawCommand3 cmd_screen_begin, cmd_screen_end;
	DrawCommand3 render_begin, render_end;
	
	
	void LinkRender();
public:
	RTTI_DECL1(ProgDraw3, DrawProxy3)
	ProgDraw3();
	ProgDraw3(void* hash, Volf sz);
	ProgDraw3(void* hash, float w, float h, float d);
	
	void Realize(void* hash, Volf sz);
	void Create(void* hash, Volf sz);
	void Create(void* hash, Volf sz, DrawCommand3& sub_begin, DrawCommand3& sub_end);
	void Clear();
	void Finish();
	void DetachTo(ProgPainter3& pp);
	
	operator Image() const;
	
	ProgPainter3& GetPainter();
	
	String Dump() const;
};


NAMESPACE_TOPSIDE_END

#endif
