#include "Core.h"

NAMESPACE_UPP_BEGIN




int iscale(int x, int y, int z)
{
#if CPU_32 && COMPILER_MSC
	__asm {
		mov		eax, [x]
		imul	[y]
		idiv	[z]
	}
#else
	int64 res = x;
	res *= y;
	res /= z;
	return (int)res;
#endif
}

Size iscale(Size a, int b, int c)
{
	return Size(iscale(a.cx, b, c), iscale(a.cy, b, c));
}

Size GetFitSize(Size sz, int cx, int cy)
{
	if(cx <= 0 || cy <= 0 || sz.cx <= 0 || sz.cy <= 0)
		return Size(0, 0);
	if(cx * sz.cy >= cy * sz.cx) // too high
		return iscale(sz, cy, sz.cy);
	else
		return iscale(sz, cx, sz.cx);
}



NAMESPACE_UPP_END
