#ifndef _GuboCore_Frame_h_
#define _GuboCore_Frame_h_

NAMESPACE_TOPSIDE_BEGIN


class Gubo;

class GuboFrame :
	public GeomInteraction3D
{
protected:
	friend class Gubo;
	Gubo* gubo = 0;
	
public:
	RTTI_DECL1(GuboFrame, GeomInteraction3D)
	
	virtual void FrameLayout(Cubf& r) = 0;
	virtual void FrameAddSize(Volf& sz) = 0;
	virtual void FramePaint(Draw3& w, const Cubf& r);
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
	virtual void FrameLayout(Cubf& r);
	virtual void FramePaint(Draw3& w, const Cubf& r);
	virtual void FrameAddSize(Volf& sz);
};

GuboFrame& NullFrame();

class MarginFrame : public GuboFrame {
public:
	virtual void FrameLayout(Cubf& r);
	virtual void FramePaint(Draw3& w, const Cubf& r);
	virtual void FrameAddSize(Volf& sz);
	virtual void FrameAdd(Gubo& parent);
	virtual void FrameRemove();

private:
	Gubo  *owner;
	Color  color;
	Cubf   margins;

public:
	void SetMargins(const Cubf& r);
	void SetColor(Color c);

	MarginFrame();
};

class BorderFrame : public GuboFrame {
public:
	virtual void FrameLayout(Cubf& r);
	virtual void FramePaint(Draw3& w, const Cubf& r);
	virtual void FrameAddSize(Volf& sz);

protected:
	const ColorF *border;

public:
	BorderFrame(const ColorF *border) : border(border) {}
};


/*GuboFrame& NullFrame();
GuboFrame& InsetFrame();*/

NAMESPACE_TOPSIDE_END

#endif
