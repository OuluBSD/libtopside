#ifndef _GuboCore_Frame_h_
#define _GuboCore_Frame_h_

NAMESPACE_TOPSIDE_BEGIN


class Gubo;

class GuboFrame :
	RTTIBase
{
public:
	RTTI_DECL0(GuboFrame)
	
	virtual void FrameLayout(Rect& r) = 0;
	virtual void FrameAddSize(Size& sz) = 0;
	virtual void FramePaint(Draw& w, const Rect& r);
	virtual void FrameAdd(Gubo& parent);
	virtual void FrameRemove();
	virtual int  OverPaint() const;

	GuboFrame() {}
	virtual ~GuboFrame() {}

private:
	GuboFrame(const GuboFrame&);
	void operator=(const GuboFrame&);
};

struct NullFrameClass : public GuboFrame {
	virtual void FrameLayout(Rect& r);
	virtual void FramePaint(Draw& w, const Rect& r);
	virtual void FrameAddSize(Size& sz);
};

GuboFrame& NullFrame();

class MarginFrame : public GuboFrame {
public:
	virtual void FrameLayout(Rect& r);
	virtual void FramePaint(Draw& w, const Rect& r);
	virtual void FrameAddSize(Size& sz);
	virtual void FrameAdd(Gubo& parent);
	virtual void FrameRemove();

private:
	Gubo  *owner;
	Color  color;
	Rect   margins;

public:
	void SetMargins(const Rect& r);
	void SetColor(Color c);

	MarginFrame();
};

class BorderFrame : public GuboFrame {
public:
	virtual void FrameLayout(Rect& r);
	virtual void FramePaint(Draw& w, const Rect& r);
	virtual void FrameAddSize(Size& sz);

protected:
	const ColorF *border;

public:
	BorderFrame(const ColorF *border) : border(border) {}
};


GuboFrame& NullFrame();
GuboFrame& InsetFrame();

NAMESPACE_TOPSIDE_END

#endif
