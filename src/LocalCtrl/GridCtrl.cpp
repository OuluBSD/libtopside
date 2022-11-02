#include "LocalCtrl.h"

NAMESPACE_TOPSIDE_BEGIN


GridCtrl::GridCtrl() {
	
}

void GridCtrl::SetGridSize(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
}

void GridCtrl::Layout() {
	ASSERT(cols > 0 && rows > 0);
	Size sz = GetSize();
	int c = GetChildCount();
	int col_w = sz.cx / cols;
	int row_h = sz.cy / rows;
	for(int i = 0; i < c; i++) {
		Ctrl* ctrl = GetIndexChild(i);
		int xi = i % cols;
		int yi = i / cols;
		int x = xi * col_w;
		int y = yi * row_h;
		Rect r = RectC(x, y, col_w, row_h);
		ctrl->SetRect(r);
	}
}


NAMESPACE_TOPSIDE_END
