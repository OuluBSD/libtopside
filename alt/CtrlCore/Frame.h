#ifndef _CtrlCore_Frame_h_
#define _CtrlCore_Frame_h_

NAMESPACE_UPP_BEGIN


class Ctrl;

class CtrlFrame :
	RTTIBase
{
public:
	RTTI_DECL0(CtrlFrame)
	
	virtual void FrameLayout(Rect& r) = 0;
	virtual void FrameAddSize(Size& sz) = 0;
	virtual void FramePaint(Draw& w, const Rect& r);
	virtual void FrameAdd(Ctrl& parent);
	virtual void FrameRemove();
	virtual int  OverPaint() const;

	CtrlFrame() {}
	virtual ~CtrlFrame() {}

private:
	CtrlFrame(const CtrlFrame&);
	void operator=(const CtrlFrame&);
};

struct NullFrameClass : public CtrlFrame {
	virtual void FrameLayout(Rect& r);
	virtual void FramePaint(Draw& w, const Rect& r);
	virtual void FrameAddSize(Size& sz);
};

CtrlFrame& NullFrame();

class MarginFrame : public CtrlFrame {
public:
	virtual void FrameLayout(Rect& r);
	virtual void FramePaint(Draw& w, const Rect& r);
	virtual void FrameAddSize(Size& sz);
	virtual void FrameAdd(Ctrl& parent);
	virtual void FrameRemove();

private:
	Ctrl  *owner;
	Color  color;
	Rect   margins;

public:
	void SetMargins(const Rect& r);
	void SetColor(Color c);

	MarginFrame();
};

class BorderFrame : public CtrlFrame {
public:
	virtual void FrameLayout(Rect& r);
	virtual void FramePaint(Draw& w, const Rect& r);
	virtual void FrameAddSize(Size& sz);

protected:
	const ColorF *border;

public:
	BorderFrame(const ColorF *border) : border(border) {}
};


CtrlFrame& NullFrame();
CtrlFrame& InsetFrame();


NAMESPACE_UPP_END

#endif
