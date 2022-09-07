#ifndef _Editor_Bottom_h_
#define _Editor_Bottom_h_


NAMESPACE_TOPSIDE_BEGIN


struct TheCalc : public CodeEditor {
	virtual bool Key(dword key, int count);
	virtual void LeftDouble(Point p, dword flags);

	ArrayMap<String, EscValue> vars;

	void    Execute();

	TheCalc();
};




class RightTabs : public FrameCtrl<Ctrl> {
public:
	virtual void Paint(Draw& w);
	virtual void LeftDown(Point p, dword);
	virtual void MouseMove(Point p, dword);
	virtual void MouseLeave();
	virtual void CancelMode();
	virtual void FramePaint(Draw& w, const Rect& r);
	virtual void FrameLayout(Rect& r);
	virtual void FrameAddSize(Size& sz);

private:
	enum       { SPACE = 7 };

	struct Tab {
		int    y;
		Image  img;
		String tip;

		int    GetHeight() const { return img.GetSize().cy + SPACE; }
		int    GetRight() const  { return y + GetHeight(); }
	};

	Array<Tab> tab;
	int        cx;
	int        hl;
	int        cursor;

	void Repos();
	void PaintTab(Draw& w, int x, int y, int cx, int cy, Color paper, const Image& img, Color hl);
	int  GetPos(Point p);

public:
	void Clear();
	void Add(const Image& img, String tip);
	void SetCursor(int i);
	int  GetCursor() const                                       { return cursor; }

	RightTabs();
};

struct ElepDisplay : public Display {
	Size    DoPaint(Draw& w, const Rect& r, const Value& q, Color ink, Color paper, dword style) const;

	virtual Size GetStdSize(const Value& q) const;
	virtual void Paint(Draw& w, const Rect& r, const Value& q, Color ink, Color paper, dword style) const;
};


NAMESPACE_TOPSIDE_END


#endif
