#include "Editor.h"


NAMESPACE_TOPSIDE_BEGIN


RightTabs::RightTabs()
{
	cx = 3;
	cursor = -1;
	Transparent();
}

void RightTabs::Clear()
{
	tab.Clear();
	cx = 3;
	cursor = -1;
	Refresh();
}

void RightTabs::Repos()
{
	int y = 0;
	for(int i = 0; i < tab.GetCount(); i++) {
		tab[i].y = y;
		y += tab[i].GetHeight();
	}
	RefreshParentLayout();
}

void RightTabs::Add(const Image& img, String tip)
{
	Tab& t = tab.Add();
	t.img = img;
	t.tip = tip;
	cx = max(cx, img.GetSize().cx + 7);
	Repos();
}

void RightTabs::PaintTab(Draw& w, int x, int y, int cx, int cy, Color paper, const Image& img, Color hl)
{
	Color fc = FieldFrameColor();
	w.DrawRect(x, y + 1, cx - 1, cy - 2, paper);
	w.DrawRect(x, y, cx - 1, 1, fc);
	w.DrawRect(x + cx - 1, y + 1, 1, cy - 2, fc);
	w.DrawRect(x, y + cy - 1, cx - 1, 1, fc);
	Size isz = img.GetSize();
	int ix = (cx - isz.cx) / 2 + x;
	int iy = (cy - isz.cx) / 2 + y;
	if(!IsNull(hl)) {
		w.DrawImage(ix - 1, iy - 1, img, hl);
		w.DrawImage(ix - 1, iy + 1, img, hl);
		w.DrawImage(ix + 1, iy - 1, img, hl);
		w.DrawImage(ix + 1, iy + 1, img, hl);
	}
	w.DrawImage(ix, iy, img);
}

void RightTabs::Paint(Draw& w)
{
	Size sz = GetSize();
	w.DrawRect(sz, Blend(SColorFace, SColorPaper));
	Color hc = Blend(Yellow, LtRed, 100);
	Color inactive = Blend(SColorPaper, SColorShadow);
	for(int i = 0; i < tab.GetCount(); i++) {
		Tab& t = tab[i];
		if(i != cursor)
			PaintTab(w, 0, t.y + 2, cx - 1, t.GetHeight() - 1, inactive, t.img, i == hl ? hc : Null);
	}
	if(cursor >= 0) {
		Tab& t = tab[cursor];
		PaintTab(w, 0, t.y, cx, t.GetHeight() + 3, SColorPaper, t.img, cursor == hl ? hc : Null);
	}
}

int RightTabs::GetPos(Point p)
{
	for(int i = 0; i < tab.GetCount(); i++)
		if(p.y < tab[i].GetRight())
			return i;
	return -1;
}

void RightTabs::SetCursor(int i)
{
	ASSERT(cursor < tab.GetCount());
	cursor = i;
	Refresh();
}

void RightTabs::LeftDown(Point p, dword)
{
	int c = GetPos(p);
	if(c >= 0 && c != cursor) {
		cursor = c;
		UpdateActionRefresh();
		if(GetParent())
			GetParent()->RefreshFrame();
	}
}

void RightTabs::MouseMove(Point p, dword)
{
	int c = GetPos(p);
	if(c != hl) {
		hl = c;
		Refresh();
		Tip(c >= 0 ? tab[c].tip : "");
	}
}

void RightTabs::MouseLeave()
{
	CancelMode();
}

void RightTabs::CancelMode()
{
	hl = -1;
	Refresh();
	if(GetParent())
		GetParent()->RefreshFrame();
}

void RightTabs::FramePaint(Draw& w, const Rect& rr)
{
	Rect r = rr;
	r.right -= cx;
	DrawFrame(w, r, FieldFrameColor());
	DrawFrame(w, r.Deflated(1), SColorPaper);
	if(cursor >= 0) {
		Tab& t = tab[cursor];
		w.DrawRect(r.right - 1, t.y + 1, 1, t.GetHeight() + 1, SColorFace);
	}
}

void RightTabs::FrameLayout(Rect& r)
{
	LayoutFrameRight(r, this, cx);
	r.top += 2;
	r.right -= 2;
	r.left += 2;
	r.bottom -= 2;
}

void RightTabs::FrameAddSize(Size& sz)
{
	sz += 4;
	sz.cx += cx + 2;
}

















Size ElepDisplay::DoPaint(Draw& w, const Rect& r, const Value& q, Color ink, Color paper, dword style) const
{
	w.DrawRect(r, paper);
	WString txt = q;
	int st = 1;
	const wchar *s = txt;
	const wchar *b = s;
	int x = 0;
	int y = 0;
	int cx = 0;
	int linecy = StdFont().GetLineHeight();
	for(;;) {
		if((byte)*s < ' ') {
			int tcx = GetTextSize(b, StdFont(), int(s - b)).cx;
			if(st != 1 && (style & CURSOR) == 0)
				w.DrawRect(x + r.left, y + r.top, tcx, linecy,
				           st == 2 ? Red() : Yellow());
			w.DrawText(x + r.left, y + r.top, b, StdFont(), ink, int(s - b));
			x += tcx;
			cx = max(cx, tcx + x);
			if(*s == '\0')
				break;
			if(*s == '\n') {
				x = 0;
				y += linecy;
			}
			else
				st = *s;
			b = ++s;
		}
		else
			s++;
	}
	return Size(cx, y + linecy);
}

Size ElepDisplay::GetStdSize(const Value& q) const
{
	NilDraw w;
	return DoPaint(w, Rect(0, 0, INT_MAX, INT_MAX), q, Null, Null, 0);
}

void ElepDisplay::Paint(Draw& w, const Rect& r, const Value& q, Color ink, Color paper, dword style) const
{
	DoPaint(w, r, q, ink, paper, style);
}


NAMESPACE_TOPSIDE_END

