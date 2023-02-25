#include "Draw.h"

NAMESPACE_UPP_BEGIN


Image Rescale(const Image& src, Size sz, const Rect& src_rc, Gate<int, int> progress)
{
	if(src.GetSize() == sz && src_rc == sz)
		return src;
	TODO
	/*ImageRaster isrc(src);
	ImageEncoder tgt;
	Rescale(tgt, sz, isrc, src_rc);
	return tgt;*/
}

Image Rescale(const Image& src, Size sz, Gate<int, int> progress)
{
	return Rescale(src, sz, src.GetSize(), progress);
}


NAMESPACE_UPP_END
