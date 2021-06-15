#include "Editor.h"


NAMESPACE_TOPSIDE_BEGIN


Terminal::Terminal() {
	cursor = Point(0, 0);
	
	fb.SetCount(FB_LEN * FB_LEN);
	
	bg = White;
	fg = Black;
	
	fnt = Monospace(gridh);
	
	WriteText("Hello. This is terminal emulator...");
	
	tc.Set(-500, THISBACK(UpdateCaret));
}

void Terminal::WriteText(String s) {
	int gi = cursor.y * FB_LEN + cursor.x;
	ASSERT(gi >= 0 && gi < fb.GetCount());
	
	int i = 0;
	while (gi < FB_LEN*FB_LEN && i < s.GetCount()) {
		ScreenGlyph& g = fb[gi++];
		g.Reset();
		g.chr = s[i++];
	}
	cursor.x += s.GetCount();
	
	Refresh();
}

void Terminal::Paint(Draw& d) {
	Size sz(Ctrl::GetSize());
	
	d.DrawRect(sz, White());
	
	int cols = sz.cx / gridw;
	int rows = sz.cy / gridh;
	
	for(int i = 0; i < rows; i++) {
		int gx = i * FB_LEN;
		int x = 0;
		int y = i * gridh;
		
		for(int j = 0; j < cols; j++) {
			ScreenGlyph& g = fb[gx];
			
			bool is_cursor = i == cursor.y && j == cursor.x && caret_bit;
			
			Color bg = g.is_def_bg ? (!is_cursor ? this->bg : this->fg) : g.bg;
			Color fg = g.is_def_fg ? (!is_cursor ? this->fg : this->bg) : g.fg;
			
			d.DrawRect(x, y, gridw, gridh, bg);
			
			if (g.chr) {
				Font f = fnt;
				if (g.is_bold)		f.Bold();
				if (g.is_italic)	f.Italic();
				if (g.is_underline)	f.Underline();
				String s;
				s.Cat(g.chr);
				d.DrawText(x, y, s, f, fg);
			}
			
			x += gridw;
			gx++;
		}
		
		
	}
	
}

bool Terminal::Key(dword key, int count) {
	
	
	return false;
}


NAMESPACE_TOPSIDE_END
