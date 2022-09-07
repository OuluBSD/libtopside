#ifndef _Editor_Terminal_h_
#define _Editor_Terminal_h_


NAMESPACE_TOPSIDE_BEGIN


struct ScreenGlyph : Moveable<ScreenGlyph> {
	bool is_def_bg = true, is_def_fg = true;
	Color bg, fg;
	int chr = 0;
	bool is_bold = false, is_italic = false, is_underline = false;
	
	void Reset() {
		is_def_fg = true;
		is_def_bg = true;
		chr = 0;
		is_bold = false;
		is_italic = false;
		is_underline = false;
	}
};

class Terminal : public Ctrl {
	static const int FB_LEN = 1000;
	
	int gridw = 8, gridh = 14;
	int cols = 0, rows = 0;
	Vector<ScreenGlyph> fb;
	Color bg, fg;
	Font fnt;
	Point cursor;
	
	bool caret_bit = false;
	TimeCallback tc;
	
public:
	typedef Terminal CLASSNAME;
	Terminal();
	
	void UpdateCaret() {caret_bit = !caret_bit; Refresh();}
	void SetCursor(Point p) {cursor = p; Refresh();}
	void WriteText(String s);
	
	virtual bool Key(dword key, int count);
	virtual void Paint(Draw& d);
};


NAMESPACE_TOPSIDE_END

#endif
