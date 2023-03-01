#include "Draw.h"

NAMESPACE_UPP_BEGIN


typedef Value (*ChPainterFn)(Draw& w, const Rect& r, const Value& v, int op, Color ink);

Vector<ChPainterFn>& sChps()
{
	static Vector<ChPainterFn> x;
	return x;
}

Value sChOp(Draw& w, const Rect& r, const Value& v, int op, Color ink)
{
	if(r.right < r.left || r.bottom < r.top)
		return Rect(0, 0, 0, 0);
	Value q;
	if(!IsNull(v))
		for(int i = sChps().GetCount() - 1; i >= 0; i--) {
			q = (*sChps()[i])(w, r, v, op, ink);
			if(!IsNull(q))
				break;
		}
	return q;
}


Rect ChMargins(const Value& look)
{
	NilDraw w;
	return sChOp(w, Null, look, LOOK_MARGINS);
}

void ChPaintEdge(Draw& w, const Rect& r, const Value& look, Color ink)
{
	sChOp(w, r, look, LOOK_PAINTEDGE, ink);
}

void ChPaint(Draw& w, int x, int y, int cx, int cy, const Value& look, Color ink)
{
	sChOp(w, RectC(x, y, cx, cy), look, LOOK_PAINT, ink);
}

void ChRegisterStyle__(byte& state, byte& registered, void (*init)()) {
	LOG("ChRegisterStyle__: skipping");
}

NAMESPACE_UPP_END
