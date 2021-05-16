#include "Draw.h"


NAMESPACE_UPP_BEGIN

Image DefaultImages::Arrow;



void Image::MakeSysAccel() {
	TODO
}

const byte* Image::GetIter(int x, int y) const {
	if (!data) return 0;
	const byte* d = data->img.GetData();
	int pitch = data->img.GetPitch();
	int stride = data->img.GetStride();
	return d + y * pitch + x * stride;
}






NAMESPACE_UPP_END

