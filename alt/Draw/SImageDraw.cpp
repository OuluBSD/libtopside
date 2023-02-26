#include "Draw.h"

NAMESPACE_UPP

/*
Clipping places:
DrawLineOp
        DrawPixel
DrawRectOp
        DrawHLine
DrawPolyPolylineOp
        DrawLine
DrawTriangle
        DrawHLine
DrawPixel0
x DrawPixel
x DrawHLine
x DrawLine
        DrawPixel0
*/
void SImageDraw::Create(Size sz) {
	Create(sz, 4);
}

void SImageDraw::Create(Size sz, int stride) {
	this->stride = stride;
	this->sz = sz;
	int len = sz.cx * sz.cy * stride;
	pitch = sz.cx * stride;
	data.SetCount(len);
	pixels = data.Begin();
	
	cur_area = sz;
	//Zero();
}




END_UPP_NAMESPACE
