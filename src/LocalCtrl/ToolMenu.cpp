#include "LocalCtrl.h"

#if IS_UPP_CORE

NAMESPACE_TOPSIDE_BEGIN

ToolBackground::ToolBackground() {
	horz = false;
	//a = Color(167, 203, 211);
	//b = Color(226, 238, 240);
	a = Color(193, 196, 193);
	b = Color(217, 220, 217);
	IgnoreMouse();
	WantFocus(false);
}

void ToolBackground::Paint(Draw& d) {
	Size sz(GetSize());
	
	d.DrawLine(0, 0, sz.cx-1, 0, 1, GrayColor(128+64));
	d.DrawLine(0, sz.cy-1, sz.cx-1, sz.cy-1, 1, GrayColor(128));
	
	if (horz) {
		int count = sz.cy - 1;
		for(int i = 1; i < count; i++) {
			Color c = Blend(a, b, 255 * i / count);
			d.DrawLine(0, i, sz.cx-1, i, 1, c);
		}
		d.DrawText(4, 3, label, StdFont(12), White());
		d.DrawText(5, 4, label, StdFont(12), Black());
	} else {
		int count = sz.cx / 2 + 1;
		for(int i = 0; i < count; i++) {
			Color c = Blend(a, b, 255 * i / count);
			d.DrawLine(i, 1, i, sz.cy-1, 1, c);
			int x2 = sz.cx-1-i;
			d.DrawLine(x2, 1, x2, sz.cy-1, 1, c);
		}
	}
}






ToolGrid::ToolGrid() {
	Add(label.TopPos(0, 20).HSizePos());
	label.Horz();
	cols = 1;
	height = 24;
	cursor = -1;
}

ButtonOption& ToolGrid::AddButton(const Image& img, String text) {
	int id = buttons.GetCount();
	ButtonOption& btn = buttons.Add();
	btn.Tip(text);
	btn.SetImage(img);
	btn <<= THISBACK1(Select, id);
	grid.Add(&btn);
	Add(btn);
	return btn;
}

void ToolGrid::Select(int id) {
	for(int i = 0; i < buttons.GetCount(); i++) {
		buttons[i].Set(i == id);
	}
	if (id >= 0 && id < buttons.GetCount()) {
		cursor = id;
		WhenSelect();
	}
}

void ToolGrid::Layout() {
	if (grid.GetCount()) {
		Size sz(GetSize());
		label.SetRect(0, 0, sz.cx, 20);
		int grid = sz.cx / cols;
		int col = 0, row = 0;
		for(int i = 0; i < this->grid.GetCount(); i++) {
			Ctrl& c = *this->grid[i];
			c.SetRect(col*grid+1, 20+row*grid+1, grid-2, grid-2);
			col++;
			if (col >= cols) {col = 0; row++;}
		}
	}
	else {
		ParentCtrl::Layout();
	}
}

int ToolGrid::GetHeight(int width) {
	int title_height = 20;
	if (grid.GetCount()) {
		int grid = width / cols;
		return (this->grid.GetCount() / cols + 1) * grid + title_height;
	} else {
		return height + title_height;
	}
}




ToolList::ToolList() {
	Add(bg);
	
}

ToolGrid& ToolList::AddGrid(String name) {
	ToolGrid& grid = grids.Add();
	grid.SetLabel(name);
	Add(grid);
	return grid;
}

void ToolList::Layout() {
	Size sz(GetSize());
	
	bg.SetRect(0, 0, sz.cx, sz.cy);
	
	int y = 0;
	for(int i = 0; i < grids.GetCount(); i++) {
		ToolGrid& g = grids[i];
		int height = g.GetHeight(sz.cx);
		g.SetRect(0, y, sz.cx, height);
		g.Layout();
		y += height + 30;
	}
}

NAMESPACE_TOPSIDE_END

#endif
