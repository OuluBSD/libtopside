#include "CtrlLib.h"

NAMESPACE_UPP_BEGIN


void CtrlsImageLook(Value *look, int i, int n)
{
	TODO
	/*while(n--)
		*look++ = CtrlsImg::Get(i++);*/
}
void CtrlsImageLook(Value *look, int i, const Image& image, int n)
{
	TODO
	/*for(int q = 0; q < n; q++)
		*look++ = ChLookWith(CtrlsImg::Get(i++), image);*/
}

void CtrlsImageLook(Value *look, const Image& img) {
	LOG("CtrlsImageLook: skipping");
}


NAMESPACE_UPP_END
