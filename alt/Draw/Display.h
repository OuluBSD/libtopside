#ifndef _Draw_Display_h_
#define _Draw_Display_h_

NAMESPACE_UPP_BEGIN

class Display {
public:
	enum {
		CURSOR   = 0x01,
		FOCUS    = 0x02,
		SELECT   = 0x04,
		READONLY = 0x08,
	};

	virtual void PaintBackground(Draw& w, const Rect& r, const Value& q,
	                             Color ink, Color paper, dword style) const;
	virtual void Paint(Draw& w, const Rect& r, const Value& q,
		               Color ink, Color paper, dword style) const;
	virtual Size GetStdSize(const Value& q) const;
	virtual Size RatioSize(const Value& q, int cx, int cy) const;

	virtual ~Display();
};

class PaintRect : Moveable<PaintRect> {
protected:
	Value          value;
	const Display *display;

public:
	void     Paint(Draw& w, const Rect& r,
	               Color ink = SColorText, Color paper = SColorPaper, dword style = 0) const;
	void     Paint(Draw& w, int x, int y, int cx, int cy,
		           Color ink = SColorText, Color paper = SColorPaper, dword style = 0) const;
	Size     GetStdSize() const;
	Size     RatioSize(int cx, int cy) const;
	Size     RatioSize(Size sz) const              { return RatioSize(sz.cx, sz.cy); }

	void     SetDisplay(const Display& d)          { display = &d; }
	void     SetValue(const Value& v)              { value = v; }
	void     Set(const Display& d, const Value& v) { display = &d; value = v; }
	void     Clear()                               { display = NULL; }

	const Value&   GetValue() const                { return value; }
	const Display& GetDisplay() const              { return *display; }

	operator bool() const                          { return display; }

	PaintRect();
	PaintRect(const Display& display);
	PaintRect(const Display& display, const Value& val);
};


NAMESPACE_UPP_END

#endif
