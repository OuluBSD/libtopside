#include "LocalCtrl.h"

#if IS_UPP_CORE

NAMESPACE_TOPSIDE_BEGIN

ToolBarBg::ToolBarBg() {
	WantFocus(false);
	
}
	
void ToolBarBg::Paint(Draw& w) {
	
	// Inverse vertically normal toolbar background image
	Size sz = GetSize();
	ImageDraw id(sz);
	#ifdef flagWIN32
	ChPaint(id, GetSize(), ToolBar().StyleDefault().look);
	#else
	if(IsNull(ToolBar().StyleDefault().arealook))
		ChPaint(id, GetSize(), ToolBar().StyleDefault().look);
	else
		PaintBarArea(id, this, ToolBar().StyleDefault().arealook, Null);
	#endif
	ImageBuffer ib(id);
	
	int h2 = sz.cy / 2;
	RGBA* begin = ib.Begin();
	for(int i = 0; i < h2; i++) {
		RGBA* l1 = begin + i * sz.cx;
		RGBA* l2 = begin + (sz.cy - 1 - i) * sz.cx;
		for(int j = 0; j < sz.cx; j++) {
			Swap(*l1, *l2);
			l1++;
			l2++;
		}
	}
	
	w.DrawImage(0, 0, ib);
}

	

PathCtrl::PathCtrl() {
	Add(bg.SizePos());
	Add(edit.VSizePos(3,3).LeftPos(3,30));
	Add(path.VSizePos(3,3).HSizePos(3+30+3,3));
	
	edit.Button::SetImage(Images::edit());
	edit <<= THISBACK(SwitchMode);
	
	path.WhenEnter = THISBACK(SetEditPath);
	
	dir_seps = DIR_SEPS;
	
	is_edit = 0;
	RefreshEdit();
	
}

void PathCtrl::SetEditPath() {
	String s = path.GetData();
	SetDirectory(s);
	SetEdit(false);
}

void PathCtrl::SetEdit(bool b) {
	is_edit = b;
	RefreshEdit();
}

void PathCtrl::SetPath(String path) {
	this->path.SetData(path);
	RefreshEdit();
}

void PathCtrl::RefreshEdit() {
	path.Hide();
	
	for(int i = 0; i < path_buttons.GetCount(); i++) {
		Ctrl::RemoveChild(&path_buttons[i]);
	}
	path_buttons.Clear();
	
	if (is_edit) {
		path.Show();
	}
	else {
		String p = path.GetData();
		Vector<String> items = Split(p, dir_seps);
		
		String cur_path;
		
		if (dir_seps == "/") {
			Button& item = path_buttons.Add();
			item.SetLabel(DIR_SEPS);
			Add(item);
			item <<= THISBACK1(SetDirectory, "/");
			cur_path.Cat('/');
		}
		
		for(int i = 0; i < items.GetCount(); i++) {
			Button& item = path_buttons.Add();
			item.SetLabel(items[i]);
			if (i) cur_path += dir_seps;
			cur_path += items[i];
			item <<= THISBACK1(SetDirectory, cur_path);
			Add(item);
		}
		
		int x = 3+30+3;
		int h = 30;
		int xpad = 5;
		for(int i = 0; i < path_buttons.GetCount(); i++) {
			Button& item = path_buttons[i];
			String s = item.GetLabel();
			Font fnt = item.GetFont();
			Size sz = GetTextSize(s, fnt);
			int w = sz.cx + xpad + xpad + 3;
			item.SetRect(x, 3, w, h - 3 - 3);
			x += w;
		}
	}
	
}

NAMESPACE_TOPSIDE_END

#endif
